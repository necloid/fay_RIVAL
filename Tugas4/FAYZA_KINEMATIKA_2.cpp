#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

#define M_PI 3.14159265358979323846
using namespace std;

// perkalian matrix
void ngaliMatriks(const double matriks1[4][4], const double matriks2[4][4], double hasil[4][4]){

    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            hasil[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                hasil[i][j] += matriks1[i][k] * matriks2[k][j];
            }
        }
    }

}

// transformasi jadi matrix Denavit apalah (D-H)
void intoMatriksDH(double alpha, double a, double d, double theta, double matriksDH[4][4]){

    matriksDH[0][0] = cos(theta);
    matriksDH[0][1] = -sin(theta) * cos(alpha);
    matriksDH[0][2] = sin(theta) * sin(alpha);
    matriksDH[0][3] = a * cos(theta);

    matriksDH[1][0] = sin(theta);
    matriksDH[1][1] = cos(theta) * cos(alpha);
    matriksDH[1][2] = -cos(theta) * sin(alpha);
    matriksDH[1][3] = a * sin(theta);

    matriksDH[2][0] = 0;
    matriksDH[2][1] = sin(alpha);
    matriksDH[2][2] = cos(alpha);
    matriksDH[2][3] = d;

    matriksDH[3][0] = 0;
    matriksDH[3][1] = 0;
    matriksDH[3][2] = 0;
    matriksDH[3][3] = 1;

}

// ngitung koordinat kartesian dari end-effector arm robot
void PosisiEndEffector(double d1, double sudut1_deg, double sudut2_deg, double sudut3_deg, double a2, double a3, double posisi[3]) {

    double sudut1 = sudut1_deg * M_PI / 180.0; // ubah ke rad
    double sudut2 = sudut2_deg * M_PI / 180.0;
    double sudut3 = sudut3_deg * M_PI / 180.0;

    double T01[4][4], T12[4][4], T23[4][4], T02[4][4], T03[4][4]; 

    intoMatriksDH(M_PI / 2, 0, d1, sudut1, T01);
    intoMatriksDH(0, a2, 0, sudut2, T12);
    intoMatriksDH(0, a3, 0, sudut3, T23);

    // T01 x T12 = T02
    ngaliMatriks(T01, T12, T02);

    // T02 x T23 = T03
    ngaliMatriks(T02, T23, T03);

    // posisi end-effector
    posisi[0] = T03[0][3];
    posisi[1] = T03[1][3];
    posisi[2] = T03[2][3];
}

int main(){

    char RobotSiapa;
    double d1, a2 = 0.03, a3 = 0.02;
    double sudut1, sudut2, sudut3;

    cin >> RobotSiapa;
    cin >> sudut1 >> sudut2 >> sudut3;

    switch(RobotSiapa){
        case 'L': d1 = 0.05; break;
        case 'W': d1 = 0.06; break;
    }

    double posisi[3];
    PosisiEndEffector(d1, sudut1, sudut2, sudut3, a2, a3, posisi);

    // biar ga jadi angka aneh
    double batas = 1e-9;
    for(int i = 0; i < 3; i++){
        if(abs(posisi[i]) < batas){
            posisi[i] = 0;
        }
    }
    
    cout << setprecision(2) << fixed; // mas ini ngebuletinnya ke atas jadi 3.535 dibuletin jadi 3.54 gapapa ya mas hehe
    cout << posisi[0] * 100 << endl;
    cout << posisi[1] * 100 << endl;
    cout << posisi[2] * 100 << endl;

    return 0;
}
