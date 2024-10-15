#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#pragma once

using namespace std;
using namespace cv;

class Program{
private:
    Bola bola;
    int score;
    bool statusTabrak = false;
    int cooldown;
    VideoCapture kamera;

public:
    Program(): bola(Point(100, 100), 10, 10, Scalar(255, 0, 0), 20), score(0), statusTabrak(false), cooldown(0){

        kamera.open(0);
        if (!kamera.isOpened()) {
            cerr << "Tidak dapat membuka kamera." << endl;
        }

    }

    void execute(){

        Mat frame;
        while (true){
            kamera >> frame;
            if(frame.empty()) break;

            realtimeVideo(frame);
            afterNabrak();
            videoAssembly(frame);

            imshow("Permen Mulyadi", frame);
            if (waitKey(30) == 32){
                break;
            }
        }

    }

    void realtimeVideo(Mat &frame){

        Mat hsv, lim_color;
        flip(frame, frame, 1);
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        Scalar biruGelap(100, 100, 100);
        Scalar biruTerang(130, 255, 255);
        inRange(hsv, biruGelap, biruTerang, lim_color);

        vector<vector<Point>> contours;
        findContours(lim_color, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        for(size_t i = 0; i < contours.size(); i++){

            Point2f center;
            float radius;

            minEnclosingCircle(contours[i], center, radius);
            circle(frame, center, radius, Scalar(0, 255, 0), 2);

            if(pow(center.x - bola.posisi.x, 2) + pow(center.y - bola.posisi.y, 2) <= pow(radius + bola.radius, 2)){
                if(!statusTabrak){
                    score++;
                    bola.dx *= -1;
                    bola.dy *= -1;
                    statusTabrak = true;
                    cooldown = 20;
                    bola.ubahWarna();
                }
            }

        }
    }

    void afterNabrak(){

        if(cooldown > 0){
            cooldown--;
            if (cooldown == 0) {
                statusTabrak = false;
            }
        }

    }

    void videoAssembly(Mat &frame){
        
        bola.move(frame.cols, frame.rows);
        bola.draw(frame);

        putText(frame, "SCORE: " + to_string(score),
                Point(10, 40), FONT_HERSHEY_DUPLEX, 1.0, Scalar(0, 0, 0), 7);
        putText(frame, "SCORE: " + to_string(score),
                Point(10, 40), FONT_HERSHEY_DUPLEX, 1.0, Scalar(255, 255, 255), 2);

    }
};