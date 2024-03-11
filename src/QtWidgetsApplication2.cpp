#pragma once
#include<iostream>
#include "Voxel.h"
#include <string>
#include "OcTree.h"
#include"tree_class.h"
#include "QtWidgetsApplication2.h"
#include <QFileDialog>
#include <QMessageBox>
#include<vtkSmartPointer.h>
#include <vtkLight.h>
#include<vtkConeSource.h>
#include<vtkPolyDataMapper.h>
#include<vtkActor.h>
#include<vtkRenderer.h>
#include<vtkRenderWindow.h>
#include<vtkRenderWindowInteractor.h>
#include <vtkCylinderSource.h>
#include<vtkInteractorStyleTrackballCamera.h>
#include <vtkTransform.h>
#include <vtkBalloonRepresentation.h>
#include <vtkBalloonWidget.h>
#include <vtkCamera.h>
#include "vtkInformation.h"
#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCellPicker.h>
#include <vtkImagePlaneWidget.h>
#include <vtkMarchingCubes.h>
#include <vtkImageCast.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkImageMapToColors.h>
#include <vtkProperty.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkAutoInit.h>
#include<vtkShortArray.h>
#include<vtkFixedPointVolumeRayCastMapper.h>
#include<vtkPointdata.h>

Ui::MainWindow ui;
static vector<vtkSmartPointer<vtkActor>> m_actor1;
static vector<vtkSmartPointer<vtkActor>> m_actor2;
static vector<vtkSmartPointer<vtkActor>> m_actor3;


vector<vtkSmartPointer<vtkActor>> match_actor(double* color)
{
    vector<vector<vtkSmartPointer<vtkActor>>> actor_vec = { m_actor1,m_actor2,m_actor3 };
    for (int i = 0; i < actor_vec.size(); i++)
    {
        if (actor_vec[i][0]->GetProperty()->GetColor()[0] == color[0])
            return actor_vec[i];
    }
}
// Handle mouse events
class PropPickerInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
    static PropPickerInteractorStyle* New();
    vtkTypeMacro(PropPickerInteractorStyle, vtkInteractorStyleTrackballCamera);

    PropPickerInteractorStyle()
    {
        LastPickedActor = NULL;
        LastPickedProperty = vtkProperty::New();
        //LastPickedActorarray = vector<vtkActor*>(10000,LastPickedActor);
        //LastPickedPropertyarray = vector<vtkProperty*>(10000, LastPickedProperty);
    }
    virtual ~PropPickerInteractorStyle()
    {
        LastPickedProperty->Delete();
    }
    virtual void OnLeftButtonDown()
    {
        int* clickPos = this->GetInteractor()->GetEventPosition();//输出鼠标点击的屏幕坐标

        // Pick from this location.
        vtkSmartPointer<vtkPropPicker>  picker =
            vtkSmartPointer<vtkPropPicker>::New();
        picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());
        //实现拾取的函数，输入的参数（按从左到右顺序）：鼠标当前的坐标x，y，z(一般为0)，vtkRenderer对象
        double* pos = picker->GetPickPosition();//输出鼠标当前单击位置的世界坐标系下的坐标值
        // If we picked something before, reset its property
        //double* color1 = picker->GetActor()->GetProperty()->GetColor();
        if (this->LastPickedActor)
        {
            for (int i = 0; i < LastPickedActorarray.size(); i++)
            {
                this->LastPickedActorarray[i]->GetProperty()->SetColor(this->LastPickedProperty->GetColor());
                this->LastPickedActorarray[i]->GetProperty()->SetSpecular(this->LastPickedProperty->GetSpecular());
                this->LastPickedActorarray[i]->GetProperty()->SetSpecularPower(this->LastPickedProperty->GetSpecularPower());
            }
            //this->LastPickedActor->GetProperty()->DeepCopy(this->LastPickedProperty);
        }
        if ((this->LastPickedActor = picker->GetActor()) == nullptr)
            return;
        double* color = this->LastPickedActor->GetProperty()->GetColor();
        //匹配actor数组
        vector<vtkSmartPointer<vtkActor>> temp = match_actor(color);
        if (this->LastPickedActor)
        {
            this->size = temp.size();
            LastPickedActorarray.resize(this->size);
            for (int i = 0; i < LastPickedActorarray.size(); i++)
            {
                LastPickedActorarray[i] = temp[i];
            }
            // Save the property of the picked actor so that we can restore it next time
            //for (; i < LastPickedPropertyarray.size(); i++)
            //{
            //    if (this->LastPickedPropertyarray[i] == nullptr)
            //            break;
            //    //this->LastPickedPropertyarray[i]->DeepCopy(this->LastPickedActor->GetProperty());
            //}
            //QString size = QString::fromStdString(to_string(i));
            this->LastPickedProperty->DeepCopy(this->LastPickedActor->GetProperty());
            //QString actor_size = QString::fromStdString(to_string(m_actor1.size())) + QString::fromStdString(to_string(m_actor2.size())) + QString::fromStdString(to_string(m_actor3.size()));
            string material_pick = material_find(color);
            //string colorstr = to_string(color[0]) + to_string(color[1]) + to_string(color[2]);
            QString materialstr = QString::fromStdString(material_pick);
            //ui.material->setText(materialstr);
            QTime datetime = QTime::currentTime();
            QString outputtext = datetime.toString() + QString::fromStdString(" ") + materialstr;
            ui.history_output->append(outputtext);
            /*for (auto& i : HexDisplay::umap)
            {
                if (i.second[0] == color[0] && i.second[1] == color[1] && i.second[2] == color[2])
                {
                    cout << "材料为:" << i.first << endl;
                    break;
                }
            }*/
            // Highlight the picked actor by changing its properties
            for (auto& act : temp)
            {
                act->GetProperty()->SetColor(1, 0, 0);
                act->GetProperty()->SetDiffuse(1);
                act->GetProperty()->SetSpecular(0.0);
            }
            /*this->LastPickedActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
            this->LastPickedActor->GetProperty()->SetDiffuse(1.0);
            this->LastPickedActor->GetProperty()->SetSpecular(0.0);*/
            
        }
       // Forward events
        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }

    string material_find(double* color)
    {
        map<string, vector<double>> umap = material.umap;
        for (auto& i : umap)
        {
            if (i.second[0] == color[0] && i.second[1] == color[1] && i.second[2] == color[2])
            {
                return i.first;
            }
        }
    }
