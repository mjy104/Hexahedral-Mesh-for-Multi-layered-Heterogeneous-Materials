/*----------------------------
获取每一个六面体的显示actor
------------------------------
*/
#pragma once
#include"tree_class.h"
#include<unordered_map>
#include<vector>

class HexDisplay
{
public:
	HexDisplay();
	~HexDisplay();

	//节点显示
	vtkSmartPointer<vtkActor> HexActor(Hexahedral3D* n,string material);
	//边框
	vtkSmartPointer<vtkActor> edgeActor(Hexahedral3D* n);
	//vtkSmartPointer<vtkActor> set_material_color(vtkSmartPointer<vtkActor>& hexactor,string material);
	//创建坐标轴
	void createAxes(vtkSmartPointer<vtkRenderer> renderer);
	map<string, vector<double>> umap;//用来储存不同材料对应得RGB颜色属性
};

