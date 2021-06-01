#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#define resize 200
using namespace cv;
using namespace std;
typedef long long lint;

struct data{
    double r, m, Vx, Vy, Px, Py;
    int R, G, B;
};

int n;
double Bx, By;
data rec;
vector <data> ball;

void collision(int a, int b){
    double m1 = ball[a].m, m2 = ball[b].m, Vx1 = ball[a].Vx , Vx2 = ball[b].Vx, Vy1 = ball[a].Vy, Vy2 = ball[b].Vy;

    ball[a].Vx = ((m1 - m2) * Vx1 + 2 * m2 * Vx2) / (m1 + m2);
    ball[b].Vx = ((m2 - m1) * Vx2 + 2 * m1 * Vx1) / (m1 + m2);
    ball[a].Vy = ((m1 - m2) * Vy1 + 2 * m2 * Vy2) / (m1 + m2);
    ball[b].Vy = ((m2 - m1) * Vy2 + 2 * m1 * Vy1) / (m1 + m2);
}

void judge(){
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            double dis = (ball[i].Px - ball[j].Px) * (ball[i].Px - ball[j].Px) + (ball[i].Py - ball[j].Py) * (ball[i].Py - ball[j].Py);
            double rad = (ball[i].r + ball[j].r)*(ball[i].r + ball[j].r);

            if(dis < rad) collision(i, j);
        }
    }
}

void movee(){
    Mat img(By, Bx, CV_8UC3, Scalar(255,237,199));
    Mat img2;
    img.copyTo(img2);

    for(int i = 0; i <n; i++){
        if(ball[i].Px - ball[i].r <= 0  || ball[i].Px + ball[i].r >= Bx)
            ball[i].Vx = -ball[i].Vx;

        if(ball[i].Py - ball[i].r <= 0  || ball[i].Py + ball[i].r >= By)
            ball[i].Vy = -ball[i].Vy;

        ball[i].Px += ball[i].Vx;
        ball[i].Py += ball[i].Vy;
        circle(img2, Point(ball[i].Px, ball[i].Py), ball[i].r, Scalar(ball[i].R, ball[i].G, ball[i].B), -1);
    }
    imshow("windows", img2);
    waitKey(1);
}

int main(){
    cin >> n;
    cin >> Bx >> By;
    Bx *= resize;
    By *= resize;
    if(!By) By = 160;

    cout << Bx << " " << By << "\n";
    Mat img(By, Bx, CV_8UC3, Scalar(255,237,199));
    Mat img2;
    img.copyTo(img2);

    for(int i = 0; i < n; i++){
        cin >> rec.r >> rec.m >> rec.Vx >> rec.Vy >> rec.Px >>rec.Py;
        rec.r *= resize;
        rec.Px *= resize;
        rec.Py *= resize;
        if(!rec.Py) rec.Py = 80;
        rec.R = rand() % (255 + 1);
        rec.G = rand() % (255 + 1);
        rec.B = rand() % (255 + 1);

        circle(img2, Point(rec.Px, rec.Py), rec.r, Scalar(rec.R, rec.G, rec.B), -1);

        ball.push_back(rec);
    }
    while(1){
        movee();
        judge();
    }
    return 0;
}