private:
    vtkActor* LastPickedActor;
    vector<vtkActor*> LastPickedActorarray;
    vtkProperty* LastPickedProperty;
    int size;
    //vector<vtkProperty*> LastPickedPropertyarray;
    HexDisplay material;
};
vtkStandardNewMacro(PropPickerInteractorStyle);

void QtWidgetsApplication2::CreatTxt(string& pathName, const vector<Hexahedral3D*>& m_node1, const vector<Hexahedral3D*>& m_node2, const vector<Hexahedral3D*>& m_node3)
{

    //char* path = "C:\\1.txt"; // 你要创建文件的路径

    ofstream fout(pathName);
    if (fout)
    { // 如果创建成功
        fout << "fini" << endl << "/clear" << endl << "/prep7" << endl << "SHPP,off,,nowarn" << endl << "et,1,solid185" << endl;//前处理步骤
        //设置材料
        fout << "MP,EX,1,1.69e5" << endl << "MP,PRXY,1,0.275 " << endl
            << "MP,EX,2,1.69e5 " << endl << "MP,PRXY,2,0.28" << endl
            << "MP,EX,3,1.69e5" << endl << "MP,PRXY,3,0.30" << endl;
        /*for (int rows = 0; rows < ui.tableWidget->rowCount(); rows++)
        {
            string ex = (ui.tableWidget->item(rows, 1)->text()).toStdString();
            string prxy = (ui.tableWidget->item(rows, 2)->text()).toStdString();
            fout << "MP,EX," << rows+1 << "," << ex << endl;
            fout << "MP,PRXY," << rows+1 << "," << prxy << endl;
        }*/
        unsigned int j = 1;
        unsigned int k = 771528 + 1;

        //材料设置语句
        fout << "MAT,1" << endl;
        //fout << m_node1.size();
        for (unsigned long i = 0; i < m_node1.size(); i++)
        {
            Hexahedral3D* tmp = m_node1[i];

            fout << "n" << "," << k++ << "," << tmp->p[0]->x << "e-3" << "," << tmp->p[0]->y << "e-3" << "," << tmp->p[0]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[1]->x << "e-3" << "," << tmp->p[1]->y << "e-3" << "," << tmp->p[1]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[2]->x << "e-3" << "," << tmp->p[2]->y << "e-3" << "," << tmp->p[2]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[3]->x << "e-3" << "," << tmp->p[3]->y << "e-3" << "," << tmp->p[3]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[4]->x << "e-3" << "," << tmp->p[4]->y << "e-3" << "," << tmp->p[4]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[5]->x << "e-3" << "," << tmp->p[5]->y << "e-3" << "," << tmp->p[5]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[6]->x << "e-3" << "," << tmp->p[6]->y << "e-3" << "," << tmp->p[6]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[7]->x << "e-3" << "," << tmp->p[7]->y << "e-3" << "," << tmp->p[7]->z << "e-3" << endl;
            fout << "e" << "," << k - 8 << "," << k - 7 << "," << k - 6 << "," << k - 5 << "," << k - 4 << "," << k - 3 << "," << k - 2 << "," << k - 1 << endl;

        }

        //材料设置语句
        fout << "MAT,2" << endl;
        for (unsigned long i = 0; i < m_node2.size(); i++)
        {
            Hexahedral3D* tmp = m_node2[i];

            fout << "n" << "," << k++ << "," << tmp->p[0]->x << "e-3" << "," << tmp->p[0]->y << "e-3" << "," << tmp->p[0]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[1]->x << "e-3" << "," << tmp->p[1]->y << "e-3" << "," << tmp->p[1]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[2]->x << "e-3" << "," << tmp->p[2]->y << "e-3" << "," << tmp->p[2]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[3]->x << "e-3" << "," << tmp->p[3]->y << "e-3" << "," << tmp->p[3]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[4]->x << "e-3" << "," << tmp->p[4]->y << "e-3" << "," << tmp->p[4]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[5]->x << "e-3" << "," << tmp->p[5]->y << "e-3" << "," << tmp->p[5]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[6]->x << "e-3" << "," << tmp->p[6]->y << "e-3" << "," << tmp->p[6]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[7]->x << "e-3" << "," << tmp->p[7]->y << "e-3" << "," << tmp->p[7]->z << "e-3" << endl;
            fout << "e" << "," << k - 8 << "," << k - 7 << "," << k - 6 << "," << k - 5 << "," << k - 4 << "," << k - 3 << "," << k - 2 << "," << k - 1 << endl;

        }

        fout << "MAT,3" << endl;
        for (unsigned long i = 0; i < m_node3.size(); i++)
        {
            Hexahedral3D* tmp = m_node3[i];

            fout << "n" << "," << k++ << "," << tmp->p[0]->x << "e-3" << "," << tmp->p[0]->y << "e-3" << "," << tmp->p[0]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[1]->x << "e-3" << "," << tmp->p[1]->y << "e-3" << "," << tmp->p[1]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[2]->x << "e-3" << "," << tmp->p[2]->y << "e-3" << "," << tmp->p[2]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[3]->x << "e-3" << "," << tmp->p[3]->y << "e-3" << "," << tmp->p[3]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[4]->x << "e-3" << "," << tmp->p[4]->y << "e-3" << "," << tmp->p[4]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[5]->x << "e-3" << "," << tmp->p[5]->y << "e-3" << "," << tmp->p[5]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[6]->x << "e-3" << "," << tmp->p[6]->y << "e-3" << "," << tmp->p[6]->z << "e-3" << "$";
            fout << "n" << "," << k++ << "," << tmp->p[7]->x << "e-3" << "," << tmp->p[7]->y << "e-3" << "," << tmp->p[7]->z << "e-3" << endl;
            fout << "e" << "," << k - 8 << "," << k - 7 << "," << k - 6 << "," << k - 5 << "," << k - 4 << "," << k - 3 << "," << k - 2 << "," << k - 1 << endl;

        }


        fout << "nummrg,node" << endl << "NUMCMP,node" << endl;
        fout.close();  // 执行完操作后关闭文件句柄
        /*QString time = datetime.toString("hh:mm:ss");
        time += "  successful output txt";
        ui.history_output->append(time);*/
    }
}

