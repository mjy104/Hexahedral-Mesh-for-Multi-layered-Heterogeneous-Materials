#include"tree_class.h"
Point3D::Point3D()
{
    //构造函数 初值为0
    this->index = 0;
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

Point3D::Point3D(const Point3D& other)
{
    //将当前点属性赋值进来
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->index = other.index;
}

Point3D::Point3D(double _x, double _y, double _z)
{
    this->x = _x;
    this->y = _y;
    this->z = _z;
    this->index = 0;
}

Point3D& Point3D::operator = (const Point3D& p)
{
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
    this->index = p.index;
    return *this;
}

Point3D::~Point3D() {}


Hexahedral3D::Hexahedral3D(Point3D* _p1, Point3D* _p2, Point3D* _p3, Point3D* _p4,
    Point3D* _p5, Point3D* _p6, Point3D* _p7, Point3D* _p8, unsigned int index)
{
    max_slender = 0;
    //max_angle = 0;
    //min_angle = 450;
    //Jacobi = 0;
    //skewness = 0;

    //三维点编号
    this->p[0] = _p1;
    this->p[1] = _p2;
    this->p[2] = _p3;
    this->p[3] = _p4;
    this->p[4] = _p5;
    this->p[5] = _p6;
    this->p[6] = _p7;
    this->p[7] = _p8;

    //构造面
    this->f[0] = new Face3D(this->p[0], this->p[1], this->p[5], this->p[4]);
    this->f[1] = new Face3D(this->p[1], this->p[2], this->p[6], this->p[5]);
    this->f[2] = new Face3D(this->p[2], this->p[3], this->p[7], this->p[6]);
    this->f[3] = new Face3D(this->p[3], this->p[0], this->p[4], this->p[7]);
    this->f[4] = new Face3D(this->p[4], this->p[5], this->p[6], this->p[7]);
    this->f[5] = new Face3D(this->p[0], this->p[3], this->p[2], this->p[1]);

    //将索引放进面索引容器
    for (short i = 0; i < 8; i++)
        p[i]->HexIndex.push_back(index);

}
void Hexahedral3D::point_clear()
{
    //3D点清除  将索引容器清空
    for (short i = 0; i < 8; i++)
        p[i]->HexIndex.pop_back();
}

Hexahedral3D::~Hexahedral3D() {}

Line3D::Line3D()
{
    this->a = 0.0;
    this->b = 0.0;
    this->c = 0.0;
    this->d = 0.0;
    IsAline = false;
}

Line3D::Line3D(double _a, double _b, double _c, double _d, bool _IsAline)
{
    //线表达式常数赋值
    this->a = _a;
    this->b = _b;
    this->c = _c;
    this->d = _d;
    this->IsAline = _IsAline;
}

Line3D::~Line3D()
{
}

Vec3D::Vec3D()
{
    this->i = 0.0;
    this->j = 0.0;
    this->k = 0.0;
}

Vec3D::Vec3D(const Vec3D& other)
{
    this->i = other.i;
    this->j = other.j;
    this->k = other.k;
}

Vec3D::Vec3D(double _i, double _j, double _k)
{
    this->i = _i;
    this->j = _j;
    this->k = _k;
}

Vec3D::Vec3D(Point3D* _p0, Point3D* _p1, Point3D* _p2, Point3D* _p3)
{
    this->i = (_p1->y - _p0->y) * (_p3->z - _p0->z) - (_p3->y - _p0->y) * (_p1->z - _p0->z);
    this->j = (_p1->z - _p0->z) * (_p3->x - _p0->x) - (_p3->z - _p0->z) * (_p1->x - _p0->x);
    this->k = (_p1->x - _p0->x) * (_p3->y - _p0->y) - (_p3->x - _p0->x) * (_p1->y - _p0->y);
}

Vec3D& Vec3D::operator = (const Vec3D& v)
{
    this->i = v.i;
    this->j = v.j;
    this->k = v.k;
    return *this;
}

Vec3D& Vec3D::operator + (const Vec3D& v)
{
    this->i += v.i;
    this->j += v.j;
    this->k += v.k;
    return *this;
}

Vec3D::~Vec3D()
{
}

Face3D::Face3D(Point3D* _p0, Point3D* _p1, Point3D* _p2, Point3D* _p3)
{
    this->p[0] = _p0;
    this->p[1] = _p1;
    this->p[2] = _p2;
    this->p[3] = _p3;

    this->n = new Vec3D(_p0, _p1, _p2, _p3);
}

Face3D::~Face3D()
{
}

/*-------- CLASS TreeNode ---------*/
OcTreeNode::OcTreeNode(unsigned int _x, unsigned int _y, unsigned int _z, bool _isfull, unsigned int _lenth, string _ID)
{
    //所有变量赋值
    this->x = _x;
    this->y = _y;
    this->z = _z;
    this->isfull = _isfull;
    this->lenth = _lenth;
    this->ID = _ID;
    //this->done = false;

    this->node[0] = nullptr;//nullptr表示空指针，空指针常数可以转换为任意类型的指针类型
    this->node[1] = nullptr;
    this->node[2] = nullptr;
    this->node[3] = nullptr;
    this->node[4] = nullptr;
    this->node[5] = nullptr;
    this->node[6] = nullptr;
    this->node[7] = nullptr;
}

//OcTreeNode::OcTreeNode()
//{
//	this->x = 0;
//	this->y = 0;
//	this->z = 0;
//	this->isfull = false;
//	this->lenth = 0;
//	this->ID = "0";
//	//this->done = false;
//
//	this->node[0] = nullptr;
//	this->node[1] = nullptr;
//	this->node[2] = nullptr;
//	this->node[3] = nullptr;
//	this->node[4] = nullptr;
//	this->node[5] = nullptr;
//	this->node[6] = nullptr;
//	this->node[7] = nullptr;
//}
//
//OcTreeNode::OcTreeNode(const OcTreeNode& other)
//{
//	this->x = other.x;
//	this->y = other.y;
//	this->z = other.z;
//	this->isfull = other.isfull;
//	this->lenth = other.lenth;
//	this->ID = other.ID;
//	//this->done = other.done;
//
//	this->node[0] = other.node[0];
//	this->node[1] = other.node[1];
//	this->node[2] = other.node[2];
//	this->node[3] = other.node[3];
//	this->node[4] = other.node[4];
//	this->node[5] = other.node[5];
//	this->node[6] = other.node[6];
//	this->node[7] = other.node[7];
//}
//
//OcTreeNode& OcTreeNode::operator = (const OcTreeNode& other)
//{
//	this->x = other.x;
//	this->y = other.y;
//	this->z = other.z;
//	this->isfull = other.isfull;
//	this->lenth = other.lenth;
//	this->ID = other.ID;
//	//this->done = other.done;
//
//	this->node[0] = other.node[0];
//	this->node[1] = other.node[1];
//	this->node[2] = other.node[2];
//	this->node[3] = other.node[3];
//	this->node[4] = other.node[4];
//	this->node[5] = other.node[5];
//	this->node[6] = other.node[6];
//	this->node[7] = other.node[7];
//
//	return *this;
//}

OcTreeNode::~OcTreeNode()
{
}
