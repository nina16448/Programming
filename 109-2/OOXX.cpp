#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#define resize 200
#define LU (x > 70 && x < 176 && y > 18 && y < 125)
#define MU (x > 185 && x < 306 && y > 18 && y < 125)
#define RU (x > 315 && x < 430 && y > 18 && y < 125)
#define LM (x > 70 && x < 176 && y > 137 && y < 250)
#define MM (x > 185 && x < 306 && y > 137 && y < 250)
#define RM (x > 315 && x < 430 && y > 137 && y < 250)
#define LD (x > 70 && x < 176 && y > 260 && y < 376)
#define MD (x > 185 && x < 306 && y > 260 && y < 376)
#define RD (x > 315 && x < 430 && y > 260 && y < 376)

using namespace cv;
using namespace std;
typedef long long lint;

Mat img(500, 500, CV_8UC3, Scalar(177,196,53));
Mat img2;
Mat img3;
vector <int> row1{-1, -1, -1}, row2{-1, -1, -1}, row3{-1, -1, -1};
vector <int> col1{-1, -1, -1}, col2{-1, -1, -1}, col3{-1, -1, -1};
vector <int> rec1{-1, -1, -1}, rec2{-1, -1, -1}, OOO{1, 1, 1}, XXX{0, 0, 0};
bool ENDflag;
int win = -1;
int CP;


int firstchoose;
void init();
void OO();
void XX();
void CallBackFunc(int event, int x, int y, int flags, void* userdata);
void draw(int turn);
void judge();
void END();

void END(){
    ENDflag = 1;
    waitKey(500);
    putText(img2, std::string("press any key to play again."), Point(27,450), 0, 1, Scalar(69,69,69),3);
    imshow("windows", img2);
    waitKey(0);
    init();
}

