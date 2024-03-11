#include"Voxel.h"
My_Voxel::My_Voxel(unsigned int _interval,int length)
{
	this->Interval_m = _interval;
	//this->get_images();
	//this->img_long = this->getMaxLenthOne(this->AllImage_m[0]);
	//this->cols = this->AllImage_m[0].cols;
	//this->rows = this->AllImage_m[0].rows;
}


My_Voxel::~My_Voxel()
{

}

unsigned int My_Voxel::getMaxLenthOne(Mat& _image)
{
	unsigned int col = _image.cols;
	unsigned int row = _image.rows;
	row = row > col ? row : col;
	return row;
}

unsigned int My_Voxel::getMaxLenthAll()
{
	return getMaxLenthOne(AllImage_m[0]) > AllImage_m.size() ? getMaxLenthOne(AllImage_m[0]) : AllImage_m.size();
	/*unsigned int max_lenth = 0;
	vector<unsigned int>* M_L = new vector<unsigned int>;
	for (vector<Mat>::iterator i = this->AllImage_m.begin(); i != this->AllImage_m.end(); i++)
	{
		M_L->push_back(getMaxLenthOne(*i));
	}
	for (vector<unsigned int>::iterator i = M_L->begin(); i != M_L->end(); i++)
	{
		max_lenth = *i > max_lenth ? *i : max_lenth;
	}
	delete M_L;
	return max_lenth;*/
}

unsigned int My_Voxel::getInterval()
{
	return this->Interval_m;
}

//获取图片
void My_Voxel::get_images()
{
	string path = "D:\\picture\\CTpicture\\*.jpg";
	std::cout << "读取路径：" << path << endl;
	vector<String> fn;
	cv::glob(path, fn, false);
	size_t count = fn.size();
	std::cout << "读取图片张数：" << count << endl;	
	//按照图片编号顺序进行读图
	vector<Mat> images; //储存原始图片
	vector<Mat> imgGray; //储存进行二值化后的灰度图片

	for (int i = 1; i < count+1; i++) 
	{
		string name = "D:\\picture\\CTpicture\\" + to_string(i) + ".jpg";//这里是你的文件路径以及文件名
		Mat img = imread(name);
		cout << "name: " << name << endl;

		if (img.empty()) //判断是否读进有效图片
		{
			cout << "Please input image path" << endl;
			return;
		}
		images.push_back(img);
	}
#if 0
	//绝对路径
	string path = "C:\\Users\\xushu\\Desktop\\课题文件\\CT\\*.jpg";
	std::cout << "读取路径：" << path << endl;
	vector<Mat> images;
	vector<Mat> imgGray;
	//cv::String 为 cv 中的字符串类型
	vector<String> fn;
	glob(path, fn, false);
	size_t count = fn.size();
	std::cout << "读取图片张数：" << count << endl;
	for (int i = 0; i < count; i++)
	{
		if (!imread(fn[i]).data)
		{
			cout << "Please input image path" << endl;
			return;
		}
		images.push_back(imread(fn[i]));
	}
#endif

#if 0
	for (int i = 0; i < images.size(); i++)
	{

		Mat* img_G = new Mat;
		Mat* relt = new Mat;
		//灰度化
		cvtColor(images[i], *img_G, COLOR_BGR2GRAY);
		imgGray.push_back(*img_G);
		//二值化
		threshold(imgGray[i], *relt, 150, 255, THRESH_BINARY);
		AllImage_m.push_back(*relt);
		delete img_G;
		delete relt;
	}
#endif


#if 1
	for (int i = 0; i < images.size(); i++)
	{
		Mat* img_G = new Mat;
		//灰度化
		cvtColor(images[i], *img_G, COLOR_BGR2GRAY);
		imgGray.push_back(*img_G);


		AllImage_m.push_back(*img_G);
	}
#endif
}