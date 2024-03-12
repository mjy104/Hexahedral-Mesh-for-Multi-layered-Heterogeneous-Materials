#pragma once
#include "Voxel.h"
#include "OcTree.h"
#include <QtWidgets/QMainWindow>
#include "ui_123.h"
#include <QDateTime>
#include "HexActor.h"
#pragma execution_character_set("utf-8")

class QtWidgetsApplication2 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication2(QWidget *parent = nullptr);
    void CreatTxt(string& pathName, const vector<Hexahedral3D*>& m_node1, const vector<Hexahedral3D*>& m_node2, const vector<Hexahedral3D*>& m_node3);
    ~QtWidgetsApplication2();
    vector<Mat> All_images;
    //槽函数
    void PushedButton();

    void input_picture();

    void input_material();

    void set_parameter();
    //vtkSmartPointer<vtkActor> set_material_color(vtkSmartPointer<vtkActor>& hexactor, string material);
    //Ui::MainWindow ui;
public:
    vector<vector<string>> material_container;
    unsigned int max_lenth;//网格最大值
    unsigned int min_lenth;//网格最小值
    unsigned int interval;//图片间隔
    string textpath;//text路径
    bool istextpath;
private:
    HexDisplay hexactor;
    QStringList strPathList;//读取图片路径
    QTime datetime;//时间
    //unordered_map<string, vector<double>> umap;//用来储存不同材料对应得RGB颜色属性

};
