#include"HexActor.h"


HexDisplay::HexDisplay()
{
	vector<double> rgb = { 0.8980, 0.8745, 0.8078 };
	umap.insert(std::make_pair("Fe", rgb));
	rgb = { 0.7490, 0.6784, 0.4353 };
	umap.insert(std::make_pair("Cu", rgb));
	rgb = { 0.8627, 0.8745, 0.8902 };
	umap.insert(std::make_pair("Al", rgb));
	rgb = { 0.9176, 0.7803, 0.5294 };
	umap.insert(std::make_pair("18Au", rgb));
	rgb = { 0.8549, 0.6980, 0.4509 };
	umap.insert(std::make_pair("24Au", rgb));
	rgb = { 0.8627, 0.8627, 0.8627 };
	umap.insert(std::make_pair("不锈钢", rgb));
	rgb = { 0.9137, 0.9137, 0.8470 };
	umap.insert(std::make_pair("Ag", rgb));
}

HexDisplay::~HexDisplay()
{

}
//为不同节点赋值
//vtkSmartPointer<vtkActor> HexDisplay::set_material_color(vtkSmartPointer<vtkActor>& hexactor,string material)
//{
//		vector<double> rgb1 = umap.find(material)->second;
//		hexactor->GetProperty()->SetColor(rgb1[0], rgb1[1], rgb1[2]);//根据材料设置颜色
//		//hexactor->GetProperty()->SetOpacity(0.3);
//		hexactor->GetProperty()->SetEdgeVisibility(true);
//		return hexactor;
//}

//建立每个单元的actor
vtkSmartPointer<vtkActor> HexDisplay::HexActor(Hexahedral3D* n,string material)
{
	float pnts[8][3] = { {n->p[0]->x, n->p[0]->y, n->p[0]->z}, {n->p[1]->x, n->p[1]->y, n->p[1]->z},
			{n->p[2]->x, n->p[2]->y, n->p[2]->z}, {n->p[3]->x, n->p[3]->y, n->p[3]->z},
			{n->p[4]->x, n->p[4]->y, n->p[4]->z}, {n->p[5]->x, n->p[5]->y, n->p[5]->z},
			{n->p[6]->x, n->p[6]->y, n->p[6]->z}, {n->p[7]->x, n->p[7]->y, n->p[7]->z} };
	vtkIdType faces[6][4] = { {0, 1, 2, 3},{4, 5, 6, 7},{0, 1, 5, 4},
		   {1, 2, 6, 5},{2, 3, 7, 6},{3, 0, 4, 7} };

	vtkSmartPointer<vtkPolyData> hex = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> polys = vtkSmartPointer<vtkCellArray>::New();
	vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();

	for (int i = 0; i < 8; i++) points->InsertPoint(i, pnts[i]);
	for (int i = 0; i < 6; i++) polys->InsertNextCell(4, faces[i]);
	for (int i = 0; i < 10; i++) scalars->InsertTuple1(i, i);

	hex->SetPoints(points);
	hex->SetPolys(polys);
	hex->GetPointData()->SetScalars(scalars);


	vtkSmartPointer<vtkPolyDataMapper> hexmapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	hexmapper->SetInputData(hex);
	hexmapper->SetScalarRange(0, 7);

	vtkSmartPointer<vtkActor> hexactor =
		vtkSmartPointer<vtkActor>::New();
	hexactor->SetMapper(hexmapper);

	hexmapper->ScalarVisibilityOff();
	vector<double> rgb1 = umap[material];
	//cout << rgb1[0] << rgb1[1] << rgb1[2] << endl;
	hexactor->GetProperty()->SetColor(rgb1[0], rgb1[1], rgb1[2]);//根据材料设置颜色
		//set_material_color(hexactor,material);//根据材料设置颜色
		//hexactor->GetProperty()->SetColor(0.8980, 0.8745, 0.8078);//废白铁罐 229, 223, 206
		//hexactor->GetProperty()->SetColor(0.7490, 0.6784, 0.4353);//磨亮的黄铜 191,173,111 
		//hexactor->GetProperty()->SetColor(0.8627, 0.8745, 0.8902); //磨亮的铝 220, 223, 227
		//hexactor->GetProperty()->SetColor(0.9176, 0.7803, 0.5294);//18K 金234,199,135
		//hexactor->GetProperty()->SetColor(0.8549, 0.6980, 0.4509);//24K金 218, 178, 115
		//hexactor->GetProperty()->SetColor(0.8627, 0.8627, 0.8627);//磨亮的不锈钢 220,220,220 
		//hexactor->GetProperty()->SetColor(0.9137, 0.9137, 0.8470);//银233,233,216 
		//hexactor->GetProperty()->SetColor(0.5019, 0.5019, 0.4941);//不锈钢 128,128,126 
		//hexactor->GetProperty()->SetColor(0.9843, 1, 0.949);//亮白
		//hexactor->GetProperty()->SetColor(1, 0.843, 0);//金黄
		//hexactor->GetProperty()->SetColor(0.78, 0.78, 0.78);//银灰
		//hexactor->GetProperty()->SetOpacity(0.3);
		//hexactor->GetProperty()->SetEdgeVisibility(true);
	hexactor->GetProperty()->SetEdgeVisibility(true);
	return hexactor;

}

