#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include<string>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("D:/packages/img/RM.png");
    if (img.empty()) {
        cout << "读取图片失败" << endl;
        return -1; }


    Mat gray,  img32;

    img.convertTo(img32, CV_32F, 1.0 / 255);  //将CV_8U转为CV_32F

    cvtColor(img32, gray, COLOR_BGR2GRAY); //转为灰度图
    imwrite("D:/packages/img/gray.jpg", gray*255);


     //添加高斯滤波
        Mat srcImage = imread("D:/packages/img/gray.jpg");
        Mat dstImage;
        GaussianBlur(srcImage, dstImage, Size(3, 3), 0, 0);
        //imshow("gaussianblured.jpg", dstImage);
      imwrite("D:/packages/img/dstImage.jpg", dstImage);


     //对得到的转换图二值化并显示

    Mat img2=imread("D:/packages/img/dstImage.jpg");
    cvtColor(img2,gray,COLOR_BGR2GRAY);
    Mat gray_B,gray_B_V;

    threshold(gray,gray_B,125,255,THRESH_BINARY);
    threshold(gray,gray_B_V,125,255,THRESH_BINARY_INV);
    imshow("gray_B",gray_B);
    imshow("gray_B_V",gray_B_V);


    waitKey(0);
    return 0;
}
