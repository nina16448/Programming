#include <cstdio>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(){

    //創建畫板的寬高（480*720）    scalar顏色BGR（255,255,255）白
    Mat img(480, 720, CV_8UC3, Scalar(255,255,255));


    //畫板左上角座標為(0,0)


    //把直線輸出到畫板上
    //兩點的位置[point(20,40), point(120.140)]
    //const scalar(255,0,0) 藍色
    //thickness = 3   線的寬度（不得為0）
    line(img, Point(20,40), Point(120,140), Scalar(255,0,0), 3);


    //把長方形輸出到畫板上
    //給兩個對角點
    //const scalar（0,0,255） 紅色
    //int thickness = -1（線條寬度，負數表示填滿圖形)
    rectangle(img, Point(150,40), Point(250,140), Scalar(0,0,255), -1);


    //把圓形輸出到畫板上
    //給圓心 point(330,90)
    //int radius半徑 = 50
    //const scalar（0,255,0） 綠色
    //int thickness = -1（線條寬度，負數表示填滿圖形)
    circle(img, Point(330,90), 50, Scalar(0,255,0), -1);


    //把橢圓形輸出到畫板上
    //Point給圓心 Point(80,280)
    //Size橢圓軸的尺寸 Size（60,40）
    //double angle旋轉角度 = 45 度
    //double startAngle = 0 橢圓弧起始角度
    //double endAngle = 360 橢圓弧結束角度
    //const scalar（255,255,0） 海藍色
    //int thickness = 2（線條寬度，負數表示填滿圖形)
    ellipse(img, Point(80,280), Size(60,40), 45, 0, 360, Scalar(255,255,0), 2);


    //把多邊線段輸出到畫板上
    //const points** ppt 多邊形曲線的array
    //const int* npt 多邊形頂點數目的array
    //int ncontours = 1 多邊形的數目（因為是設一維陣列所以只會畫出一個多邊形個n為可以畫n個）
    //bool isclosed = 1 是否為封閉的多邊型（設為0的話投頭尾不會相連）
    //scalar（280,280,0） 黃色
    //int thickness = 5 (線條寬度，負數表示填滿圖形)
    Point points[1][5];
    points[0][0] = Point(150, 270);
    points[0][1] = Point(190, 220);
    points[0][2] = Point(260, 255);
    points[0][3] = Point(224, 296);
    points[0][4] = Point(178, 316);
    const Point* ppt[1] = {points[0]};
    int npt[] = {5};
    polylines(img, ppt, npt, 1, 1, Scalar(0,255,255),5);


    //把文字輸出到畫板上
    //std::string 想要輸出的文字
    //Point 文字位置起點（由左下角出發）
    //font
    //fontFace
    //scalar (0,0,0) 黑色
    //int thickness = 3 (線條寬度，負數表示填滿圖形)
    putText(img, std::string("OpenCV"), Point(280,280), 0, 1, Scalar(0,0,0),3);

    putText(img, std::string("409410002"), Point(0,400), 0, 1, Scalar(0,0,0),3);

    imshow("window", img);
    waitKey(0);

    return 0;
}
