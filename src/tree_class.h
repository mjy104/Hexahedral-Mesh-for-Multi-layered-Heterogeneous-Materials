/*
八叉树：八叉树节点、点、体、线
*/
#pragma once
#pragma warning(disable:4996)
#include<vcruntime.h>
#include <iostream>
#include <fstream> 
#include<vector>
#include <stdlib.h>
#include<Windows.h>
#include <assert.h>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp> 
#include <opencv2/highgui/highgui_c.h>
#include<math.h>
#include<set>
#include<map>
#include<unordered_set>
#include<unordered_map>
#include<stack>

//opencascade头文件
//#include <gp_Circ.hxx>
//#include <gp_Elips.hxx>
//#include <gp_Sphere.hxx>
//
//#include <Poly_Polygon3D.hxx>
//#include <Poly_Triangulation.hxx>
//
//#include <TopTools_ListIteratorOfListOfShape.hxx>
//#include <TopTools_HSequenceOfShape.hxx>
//
//#include <BRepBuilderAPI_MakeVertex.hxx>
//#include <BRepBuilderAPI_MakeEdge.hxx>
//
//#include <TopoDS_Edge.hxx>
//#include <TopoDS_Face.hxx>
//#include <TopoDS.hxx>
//
//#include <BRep_Tool.hxx>
//#include <BRepMesh.hxx>
//#include <BRepMesh_IncrementalMesh.hxx>
//#include <BRepBuilderAPI_MakeEdge.hxx>
//#include <BRepBuilderAPI_MakeFace.hxx>
//
//#include <BRepAdaptor_Curve.hxx>
//#include <GCPnts_TangentialDeflection.hxx>
//#include <TopExp_Explorer.hxx>
//#include <Standard_TypeDef.hxx>

//vtk lib
#include <vtkcamera.h>
#include <vtkfloatarray.h>
#include <vtkpointdata.h>
#include <vtkinteractorstyletrackballactor.h>
#include <vtkextractedges.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkMath.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkAutoInit.h>
#include <vtkObjectFactory.h>
#include <vtkPropPicker.h>
//VTK显示坐标轴
#include <vtkAxesActor.h>
#include <vtkLineSource.h>
#include <vtkAxis.h>
#include <vtkAxes.h>
#include <vtkConeSource.h>
#include <vtkCaptionActor2D.h>

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackball.h>  
#include <vtkInteractorStyleTrackballCamera.h>  
#include <vtkProperty.h>
#include <vtkTriangle.h>
#include <vtkSTLReader.h>

//进行旋转操作所需的头文件
//vtkTransform, vtkTransformFilter, vtkMatrix4x4
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <vtkMatrix4x4.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);

extern unsigned int max_lenth;//最大长度 全局变量
using namespace cv;
using namespace std;

class OcTreeNode//八叉树节点类
{
public:
	//默认构造
	//OcTreeNode();
	//构造函数
	OcTreeNode(unsigned int _x, unsigned int _y, unsigned int _z,
				bool _isfull, unsigned int _lenth, string _ID);
	//拷贝构造
	//OcTreeNode(const OcTreeNode& other);
	//拷贝赋值运算符重载
	//OcTreeNode& operator = (const OcTreeNode& other);
	//析构函数
	~OcTreeNode();


public:
	OcTreeNode* node[8];//子节点数组指针
	string ID;//节点id
	bool isfull;
	//bool done;
	unsigned x;//x坐标
	unsigned y;//y坐标
	unsigned z;//z坐标
	unsigned lenth;//长度
};

struct Point3D//三维点结构体
{
public:
	Point3D();//构造函数
	Point3D(const Point3D& other);//拷贝函数
	Point3D(double _x, double _y, double _z);
	Point3D& operator = (const Point3D& p);
	~Point3D();
public:
	unsigned int index;
	double x;
	double y;
	double z;
	vector<unsigned int>LineIndex;//线索引
	vector<unsigned int>HexIndex;//节点索引
};

struct Vec3D //三维向量
{
	Vec3D();
	Vec3D(const Vec3D& other);
	Vec3D(double _i, double _j, double _k);
	Vec3D(Point3D* _p0, Point3D* _p1, Point3D* _p2, Point3D* _p3);
	Vec3D& operator = (const Vec3D& v);
	Vec3D& operator + (const Vec3D& v);
	~Vec3D();
public:
	double i;//x方向分量
	double j;//y方向分量
	double k;//z方向分量
};

struct Face3D //三维面类，四个点，一个法向量
{
	Face3D(Point3D* _p0, Point3D* _p1, Point3D* _p2, Point3D* _p3);
	~Face3D();
public:
	Point3D* p[4];
	Vec3D* n;
};


//暂时不知道index的作用 2021.10.4
struct Hexahedral3D//六面体类
{
	Hexahedral3D(Point3D* _p1, Point3D* _p2, Point3D* _p3, Point3D* _p4,
		Point3D* _p5, Point3D* _p6, Point3D* _p7, Point3D* _p8, unsigned int index);
	~Hexahedral3D();
	void point_clear();
public:
	Point3D* p[8];
	Face3D* f[6];
	float max_slender;
	//float max_angle;//最大角
	//float min_angle;//最小角
	//float Jacobi;//雅可比矩阵
	//float skewness;//偏斜度

};

struct Line3D //F0(x) = a*x + b*y + c*z + d  平面直线类
{
	Line3D();
	Line3D(double _a, double _b, double _c, double _d, bool _IsAline);
	~Line3D();
public:
	double a;
	double b;
	double c;
	double d;
	bool IsAline;
};


