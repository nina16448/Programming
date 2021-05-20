#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#define pi 3.14159
using namespace cv;
using namespace std;


int main(){
    double a, b, c;

    cin >> a >> b >> c;

    Mat img(500, 500, CV_8UC3, Scalar(255,255,255));
    Mat img2;

    img.copyTo(img2);
    for(double t = 0; t <=  20 * pi; t += 0.01)
        circle(img2, Point(250 + a * sin(t), 250 + b * cos(c * t)), 1, Scalar(0, 0, 0), -1);

    imshow("windows", img2);
    waitKey(0);

    int num = 1;

    while(1){
        img.copyTo(img2);
        int rec = waitKey();

        if(rec == 61){
            num++;
            for(double t = 0; t <= 20 * pi; t += 0.0001)
                circle(img2, Point(250 + a * sin(t) * num, 250 + b * cos(c * t) * num), 1, Scalar(0, 0, 0), -1);
        }

        if(rec == 45){
            num--;
            for(double t = 0; t <= 20 * pi; t += 0.0001)
                circle(img2, Point(250 + a * sin(t) * num, 250 + b * cos(c * t) * num), 1, Scalar(0, 0, 0), -1);
        }

        imshow("windows", img2);
    }

    return 0;
}
