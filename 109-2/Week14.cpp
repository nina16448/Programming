#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
#define ID first
#define x second.first
#define y second.second
typedef long long lint;

lint n, ans, stx, sty, st;
vector <pair <lint, pair <lint, lint> > > U, L;
vector <pair <lint, pair <lint, lint> > > point;
pair <lint, pair <lint, lint> > rec;
lint Cross_Product(lint x1, lint y1, lint x2, lint y2);
Mat img(500, 500, CV_8UC3, Scalar(255,255,255));
Mat img2;


bool cmp(pair <lint, pair <lint, lint> > A, pair <lint, pair <lint, lint> > B){
    if(A.x == B.x) return A.y < B.y;
    return A.x < B.x;
}

void Upper_Hull(){
    U.push_back(point[0]);

    U.push_back(point[1]);

    for(lint i = 2; i < n; i++){
        while(U.size() > 1){
            pair <lint, pair <lint, lint> > p, pp;
            lint index = U.size() - 1;
            p = U[index];
            pp = U[index - 1];

            circle(img, Point(250 + pp.x * 2, 250 + -pp.y * 2), 2, Scalar(255, 255, 0), -1);
            img.copyTo(img2);
            imshow("windows", img2);
            waitKey(0);

            circle(img2, Point(250 + p.x * 2, 250 + -p.y * 2), 2, Scalar(0, 0, 255), -1);
            imshow("windows", img2);
            waitKey(0);

            line(img2, Point(250 + p.x * 2, 250 - p.y * 2), Point(250 + pp.x * 2, 250 - pp.y * 2), Scalar(255,255,0), 2);
            circle(img2, Point(250 + p.x * 2, 250 + -p.y * 2), 2, Scalar(0, 0, 255), -1);
            imshow("windows", img2);
            waitKey(0);

            circle(img2, Point(250 + point[i].x * 2, 250 + -point[i].y * 2), 2, Scalar(255, 255, 0), -1);
            imshow("windows", img2);
            waitKey(0);

            line(img2, Point(250 + p.x * 2, 250 - p.y * 2), Point(250 + point[i].x * 2, 250 - point[i].y * 2), Scalar(255,255,0), 2);
            circle(img2, Point(250 + p.x * 2, 250 + -p.y * 2), 2, Scalar(0, 0, 255), -1);
            imshow("windows", img2);
            waitKey(0);

            if(Cross_Product(p.x - pp.x, p.y - pp.y, point[i].x - p.x, point[i].y - p.y) >= 0){
                U.pop_back();
            }
            else{
                circle(img2, Point(250 + p.x * 2, 250 + -p.y * 2), 2, Scalar(255, 255, 0), -1);
                imshow("windows", img2);
                waitKey(0);
                circle(img, Point(250 + p.x * 2, 250 + -p.y * 2), 2, Scalar(255, 255, 0), -1);

                line(img, Point(250 + pp.x * 2, 250 - pp.y * 2), Point(250 + p.x * 2, 250 - p.y * 2), Scalar(0,0,0), 2);
                img.copyTo(img2);
                imshow("windows", img2);
                waitKey(0);
                break;
            }
        }
        U.push_back(point[i]);
    }
    line(img, Point(250 + U[U.size() - 2].x * 2, 250 - U[U.size() - 2].y * 2), Point(250 + point.back().x * 2, 250 - point.back().y * 2), Scalar(0,0,0), 2);
    img.copyTo(img2);
    imshow("windows", img2);
    waitKey(0);
}

void Lower_Hull(){
    L.push_back(point[n - 1]);
    L.push_back(point[n - 2]);
    for(lint i = n - 3; i >= 0; i--){
        while(L.size() > 1){
            pair <lint, pair <lint, lint> > p, pp;
            lint index = L.size() - 1;
            p = L[index - 1];
            pp = L[index];
            circle(img, Point(250 + p.x * 2, 250 + -p.y * 2), 2, Scalar(255, 255, 0), -1);
            img.copyTo(img2);
            imshow("windows", img2);
            waitKey(0);

            circle(img2, Point(250 + pp.x * 2, 250 + -pp.y * 2), 2, Scalar(0, 0, 255), -1);
            imshow("windows", img2);
            waitKey(0);

            line(img2, Point(250 + pp.x * 2, 250 - pp.y * 2), Point(250 + p.x * 2, 250 - p.y * 2), Scalar(255,255,0), 2);
            circle(img2, Point(250 + pp.x * 2, 250 + -pp.y * 2), 2, Scalar(0, 0, 255), -1);
            imshow("windows", img2);
            waitKey(0);

            circle(img2, Point(250 + point[i].x * 2, 250 + -point[i].y * 2), 2, Scalar(255, 255, 0), -1);
            imshow("windows", img2);
            waitKey(0);

            line(img2, Point(250 + pp.x * 2, 250 - pp.y * 2), Point(250 + point[i].x * 2, 250 - point[i].y * 2), Scalar(255,255,0), 2);
            circle(img2, Point(250 + pp.x * 2, 250 + -pp.y * 2), 2, Scalar(0, 0, 255), -1);
            imshow("windows", img2);
            waitKey(0);
            if(Cross_Product(p.x - pp.x, p.y - pp.y, point[i].x - p.x, point[i].y - p.y) <= 0)
                L.pop_back();
            else{
                circle(img2, Point(250 + pp.x * 2, 250 + -pp.y * 2), 2, Scalar(255, 255, 0), -1);
                imshow("windows", img2);
                waitKey(0);
                circle(img, Point(250 + pp.x * 2, 250 + -pp.y * 2), 2, Scalar(255, 255, 0), -1);

                line(img, Point(250 + pp.x * 2, 250 - pp.y * 2), Point(250 + p.x * 2, 250 - p.y * 2), Scalar(0,0,0), 2);
                img.copyTo(img2);
                imshow("windows", img2);
                waitKey(0);
                break;
            }
        }
        L.push_back(point[i]);
    }
    line(img, Point(250 + L[L.size() - 2].x * 2, 250 - L[L.size() - 2].y * 2), Point(250 + point.front().x * 2, 250 - point.front().y * 2), Scalar(0,0,0), 2);
    img.copyTo(img2);
    imshow("windows", img2);
    waitKey(0);
}

lint Cross_Product(lint x1, lint y1, lint x2, lint y2){
    return (x1 * y2) - (x2 * y1);
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);


    img.copyTo(img2);

    cin >> n;
    for(lint i = 1; i <= n; i++){
        rec.ID = i;
        cin >> rec.x >> rec.y;

        circle(img, Point(250 + rec.x * 2, 250 + -rec.y * 2), 2, Scalar(0, 0, 0), -1);

        point.push_back(rec);
    }
    img.copyTo(img2);

    imshow("windows", img2);
    waitKey(0);

    if(n == 1){
        cout << "1\n1\n";
        return 0;
    }
    sort(point.begin(), point.end(), cmp);
    Upper_Hull();
    Lower_Hull();

    cout << U.size() + L.size() - 1 << "\n";
    for(auto po: U) cout << po.ID << " ";
    for(int i = 1; i < L.size(); i++)
        cout << L[i].ID << " ";


    cout << "\n";
    return 0;
}
