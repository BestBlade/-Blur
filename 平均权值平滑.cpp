/*
*����������������������������������������������������������������������������������������������������
*������    ��������ԭ���д����ʵ�־�ֵģ��													   ��
*������    �ߣ�Ĳ����|BestBlade																	   ��
*������    ����1.0																			   	   ��
*��������ʱ�䣺2020.07.10																		   ��
*����������������������������������������������������������������������������������������������������
*/

#include <iostream>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include"opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

int  Smooth_Blur(Mat origin_pic, Mat &result_pic,Size ksize)							/*	ע����ͼƬҪȡ��ַ������ͨ�������ı��������е�result_pic	*/
{
	int kw = ksize.width;
	int kh = ksize.height;

	result_pic = origin_pic.clone();													/*	����һ��ͼƬ����������ɶ����ز�����������޷���ͼƬ���ظ�ֵ	*/

	int row = origin_pic.rows;
	int col = origin_pic.cols;

	if ((row < kw) && (col < kh))
	{
		return -1;																		/*	ͼƬ�ߴ��С	*/
	}
	else
		if ((kw % 2 == 0) || (kh % 2 == 0))
		{
			return -2;																	/*	ƽ�����ڳߴ����	*/
		}
		else
		{
			int row_start = kw / 2;
			int col_start = kh / 2;

			for (int i = row_start; i < row - row_start; i++)
			{
				for (int j = col_start; j < col - col_start; j++)						/*	ѭ��ͼ���(i,j)������	*/
				{
					int channel_r = { 0 };
					int channel_g = { 0 };
					int channel_b = { 0 };

					for (int p = i - row_start; p <= i + row_start; p++)
					{
						for (int q = j - col_start; q <= j + col_start; q++)			/*	�ڵ�(i,j)������Χ��ksize(weight,height)�������м����ܺ�	*/
						{
							Vec3b pq = origin_pic.at<Vec3b>(p, q);						/*	����ǰ���ص�ֽ�Ϊ�ɲ�����rgbͨ����������	*/
							channel_r += pq[2];											/*	���ͨ�����ܺ�	*/
							channel_g += pq[1];
							channel_b += pq[0];
						}
					}

					result_pic.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(channel_b / (kw * kh));			/*	��saturate_cast���������Ա������ݲ����	*/
					result_pic.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(channel_g / (kw * kh));			/*	��һ����������	*/
					result_pic.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(channel_r / (kw * kh));
				}
			}
			return 0;
		}
}
int main()
{


	Mat origin_pic = imread("C:/Users/Chrysanthemum/Desktop/�ͻ��˿���.JPG");
	Mat result_pic;
	Size ksize(5,5);

	Smooth_Blur( origin_pic, result_pic, ksize);															/*	�Զ����ֵģ������	*/

	imshow("ԭͼ", origin_pic);
	imshow("5x5ƽ�����ͼ",result_pic);

	Mat result_pic_opencv_blur;
	blur(origin_pic, result_pic_opencv_blur, ksize, Point(-1, -1), BORDER_DEFAULT);					/*	OPENCV�Դ���ֵģ������	*/
	imshow("OPENCV blur() 3x3ƽ�����ͼ", result_pic_opencv_blur);	

	waitKey(0);
	//return 0;
}
