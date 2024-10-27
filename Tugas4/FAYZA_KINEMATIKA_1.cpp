#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

#define M_PI 3.14159265358979323846 
using namespace std;

struct KonfigurasiRobot{
    double radius_roda;
    double radius_robot;
    double sudut_roda[3];
};

KonfigurasiRobot PemilihanRobot(const string& name){

    KonfigurasiRobot config;
    config.radius_robot = 0.15;

    if(name == "LILDAN"){
        config.radius_roda = 0.0635;
        config.sudut_roda[0] = 3 * M_PI / 4;
        config.sudut_roda[1] = -M_PI / 2;
        config.sudut_roda[2] = -3 * M_PI / 4;
    }else{
        config.radius_roda = 0.024;
        config.sudut_roda[0] = -2 * M_PI / 3;
        config.sudut_roda[1] = 2 * M_PI / 3;
        config.sudut_roda[2] = 0;
    }
    return config;

}

void KecepatanRoda(double vx, double vy, double theta, const KonfigurasiRobot& config, double& m0, double& m1, double& m2){
    m0 = (sin(config.sudut_roda[0]) * vx + cos(config.sudut_roda[0]) * vy + config.radius_robot * theta) / config.radius_roda;
    m1 = (sin(config.sudut_roda[1]) * vx + cos(config.sudut_roda[1]) * vy + config.radius_robot * theta) / config.radius_roda;
    m2 = (sin(config.sudut_roda[2]) * vx + cos(config.sudut_roda[2]) * vy + config.radius_robot * theta) / config.radius_roda;
}

void GetRobotInput(string& robotWho, int input[3][3], int& num_input){
    cin >> robotWho;
    num_input = (robotWho == "LILDAN" ? 3 : 2);
    for(int i = 0; i < num_input; i++){
        cin >> input[i][0] >> input[i][1] >> input[i][2];
    }
}

bool GasAtauGa(const string& command){
    if(command != "GAS"){
        cout << "robot gamau jalan >:(\n";
        return false;
    }
    return true;
}

void PrintOutput(int num_input, const int input[3][3], const KonfigurasiRobot& config){
    double m0, m1, m2;
    for(int i = 0; i < num_input; i++){
        KecepatanRoda(input[i][0], input[i][1], input[i][2], config, m0, m1, m2);

        cout << fixed << setprecision(2);
        cout << m0 << "\n" << m1 << "\n" << m2 << "\n";
    }
}

int main(){
    string robotWho;
    int input[3][3], num_input;
    string command;

    GetRobotInput(robotWho, input, num_input);
    cin >> command;

    if(!GasAtauGa(command)){
        return 1;
    }

    cout << (input[0][1] >= 0 ? "∇" : "Δ") << "\n";

    KonfigurasiRobot config = PemilihanRobot(robotWho);
    PrintOutput(num_input, input, config);

    return 0;
}
