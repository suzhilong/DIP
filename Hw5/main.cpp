//
//  main.cpp
//  DIP_Hw5
//
//  Created by SOUSIC on 2019/5/15.
//  Copyright © 2019 SOUSIC. All rights reserved.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>

#define PATH "/Users/sousic/code/cpp/DIP/Hw5/"


cv::Mat subWTH(cv::Mat srcImg,int kerSize)
{//得到kerSize的WTH相减后的图片
    cv::Mat WTHImg, binWTHImg;
    cv::Mat WTHImg2, binWTHImg2;
    cv::Mat result;
    
    //kerSize-1
    cv::Mat kernel1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kerSize-1, kerSize-1));
    morphologyEx(srcImg, WTHImg, cv::MORPH_TOPHAT, kernel1);//WTH of origin
    cvtColor(WTHImg, WTHImg, CV_BGR2GRAY);//灰度化
    threshold(WTHImg, binWTHImg, 15, 255, CV_THRESH_BINARY);//灰度阈值处理

    //kerSize+1
    cv::Mat kernel2 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kerSize+1, kerSize+1));
    morphologyEx(srcImg, WTHImg2, cv::MORPH_TOPHAT, kernel2);//WTH of origin
    cvtColor(WTHImg2, WTHImg2, CV_BGR2GRAY);//灰度化
    threshold(WTHImg2, binWTHImg2, 15, 255, CV_THRESH_BINARY);//灰度阈值处理
    
    //sub
    cv::subtract(WTHImg2,WTHImg,result);
    threshold(result, result, 20, 255, CV_THRESH_OTSU);//灰度阈值处理
    //cv::imshow(std::to_string(kerSize+2)+"-"+std::to_string(kerSize),result);
    return result;
}

void open(cv::Mat srcImg,int kerSize,bool wr=false)
{
    /*
     
     */
    cv::Mat openImg;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(kerSize,kerSize));
    morphologyEx(srcImg, openImg, cv::MORPH_OPEN, kernel);
    //cv::imshow("open"+std::to_string(kerSize),openImg);
    if (wr==true)
    {
        std::string folder = "opt/open/";
        cv::imwrite(PATH + folder + std::to_string(kerSize)+".jpg",openImg);
    }
}

void getSubWTH(bool wr=false){//得到不同尺寸的subWTH
    std::string path = PATH;
    cv::Mat srcImg = cv::imread(path+"Chapter5_1.bmp");
    for (int kerSize = 3; kerSize < 52; kerSize+=3)
    {
        cv::Mat result = subWTH(srcImg,kerSize);
        
        if (wr==true) {//save
            std::string folder="/opt/WTH/";
            cv::imwrite(PATH + folder + std::to_string(kerSize)+".jpg",result);
        }
    }
}

void getWTH(){
    std::string path = PATH;
    cv::Mat srcImg = cv::imread(path+"Chapter5_1.bmp");
    cv::Mat WTHImg1, binWTHImg1;
    cv::Mat WTHImg2, binWTHImg2;
    for (int kerSize=3; kerSize<52; kerSize+=3) {
        cv::Mat kernel1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kerSize-1, kerSize-1));
        cv::Mat kernel2 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kerSize+1, kerSize+1));
        morphologyEx(srcImg, WTHImg1, cv::MORPH_TOPHAT, kernel1);//WTH of origin
        cvtColor(WTHImg1, WTHImg1, CV_BGR2GRAY);//灰度化
        threshold(WTHImg1, binWTHImg1, 60, 255, CV_THRESH_BINARY);//灰度阈值处理
        morphologyEx(srcImg, WTHImg2, cv::MORPH_TOPHAT, kernel2);//WTH of origin
        cvtColor(WTHImg2, WTHImg2, CV_BGR2GRAY);//灰度化
        threshold(WTHImg2, binWTHImg2, 40, 255, CV_THRESH_BINARY);//灰度阈值处理
        
        std::string orifolder="/opt/oriWTH/";
        cv::imwrite(PATH + orifolder + std::to_string(kerSize-1)+".jpg",WTHImg1);
        cv::imwrite(PATH + orifolder + std::to_string(kerSize+1)+".jpg",WTHImg2);
        std::string binfolder="/opt/binWTH/";
        cv::imwrite(PATH + binfolder + std::to_string(kerSize-1)+".jpg",binWTHImg1);
        cv::imwrite(PATH + binfolder + std::to_string(kerSize+1)+".jpg",binWTHImg2);
    }
}

int getBalls(cv::Mat img,int kerSize){
    //计算亮点的数量
    int n = 0;//亮点的数量
    int row = img.rows;            //获取行数目；
    int col = img.cols;            //获取列数目；
    //int chan = img.channels();  //获取通道数目；
    for (int i = 0; i<row; i++) {
        for (int j = 0; j<col; j++) {
            int v =img.at<uchar>(i,j);
            if (v>128) {
                n++;
            }
        }
    }
    //kernel的面积
    int s = kerSize*kerSize;
    //亮像素点总数除以kernel的面积得到球的数量
    int balls = n / s;
    return balls;
}

int main()
{
    getWTH();//保存原WTH的灰度图和二值图
    
    getSubWTH(true);//保存相减后的WTH图

    std::string path = PATH;
    cv::Mat srcImg = cv::imread(path+"Chapter5_1.bmp");

    std::ofstream writer;
    std::string filename = "opt/ballsDis.txt";
    writer.open(PATH+filename);
    cv::Mat subImg;
    for (int kerSize=3; kerSize<52; kerSize+=3) {

        //白帽子相减
        subImg = subWTH(srcImg,kerSize);
        //计算球的数量
        int balls = getBalls(subImg, kerSize);
        //std::cout <<kerSize<<":"<<balls<<std::endl;
        writer << kerSize<<":"<<balls <<"\n";
    }
    writer.close();
    
    cv::waitKey(0);
    return 0;
}


