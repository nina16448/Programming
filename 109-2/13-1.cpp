#include <cstdio>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(){
    Mat img(480, 720, CV_8UC3, Scalar(255,255,255));

    putText(img, std::string("409410002"), Point(100, 100), 0, 1, Scalar(0,0,0),3);

    imshow("window", img);
    waitKey(0);

    return 0;
}