//QPixmap* m_crtPixmap; // 显示其中某张图片
QtWidgetsApplication2::QtWidgetsApplication2(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle("多层异质材料的力学性能测量");
    ui.output_text->setChecked(1);
    ui.tableWidget->clear();

    ui.tableWidget->setColumnCount(3);//只设置列数
    ui.tableWidget->setHorizontalHeaderLabels(QStringList() << "材料" << "杨氏模量" << "泊松比");
    ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列宽自动分配
    ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);//可以手动调整
    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选项
    ui.tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);//禁止修改
    ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//可以单选

    //创建菜单栏
    QMenuBar* menuBar = new QMenuBar(this);

    //添加菜单栏到主窗口中
    this->setMenuBar(menuBar);
    //创建菜单
    QMenu* menu1 = new QMenu("文件(J)", this);
    QMenu* menu2 = new QMenu("视图(O)", this);
    QMenu* menu3 = new QMenu("可视化操作(K)", this);
    QMenu* menu4 = new QMenu("工具(E)", this);
    QMenu* menu5 = new QMenu("帮助(R)", this);

    //菜单栏添加菜单
    menuBar->addMenu(menu1);
    menuBar->addMenu(menu2);
    menuBar->addMenu(menu3);
    menuBar->addMenu(menu4);
    menuBar->addMenu(menu5);

    //创建菜单项
    QAction* action1 = new QAction("新建文件或项目", this);//有图标
    QAction* action2 = new QAction("打开文件或项目", this);//有图标
    QAction* action3 = new QAction("退出", this);

    //菜单添加菜单项
    menu1->addAction(action1);
    menu1->addAction(action2);
    menu1->addSeparator();//插入分割线

    QMenu* menu9 = new QMenu("最近访问的文件", this);
    menu1->addMenu(menu9);//添加二级菜单
    menu9->addAction(new QAction("暂无最近打开项目", this));//二级菜单添加菜单项

    menu1->addAction(action3);

    //工具栏
    QPushButton* portBtn = new QPushButton(this);
    portBtn->setIcon(QIcon("D:/QT/QTxiangmu/123/image/file.png"));	//按钮添加图片
    portBtn->setToolTip("文件");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton* portBtn1 = new QPushButton(this);
    portBtn1->setIcon(QIcon("D:/QT/QTxiangmu/123/image/openfile.png"));	//按钮添加图片
    portBtn1->setToolTip("打开文件");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton* portBtn2 = new QPushButton(this);
    portBtn2->setIcon(QIcon("D:/QT/QTxiangmu/123/image/Xrotate.png"));	//按钮添加图片
    portBtn2->setToolTip("绕x轴旋转");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton* portBtn3 = new QPushButton(this);
    portBtn3->setIcon(QIcon("D:/QT/QTxiangmu/123/image/Yrotate.png"));	//按钮添加图片
    portBtn3->setToolTip("绕y轴旋转");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton* portBtn4 = new QPushButton(this);
    portBtn4->setIcon(QIcon("D:/QT/QTxiangmu/123/image/Zrotate.png"));	//按钮添加图片
    portBtn4->setToolTip("绕z轴旋转");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton* portBtn5 = new QPushButton(this);
    portBtn5->setIcon(QIcon("D:/QT/QTxiangmu/123/image/on.png"));	//按钮添加图片
    portBtn5->setToolTip("上视图");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton* portBtn6 = new QPushButton(this);
    portBtn6->setIcon(QIcon("D:/QT/QTxiangmu/123/image/under.png"));	//按钮添加图片
    portBtn6->setToolTip("下视图");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton* portBtn7 = new QPushButton(this);
    portBtn7->setIcon(QIcon("D:/QT/QTxiangmu/123/image/behind.png"));	//按钮添加图片
    portBtn7->setToolTip("后视图");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton* portBtn8 = new QPushButton(this);
    portBtn8->setIcon(QIcon("D:/QT/QTxiangmu/123/image/front.png"));	//按钮添加图片
    portBtn8->setToolTip("前视图");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton* portBtn9 = new QPushButton(this);
    portBtn9->setIcon(QIcon("D:/QT/QTxiangmu/123/image/right.png"));	//按钮添加图片
    portBtn9->setToolTip("右视图");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton* portBtn10 = new QPushButton(this);
    portBtn10->setIcon(QIcon("D:/QT/QTxiangmu/123/image/left.png"));	//按钮添加图片
    portBtn10->setToolTip("左视图");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton* portBtn11 = new QPushButton(this);
    portBtn11->setIcon(QIcon("D:/QT/QTxiangmu/123/image/bigger.png"));	//按钮添加图片
    portBtn11->setToolTip("放大");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton* portBtn12 = new QPushButton(this);
    portBtn12->setIcon(QIcon("D:/QT/QTxiangmu/123/image/smaller.png"));	//按钮添加图片
    portBtn12->setToolTip("缩小");			//鼠标移动到按钮上时显示提示 aaaa

    ui.toolBar->addWidget(portBtn);
    ui.toolBar->addWidget(portBtn1);
    ui.toolBar->addSeparator();
    ui.toolBar->addWidget(portBtn2);
    ui.toolBar->addWidget(portBtn3);
    ui.toolBar->addWidget(portBtn4);
    ui.toolBar->addSeparator();
    ui.toolBar->addWidget(portBtn5);
    ui.toolBar->addWidget(portBtn6);
    ui.toolBar->addWidget(portBtn7);
    ui.toolBar->addWidget(portBtn8);
    ui.toolBar->addWidget(portBtn9);
    ui.toolBar->addWidget(portBtn10);
    ui.toolBar->addSeparator();
    ui.toolBar->addWidget(portBtn11);
    ui.toolBar->addWidget(portBtn12);
    ui.toolBar->addSeparator();

    //状态栏
    ui.statusbar->setSizeGripEnabled(false);

    //进度条
    ui.statusbar->addWidget(ui.progressBar, 50);
    ui.progressBar->setFixedSize(125, 15);
    ui.progressBar->setOrientation(Qt::Horizontal);  // 水平方向
    ui.progressBar->setMinimum(0);  // 最小值
    ui.progressBar->setMaximum(100);  // 最大值
    ui.progressBar->setValue(0);  // 当前进度
    ui.progressBar->hide();

    connect(ui.pushButton_2, &QPushButton::clicked, this, &QtWidgetsApplication2::PushedButton);
    connect(ui.input_picture, &QPushButton::clicked, this, &QtWidgetsApplication2::input_picture);
    connect(ui.InputButton, &QPushButton::clicked, this, &QtWidgetsApplication2::inputbutton);
    connect(ui.deletButton, &QPushButton::clicked, this, &QtWidgetsApplication2::deletebutton); 


}

