#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#pragma once


using namespace std;
using namespace cv;

class Bola{

public:
    Point posisi;
    int dx, dy;
    Scalar warna;
    int radius;

    Bola(Point posAwal, int kecepatanX, int kecepatanY, Scalar warnaBola, int radiusBola)
        : posisi(posAwal), dx(kecepatanX), dy(kecepatanY), warna(warnaBola), radius(radiusBola){}

    void move(int frameWidth, int frameHeight){

        posisi.x += dx;
        posisi.y += dy;

        if(posisi.y >= frameHeight || posisi.y <= 0) dy *= -1;
        if(posisi.x >= frameWidth || posisi.x <= 0) dx *= -1;

    }

    void draw(Mat &frame)const{

        circle(frame, posisi, radius, warna, -1);

    }

    void ubahWarna(){

        warna = Scalar(rand() % 256, rand() % 256, rand() % 256);

    }
};