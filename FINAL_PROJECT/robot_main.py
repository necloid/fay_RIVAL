import queue
import time
from threading import Thread
from pyfirmata import Arduino, util, OUTPUT, PWM, SERVO
from pyzbar.pyzbar import decode
from ultralytics import YOLO
import torch
import cv2

#pendefinisian pin

motor1pin2 = 4
motor2pin1 = 7
motor2pin2 = 8
motor3pin1 = 12
motor3pin2 = 2
speedPin1 = 3
speedPin2 = 5
speedPin3 = 6

armServoPin = 9
gripperServoPin = 10

triggerPin = 13
echoPin = 11

armDownPosition = 0    
armUpPosition = 90  
gripperOpenPosition = 20
gripperClosePosition = 100

searching_mode = True
object_picked = False
detected_color = None

board = Arduino('/dev/ttyACM0')  #kalo error ganti
time.sleep(2)

it = util.Iterator(board)
it.start()

#ssetup pin 

board.digital[armServoPin].mode = SERVO
board.digital[gripperServoPin].mode = SERVO
board.digital[motor1pin2].mode = OUTPUT
board.digital[motor2pin1].mode = OUTPUT
board.digital[motor2pin2].mode = OUTPUT
board.digital[motor3pin1].mode = OUTPUT
board.digital[motor3pin2].mode = OUTPUT
board.digital[speedPin1].mode = PWM
board.digital[speedPin2].mode = PWM
board.digital[speedPin3].mode = PWM

#setup kamera dan model yolo
device = "cuda" if torch.cuda.is_available() else "cpu"
model = YOLO("bestnew.pt").to(device)

camera_url = "http://192.168.195.24:8080/video" 
cap = cv2.VideoCapture(camera_url)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)
frame_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
frame_center_x = frame_width // 2
tolerance = 0.2 * frame_width  #toleransi 20% off-center dari frame

#fungsi pengukuran jarak dengan sensor ultrasonik
def measure_distance():
    try:
        board.digital[triggerPin].write(1)
        time.sleep(0.00001)
        board.digital[triggerPin].write(0)

        while board.digital[echoPin].read() == 0:
            pass
        start_time = time.time()
        
        while board.digital[echoPin].read() == 1:
            if time.time() - start_time > 0.1:  
                raise TimeoutError("Ultrasonic sensor timeout")
            pass
            
        travel_time = time.time() - start_time
        distance = travel_time * 17150  
        return distance
    except Exception as e:
        print(f"Error measuring distance: {str(e)}")
        return float('inf')


#fungsi pergerakan robot 

def moveForward(speed, duration):
    board.digital[speedPin1].write(speed / 255.0)
    board.digital[speedPin2].write(speed / 255.0)
    board.digital[speedPin3].write(speed / 255.0)

    board.digital[motor1pin2].write(1)
    board.digital[motor2pin1].write(0)
    board.digital[motor2pin2].write(1)
    board.digital[motor3pin1].write(0)
    board.digital[motor3pin2].write(1)

    time.sleep(duration)

    stopMotors()

def rotateClockwise(speed, duration):
    board.digital[speedPin1].write(speed / 255.0)
    board.digital[speedPin2].write(speed / 255.0)
    board.digital[speedPin3].write(speed / 255.0)

    board.digital[motor1pin2].write(1)
    board.digital[motor2pin1].write(0)
    board.digital[motor2pin2].write(1)
    board.digital[motor3pin1].write(0)
    board.digital[motor3pin2].write(1)

    time.sleep(duration)

    stopMotors()

def stopMotors():
    board.digital[motor1pin2].write(0)
    board.digital[motor2pin1].write(0)
    board.digital[motor2pin2].write(0)
    board.digital[motor3pin1].write(0)
    board.digital[motor3pin2].write(0)

def closeGripper():
    board.digital[gripperServoPin].write(gripperClosePosition)
    print("Gripper closed.")

def rotateArm():
    board.digital[armServoPin].write(armUpPosition)
    print("Arm rotated.")

def resetArm():
    board.digital[armServoPin].write(armDownPosition)
    print("Arm and gripper reset.")

def resetGripper():
    board.digital[gripperServoPin].write(gripperOpenPosition)
    print("Gripper open.")

def is_correct_destination(qr_code, color):
    """Check if QR code matches object color"""
    if qr_code is None or color is None:
        return False
    return ((qr_code == "PENJARA BIRU" and color == 0) or
            (qr_code == "PENJARA PUTIH" and color == 1))

# inisialisasi posisi
def setup():

    board.digital[armServoPin].write(armDownPosition)
    board.digital[gripperServoPin].write(gripperOpenPosition)
    print("Robot arm initialized.")

# fungsi utama
def main():
    global searching_mode, object_picked, detected_color

    frame_skip = 5
    frame_count = 0

    input_queue = queue.Queue(maxsize=1)
    output_queue = queue.Queue(maxsize=1)

    class FrameProcessor(Thread):
        def __init__(self, input_queue, output_queue):
            super().__init__()
            self.input_queue = input_queue
            self.output_queue = output_queue
            self.daemon = True

        def run(self):
            while True:
                frame = self.input_queue.get()
                if searching_mode:
                    results = model(frame, conf=0.5)
                    self.output_queue.put(('detection', results))
                else:
                    # QR code scanning when carrying object
                    qr_codes = decode(frame)
                    self.output_queue.put(('qr', qr_codes))

    processor = FrameProcessor(input_queue, output_queue)
    processor.start()

    try:
        while True:
            ret, frame = cap.read()
            if not ret:
                print("Failed to grab frame")
                break

            if frame_count % frame_skip == 0:
                if not input_queue.full():
                    input_queue.put(frame)

                if not output_queue.empty():
                    mode, results = output_queue.get()
                    
                    if searching_mode and mode == 'detection':
                        if results and len(results[0].boxes) > 0:
                            box = results[0].boxes[0]
                            color_class = int(box.cls[0].cpu().numpy())
                            x1, y1, x2, y2 = box.xyxy[0].cpu().numpy()
                            object_center_x = (x1 + x2) / 2

                            frame_center_x = frame.shape[1] / 2
                            tolerance = 30 

                            if (frame_center_x - tolerance) <= object_center_x <= (frame_center_x + tolerance):
                                distance = measure_distance()
                                if distance <= 6:
                                    print("Object centered and in range - picking up")
                                    stopMotors()
                                    closeGripper()
                                    rotateArm()
                                    searching_mode = False
                                    object_picked = True
                                    detected_color = color_class
                                    print("Switching to QR code detection mode")
                                else:
                                    print("Object centered, moving forward")
                                    moveForward(150, 0.5)
                            else:
                                print("Object not centered, rotating")
                                rotateClockwise(150, 0.1)

                    elif not searching_mode and mode == 'qr':
                        if results:
                            qr_code = results[0].data.decode('utf-8')
                            if is_correct_destination(qr_code, detected_color):
                                print("Found correct destination - delivering object")
                                moveForward(150, 1)
                                
                                while measure_distance() > 6:
                                    time.sleep(0.1)
                                
                                resetArm()
                                resetGripper()
        
                                searching_mode = True
                                object_picked = False
                                detected_color = None
                                print("Object placed, switching back to searching mode")
                                time.sleep(1)
                            else:
                                rotateClockwise(150, 1)

            frame_count += 1

            cv2.imshow("Robot Vision", frame)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

    except KeyboardInterrupt:
        print("Program terminated.")
    finally:
        stopMotors()
        cap.release()
        cv2.destroyAllWindows()
        board.exit()

if __name__ == "__main__":
    setup()
    main()