QtWidgetsApplication2::~QtWidgetsApplication2()
{}



void QtWidgetsApplication2::PushedButton()
{
    //测试案例
    //vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    //cylinder->SetHeight(3);
    //cylinder->SetRadius(1);
    //cylinder->SetResolution(10);//设置柱体横截面的等边多边形的边数

    //vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    //cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    //vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
    //cylinderActor->SetMapper(cylinderMapper);

    //vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
    //transform->PostMultiply();//表示使用右乘变换矩阵的方式
    //transform->RotateX(90);//表示设置绕Z轴旋转40度
    //transform->Translate(-10, 0, 0);//设置平移大小
    //cylinderActor->SetUserTransform(transform);

    //vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    //vtkSmartPointer<vtkLight> myLight1 = vtkSmartPointer<vtkLight>::New();
    //myLight1->SetColor(1, 0, 0);
    //myLight1->SetPosition(0, 0, 1);
    //myLight1->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
    //renderer->AddLight(myLight1);

    //vtkSmartPointer<vtkLight> myLight2 = vtkSmartPointer<vtkLight>::New();
    //myLight2->SetColor(0, 0, 1);
    //myLight2->SetPosition(0, 0, -1);
    //myLight2->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
    //renderer->AddLight(myLight2);

    //renderer->AddActor(cylinderActor);//将vtkprop类型的对象添加到渲染场景中
    //renderer->SetBackground(0.1, 0.2, 0.4);//设置R、G、B的格式

    //ui.qvtkWidget->GetRenderWindow()->AddRenderer(renderer); //替代vtkRenderWindow
    //vtkSmartPointer<vtkRenderWindowInteractor> iren = ui.qvtkWidget->GetRenderWindow()->GetInteractor();
    //iren->SetRenderWindow(ui.qvtkWidget->GetRenderWindow());

    ////控制相机对物体作旋转、放大、缩小操作
    //vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    //iren->SetInteractorStyle(style);

    ///*               导入数据，添加变量条等程序                */
    ////刷新渲染
    //ui.qvtkWidget->GetRenderWindow()->Render();
    ////初始化交互器
    //iren->Initialize();
    ////启动交互器
    //iren->Start();
    
    //unsigned int max_length = 32;
    //unsigned int min_length = 32;
    //unsigned int interval = 1; //图片间隔设置为1

    int max_length = ui.spinBox->value();
    int min_length = ui.spinBox_2->value();
    int interval = ui.spinBox_3->value();

    //获取txt
    vector<Hexahedral3D*> temp;

    My_Voxel vox(interval,min_length);
    vox.AllImage_m = All_images;
    vox.cols = vox.AllImage_m[0].cols;
    vox.rows = vox.AllImage_m[0].rows;
    datetime = QTime::currentTime();
    QString outputtext = datetime.toString() + tr(" 成功读取初始体数据");
    ui.history_output->append(outputtext);
    ui.progressBar->show();
    ui.progressBar->setValue(25);  // 当前进度

    OcTree My_Tree(vox, max_length, min_length); //建立初始六面体网格
    datetime = QTime::currentTime();
    outputtext = datetime.toString() + tr(" 成功建立六面体网格");
    ui.history_output->append(outputtext);
    /*outputtext = "Maximum image size:" + QString::number(vox.getMaxLenthAll(), 10);
    ui.history_output->append(outputtext);*/
    ui.progressBar->setValue(50);  // 当前进度
    //cout << "最大图片大小：" << vox.getMaxLenthAll() << endl;

    My_Tree.build_adaptive_tree();
    /*outputtext = "Number of surface meshes:" + QString::number(My_Tree.nodes.size(), 10);
    ui.history_output->append(outputtext);*/
    //cout << "表面网格数量：" << My_Tree.nodes.size() << endl;


#if 0
    //表面拟合
    get_Surface sur_node(My_Tree.nodes, vox);
    sur_node.get_SurNode();
    cout << "表面单元数量：" << sur_node.sur_nodes.size() << endl;
    cout << "拟合失败的面：" << sur_node.fail_faces.size() << endl;
#endif


    //获取actor
    HexDisplay hexactor;
    //渲染窗口
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    //交互
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    
    //VTK显示网格
#if 0

    //表面网格显示
    for (int i = 0; i < sur_node.sur_nodes.size(); i++)
    {
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetPosition(sur_node.sur_nodes[i]->p[0]->x, sur_node.sur_nodes[i]->p[0]->y, sur_node.sur_nodes[i]->p[0]->z);
        renderer->AddActor(hexactor.HexActor(sur_node.sur_nodes[i]));
        //text
        //temp.push_back(sur_node.sur_nodes[i]);
    }

#endif
#if 0
    string material = ui.tableWidget->item(0, 0)->text().toStdString();
    for (int i = 0; i < My_Tree.nodes.size(); i++)
    {
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetPosition(My_Tree.nodes[i]->p[0]->x, My_Tree.nodes[i]->p[0]->y, My_Tree.nodes[i]->p[0]->z);
        renderer->AddActor(hexactor.HexActor(My_Tree.nodes[i],material));
        //text
        //temp.push_back(My_Tree.nodes[i]);
    }

#endif 
    vtkSmartPointer<PropPickerInteractorStyle> style =
        vtkSmartPointer<PropPickerInteractorStyle>::New();
    style->SetDefaultRenderer(renderer);
    renderWindowInteractor->SetInteractorStyle(style);

    /*vtkSmartPointer<vtkBalloonRepresentation> balloonRep =
        vtkSmartPointer<vtkBalloonRepresentation>::New();
    balloonRep->SetBalloonLayoutToImageRight();
    vtkSmartPointer<vtkBalloonWidget> balloonWidget =
        vtkSmartPointer<vtkBalloonWidget>::New();
    balloonWidget->SetInteractor(renderWindowInteractor);
    balloonWidget->SetRepresentation(balloonRep);
    balloonWidget->On();*/


#if 1
    string material = ui.tableWidget->item(0, 0)->text().toStdString();
        for (int i = 0; i < My_Tree.m_node1.size(); i++)
        {
            vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
            actor->SetPosition(My_Tree.m_node1[i]->p[0]->x, My_Tree.m_node1[i]->p[0]->y, My_Tree.m_node1[i]->p[0]->z);
            actor = hexactor.HexActor(My_Tree.m_node1[i], material);
            renderer->AddActor(actor);
            m_actor1.push_back(actor);
            /*balloonWidget->AddBalloon(actor, "Hello", NULL);*/
            //text
            temp.push_back(My_Tree.nodes[i]);
        }
        material = ui.tableWidget->item(1, 0)->text().toStdString();
        for (int i = 0; i < My_Tree.m_node2.size(); i++)
        {
            vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
            actor->SetPosition(My_Tree.m_node2[i]->p[0]->x, My_Tree.m_node2[i]->p[0]->y, My_Tree.m_node2[i]->p[0]->z);
            actor = hexactor.HexActor(My_Tree.m_node2[i], material);
            renderer->AddActor(actor);
            m_actor2.push_back(actor);
            /*balloonWidget->AddBalloon(actor, "Hello", NULL);*/
            //text
            temp.push_back(My_Tree.nodes[i]);
        }
        material = ui.tableWidget->item(2, 0)->text().toStdString();
        for (int i = 0; i < My_Tree.m_node3.size(); i++)
        {
            vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
            actor->SetPosition(My_Tree.m_node3[i]->p[0]->x, My_Tree.m_node3[i]->p[0]->y, My_Tree.m_node3[i]->p[0]->z);
            actor = hexactor.HexActor(My_Tree.m_node3[i], material);
            renderer->AddActor(actor);
            m_actor3.push_back(actor);
            /*balloonWidget->AddBalloon(actor, "Hello", NULL);*/
            //text
            temp.push_back(My_Tree.m_node3[i]);
        }
#endif
#if 1
    ////输出txt
    //string path1 = "D:\\picture\\CTpicture\\test2.txt";
    ////CreatTxt(path1, My_Tree.m_node1, My_Tree.m_node2, My_Tree.m_node3);
    if (ui.output_text->isChecked())
    {
        //获取txt
        String path = ui.textpath->text().toStdString();//输入格式：.../文件名字.txt
        CreatTxt(path, My_Tree.m_node1, My_Tree.m_node2, My_Tree.m_node3);
        //输出日志
        datetime = QTime::currentTime();
        QString outputtext = datetime.toString() + tr(" 成功输出txt文件");
        ui.history_output->append(outputtext);
        ui.progressBar->setValue(75);  // 当前进度
    }
    
    //ui->statusbar->showMessage(tr("已完成！"));
    

#endif
    //vtkSmartPointer<vtkRenderWindow> renderwindow =
        //vtkSmartPointer<vtkRenderWindow>::New();
    datetime = QTime::currentTime();
    outputtext = datetime.toString() + tr(" 正在生成三维模型");
    ui.history_output->append(outputtext);
    ui.progressBar->setValue(90);  // 当前进度


    ui.qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
    renderWindowInteractor->SetRenderWindow(ui.qvtkWidget->GetRenderWindow());


    //坐标轴
    //hexactor.createAxes(renderer);
    renderer->SetBackground(0.1, 0.2, 0.4);

    ui.qvtkWidget->GetRenderWindow()->Render();
    datetime = QTime::currentTime();
    outputtext = datetime.toString() + tr(" 完成！");
    ui.history_output->append(outputtext);
    ui.progressBar->setValue(100);
    ui.progressBar->hide();
    /*vtkInteractorStyleTrackballCamera* style =
        vtkInteractorStyleTrackballCamera::New();*/


    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
    
    //释放表面网格
    /*for (int i = 0; i < sur_node.sur_nodes.size(); i++)
    {
        if (sur_node.sur_nodes[i] != nullptr)
        {
            delete sur_node.sur_nodes[i];
        }
    }*/

    ////释放内部网格
    //for (int i = 0; i < My_Tree.nodes.size(); i++)
    //{
    //	if (My_Tree.nodes[i] != nullptr)
    //	{
    //		delete My_Tree.nodes[i];
    //	}
    //}
}

