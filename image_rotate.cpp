#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<iostream> 
#include<math.h>
#include<fstream>
#include<string>

using namespace cv;

#define SCALE 1   //缩放比例  

//interpolation seting,can look up the Enumerator in opencv document
//if set '0' it is nearest neighbor interpolation,
//if set '1' it is bilinear interpolation,
//if set '2' it is bicubic interpolation,
//if set '3' it is area-based (or super) interpolation,
//if set '4' it is Lanczos interpolation over 8x8 neighborhood.

Mat imgRotate(Mat srcMat,int angle,int interpolation)
{
	double pi_angle = abs(angle * CV_PI / 180);//cos sin 函数需要用弧度值
	double w = 0., h = 0., w_r = 0., h_r = 0.;

	h = srcMat.rows;
	w = srcMat.cols;
	w_r = w*cos(pi_angle) + h*sin(pi_angle);//输出图像的宽
	h_r = h*cos(pi_angle) + w*sin(pi_angle);//输出图像的高
  
	Mat tempImg(h_r, w_r, srcMat.type(), Scalar(0));
	int roi_x = w_r / 2 - srcMat.cols / 2;//roi左上角的x坐标
	int roi_y = h_r / 2 - srcMat.rows / 2;//roi左上角的y坐标
	Rect roiRect(roi_x, roi_y, srcMat.cols, srcMat.rows);//roi矩形
	Mat tempImgRoi(tempImg, roiRect);//tempImg的中间部分，与原Mat关联，并不会创建一个新Mat
	srcMat.copyTo(tempImgRoi);//将原图复制到tempImg的中心  

	Point2f center(w_r / 2, h_r / 2);//旋转中心  
	Mat trans = getRotationMatrix2D(center, angle, SCALE);//计算旋转的仿射变换矩阵  

	std::cout << "变换矩阵：" << std::endl;
	std::cout << trans.at<double>(0, 0) << "," 
                << trans.at<double>(0, 1) << "," 
                << trans.at<double>(0, 2) << "," 
                << std::endl;
	std::cout << trans.at<double>(1, 0) << "," 
                << trans.at<double>(1, 1) << "," 
                << trans.at<double>(1, 2) << "," 
                << std::endl;

    Mat dstMat;//旋转后的图像
	warpAffine(tempImg, dstMat, trans, Size(w_r, h_r), interpolation);//仿射变换

	return dstMat;

}

Mat imgRotateBack(Mat origin ,Mat src, int angle, int interpolation)
{
	double w = 0., h = 0.;

	h = src.rows;
	w = src.cols;
	
	Point2f center(w / 2, h / 2);//旋转中心  
	Mat trans = getRotationMatrix2D(center, angle, SCALE);//计算旋转的仿射变换矩阵  

	std::cout << "变换矩阵：" << std::endl;
	std::cout << trans.at<double>(0, 0) << "," 
                << trans.at<double>(0, 1) << "," 
                << trans.at<double>(0, 2) << "," 
                << std::endl;
	std::cout << trans.at<double>(1, 0) << "," 
                << trans.at<double>(1, 1) << "," 
                << trans.at<double>(1, 2) << ","
                << std::endl;

    Mat dst_2;//旋转后的图像
	warpAffine(src, dst_2, trans, Size(w, h), interpolation);//仿射变换 

	int roi_x = w / 2 - origin.cols / 2;//roi左上角的x坐标  
	int roi_y = h / 2 - origin.rows / 2;//roi左上角的y坐标  
	Rect roiRect(roi_x, roi_y, origin.cols, origin.rows);//roi矩形  
	Mat tempImgRoi(dst_2, roiRect);//dst_2的中间部分
	std::cout << "rotate back img_columns: " << tempImgRoi.cols << std::endl;
	std::cout << "rotate back img_rows: " << tempImgRoi.rows << std::endl;
	return tempImgRoi;
}

void saveTxt(Mat &image, std::string path, std::string txt_name)
{//存成txt文件
	std::ofstream writer;
	writer.open(path + txt_name + ".txt");
	
	Mat input_image = image.clone();//复制实参到临时变量
	int n_r = input_image.rows;
	//列数*通道数等于每一行元素的个数
	int n_c = input_image.cols * input_image.channels(); 
	for (int j = 0; j<n_r; j++)
	{
		uchar* data = input_image.ptr<uchar>(j);
		for (int i = 0; i<n_c; i++)
		{
			if (writer.is_open())
			{
				writer << (int)data[i] << ","; //程序中处理的数据
				//writer.close();
			}
			else
			{
				std::cout << "不能打开文件!" << std::endl;
			}
			//std::cout << (int)data[i] << ",";
		}
		if (writer.is_open())
		{
			writer << std::endl; //message是程序中处理的数据
			//writer.close();
		}
		else
		{
			std::cout << "不能打开文件!" << std::endl;
		}
		//std::cout << std::endl;
	}
	writer.close();
    std::cout<< "img_txt saved." << std::endl;
}

int main()
{
	std::string path = "/home/su/code/DIP/";
    std::string savePath = "opt/";
    Mat origin = imread(path+"Chapter2_1.pgm", 0);
    
    for(int interpolation = 0; interpolation < 5; interpolation++)
    {
        std::string txt_src = "Chapter2_1_interpolation_" + std::to_string(interpolation);
        std::string txt_rotateBack = "img_rotate_interpolation_" + std::to_string(interpolation);

        std::cout << "src_img columns: " << origin.cols << std::endl;
        std::cout << "src_img rows: " << origin.rows << std::endl;

        saveTxt(origin, path+savePath , txt_src);

        //旋转角度(正值表示逆时针旋转)
        int angle_1 = -15;
        int angle_2 = 15;

        Mat rotatedImg = imgRotate(origin,angle_1,interpolation);
        Mat rotateBack = imgRotateBack(origin, rotatedImg, angle_2, interpolation);

        saveTxt(rotateBack, path+savePath , txt_rotateBack);

        // imshow("src", origin);
        // imshow("rotated", rotatedImg);
        // imshow("rotateBack", rotateBack);
        
        // 保存图像
        imwrite(path + savePath + "rotated_"+std::to_string(interpolation)+".jpg", rotatedImg);
        imwrite(path + savePath + "rotatedBack_"+std::to_string(interpolation)+".jpg", rotateBack);
    }

	waitKey(0);
	return 0;
}