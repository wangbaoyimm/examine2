#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/imgproc/imgproc_c.h>

using namespace cv;
using namespace std;

int main()
{

    Mat srcImage = imread("D:/packages/img/board.jpg");
    Mat midImage, dstImage;

    Canny(srcImage, midImage, 50, 200, 3);
    cvtColor(midImage, dstImage, COLOR_GRAY2BGR);

    vector <Vec2f> lines;
    HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);

    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1,CV_AA);
    }

    imshow("original", srcImage);

    imshow("canny", midImage);

    imshow("fruit", dstImage);

    waitKey(0);

    return 0;
}




















