vtkSmartPointer<vtkActor> HexDisplay::edgeActor(Hexahedral3D* n)
{
	float pnts[8][3] = { {n->p[0]->x, n->p[0]->y, n->p[0]->z}, {n->p[1]->x, n->p[1]->y, n->p[1]->z},
			{n->p[2]->x, n->p[2]->y, n->p[2]->z}, {n->p[3]->x, n->p[3]->y, n->p[3]->z},
			{n->p[4]->x, n->p[4]->y, n->p[4]->z}, {n->p[5]->x, n->p[5]->y, n->p[5]->z},
			{n->p[6]->x, n->p[6]->y, n->p[6]->z}, {n->p[7]->x, n->p[7]->y, n->p[7]->z} };
	vtkIdType faces[6][4] = { {0, 1, 2, 3},{4, 5, 6, 7},{0, 1, 5, 4},
		   {1, 2, 6, 5},{2, 3, 7, 6},{3, 0, 4, 7} };

	vtkSmartPointer<vtkPolyData> hex = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> polys = vtkSmartPointer<vtkCellArray>::New();
	vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();

	for (int i = 0; i < 8; i++) points->InsertPoint(i, pnts[i]);
	for (int i = 0; i < 6; i++) polys->InsertNextCell(4, faces[i]);
	for (int i = 0; i < 8; i++) scalars->InsertTuple1(i, i);

	hex->SetPoints(points); //创建的点/体数据加入到vtk文件中（几何结构）
	hex->SetPolys(polys);  //创建拓扑结构
	hex->GetPointData()->SetScalars(scalars);

	vtkSmartPointer<vtkExtractEdges> extract = vtkSmartPointer<vtkExtractEdges>::New();
	extract->SetInputData(hex);  //提取单元格边缘
	vtkSmartPointer<vtkPolyDataMapper> mapEdges = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapEdges->SetInputConnection(extract->GetOutputPort());
	mapEdges->SetScalarVisibility(1);
	vtkSmartPointer<vtkActor> edgeActor = vtkSmartPointer<vtkActor>::New();
	edgeActor->SetMapper(mapEdges);
	edgeActor->VisibilityOn();

	return edgeActor;
}

void HexDisplay::createAxes(vtkSmartPointer<vtkRenderer> renderer)
{
	vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
	axes->SetTotalLength(1000.0, 1000.0, 1000.0);
	axes->SetShaftType(vtkAxesActor::CYLINDER_SHAFT);//设置轴类型圆柱形状
	axes->SetCylinderRadius(0.01);

	axes->GetXAxisCaptionActor2D()->SetWidth(0.03);
	axes->GetYAxisCaptionActor2D()->SetWidth(0.03);
	axes->GetZAxisCaptionActor2D()->SetWidth(0.03);

	renderer->AddActor(axes);
}

