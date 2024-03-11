/*----------------------------
获取核心网格外表面集合
获取表面单元
------------------------------
*/
#pragma once
#include"tree_class.h"
#include"OcTree.h"

class myCompare
{
public:
	//重载（）
	bool operator()(const Point3D& p1, const Point3D& p2)const
	{
		bool i = false;
		if (p1.x != p2.x) {
			i = p1.x < p2.x;
		}
		else if (p1.y != p2.y) {
			i = p1.y < p2.y;
		}
		else if (p1.z != p2.z) {
			i = p1.z < p2.z;
		}
		return i;


		//if (p1.x != p2.x) { return p1.x < p2.x; }
		//else if (p1.y != p2.y) { return p1.y < p2.y; }
		//else if (p1.z != p2.z) { return p1.z < p2.z; }
		//return i;
	}
};

class get_Surface
{
public:
	//读取所有节点并识别出外表面
	get_Surface(vector<Hexahedral3D*>& nodes, My_Voxel& _vox);
	//获取表面单元
	void get_SurNode();

	//优化1 边界单元 内点-拟合点边
	Point3D optimize(Point3D p, Vec3D v);

	//优化2 边界单元 拟合点-拟合点
	void optimize2();
	//优化3
	void optimize3();


	~get_Surface();
private:
	//判断是否为外表面
	bool out_face(Hexahedral3D* node, int direction);
	//点与单元所属关系
	bool out_face_index(Point3D* point);

	vector<vector<Point>> Obtain_contours(const cv::Mat& image_index);

	vector<Point2f> BSplineFit(vector<Point2f> discretePoints, bool closed, double stride = 0.01);
	vector<Point3f> BSplineFit3D(std::vector<Point3f> discretePoints, bool closed, double stride);
	vector<Point2f> GetBSpline(const cv::Mat& image_index);
	vector<Point3f> Get3DBSpline(My_Voxel& _vox);
	bool jud_Surface(Face3D* face1, Face3D* face2,int i);
	void get_faces();
	Face3D* neighbour_faces(Point3D* p, Face3D* face);
	bool jud_crop(Point3D* p);
	Face3D* jud_point(Face3D* p);
	Point3D* find_point(Face3D* face1, Face3D* face2, Face3D* face3);
	bool get_cos(Vec3D vec1, Vec3D vec2);

	vector<Point2f> generateLinePoints(const cv::Point2f& start, const cv::Point2f& end);
	void normalize1(double& x, double& y, double& z);
	float determinant(const Point3D& p1, const Point3D& p2, const Point3D& p3);
	float Scaled_Jacobian(Point3D p0, Point3D p1, Point3D p2, Point3D p3, Point3D p4, Point3D p5, Point3D p6, Point3D p7);
	//尝试哈希表提高查询效率
	//获取点向量
	Vec3D* point_vec(Point3D* point); 
	//检测点面所属关系
	bool check(Face3D* face, Point3D* point);
	double distance2(const Point& p1, double x, double y);
	//二维空间中直线与图像轮廓的交点
	Point3D* get_outline_point(Point3D* point, Vec3D vec_p, int index);
	Point3D* get_outline_point_spe(Point3D* point, Vec3D vec_p, int index, Face3D* face1);
	//三维空间中两直线交点
	Point3D* get_intersection_point(Point3D* p1, Point3D* p2, Point3D* p3, Point3D* p4);
	//求对应边界点
	Point3D* get_fit_point(Point3D* point, Vec3D vec_p);
	
	//两点距离的平方
	double distance(Point3D* p1, Point3D* p2)
	{
		double dis = (p1->x - p2->x) * (p1->x - p2->x) +
			(p1->y - p2->y) * (p1->y - p2->y) +
			(p1->z - p2->z) * (p1->z - p2->z);
		return dis;
	}
	
	float distance3(const cv::Point2f& p1, const cv::Point2f& p2) {
		return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
	}
public:
	//存储识别出的表面面片
	vector<Face3D*> sur_faces;

	//储存法向量为z的表面
	vector<Face3D*> sur_faces_z;
	//储存网格
	vector<Face3D*> all_sur_faces_z;
	//待处理外表面2
	vector<Face3D*> need_faces_double;
	vector<Face3D*> faces_double_z;
	//待处理外表面1
	vector<Face3D*> need_faces_single;
	unordered_set<Face3D*> need_faces_single1;
	vector<Face3D*> neighbour_faces_single;
	//未拟合的面片
	vector<Face3D*> fail_faces;
	//得到最后的表面节点
	vector<Hexahedral3D*> sur_nodes;
	//需要调节的边界单元
	vector<Hexahedral3D*> poor_nodes;
	//待调节点数组
	vector<Point3D*> poor_point;
	set<Point3D, myCompare> poor_point_hash;

	//传递单元的0顶点哈希表
	set<Point3D, myCompare> nodeHash;
	//构建共享同一点的单元数组哈希表，用于查询共享某一点的单元，  2022.4.21
	map<Point3D, vector<Hexahedral3D*>, myCompare> pointHash;
	//点对应向量的哈希表 2022.4.23
	map<Point3D, Vec3D, myCompare> vecHash;

	//点对应单位向量的哈希表 2022.5.26
	map<Point3D, Vec3D, myCompare> unitVecHash;
	//点坐标对应相邻点
	map<Point3D, vector<Point3D*>, myCompare> broPoint;
	//拟合点对应待调节点
	map<Point3D, vector<Point3D*>, myCompare> optPoint;

	//层间距
	My_Voxel& vox;

	//--------------------------------------------------------------待补全2023.3.22
//设置<index,vector<Point>>的哈希表存储单张CT切片图像的角点数组，用数组序列索引进行查找
	unordered_map<int, vector<Point>> GoodFeatures;


	//计算两个二维点的距离
	double Distance_Two2Dpoint(Point2d p1, Point2d p2);

	//使用tomasi算法求单张切片图像上的特征点
	void Get_TotomasiFeatures(int index, int MaxCornerNumber);//传入表示图片序数的int数据,想要求取的最大角点数量

	//计算出轮廓最近点
	Point Get_NearestPT(vector<Point>GoodFeatures, Point it, double r);//传入轮廓、点坐标和半径

	//查找距离特征点最近的点的距离
	double Dis_goodfeatures(vector<Point>& GoodFeatures, Point it);

	//将拟合到的特征点弹出防止重复拟合
	void delete_goodfeatures(vector<Point>& GoodFeatures, Point it);
	
	//计算一个外表面点共享片面数量
	int num_face(Point3D* point);
};