void judge(){
    win++;
    if(row1 == OOO){
        circle(img3, Point(121,71), 40, Scalar(177,196,53), 10);
        circle(img3, Point(246,71), 40, Scalar(177,196,53), 10);
        circle(img3, Point(372,71), 40, Scalar(177,196,53), 10);
        img3.copyTo(img2);
        circle(img2, Point(121,71), 40, Scalar(219,252,255), 10);
        circle(img2, Point(246,71), 40, Scalar(219,252,255), 10);
        circle(img2, Point(372,71), 40, Scalar(219,252,255), 10);
        for(int i = 50; i <= 450; i++){
            circle(img2, Point(i,71), 5, Scalar(219,252,255), -1);

            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        double j = 0;
        for(int i = 0; i <= 200; i++){
            img3.copyTo(img2);
            line(img2, Point(50 + i,71 + j), Point(450 - i,71 + j), Scalar(219,252,255), 10);

            circle(img2, Point(121 + j,71 + j), 40, Scalar(219,252,255), 10);
            circle(img2, Point(246,71 + j), 40, Scalar(219,252,255), 10);
            circle(img2, Point(372 - j,71 + j), 40, Scalar(219,252,255), 10);
            j += (double)123/200;
            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        win = 5151;
    }
    if(row2 == OOO){
        circle(img3, Point(121,194), 40, Scalar(177,196,53), 10);
        circle(img3, Point(246,194), 40, Scalar(177,196,53), 10);
        circle(img3, Point(372,194), 40, Scalar(177,196,53), 10);
        img3.copyTo(img2);
        circle(img2, Point(121,194), 40, Scalar(219,252,255), 10);
        circle(img2, Point(246,194), 40, Scalar(219,252,255), 10);
        circle(img2, Point(372,194), 40, Scalar(219,252,255), 10);
        for(int i = 50; i <= 450; i++){
            circle(img2, Point(i,194), 5, Scalar(219,252,255), -1);

            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        double j = 0;
        for(int i = 0; i <= 200; i++){
            img3.copyTo(img2);
            line(img2, Point(50 + i,194), Point(450 - i,194), Scalar(219,252,255), 10);

            circle(img2, Point(121 + j, 194), 40, Scalar(219,252,255), 10);
            circle(img2, Point(246, 194), 40, Scalar(219,252,255), 10);
            circle(img2, Point(372 - j, 194), 40, Scalar(219,252,255), 10);
            j += (double)123/200;
            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        win = 5151;
    }
    if(row3 == OOO){
        circle(img3, Point(121,318), 40, Scalar(177,196,53), 10);
        circle(img3, Point(246,318), 40, Scalar(177,196,53), 10);
        circle(img3, Point(372,318), 40, Scalar(177,196,53), 10);
        img3.copyTo(img2);
        circle(img2, Point(121,318), 40, Scalar(219,252,255), 10);
        circle(img2, Point(246,318), 40, Scalar(219,252,255), 10);
        circle(img2, Point(372,318), 40, Scalar(219,252,255), 10);
        for(int i = 50; i <= 450; i++){
            circle(img2, Point(i,318), 5, Scalar(219,252,255), -1);

            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        double j = 0;
        for(int i = 0; i <= 200; i++){
            img3.copyTo(img2);
            line(img2, Point(50 + i,318 - j), Point(450 - i,318 - j), Scalar(219,252,255), 10);

            circle(img2, Point(121 + j, 318 - j), 40, Scalar(219,252,255), 10);
            circle(img2, Point(246, 318 - j), 40, Scalar(219,252,255), 10);
            circle(img2, Point(372 - j, 318 - j), 40, Scalar(219,252,255), 10);
            j += (double)123/200;
            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        win = 5151;
    }
    if(row1 == XXX){
        line(img3, Point(161,111), Point(81,31), Scalar(177,196,53), 10);
        line(img3, Point(81,111), Point(161,31), Scalar(177,196,53), 10);
        line(img3, Point(286,111), Point(206,31), Scalar(177,196,53), 10);
        line(img3, Point(206,111), Point(286,31), Scalar(177,196,53), 10);
        line(img3, Point(412,111), Point(332,31), Scalar(177,196,53), 10);
        line(img3, Point(332,111), Point(412,31), Scalar(177,196,53), 10);
        img3.copyTo(img2);
        line(img2, Point(161,111), Point(81,31), Scalar(69,69,69), 10);
        line(img2, Point(81,111), Point(161,31), Scalar(69,69,69), 10);
        line(img2, Point(286,111), Point(206,31), Scalar(69, 69, 69), 10);
        line(img2, Point(206,111), Point(286,31), Scalar(69, 69, 69), 10);
        line(img2, Point(412,111), Point(332,31), Scalar(69, 69, 69), 10);
        line(img2, Point(332,111), Point(412,31), Scalar(69, 69, 69), 10);
        for(int i = 50; i <= 450; i++){
            circle(img2, Point(i,71), 5, Scalar(69, 69, 69), -1);

            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        double j = 0;
        for(int i = 0; i <= 200; i++){
            img3.copyTo(img2);
            line(img2, Point(50 + i,71 + j), Point(450 - i,71 + j), Scalar(69,69,69), 10);

            line(img2, Point(161 + j,111 + j), Point(81 + j,31 + j), Scalar(69,69,69), 10);
            line(img2, Point(81 + j,111 + j), Point(161 + j,31 + j), Scalar(69,69,69), 10);

            line(img2, Point(286,111 + j), Point(206,31 + j), Scalar(69, 69, 69), 10);
            line(img2, Point(206,111 + j), Point(286,31 + j), Scalar(69, 69, 69), 10);

            line(img2, Point(412 - j,111 + j), Point(332 - j,31 + j), Scalar(69, 69, 69), 10);
            line(img2, Point(332 - j,111 + j), Point(412 - j,31 + j), Scalar(69, 69, 69), 10);

            j += (double)123/200;
            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        win = 45454;
    }
    if(row2 == XXX){
        line(img3, Point(161,230), Point(81,150), Scalar(177,196,53), 10);
        line(img3, Point(81,230), Point(161,150), Scalar(177,196,53), 10);
        line(img3, Point(286,230), Point(206,150), Scalar(177,196,53), 10);
        line(img3, Point(206,230), Point(286,150), Scalar(177,196,53), 10);
        line(img3, Point(412,230), Point(332,150), Scalar(177,196,53), 10);
        line(img3, Point(332,230), Point(412,150), Scalar(177,196,53), 10);
        img3.copyTo(img2);
        line(img2, Point(161,230), Point(81,150), Scalar(69,69,69), 10);
        line(img2, Point(81,230), Point(161,150), Scalar(69,69,69), 10);
        line(img2, Point(286,230), Point(206,150), Scalar(69, 69, 69), 10);
        line(img2, Point(206,230), Point(286,150), Scalar(69, 69, 69), 10);
        line(img2, Point(412,230), Point(332,150), Scalar(69, 69, 69), 10);
        line(img2, Point(332,230), Point(412,150), Scalar(69, 69, 69), 10);
        for(int i = 50; i <= 450; i++){
            circle(img2, Point(i,194), 5, Scalar(69, 69, 69), -1);

            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        double j = 0;
        for(int i = 0; i <= 200; i++){
            img3.copyTo(img2);
            line(img2, Point(50 + i, 194), Point(450 - i, 194), Scalar(69,69,69), 10);

            line(img2, Point(161 + j, 230), Point(81 + j, 150), Scalar(69,69,69), 10);
            line(img2, Point(81 + j, 230), Point(161 + j, 150), Scalar(69,69,69), 10);

            line(img2, Point(286, 230), Point(206, 150), Scalar(69, 69, 69), 10);
            line(img2, Point(206, 230), Point(286, 150), Scalar(69, 69, 69), 10);

            line(img2, Point(412 - j, 230), Point(332 - j, 150), Scalar(69, 69, 69), 10);
            line(img2, Point(332 - j, 230), Point(412 - j, 150), Scalar(69, 69, 69), 10);

            j += (double)123/200;
            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        win = 45454;
    }
    if(row3 == XXX){
        line(img3, Point(161,358), Point(81,278), Scalar(177,196,53), 10);
        line(img3, Point(81,358), Point(161,278), Scalar(177,196,53), 10);
        line(img3, Point(286,358), Point(206,278), Scalar(177,196,53), 10);
        line(img3, Point(206,358), Point(286,278), Scalar(177,196,53), 10);
        line(img3, Point(412,358), Point(332,278), Scalar(177,196,53), 10);
        line(img3, Point(332,358), Point(412,278), Scalar(177,196,53), 10);
        img3.copyTo(img2);
        line(img2, Point(161,358), Point(81,278), Scalar(69,69,69), 10);
        line(img2, Point(81,358), Point(161,278), Scalar(69,69,69), 10);
        line(img2, Point(286,358), Point(206,278), Scalar(69, 69, 69), 10);
        line(img2, Point(206,358), Point(286,278), Scalar(69, 69, 69), 10);
        line(img2, Point(412,358), Point(332,278), Scalar(69, 69, 69), 10);
        line(img2, Point(332,358), Point(412,278), Scalar(69, 69, 69), 10);
        for(int i = 50; i <= 450; i++){
            circle(img2, Point(i, 318), 5, Scalar(69, 69, 69), -1);

            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        double j = 0;
        for(int i = 0; i <= 200; i++){
            img3.copyTo(img2);
            line(img2, Point(50 + i,318 - j), Point(450 - i,318 - j), Scalar(69,69,69), 10);

            line(img2, Point(161 + j, 358 - j), Point(81 + j, 278 - j), Scalar(69,69,69), 10);
            line(img2, Point(81 + j, 358 - j), Point(161 + j, 278 - j), Scalar(69,69,69), 10);

            line(img2, Point(286, 358 - j), Point(206, 278 - j), Scalar(69, 69, 69), 10);
            line(img2, Point(206, 358 - j), Point(286, 278 - j), Scalar(69, 69, 69), 10);

            line(img2, Point(412 - j, 358 - j), Point(332 - j, 278 - j), Scalar(69, 69, 69), 10);
            line(img2, Point(332 - j, 358 - j), Point(412 - j, 278 - j), Scalar(69, 69, 69), 10);

            j += (double)123/200;
            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        win = 45454;
    }

    if(col1 == OOO){
        circle(img3, Point(121,71), 40, Scalar(177,196,53), 10);
        circle(img3, Point(121,194), 40, Scalar(177,196,53), 10);
        circle(img3, Point(121,318), 40, Scalar(177,196,53), 10);
        img3.copyTo(img2);
        circle(img2, Point(121,71), 40, Scalar(219,252,255), 10);
        circle(img2, Point(121,194), 40, Scalar(219,252,255), 10);
        circle(img2, Point(121,318), 40, Scalar(219,252,255), 10);
        for(int i = 10; i <= 410; i++){
            circle(img2, Point(121,i), 5, Scalar(219,252,255), -1);

            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        double j = 0;
        for(int i = 0; i <= 200; i++){
            img3.copyTo(img2);
            line(img2, Point(121 + j,10 + i), Point(121 + j,410 - i), Scalar(219,252,255), 10);

            circle(img2, Point(121 + j,71 + j), 40, Scalar(219,252,255), 10);
            circle(img2, Point(121 + j,194), 40, Scalar(219,252,255), 10);
            circle(img2, Point(121 + j,318 - j), 40, Scalar(219,252,255), 10);
            j += (double)125/200;
            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        win = 5151;
    }
    if(col2 == OOO){
        circle(img3, Point(246,71), 40, Scalar(177,196,53), 10);
        circle(img3, Point(246,194), 40, Scalar(177,196,53), 10);
        circle(img3, Point(246,318), 40, Scalar(177,196,53), 10);
        img3.copyTo(img2);
        circle(img2, Point(246,71), 40, Scalar(219,252,255), 10);
        circle(img2, Point(246,194), 40, Scalar(219,252,255), 10);
        circle(img2, Point(246,318), 40, Scalar(219,252,255), 10);
        for(int i = 10; i <= 410; i++){
            circle(img2, Point(246,i), 5, Scalar(219,252,255), -1);

            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        double j = 0;
        for(int i = 0; i <= 200; i++){
            img3.copyTo(img2);
            line(img2, Point(246,10 + i), Point(246,410 - i), Scalar(219,252,255), 10);

            circle(img2, Point(246,71 + j), 40, Scalar(219,252,255), 10);
            circle(img2, Point(246,194), 40, Scalar(219,252,255), 10);
            circle(img2, Point(246,318 - j), 40, Scalar(219,252,255), 10);
            j += (double)125/200;
            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        win = 5151;
    }
    if(col3 == OOO){
        circle(img3, Point(372,71), 40, Scalar(177,196,53), 10);
        circle(img3, Point(372,194), 40, Scalar(177,196,53), 10);
        circle(img3, Point(372,318), 40, Scalar(177,196,53), 10);
        img3.copyTo(img2);
        circle(img2, Point(372,71), 40, Scalar(219,252,255), 10);
        circle(img2, Point(372,194), 40, Scalar(219,252,255), 10);
        circle(img2, Point(372,318), 40, Scalar(219,252,255), 10);
        for(int i = 10; i <= 410; i++){
            circle(img2, Point(372,i), 5, Scalar(219,252,255), -1);

            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        double j = 0;
        for(int i = 0; i <= 200; i++){
            img3.copyTo(img2);
            line(img2, Point(372 - j,10 + i), Point(372 - j,410 - i), Scalar(219,252,255), 10);

            circle(img2, Point(372 - j,71 + j), 40, Scalar(219,252,255), 10);
            circle(img2, Point(372 - j,194), 40, Scalar(219,252,255), 10);
            circle(img2, Point(372 - j,318 - j), 40, Scalar(219,252,255), 10);
            j += (double)125/200;
            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        win = 5151;
    }
    if(col1 == XXX){
        line(img3, Point(161,111), Point(81,31), Scalar(177,196,53), 10);
        line(img3, Point(81,111), Point(161,31), Scalar(177,196,53), 10);
        line(img3, Point(161,230), Point(81,150), Scalar(177,196,53), 10);
        line(img3, Point(81,230), Point(161,150), Scalar(177,196,53), 10);
        line(img3, Point(161,358), Point(81,278), Scalar(177,196,53), 10);
        line(img3, Point(81,358), Point(161,278), Scalar(177,196,53), 10);
        img3.copyTo(img2);
        line(img2, Point(161,111), Point(81,31), Scalar(69,69,69), 10);
        line(img2, Point(81,111), Point(161,31), Scalar(69,69,69), 10);
        line(img2, Point(161,230), Point(81,150), Scalar(69, 69, 69), 10);
        line(img2, Point(81,230), Point(161,150), Scalar(69, 69, 69), 10);
        line(img2, Point(161,358), Point(81,278), Scalar(69, 69, 69), 10);
        line(img2, Point(81,358), Point(161,278), Scalar(69, 69, 69), 10);
        for(int i = 10; i <= 410; i++){
            circle(img2, Point(121,i), 5, Scalar(69, 69, 69), -1);

            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        double j = 0;
        for(int i = 0; i <= 200; i++){
            img3.copyTo(img2);
            line(img2, Point(121 + j,10 + i), Point(121 + j,410 - i), Scalar(69,69,69), 10);

            line(img2, Point(161 + j,111 + j), Point(81 + j,31 + j), Scalar(69,69,69), 10);
            line(img2, Point(81 + j,111 + j), Point(161 + j,31 + j), Scalar(69,69,69), 10);

            line(img2, Point(161 + j,230), Point(81 + j,150), Scalar(69, 69, 69), 10);
            line(img2, Point(81 + j,230), Point(161 + j,150), Scalar(69, 69, 69), 10);

            line(img2, Point(161 + j,358 - j), Point(81 + j,278 - j), Scalar(69, 69, 69), 10);
            line(img2, Point(81 + j,358 - j), Point(161 + j,278 - j), Scalar(69, 69, 69), 10);

            j += (double)123/200;
            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        win = 45454;
    }
    if(col2 == XXX){
        line(img3, Point(286,111), Point(206,31), Scalar(177,196,53), 10);
        line(img3, Point(206,111), Point(286,31), Scalar(177,196,53), 10);
        line(img3, Point(286,230), Point(206,150), Scalar(177,196,53), 10);
        line(img3, Point(206,230), Point(286,150), Scalar(177,196,53), 10);
        line(img3, Point(286,358), Point(206,278), Scalar(177,196,53), 10);
        line(img3, Point(206,358), Point(286,278), Scalar(177,196,53), 10);
        img3.copyTo(img2);
        line(img2, Point(286,111), Point(206,31), Scalar(69,69,69), 10);
        line(img2, Point(206,111), Point(286,31), Scalar(69,69,69), 10);
        line(img2, Point(286,230), Point(206,150), Scalar(69, 69, 69), 10);
        line(img2, Point(206,230), Point(286,150), Scalar(69, 69, 69), 10);
        line(img2, Point(286,358), Point(206,278), Scalar(69, 69, 69), 10);
        line(img2, Point(206,358), Point(286,278), Scalar(69, 69, 69), 10);
        for(int i = 10; i <= 410; i++){
            circle(img2, Point(246,i), 5, Scalar(69, 69, 69), -1);

            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        double j = 0;
        for(int i = 0; i <= 200; i++){
            img3.copyTo(img2);
            line(img2, Point(246,10 + i), Point(246,410 - i), Scalar(69,69,69), 10);

            line(img2, Point(286,111 + j), Point(206,31 + j), Scalar(69,69,69), 10);
            line(img2, Point(206,111 + j), Point(286,31 + j), Scalar(69,69,69), 10);

            line(img2, Point(286,230), Point(206,150), Scalar(69, 69, 69), 10);
            line(img2, Point(206,230), Point(286,150), Scalar(69, 69, 69), 10);

            line(img2, Point(286,358 - j), Point(206,278 - j), Scalar(69, 69, 69), 10);
            line(img2, Point(206,358 - j), Point(286,278 - j), Scalar(69, 69, 69), 10);

            j += (double)123/200;
            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        win = 45454;
    }
    if(col3 == XXX){
        line(img3, Point(412,111), Point(332,31), Scalar(177,196,53), 10);
        line(img3, Point(332,111), Point(412,31), Scalar(177,196,53), 10);
        line(img3, Point(412,230), Point(332,150), Scalar(177,196,53), 10);
        line(img3, Point(332,230), Point(412,150), Scalar(177,196,53), 10);
        line(img3, Point(412,358), Point(332,278), Scalar(177,196,53), 10);
        line(img3, Point(332,358), Point(412,278), Scalar(177,196,53), 10);
        img3.copyTo(img2);
        line(img2, Point(412,111), Point(332,31), Scalar(69,69,69), 10);
        line(img2, Point(332,111), Point(412,31), Scalar(69,69,69), 10);
        line(img2, Point(412,230), Point(332,150), Scalar(69, 69, 69), 10);
        line(img2, Point(332,230), Point(412,150), Scalar(69, 69, 69), 10);
        line(img2, Point(412,358), Point(332,278), Scalar(69, 69, 69), 10);
        line(img2, Point(332,358), Point(412,278), Scalar(69, 69, 69), 10);
        for(int i = 10; i <= 410; i++){
            circle(img2, Point(372,i), 5, Scalar(69, 69, 69), -1);

            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        double j = 0;
        for(int i = 0; i <= 200; i++){
            img3.copyTo(img2);
            line(img2, Point(372 - j,10 + i), Point(372 - j,410 - i), Scalar(69,69,69), 10);

            line(img2, Point(412 - j,111 + j), Point(332 - j,31 + j), Scalar(69,69,69), 10);
            line(img2, Point(332 - j,111 + j), Point(412 - j,31 + j), Scalar(69,69,69), 10);

            line(img2, Point(412 - j,230), Point(332 - j,150), Scalar(69, 69, 69), 10);
            line(img2, Point(332 - j,230), Point(412 - j,150), Scalar(69, 69, 69), 10);

            line(img2, Point(412 - j,358 - j), Point(332 - j,278 - j), Scalar(69, 69, 69), 10);
            line(img2, Point(332 - j,358 - j), Point(412 - j,278 - j), Scalar(69, 69, 69), 10);

            j += (double)123/200;
            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        win = 45454;
    }

    if(rec1 == OOO){
        circle(img3, Point(121,71), 40, Scalar(177,196,53), 10);
        circle(img3, Point(246,194), 40, Scalar(177,196,53), 10);
        circle(img3, Point(372,318), 40, Scalar(177,196,53), 10);
        img3.copyTo(img2);
        circle(img2, Point(121,71), 40, Scalar(219,252,255), 10);
        circle(img2, Point(246,194), 40, Scalar(219,252,255), 10);
        circle(img2, Point(372,318), 40, Scalar(219,252,255), 10);
        for(int i = 15; i <= 375; i++){
            circle(img2, Point(i + 50, i), 5, Scalar(219,252,255), -1);

            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        double j = 0;
        for(int i = 0; i <= 180; i++){
            img3.copyTo(img2);
            line(img2, Point(65 + i,15 + i), Point(425 - i,375 - i), Scalar(219,252,255), 10);

            circle(img2, Point(121 + j,71 + j), 40, Scalar(219,252,255), 10);
            circle(img2, Point(246, 194), 40, Scalar(219,252,255), 10);
            circle(img2, Point(372 - j,318 - j), 40, Scalar(219,252,255), 10);
            j += (double)123/200;
            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        win = 5151;
    }
    if(rec1 == XXX){
        line(img3, Point(161,111), Point(81,31), Scalar(177,196,53), 10);
        line(img3, Point(81,111), Point(161,31), Scalar(177,196,53), 10);
        line(img3, Point(286,230), Point(206,150), Scalar(177,196,53), 10);
        line(img3, Point(206,230), Point(286,150), Scalar(177,196,53), 10);
        line(img3, Point(412,358), Point(332,278), Scalar(177,196,53), 10);
        line(img3, Point(332,358), Point(412,278), Scalar(177,196,53), 10);
        img3.copyTo(img2);
        line(img2, Point(161,111), Point(81,31), Scalar(69,69,69), 10);
        line(img2, Point(81,111), Point(161,31), Scalar(69,69,69), 10);
        line(img2, Point(286,230), Point(206,150), Scalar(69, 69, 69), 10);
        line(img2, Point(206,230), Point(286,150), Scalar(69, 69, 69), 10);
        line(img2, Point(412,358), Point(332,278), Scalar(69, 69, 69), 10);
        line(img2, Point(332,358), Point(412,278), Scalar(69, 69, 69), 10);
        for(int i = 15; i <= 375; i++){
            circle(img2, Point(i + 50, i), 5, Scalar(69, 69, 69), -1);

            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        double j = 0;
        for(int i = 0; i <= 180; i++){
            img3.copyTo(img2);
            line(img2, Point(65 + i,15 + i), Point(425 - i,375 - i), Scalar(69, 69, 69), 10);

            line(img2, Point(161 + j,111 + j), Point(81 + j,31 + j), Scalar(69,69,69), 10);
            line(img2, Point(81 + j,111 + j), Point(161 + j,31 + j), Scalar(69,69,69), 10);
            line(img2, Point(286,230), Point(206,150), Scalar(69, 69, 69), 10);
            line(img2, Point(206,230), Point(286,150), Scalar(69, 69, 69), 10);
            line(img2, Point(412 - j,358 - j), Point(332 - j,278 - j), Scalar(69, 69, 69), 10);
            line(img2, Point(332 - j,358 - j), Point(412 - j,278 - j), Scalar(69, 69, 69), 10);

            j += (double)123/200;
            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        win = 45454;
    }
    if(rec2 == OOO){
        circle(img3, Point(372,71), 40, Scalar(177,196,53), 10);
        circle(img3, Point(246,194), 40, Scalar(177,196,53), 10);
        circle(img3, Point(121,318), 40, Scalar(177,196,53), 10);
        img3.copyTo(img2);
        circle(img2, Point(372,71), 40, Scalar(219,252,255), 10);
        circle(img2, Point(246,194), 40, Scalar(219,252,255), 10);
        circle(img2, Point(121,318), 40, Scalar(219,252,255), 10);
        for(int i = 15; i <= 375; i++){
            circle(img2, Point(390 - i + 50, i), 5, Scalar(219,252,255), -1);

            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        double j = 0;
        for(int i = 0; i <= 180; i++){
            img3.copyTo(img2);
            line(img2, Point(425 - i,15 + i), Point(65 + i,375 - i), Scalar(219,252,255), 10);

            circle(img2, Point(372 - j,71 + j), 40, Scalar(219,252,255), 10);
            circle(img2, Point(246, 194), 40, Scalar(219,252,255), 10);
            circle(img2, Point(121 + j,318 - j), 40, Scalar(219,252,255), 10);
            j += (double)123/200;
            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        win = 5151;
    }
    if(rec2 == XXX){
        line(img3, Point(161,358), Point(81,278), Scalar(177,196,53), 10);
        line(img3, Point(81,358), Point(161,278), Scalar(177,196,53), 10);
        line(img3, Point(286,230), Point(206,150), Scalar(177,196,53), 10);
        line(img3, Point(206,230), Point(286,150), Scalar(177,196,53), 10);
        line(img3, Point(412,111), Point(332,31), Scalar(177,196,53), 10);
        line(img3, Point(332,111), Point(412,31), Scalar(177,196,53), 10);
        img3.copyTo(img2);
        line(img2, Point(161,358), Point(81,278), Scalar(69,69,69), 10);
        line(img2, Point(81,358), Point(161,278), Scalar(69,69,69), 10);
        line(img2, Point(286,230), Point(206,150), Scalar(69, 69, 69), 10);
        line(img2, Point(206,230), Point(286,150), Scalar(69, 69, 69), 10);
        line(img2, Point(412,111), Point(332,31), Scalar(69, 69, 69), 10);
        line(img2, Point(332,111), Point(412,31), Scalar(69, 69, 69), 10);
        for(int i = 15; i <= 375; i++){
            circle(img2, Point(390 - i + 50, i), 5, Scalar(69, 69, 69), -1);

            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        double j = 0;
        for(int i = 0; i <= 180; i++){
            img3.copyTo(img2);
            line(img2, Point(425 - i,15 + i), Point(65 + i,375 - i), Scalar(69, 69, 69), 10);

            line(img2, Point(161 + j,358 - j), Point(81 + j,278 - j), Scalar(69, 69, 69), 10);
            line(img2, Point(81 + j,358 - j), Point(161 + j,278 - j), Scalar(69, 69, 69), 10);
            line(img2, Point(286,230), Point(206,150), Scalar(69, 69, 69), 10);
            line(img2, Point(206,230), Point(286,150), Scalar(69, 69, 69), 10);
            line(img2, Point(412 - j,111 + j), Point(332 - j,31 + j), Scalar(69,69,69), 10);
            line(img2, Point(332 - j,111 + j), Point(412 - j,31 + j), Scalar(69,69,69), 10);

            j += (double)123/200;
            imshow("windows", img2);
            if(!(i % 7))waitKey(1);
        }
        win = 45454;
    }

    if(win == 5151){
        img3.copyTo(img2);
        circle(img2, Point(246,194), 40, Scalar(219,252,255), 10);
        imshow("windows", img2);
        rectangle(img3, Point(0,0), Point(500,500), Scalar(177,196,53), -1);

        double r = 0, R = 0, G = 0, B = 0;
        for(int i = 0; i <= 55; i += 2){
            img3.copyTo(img2);

            line(img2, Point(180 , 20 + i), Point(180, 370 - i), Scalar(135 + B,150 + G,35 + R), 10);
            line(img2, Point(310 , 20 + i), Point(310, 370 - i), Scalar(135 + B,150 + G,35 + R), 10);
            line(img2, Point(75 + i , 130), Point(425 - i, 130), Scalar(135 + B,150 + G,35 + R), 10);
            line(img2, Point(75 + i , 255), Point(425 - i, 255), Scalar(135 + B,150 + G,35 + R), 10);
            circle(img2, Point(246,71 + 123 - (i * 0.6)), 40 + i, Scalar(219,252,255), 10 + r);
            imshow("windows", img2);
            waitKey(1);
            r += 0.8;
            if(R < 18) R += 2;
            if(G < 46) G += 2;
            if(B < 42) B += 2;
        }
        putText(img2, std::string("WIN!"), Point(155,360), 2, 3, Scalar(69,69,69),7);
        imshow("windows", img2);
        END();
    }
    if(win == 45454){
        img3.copyTo(img2);
        line(img3, Point(286,230), Point(206,150), Scalar(69, 69, 69), 10);
        line(img3, Point(206,230), Point(286,150), Scalar(69, 69, 69), 10);
        imshow("windows", img2);
        rectangle(img3, Point(0,0), Point(500,500), Scalar(177,196,53), -1);

        double r = 0, R = 0, G = 0, B = 0;
        for(int i = 0; i <= 50; i += 2){
            img3.copyTo(img2);

            line(img2, Point(180 , 20 + i), Point(180, 370 - i), Scalar(135 + B,150 + G,35 + R), 10);
            line(img2, Point(310 , 20 + i), Point(310, 370 - i), Scalar(135 + B,150 + G,35 + R), 10);
            line(img2, Point(75 + i , 130), Point(425 - i, 130), Scalar(135 + B,150 + G,35 + R), 10);
            line(img2, Point(75 + i , 255), Point(425 - i, 255), Scalar(135 + B,150 + G,35 + R), 10);

            line(img2, Point(286 + i,230 + i - (i * 0.3)), Point(206 - i,150 - i - (i * 0.3)), Scalar(69, 69, 69), 10 + r);
            line(img2, Point(206 - i,230 + i - (i * 0.3)), Point(286 + i,150 - i - (i * 0.3)), Scalar(69, 69, 69), 10 + r);


            imshow("windows", img2);
            waitKey(1);
            r += 0.8;
            if(R < 18) R += 2;
            if(G < 46) G += 2;
            if(B < 42) B += 2;
        }
        putText(img2, std::string("WIN!"), Point(155,360), 2, 3, Scalar(69,69,69),7);
        imshow("windows", img2);
        END();
    }
    if(win == 8){
        img3.copyTo(img2);
        imshow("windows", img2);
        waitKey(200);
        rectangle(img3, Point(0,0), Point(500,500), Scalar(177,196,53), -1);

        double r = 0, R = 0, G = 0, B = 0;
        for(int i = 0; i <= 23; i += 1){
            img3.copyTo(img2);

            line(img2, Point(180 , 20 + i), Point(180, 370 - i), Scalar(135 + B,150 + G,35 + R), 10);
            line(img2, Point(310 , 20 + i), Point(310, 370 - i), Scalar(135 + B,150 + G,35 + R), 10);
            line(img2, Point(75 + i , 130), Point(425 - i, 130), Scalar(135 + B,150 + G,35 + R), 10);
            line(img2, Point(75 + i , 255), Point(425 - i, 255), Scalar(135 + B,150 + G,35 + R), 10);

            line(img2, Point(286 + i - 80,230 + i - (i * 0.3)), Point(206 - i - 80,150 - i - (i * 0.3)), Scalar(69, 69, 69), 10 + r);
            line(img2, Point(206 - i - 80,230 + i - (i * 0.3)), Point(286 + i - 80,150 - i - (i * 0.3)), Scalar(69, 69, 69), 10 + r);
            circle(img2, Point(246 + 100,71 + 123 - (i * 0.6)), 45 + i, Scalar(219,252,255), 10 + r);

            imshow("windows", img2);
            waitKey(1);
            r += 0.4;
            if(R < 18) R += 2;
            if(G < 46) G += 2;
            if(B < 42) B += 2;
        }
        putText(img2, std::string("TIE"), Point(185,360), 2, 3, Scalar(69,69,69),7);
        imshow("windows", img2);
        END();
    }
}

void draw(int turn){
    if(turn == 1){
        if(row1[0] != -1 || ENDflag == 1) return;
        row1[0] = 1;
        col1[0] = 1;
        rec1[0] = 1;
        if(firstchoose == 1)
            circle(img3, Point(121,71), 40, Scalar(219,252,255), 10);
        else{
            line(img3, Point(161,111), Point(81,31), Scalar(69, 69, 69), 10);
            line(img3, Point(81,111), Point(161,31), Scalar(69, 69, 69), 10);
            row1[0] = 0;
            col1[0] = 0;
            rec1[0] = 0;
        }

    }
    if(turn == 2){
        if(row1[1] != -1 || ENDflag == 1) return;
        row1[1] = 1;
        col2[0] = 1;
        if(firstchoose == 1)
            circle(img3, Point(246,71), 40, Scalar(219,252,255), 10);
        else{
            line(img3, Point(286,111), Point(206,31), Scalar(69, 69, 69), 10);
            line(img3, Point(206,111), Point(286,31), Scalar(69, 69, 69), 10);
            row1[1] = 0;
            col2[0] = 0;
        }
    }
    if(turn == 3){
        if(row1[2] != -1 || ENDflag == 1) return;
        row1[2] = 1;
        col3[0] = 1;
        rec2[2] = 1;
        if(firstchoose == 1)
            circle(img3, Point(372,71), 40, Scalar(219,252,255), 10);
        else{
            line(img3, Point(412,111), Point(332,31), Scalar(69, 69, 69), 10);
            line(img3, Point(332,111), Point(412,31), Scalar(69, 69, 69), 10);
            row1[2] = 0;
            col3[0] = 0;
            rec2[2] = 0;
        }
    }
    if(turn == 4){
        if(row2[0] != -1 || ENDflag == 1) return;
        row2[0] = 1;
        col1[1] = 1;
        if(firstchoose == 1)
            circle(img3, Point(121,194), 40, Scalar(219,252,255), 10);
        else{
            line(img3, Point(161,230), Point(81,150), Scalar(69, 69, 69), 10);
            line(img3, Point(81,230), Point(161,150), Scalar(69, 69, 69), 10);
            row2[0] = 0;
            col1[1] = 0;
        }
    }
    if(turn == 5){
        if(row2[1] != -1 || ENDflag == 1) return;
        row2[1] = 1;
        col2[1] = 1;
        rec2[1] = 1;
        rec1[1] = 1;
        if(firstchoose == 1)
            circle(img3, Point(246,194), 40, Scalar(219,252,255), 10);
        else{
            line(img3, Point(286,230), Point(206,150), Scalar(69, 69, 69), 10);
            line(img3, Point(206,230), Point(286,150), Scalar(69, 69, 69), 10);
            row2[1] = 0;
            col2[1] = 0;
            rec2[1] = 0;
            rec1[1] = 0;
        }
    }
    if(turn == 6){
        if(row2[2] != -1 || ENDflag == 1) return;
        row2[2] = 1;
        col3[1] = 1;
        if(firstchoose == 1)
            circle(img3, Point(372,194), 40, Scalar(219,252,255), 10);
        else{
            line(img3, Point(412,230), Point(332,150), Scalar(69, 69, 69), 10);
            line(img3, Point(332,230), Point(412,150), Scalar(69, 69, 69), 10);
            row2[2] = 0;
            col3[1] = 0;
        }
    }
    if(turn == 7){
        if(row3[0] != -1 || ENDflag == 1) return;
        row3[0] = 1;
        col1[2] = 1;
        rec2[0] = 1;
        if(firstchoose == 1)
            circle(img3, Point(121,318), 40, Scalar(219,252,255), 10);
        else{
            line(img3, Point(161,358), Point(81,278), Scalar(69, 69, 69), 10);
            line(img3, Point(81,358), Point(161,278), Scalar(69, 69, 69), 10);
            row3[0] = 0;
            col1[2] = 0;
            rec2[0] = 0;
        }
    }
    if(turn == 8){
        if(row3[1] != -1 || ENDflag == 1) return;
        row3[1] = 1;
        col2[2] = 1;
        if(firstchoose == 1)
            circle(img3, Point(246,318), 40, Scalar(219,252,255), 10);
        else{
            line(img3, Point(286,358), Point(206,278), Scalar(69, 69, 69), 10);
            line(img3, Point(206,358), Point(286,278), Scalar(69, 69, 69), 10);
            row3[1] = 0;
            col2[2] = 0;
        }
    }
    if(turn == 9){
        if(row3[2] != -1 || ENDflag == 1) return;
        row3[2] = 1;
        col3[2] = 1;
        rec1[2] = 1;
        if(firstchoose == 1)
            circle(img3, Point(372,318), 40, Scalar(219,252,255), 10);
        else{
            line(img3, Point(412,358), Point(332,278), Scalar(69, 69, 69), 10);
            line(img3, Point(332,358), Point(412,278), Scalar(69, 69, 69), 10);
            row3[2] = 0;
            col3[2] = 0;
            rec1[2] = 0;
        }
    }
    judge();
    if(firstchoose == 1) XX();
    else if(firstchoose == 2) OO();
}

void init(){
    for(int i = 0; i < 3; i++){
        row1[i] = -1;
        row2[i] = -1;
        row3[i] = -1;
        col1[i] = -1;
        col2[i] = -1;
        col3[i] = -1;
        rec1[i] = -1;
        rec2[i] = -1;
    }
    ENDflag = 0;
    win = -1;
    firstchoose = 0;
    int R = 0, G = 0, B = 0;
    rectangle(img, Point(0,0), Point(500,500), Scalar(177,196,53), -1);
    for(int i = 0; i <= 175; i++){
        line(img, Point(180 , 195 - i), Point(180, 195 + i), Scalar(177 - B,196 - G,53 - R), 10);
        line(img, Point(310 , 195 - i), Point(310, 195 + i), Scalar(177 - B,196 - G,53 - R), 10);
        line(img, Point(250 - i , 130), Point(250 + i, 130), Scalar(177 - B,196 - G,53 - R), 10);
        line(img, Point(250 - i , 255), Point(250 + i, 255), Scalar(177 - B,196 - G,53 - R), 10);
        if(R < 18) R += 2;
        if(G < 46) G += 2;
        if(B < 42) B += 2;
        img.copyTo(img2);
        imshow("windows", img2);
        if(!(i % 3))waitKey(1);
    }

    img.copyTo(img2);
    img2.copyTo(img3);

    putText(img2, std::string("first player:       or"), Point(20,450), 0, 1, Scalar(69,69,69),3);
    circle(img2, Point(255,430), 30, Scalar(219,252,255), 10);

    line(img2, Point(380,405), Point(430,455), Scalar(69, 69, 69), 10);
    line(img2, Point(430,405), Point(380,455), Scalar(69, 69, 69), 10);
    imshow("windows", img2);
}

void OO(){
    img3.copyTo(img2);
    circle(img2, Point(50,430), 25, Scalar(219,252,255), 10);
    putText(img2, std::string("turn"), Point(90,450), 0, 1, Scalar(60, 66, 17),3);
    imshow("windows", img2);
    firstchoose = 1;
}

void XX(){
    img3.copyTo(img2);
    line(img2, Point(30,410), Point(70,450), Scalar(69, 69, 69), 10);
    line(img2, Point(70,410), Point(30,450), Scalar(69, 69, 69), 10);
    putText(img2, std::string("turn"), Point(90,450), 0, 1, Scalar(60, 66, 17),3);
    imshow("windows", img2);
    firstchoose = 2;
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata){
    static Point pt1,pt2;
    if  ( event == EVENT_LBUTTONDOWN ){
        pt1 = Point(x,y);
        if(!firstchoose){
            if(x > 216 && x < 292 && y > 394 && y < 466){
                firstchoose = 1;
                if(CP == 2){
                    firstchoose = 2;
                    XX();
                }
                else OO();
            }
            if(x > 376 && x < 438 && y > 400 && y < 459){
                firstchoose = 2;
                XX();
            }
        }
        else{
            if(LU)
                draw(1);

            if(MU)
                draw(2);

            if(RU)
                draw(3);

            if(LM)
                draw(4);

            if(MM)
                draw(5);

            if(RM)
                draw(6);

            if(LD)
                draw(7);

            if(MD)
                draw(8);

            if(RD)
                draw(9);

        }
        //cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
}


int main(){
    cin >> CP;
    init();
    namedWindow("windows");
    setMouseCallback("windows", CallBackFunc, NULL);

    imshow("windows", img2);

    while(1){
        int key = waitKey(0);
        //cout << key << "\n";
        if(key == 32) init();
        if(key == 113) draw(1);
        if(key == 119) draw(2);
        if(key == 101) draw(3);
        if(key == 97) draw(4);
        if(key == 115) draw(5);
        if(key == 100) draw(6);
        if(key == 122) draw(7);
        if(key == 120) draw(8);
        if(key == 99) draw(9);
        imshow("windows", img2);
    }

    return 0;
}