void QtWidgetsApplication2::input_picture()
{
    //QFileDialog fileDlg(this);
    //fileDlg.setWindowTitle("Choose Pictures/Voxels");
    //QStringList qstrFilters;//设置文件过滤器的list
    //qstrFilters << "Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm *.vols)";
    //qstrFilters << "Any files (*)";
    //fileDlg.setNameFilters(qstrFilters);//设置文件过滤器
    //fileDlg.setFileMode(QFileDialog::ExistingFiles);//设置能选择多个文件，如果是单个文件就写成QFileDialog::ExistingFile
    //if (fileDlg.exec() == QDialog::Accepted)
    //{
    //    vector<Mat> images; //储存原始图片
    //    vector<Mat> imgGray; //储存进行二值化后的灰度图片
    //    strPathList = fileDlg.selectedFiles();//得到用户选择的多个文件的路径的list
    //    string path = strPathList[0].toStdString();
    //    /*if (isvols(path))
    //    {
    //        Process_vols(path);
    //    }*/
    //    //QPixmap pixmapTemp;

    //    for (int i = 0; i < strPathList.count(); i++)
    //    {
    //        string path = strPathList[i].toStdString();
    //        Mat image = imread(path);
    //        images.push_back(image);
    //    }

    //    for (unsigned int i = 0; i < images.size(); i++)
    //    {
    //        Mat* img_G = new Mat;
    //        //灰度化
    //        cvtColor(images[i], *img_G, COLOR_BGR2GRAY);
    //        imgGray.push_back(*img_G);

    //        All_images.push_back(*img_G);
    //        //main_AllImage_m.push_back(*img_G);

    //        //show_picture(cur_picture);
    //    }
    //}
    ///*else
    //{
    //    QMessageBox mesg;
    //    mesg.warning(this, "警告", "打开图片失败!");
    //    return;
    //}*/
    QFileDialog fileDlg(this);
    fileDlg.setWindowTitle("Choose Pictures/Voxels");
    QStringList qstrFilters;//设置文件过滤器的list
    qstrFilters << "Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm *.vol)";
    qstrFilters << "Any files (*)";
    fileDlg.setNameFilters(qstrFilters);//设置文件过滤器
    fileDlg.setFileMode(QFileDialog::ExistingFiles);//设置能选择多个文件，如果是单个文件就写成QFileDialog::ExistingFile
    if (fileDlg.exec() == QDialog::Accepted)
    {
        int m_Width = 0, m_Height = 0, m_Depth = 0;
        float distance1 = 1, distance2 = 1, distance3 = 1;
        vector<vector<vector<float>>> result;
        strPathList = fileDlg.selectedFiles();//得到用户选择的多个文件的路径的list
        QString path = strPathList[0];
        QFileInfo fileInfo(path);
        string fileClass = fileInfo.suffix().toStdString();
        if (fileClass == "jpg")
        {
            datetime = QTime::currentTime();
            QString outputtext = datetime.toString() + tr(" 您导入的是图像数据,正在生成体素模型");
            ui.history_output->append(outputtext);

            vector<Mat> images; //储存原始图片
            vector<Mat> imgGray; //储存进行二值化后的灰度图片
            for (int i = 0; i < strPathList.count(); i++)
            {
                string path = strPathList[i].toStdString();
                Mat image = imread(path);
                images.push_back(image);
            }

            for (unsigned int i = 0; i < images.size(); i++)
            {
                Mat* img_G = new Mat;
                //灰度化
                cvtColor(images[i], *img_G, COLOR_BGR2GRAY);
                imgGray.push_back(*img_G);

                All_images.push_back(*img_G);

            }
            //main_AllImage_m.push_back(*img_G);
            //show_picture(cur_picture);




        //将图片数据转换为三维矩阵
            result = vector<vector<vector<float>>>(All_images[0].cols, vector<vector<float>>(All_images[0].rows, vector<float>(All_images.size(), 0)));
            for (int k = 0; k < All_images.size(); ++k)
            {
                for (int i = 0; i < All_images[0].cols; ++i)
                {
                    for (int j = 0; j < All_images[0].rows; ++j)
                    {
                        result[i][j][k] = (int)All_images[k].at<uchar>(i, j);
                    }
                }
            }
            m_Width = All_images[0].cols;
            m_Height = All_images[0].rows;
            m_Depth = All_images.size();

        }

        else if (fileClass == "vol")
        {
            datetime = QTime::currentTime();
            QString outputtext = datetime.toString() + tr(" 您导入的是体数据");
            ui.history_output->append(outputtext);
            ifstream is(path.toStdString(), ifstream::in | ios::binary);
            if (!is)
            {
                cout << "文件不能打开！" << endl;
                return;
            }
            // 2. 计算体数据长度
            is.seekg(0, is.end);
            long long length = is.tellg();
            is.seekg(0, is.beg);

            // 3.读入文件头
            uint Width = 0;					//图像宽度     //考虑初始化
            uint Height = 0;				//图像高度
            uint Depth = 0;					//图像深度
            float maxAttenuation = 0;		//最大衰减系数
            uint DataType = 0;				//体素存储类型: unsigned char=01,unsigned short=02,float=03
            float voxelWidth = 0;			//体素的宽度(mm)
            float voxelDepth = 0;			//体素的高度(mm)

            is.read((char*)(&Width), sizeof(Width));
            is.read((char*)(&Height), sizeof(Height));
            is.read((char*)(&Depth), sizeof(Depth));
            is.read((char*)(&maxAttenuation), sizeof(maxAttenuation));
            is.read((char*)(&DataType), sizeof(DataType));
            is.read((char*)(&voxelWidth), sizeof(voxelWidth));
            is.read((char*)(&voxelDepth), sizeof(voxelDepth));
            is.ignore(100);                 //丢掉保留字节里的无用内容

            m_Width = Width;
            m_Height = Height;
            m_Depth = Depth;
            distance1 = voxelWidth;
            distance2 = voxelWidth;
            distance3 = voxelDepth;
            datetime = QTime::currentTime();
            outputtext = datetime.toString() + tr(" 体数据的宽度为") + tr(to_string(Width).c_str());
            ui.history_output->append(outputtext);

            datetime = QTime::currentTime();
            outputtext = datetime.toString() + tr(" 体数据的高度为") + tr(to_string(Height).c_str());
            ui.history_output->append(outputtext);

            datetime = QTime::currentTime();
            outputtext = datetime.toString() + tr(" 体数据的深度为") + tr(to_string(Depth).c_str());
            ui.history_output->append(outputtext);

            datetime = QTime::currentTime();
            outputtext = datetime.toString() + tr(" 单个体素的宽度为") + tr(to_string(voxelWidth).c_str());
            ui.history_output->append(outputtext);

            datetime = QTime::currentTime();
            outputtext = datetime.toString() + tr(" 单个体素的高度为") + tr(to_string(voxelDepth).c_str());
            ui.history_output->append(outputtext);

            //省略不需要的1920个数据
            is.ignore(1920);


            //开始读入体数据
            result = vector<vector<vector<float>>>(Width, vector<vector<float>>(Height, vector<float>(Depth, 0)));
            for (int k = 0; k < Depth; ++k)
            {
                for (int i = 0; i < Width; ++i)
                {
                    for (int j = 0; j < Height; ++j)
                    {
                        float temp = 0;
                        is.read((char*)(&temp), sizeof(temp));
                        temp = round(temp * 255 / maxAttenuation);
                        result[i][j][k] = temp;
                    }
                }
            }
        }



        //将体数据转换为imagedata类型
        int extent[6] = { 0,m_Width - 1,0,m_Height - 1,0,m_Depth - 1 };//取值范围
        double spacing[3] = { distance1, distance2, distance3 };//像素点之间的距离
        double origin[3] = { 0 };//起始坐标

        int size_all = m_Width * m_Height * m_Depth;
        short* pBuf = new short[size_all] {0};
        int index = 0;
        for (int k = 0; k < m_Depth; ++k)
        {
            for (int i = 0; i < m_Width; ++i)
            {
                for (int j = 0; j < m_Height; ++j)
                {
                    pBuf[index++] = result[i][j][k];
                }
            }
        }
        vtkNew<vtkShortArray> dataArray;
        // 设置short*的缓存指针和数组大小，设定每个数据点元组个数为1；
        dataArray->SetArray(pBuf, size_all, 1);
        vtkNew<vtkImageData> pImageData;
        // 给vtkImageData指定VTK_SHORT类型，元组个数为1；
        pImageData->AllocateScalars(VTK_SHORT, 1);
        pImageData->SetDimensions(m_Width, m_Height, m_Depth);
        pImageData->GetPointData()->SetScalars(dataArray);
        pImageData->SetSpacing(spacing);
        pImageData->SetOrigin(origin);


        vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
        volumeMapper->SetInputData(pImageData);
        volumeMapper->SetAutoAdjustSampleDistances(0);
        volumeMapper->SetImageSampleDistance(0.5);


        //定义对象属性
        vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();//定义对象属性
        volumeProperty->SetInterpolationTypeToLinear();
        volumeProperty->ShadeOn();  //打开或者关闭阴影测试
        //vtkVolumeProperty默认关闭阴影效果,需要显示则调用ShadeOn()函数来打开阴影效果
        volumeProperty->SetAmbient(0.4);//环境光系数
        volumeProperty->SetDiffuse(0.6);  //散射光系数
        volumeProperty->SetSpecular(0.2); //反射光系数

        //
        //vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
        //compositeOpacity->AddPoint(89, 0.00);//（灰度值1，不透明度1）
        //compositeOpacity->AddPoint(130, 0.40);//（灰度值2，不透明度2）
        //compositeOpacity->AddPoint(171, 0.60);//（灰度值3，不透明度3）
        //volumeProperty->SetScalarOpacity(compositeOpacity); //设置不透明度传输函数

        //设置不同灰度值的不透明读
        vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
        compositeOpacity->AddPoint(70, 0.00);//（灰度值1，不透明度1）
        compositeOpacity->AddPoint(90, 0.40);//（灰度值2，不透明度2）
        compositeOpacity->AddPoint(180, 0.60);//（灰度值3，不透明度3）
        volumeProperty->SetScalarOpacity(compositeOpacity); //设置不透明度传输函数

        //测试隐藏部分数据,对比不同的设置
        /*compositeOpacity->AddSegment(37,0.00,171,0.4);
        compositeOpacity->AddPoint(171,  0.40,255,1.0);
        volumeProperty->SetScalarOpacity(compositeOpacity);*/


        //vtkNew<vtkPiecewiseFunction> volumeGradientOpacity;
        //volumeGradientOpacity->AddPoint(10, 0.0);//(梯度值1,不透明度乘子1)
        //volumeGradientOpacity->AddPoint(90, 0.5);//(梯度值2,不透明度乘子2)
        //volumeGradientOpacity->AddPoint(100, 1.0);//(梯度值3,不透明度乘子3)
        //volumeProperty->SetGradientOpacity(volumeGradientOpacity);//设置梯度不透明度效果对比

        vtkSmartPointer<vtkColorTransferFunction> color = vtkSmartPointer<vtkColorTransferFunction>::New();
        color->AddRGBPoint(0.000, 0.00, 0.00, 0.00);//(灰度值1,r1,g1,b1)
        color->AddRGBPoint(255, 1.00, 0.52, 0.30);//(灰度值2,r2,g2,b2)
        color->AddRGBPoint(200, 1.00, 1.00, 1.00);//(灰度值3,r3,g3,b3)
        color->AddRGBPoint(180, 0.20, 0.20, 0.20);//(灰度值4,r4,g4,b4)
        volumeProperty->SetColor(color);//颜色传输函数,与不透明度传输函数使用类似


        vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
        volume->SetMapper(volumeMapper);//该函数用于设置Mapper对象
        volume->SetProperty(volumeProperty);//该函数用于设置属性对象


        //创建渲染窗口，调整vtk的交互方式
        vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
        vtkSmartPointer<vtkRenderWindowInteractor> rwi = vtkSmartPointer<vtkRenderWindowInteractor>::New();
        vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
        style->SetDefaultRenderer(ren);
        rwi->SetInteractorStyle(style);


        //将渲染窗口放入到qt界面中进行展示
        ren->SetBackground(0.1, 0.2, 0.4);//设置背景颜色
        ren->AddVolume(volume);
        ui.qvtkWidget->GetRenderWindow()->AddRenderer(ren);
        rwi->SetRenderWindow(ui.qvtkWidget->GetRenderWindow());
        ren->ResetCamera();
        ui.qvtkWidget->GetRenderWindow()->Render();
        datetime = QTime::currentTime();
        QString outputtext = datetime.toString() + tr(" 已经显示体数据模型");
        ui.history_output->append(outputtext);
        rwi->Initialize();
        rwi->Start();
        
    }

    /*else
    {
        QMessageBox mesg;
        mesg.warning(this, "警告", "打开图片失败!");
        return;
    }*/
}

void QtWidgetsApplication2::deletebutton()
{
    int rowIndex = ui.tableWidget->currentRow();
    ui.tableWidget->removeRow(rowIndex);
}

void QtWidgetsApplication2::inputbutton()
{
    int RowCont;
    RowCont = ui.tableWidget->rowCount();
    ui.tableWidget->insertRow(RowCont);
}