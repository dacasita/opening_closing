#include <opencv2/opencv.hpp>
#include <iostream>     // std::cout
#include <algorithm>

using namespace cv;

cv::Mat dialation(cv::Mat imgIn)
{
    cv::Mat imgOut(imgIn.rows, imgIn.cols, CV_8UC1, cv::Scalar(0));
    for (int i = 1; i <= imgIn.rows - 2; i++) 
    {
        for (int j = 1; j <= imgIn.cols - 2; j++) 
        {
            uchar max_value = std::max(std::max(imgIn.at<uchar>(i, j), imgIn.at<uchar>(i, j-1)),
                          std::max(imgIn.at<uchar>(i, j+1), imgIn.at<uchar>(i-1, j)));
            imgOut.at<uchar>(i, j) = std::max(max_value, imgIn.at<uchar>(i+1, j));
        }
    }
    return imgOut;
}

cv::Mat dialationTime(cv::Mat imgIn, int num)
{
    cv::Mat imgOut = imgIn;
    for(int i = 1;i <= num; i++)
    {
        imgOut = dialation(imgOut);
    }
    return imgOut;
}

cv::Mat erosion(cv::Mat imgIn)
{
    cv::Mat imgOut(imgIn.rows, imgIn.cols, CV_8UC1, cv::Scalar(0));
    for (int i = 1; i <= imgIn.rows - 2; i++) 
    {
        for (int j = 1; j <= imgIn.cols - 2; j++) 
        {
            uchar min_value = std::min(std::min(imgIn.at<uchar>(i, j), imgIn.at<uchar>(i, j-1)),
                          std::min(imgIn.at<uchar>(i, j+1), imgIn.at<uchar>(i-1, j)));
            imgOut.at<uchar>(i, j) = std::min(min_value, imgIn.at<uchar>(i+1, j));
        }
    }
    return imgOut;
}

cv::Mat erosionTime(cv::Mat imgIn, int num)
{
    cv::Mat imgOut = imgIn;
    for(int i = 1;i <= num; i++)
    {
        imgOut = erosion(imgOut);
    }
    return imgOut;
}

int main() {
    cv::Mat img = imread("face.jpg", 0);
    cv::imshow("Origin", img);

    cv::Mat imgOut = dialationTime(img, 12);
    cv::imshow("img dialation", imgOut);

    imgOut = erosionTime(imgOut, 12);
    cv::imshow("img closing", imgOut);

    cv::Mat imgBeforeOpen = imread("open_ex.jpg", 0);
    cv::imshow("img Before Open", imgBeforeOpen);

    cv::Mat imgAfterOpen = erosionTime(imgBeforeOpen, 12);
    cv::imshow("img after erosion", imgAfterOpen);

    imgAfterOpen = dialationTime(imgAfterOpen, 12);
    cv::imshow("img after opening", imgAfterOpen);

    cv::waitKey(0); 
    cv::destroyAllWindows(); 

    return 0;
}

