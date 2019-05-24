//
//  main.cpp
//  DIP
//
//  Created by SOUSIC on 2019/5/24.
//  Copyright © 2019 SOUSIC. All rights reserved.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>

cv::Mat ssProcess(cv::Mat,int);
cv::Mat preProcess(cv::Mat);

int main(int argc, const char * argv[]) {
    std::string path = "/Users/sousic/photo/bb.JPG";
    cv::Mat srcImg = cv::imread(path,0);//0代表读入灰度图
    //自己实现的均值滤波
    cv::Mat blurSs;
    blurSs = preProcess(srcImg);
    //Opencv的均值滤波
    cv::Mat blurCV;
    cv::blur(srcImg, blurCV, cv::Size(5, 5));
    //高斯滤波
    cv::Mat blurGau;
    cv::GaussianBlur(srcImg, blurGau, cv::Size(3,3), 0, 0);
    //自己实现的一些算子
    cv::Mat optImg = ssProcess(blurCV,4);
    //拉普拉斯
    cv::Mat temp,laplacianImg;
    cv::Laplacian(blurGau, temp, CV_16S, 3);  //通过拉普拉斯算子做边缘检测
    convertScaleAbs(temp, laplacianImg);
    //Canny边缘检测
    cv::Mat cannyImg;
    cv::Canny(blurGau, cannyImg, 50, 150);
    //Sobel
    cv::Mat grad_x, grad_y;
    cv::Mat abs_grad_x, abs_grad_y;
    cv::Mat sobelImg;
    cv::Sobel(blurGau, grad_x, CV_16S, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);  //轉成CV_8U
    cv::Sobel(blurGau, grad_y, CV_16S, 0, 1, 3, 1, 0, cv::BORDER_DEFAULT );
    convertScaleAbs(grad_y, abs_grad_y);
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, sobelImg);
    
    
//    cv::imshow("src",srcImg);
//    cv::imshow("cv blur",blurCV);
//    cv::imshow("ss blur",blurSs);
//    cv::imshow("Gaussain blur",blurGau);
//    cv::imshow("opt", optImg);
//    cv::imshow("laplacian", laplacianImg);
//    cv::imshow("canny", cannyImg);
//    cv::imshow("abs_grad_x", abs_grad_x);
//    cv::imshow("abs_grad_y", abs_grad_y);
    cv::imshow("Sobel", sobelImg);
    cv::waitKey(0);
    return 0;
}

cv::Mat preProcess(cv::Mat src){//5x5的均值滤波
    cv::Mat opt = cv::Mat::zeros(src.rows, src.cols, CV_8U);
    for (int i=3; i<src.rows-3; i++) {
        for (int j=3; j<src.cols-3; j++) {
            opt.at<uchar>(i,j)=(
                src.at<uchar>(i-2,j-2)+src.at<uchar>(i-2,j-1)+src.at<uchar>(i-2,j)+src.at<uchar>(i-2,j+1)+src.at<uchar>(i-2,j+2)+
                src.at<uchar>(i-1,j-2)+src.at<uchar>(i-1,j-1)+src.at<uchar>(i-1,j)+src.at<uchar>(i-1,j+1)+src.at<uchar>(i-1,j+2)+
                src.at<uchar>(i,j-2)+src.at<uchar>(i,j-1)+src.at<uchar>(i,j)+src.at<uchar>(i,j+1)+src.at<uchar>(i,j+2)+
                src.at<uchar>(i+1,j-2)+src.at<uchar>(i+1,j-1)+src.at<uchar>(i+1,j)+src.at<uchar>(i+1,j+1)+src.at<uchar>(i+1,j+2)+
                src.at<uchar>(i+2,j-2)+src.at<uchar>(i+2,j-1)+src.at<uchar>(i+2,j)+src.at<uchar>(i+2,j+1)+src.at<uchar>(i+2,j+2)
                                )/25;
        }
    }
    return opt;
}

cv::Mat ssProcess(cv::Mat src,int i){
    cv::Mat opt = cv::Mat::zeros(src.rows, src.cols, CV_8U);
    if (i==0) {
        return src;
    }
    else if (i==1){
//        Prewiit x
        for (int m=1; m<src.rows-1; m++) {
            for (int n=1; n<src.cols-1; n++) {
                opt.at<uchar>(m,n) =
                -src.at<uchar>(m-1,n-1)-src.at<uchar>(m,n-1)-src.at<uchar>(m+1,n-1)
                +src.at<uchar>(m-1,n+1)+src.at<uchar>(m,n+1)+src.at<uchar>(m+1,n+1);
            }
        }
    }
    else if (i==2){
//        Prewiit y
        for (int m=1; m<src.rows-1; m++) {
            for (int n=1; n<src.cols-1; n++) {
                opt.at<uchar>(m,n) =
                -src.at<uchar>(m-1,n-1)-src.at<uchar>(m-1,n)-src.at<uchar>(m-1,n+1)
                +src.at<uchar>(m+1,n-1)+src.at<uchar>(m+1,n)+src.at<uchar>(m+1,n+1);
            }
        }
    }
    else if (i==3){
//        Sober x
        for (int m=1; m<src.rows-1; m++) {
            for (int n=1; n<src.cols-1; n++) {
                opt.at<uchar>(m,n) =
                -src.at<uchar>(m-1,n-1)-2*src.at<uchar>(m,n-1)-src.at<uchar>(m+1,n-1)
                +src.at<uchar>(m-1,n+1)+2*src.at<uchar>(m,n+1)+src.at<uchar>(m+1,n+1);
            }
        }
    }
    else if (i==4){
//        Sober y
        for (int m=1; m<src.rows-1; m++) {
            for (int n=1; n<src.cols-1; n++) {
                opt.at<uchar>(m,n) =
                -src.at<uchar>(m-1,n-1)-2*src.at<uchar>(m-1,n)-src.at<uchar>(m-1,n+1)
                +src.at<uchar>(m+1,n-1)+2*src.at<uchar>(m+1,n)+src.at<uchar>(m+1,n+1);
            }
        }
        
    }
    return opt;
}
