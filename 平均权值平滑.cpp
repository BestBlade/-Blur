/*
*┌────────────────────────────────────────────────┐
*│　描    述：根据原理编写程序，实现均值模糊													   │
*│　作    者：牟峙桦|BestBlade																	   │
*│　版    本：1.0																			   	   │
*│　创建时间：2020.07.10																		   │
*└────────────────────────────────────────────────┘
*/

#include <iostream>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include"opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

int  Smooth_Blur(Mat origin_pic, Mat &result_pic,Size ksize)							/*	注意结果图片要取地址，才能通过函数改变主函数中的result_pic	*/
{
	int kw = ksize.width;
	int kh = ksize.height;

	result_pic = origin_pic.clone();													/*	复制一份图片，以正常完成对像素操作，否则会无法对图片像素赋值	*/

	int row = origin_pic.rows;
	int col = origin_pic.cols;

	if ((row < kw) && (col < kh))
	{
		return -1;																		/*	图片尺寸过小	*/
	}
	else
		if ((kw % 2 == 0) || (kh % 2 == 0))
		{
			return -2;																	/*	平滑窗口尺寸错误	*/
		}
		else
		{
			int row_start = kw / 2;
			int col_start = kh / 2;

			for (int i = row_start; i < row - row_start; i++)
			{
				for (int j = col_start; j < col - col_start; j++)						/*	循环图像第(i,j)个像素	*/
				{
					int channel_r = { 0 };
					int channel_g = { 0 };
					int channel_b = { 0 };

					for (int p = i - row_start; p <= i + row_start; p++)
					{
						for (int q = j - col_start; q <= j + col_start; q++)			/*	在第(i,j)像素周围的ksize(weight,height)个像素中计算总和	*/
						{
							Vec3b pq = origin_pic.at<Vec3b>(p, q);						/*	将当前像素点分解为可操作的rgb通道数据类型	*/
							channel_r += pq[2];											/*	求各通道的总和	*/
							channel_g += pq[1];
							channel_b += pq[0];
						}
					}

					result_pic.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(channel_b / (kw * kh));			/*	『saturate_cast』函数可以保护数据不溢出	*/
					result_pic.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(channel_g / (kw * kh));			/*	归一化重组像素	*/
					result_pic.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(channel_r / (kw * kh));
				}
			}
			return 0;
		}
}
int main()
{


	Mat origin_pic = imread("C:/Users/Chrysanthemum/Desktop/客户端开发.JPG");
	Mat result_pic;
	Size ksize(5,5);

	Smooth_Blur( origin_pic, result_pic, ksize);															/*	自定义均值模糊函数	*/

	imshow("原图", origin_pic);
	imshow("5x5平滑结果图",result_pic);

	Mat result_pic_opencv_blur;
	blur(origin_pic, result_pic_opencv_blur, ksize, Point(-1, -1), BORDER_DEFAULT);					/*	OPENCV自带均值模糊函数	*/
	imshow("OPENCV blur() 3x3平滑结果图", result_pic_opencv_blur);	

	waitKey(0);
	//return 0;
}
