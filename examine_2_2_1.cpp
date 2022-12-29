#include <opencv2/opencv.hpp>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;


Mat imgOriginal;

int iLowH = 100;
int iHighH = 140;

int iLowS = 90;
int iHighS = 255;

int iLowV = 90;
int iHighV = 255;

void callback(int, void*);
int main()
{
    namedWindow("hsv", WINDOW_AUTOSIZE); //create a window called "Control"


    imgOriginal = imread("D:/packages/img/RM.png");
    resize(imgOriginal, imgOriginal, Size(400, 300));
    imshow("Original", imgOriginal); //show the original image

    //Create trackbars in "hsv" window
    createTrackbar("h-min", "hsv", &iLowH, 179, callback,0); //Hue (0 - 179)
    createTrackbar("h-max", "hsv", &iHighH, 179, callback,0);

    createTrackbar("s-min", "hsv", &iLowS, 255, callback,0); //Saturation (0 - 255)
    createTrackbar("s-max", "hsv", &iHighS, 255, callback,0);

    createTrackbar("v-min", "hsv", &iLowV, 255, callback,0); //Value (0 - 255)
    createTrackbar("v-max", "hsv", &iHighV, 255, callback,0);

    waitKey(0);

    return 0;

}

void callback(int ,void*)
{
    Mat imgHSV;
    vector<Mat> hsvSplit;
    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

                                                  //因为我们读取的是彩色图，直方图均衡化需要在HSV空间做
    split(imgHSV, hsvSplit);
    equalizeHist(hsvSplit[2], hsvSplit[2]);
    merge(hsvSplit, imgHSV);
    Mat imgThresholded;

    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

                                                                                                  //开操作 (去除一些噪点)
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);

    //闭操作 (连接一些连通域)
    morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);

    imshow("hsv", imgThresholded); //show the thresholded image
}




















































































