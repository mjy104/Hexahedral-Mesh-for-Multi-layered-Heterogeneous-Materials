/*----------------------------
读取所有图片形成体数据
------------------------------
*/

#pragma once
#include"tree_class.h"

//整个体
class My_Voxel
{
public:
	My_Voxel(unsigned int _interval,int length);
	~My_Voxel();
	unsigned int getMaxLenthAll();//获取最大尺寸
	unsigned int getInterval(); //获取图片间隔

private:
	unsigned int getMaxLenthOne(Mat& _image);
	void get_images(); //获取图片

public:
	vector<Mat> AllImage_m; //所有图片的矩阵数组
	unsigned int cols; //长
	unsigned int rows; //宽
	unsigned int minlenth;
	//int img_long;

private:
	unsigned int Interval_m; //图片间隔
	unsigned int MaxLenthAll_m; //
};