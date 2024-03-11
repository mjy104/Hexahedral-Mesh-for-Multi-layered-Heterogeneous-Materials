#include "mainwindow.h"
#include "ui_123.h"
#include "Voxel.h"
#include "OcTree.h"
#include"tree_class.h"
#include <QFileDialog>
#include <QList>
#include <QString>
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>
#include <QGroupBox>


#ifndef	uchar
#define	uchar  unsigned char
#endif
#ifndef	uint
#define	uint  unsigned int
#endif


void MainWindow::CreatTxt(string& pathName,const vector<Hexahedral3D*>& m_node1, const vector<Hexahedral3D*>& m_node2, const vector<Hexahedral3D*>& m_node3)
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
        for(int rows=0;rows<=ui->tableWidget->rowCount();rows++)
        {
                fout<<"MP,EX,"<<ui->tableWidget->item(rows,0)<<","<<ui->tableWidget->item(rows,2)<<endl;
                fout<<"MP,PRXY,"<<ui->tableWidget->item(rows,0)<<","<<ui->tableWidget->item(rows,3)<<endl;
        }
        unsigned int j = 1;
        unsigned int k = 1;

        //材料设置语句
        fout << "MAT,1" << endl;
        fout << m_node1.size();
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
        QString time = datetime.toString("hh:mm:ss");
        time += "  successful output txt";
        ui->history_output->append(time);
    }
}


QPixmap *m_crtPixmap; //显示其中某张图片
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("多层异质材料的力学性能测量");
    //this->setStyleSheet("#mainWindow{border-image:url(D:/QT/QTxiangmu/123/image/cqu.jpg);}");
    //MainWindow背景图片

    ui->output_text->setChecked(1);
    ui->tableWidget->clear();

    ui->tableWidget->setColumnCount(3);//只设置列数
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"材料 "<<"杨氏模量(GPa) "<<"泊松比 ");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列宽自动分配
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Interactive);//可以手动调整
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选项
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);//禁止修改
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//可以单选

    //创建菜单栏
    QMenuBar *menuBar=new QMenuBar(this);

    //添加菜单栏到主窗口中
    this->setMenuBar(menuBar);
    //创建菜单
    QMenu *menu1 = new QMenu("文件(J)",this);
    QMenu *menu2 = new QMenu("视图(O)",this);
    QMenu *menu3 = new QMenu("可视化操作(K)",this);
    QMenu *menu4 = new QMenu("工具(E)",this);
    QMenu *menu5 = new QMenu("帮助(R)",this);


    //菜单栏添加菜单
    menuBar->addMenu(menu1);
    menuBar->addMenu(menu2);
    menuBar->addMenu(menu3);
    menuBar->addMenu(menu4);
    menuBar->addMenu(menu5);


    //创建菜单项
    QAction *action1 = new QAction("新建文件或项目",this);//有图标
    QAction *action2 = new QAction("打开文件或项目",this);//有图标
    QAction *action3 = new QAction("退出",this);

    //菜单添加菜单项
    menu1->addAction(action1);
    menu1->addAction(action2);
    menu1->addSeparator();//插入分割线

    QMenu *menu9 = new QMenu("最近访问的文件",this);
    menu1->addMenu(menu9);//添加二级菜单
    menu9->addAction(new QAction("暂无最近打开项目",this));//二级菜单添加菜单项

    menu1->addAction(action3);

    //工具栏
    QPushButton *portBtn = new QPushButton(this);
    portBtn->setIcon(QIcon("D:/QT/QTxiangmu/123/image/file.png"));	//按钮添加图片
    portBtn->setToolTip("aaaa");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton *portBtn1 = new QPushButton(this);
    portBtn1->setIcon(QIcon("D:/QT/QTxiangmu/123/image/openfile.png"));	//按钮添加图片
    portBtn1->setToolTip("aaaa");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton *portBtn2 = new QPushButton(this);
    portBtn2->setIcon(QIcon("D:/QT/QTxiangmu/123/image/Xrotate.png"));	//按钮添加图片
    portBtn2->setToolTip("aaaa");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton *portBtn3 = new QPushButton(this);
    portBtn3->setIcon(QIcon("D:/QT/QTxiangmu/123/image/Yrotate.png"));	//按钮添加图片
    portBtn3->setToolTip("aaaa");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton *portBtn4 = new QPushButton(this);
    portBtn4->setIcon(QIcon("D:/QT/QTxiangmu/123/image/Zrotate.png"));	//按钮添加图片
    portBtn4->setToolTip("aaaa");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton *portBtn5 = new QPushButton(this);
    portBtn5->setIcon(QIcon("D:/QT/QTxiangmu/123/image/on.png"));	//按钮添加图片
    portBtn5->setToolTip("aaaa");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton *portBtn6 = new QPushButton(this);
    portBtn6->setIcon(QIcon("D:/QT/QTxiangmu/123/image/under.png"));	//按钮添加图片
    portBtn6->setToolTip("aaaa");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton *portBtn7 = new QPushButton(this);
    portBtn7->setIcon(QIcon("D:/QT/QTxiangmu/123/image/behind.png"));	//按钮添加图片
    portBtn7->setToolTip("aaaa");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton *portBtn8 = new QPushButton(this);
    portBtn8->setIcon(QIcon("D:/QT/QTxiangmu/123/image/front.png"));	//按钮添加图片
    portBtn8->setToolTip("aaaa");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton *portBtn9 = new QPushButton(this);
    portBtn9->setIcon(QIcon("D:/QT/QTxiangmu/123/image/right.png"));	//按钮添加图片
    portBtn9->setToolTip("aaaa");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton *portBtn10 = new QPushButton(this);
    portBtn10->setIcon(QIcon("D:/QT/QTxiangmu/123/image/left.png"));	//按钮添加图片
    portBtn10->setToolTip("aaaa");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton *portBtn11 = new QPushButton(this);
    portBtn11->setIcon(QIcon("D:/QT/QTxiangmu/123/image/bigger.png"));	//按钮添加图片
    portBtn11->setToolTip("aaaa");			//鼠标移动到按钮上时显示提示 aaaa

    QPushButton *portBtn12 = new QPushButton(this);
    portBtn12->setIcon(QIcon("D:/QT/QTxiangmu/123/image/smaller.png"));	//按钮添加图片
    portBtn12->setToolTip("aaaa");			//鼠标移动到按钮上时显示提示 aaaa


    ui->toolBar->addWidget(portBtn);
    ui->toolBar->addWidget(portBtn1);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(portBtn2);
    ui->toolBar->addWidget(portBtn3);
    ui->toolBar->addWidget(portBtn4);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(portBtn5);
    ui->toolBar->addWidget(portBtn6);
    ui->toolBar->addWidget(portBtn7);
    ui->toolBar->addWidget(portBtn8);
    ui->toolBar->addWidget(portBtn9);
    ui->toolBar->addWidget(portBtn10);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(portBtn11);
    ui->toolBar->addWidget(portBtn12);
    ui->toolBar->addSeparator();

    //状态栏
    ui->statusbar->setSizeGripEnabled(false);

    //进度条

    ui->statusbar->addWidget(ui->progressBar,50);
    ui->progressBar->setFixedSize(125,15);
    ui->progressBar->setOrientation(Qt::Horizontal);  // 水平方向
    ui->progressBar->setMinimum(0);  // 最小值
    ui->progressBar->setMaximum(100);  // 最大值
    ui->progressBar->setValue(0);  // 当前进度



    //获取actor
    //HexDisplay hexactor;
    //渲染窗口
    //vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

    //for (unsigned int i = 0; i < My_Tree.nodes.size(); i++)
        //{
            //vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
            //actor->SetPosition(My_Tree.nodes[i]->p[0]->x, My_Tree.nodes[i]->p[0]->y, My_Tree.nodes[i]->p[0]->z);
            //renderer->AddActor(hexactor.HexActor(My_Tree.nodes[i]));
            //text
            //temp.push_back(My_Tree.nodes[i]);
        //}
    //vtkSmartPointer<vtkRenderWindow> renderwindow =
            //vtkSmartPointer<vtkRenderWindow>::New();

    //renderwindow->AddRenderer(renderer);

    //renderer->SetBackground(1, 1, 1);

    //renderwindow->Render();

    //ui->qvtkWidget->SetRenderWindow(renderwindow);
}

//void MainWindow::show_picture(int index)
//{
//    QPixmap *m_crtPixmap;
//    m_crtPixmap = new QPixmap(strPathList.at(index));//为了显示第一张图
//    if(NULL != m_crtPixmap)
//    {
//        int with = ui->label_pic->width();
//        int height = ui->label_pic->height();
//        QPixmap fitpixmap = m_crtPixmap->scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 将图片缩放后饱满填充到label_pic控件大小
//        ui->label_pic->setPixmap(fitpixmap);//显示第一张图
//    }
//}

MainWindow::~MainWindow()
{
    delete ui;
}

//判断是否是vols格式
bool MainWindow::isvols(string filename)
{
    string suffixStr = filename.substr(filename.find_last_of('.') + 1);//获取文件后缀
    return suffixStr=="vols"?1:0;
}

void MainWindow::Process_vols(string strpath)
{
    ifstream is(strpath, ifstream::in | ios::binary);
        if (!is)
        {
            cout << "文件不能打开！" << endl;
            return;
        }

        // 2. 计算体数据长度
        is.seekg(0, is.end);
        long long length = is.tellg();
        is.seekg(0, is.beg);
        cout << "文件大小为 " << length / (1024 * 1024) << " MB。\n" << endl;

        // 3.读入文件头
        cout << "开始读入文件头。\n" << endl;
        //文件头结构
        //第一部分：DataFormat;					//图像数据格式,128字节
        //第二部分：SystemInformation;			//系统信息,128字节
        //第三部分：TaskInformation;			//任务信息,128字节
        //第四部分：SampleInformation;			//测试样品信息,128字节
        //第五部分：ProcessParameter;		    //图像处理参数,128字节
        //第六部分：Reserved[1024 - 5 * 128];   //保留，3*128字节
        //第七部分：PseudoColor;				//伪彩色,1024字节

        //读取图像数据格式
        uint Width = 0;					//图像宽度     //考虑初始化
        uint Height = 0;				//图像高度
        uint Depth = 0;					//图像深度
        float maxAttenuation = 0;		//最大衰减系数
        uint DataType = 0;				//体素存储类型: unsigned char=01,unsigned short=02,float=03
        float voxelWidth = 0;			//体素的宽度(mm)
        float voxelDepth = 0;			//体素的高度(mm)
        //char Reserved[128 - 7 * 4];	//保留字节

        is.read((char *)(&Width), sizeof(Width));
        is.read((char *)(&Height), sizeof(Height));
        is.read((char *)(&Depth), sizeof(Depth));
        is.read((char *)(&maxAttenuation), sizeof(maxAttenuation));
        is.read((char *)(&DataType), sizeof(DataType));
        is.read((char *)(&voxelWidth), sizeof(voxelWidth));
        is.read((char *)(&voxelDepth), sizeof(voxelDepth));
        is.ignore(100);                 //丢掉保留字节里的无用内容

        cout << "图像数据格式如下：" << endl;
        cout << "图像宽度为：" << Width << endl;
        cout << "图像高度为：" << Height << endl;
        cout << "图像深度为：" << Depth << endl;
        cout << "最大衰减系数为：" << maxAttenuation << endl;
        cout << "体素存储类型为：" << DataType << endl;
        cout << "体素宽度为：" << voxelWidth << "mm" << endl;
        cout << "体素高度为：" << voxelDepth << "mm\n" << endl;

        //读取系统信息格式
        char Format[9];					//文件标识，”ICTIMAGE”
        Format[8] = '\0';               //结束符
        uint Version = 0;				//文件头版本号
        char EquipmentModel[33];		//CT设备型号
        EquipmentModel[32] = '\0';
        float Current = 0;				//球管电流
        float Voltage = 0;				//球管电压
        char ImageFileName[17];			//图像文件名
        ImageFileName[16] = '\0';
        //char  Reserved[128 - 68];		//保留字节

        is.read((char *)(&Format), sizeof(Format) - 1);
        is.read((char *)(&Version), sizeof(Version));
        is.read((char *)(&EquipmentModel), sizeof(EquipmentModel) - 1);
        is.read((char *)(&Current), sizeof(Current));
        is.read((char *)(&Voltage), sizeof(Voltage));
        is.read((char *)(&ImageFileName), sizeof(ImageFileName) - 1);
        is.ignore(60);                  //丢掉保留字节里的无用内容

        cout << "系统信息如下：" << endl;
        cout << "文件标识：" << Format << endl;
        cout << "文件头版本号：" << Version << endl;
        cout << "CT设备型号：" << EquipmentModel << endl;
        cout << "球管电流：" << Current << endl;
        cout << "球管电压：" << Voltage << endl;
        cout << "图像文件名：" << ImageFileName << "\n" << endl;

        //读取测试任务信息

        char DateTime[21];				//测试日期及时间(2003/07/10 16:35:12 )
        DateTime[20] = '\0';
        char TaskName[33];				//测试任务名称
        TaskName[32] = '\0';
        char Operator[17];				//测试人员姓名
        Operator[16] = '\0';
        char SubmitUnit[33];			//送检单位
        SubmitUnit[32] = '\0';
        //char Reserved[128 - 100];			//保留字节

        is.read((char *)(&DateTime), sizeof(DateTime) - 1);
        is.read((char *)(&TaskName), sizeof(TaskName) - 1);
        is.read((char *)(&Operator), sizeof(Operator) - 1);
        is.read((char *)(&SubmitUnit), sizeof(SubmitUnit) - 1);
        is.ignore(28);

        cout << "测试日期及时间：" << DateTime << endl;
        cout << "测试任务名称：" << TaskName << endl;
        cout << "测试人员姓名：" << Operator << endl;
        cout << "送检单位：" << SubmitUnit << "\n" << endl;



        //略去测试样品信息
        is.ignore(128);


        //读取图像处理参数

        uint WindowWidth = 0;				//窗宽
        uint WindowPosition = 0;			//窗位
        float StartPoint[3];			//长度测量起点坐标
        float EndPoint[3];				//长度测量终点坐标
        //char Reserved[128 - 8 * 4];			//保留字节

        is.read((char *)(&WindowWidth), sizeof(WindowWidth));
        is.read((char *)(&WindowPosition), sizeof(WindowPosition));
        is.read((char *)(&StartPoint), sizeof(StartPoint));
        is.read((char *)(&EndPoint), sizeof(EndPoint));
        is.ignore(96);

        cout << "图像处理参数如下：" << endl;
        cout << "窗宽：" << WindowWidth << endl;
        cout << "窗位：" << WindowPosition << endl;
        cout << "长度测量起点坐标：" << StartPoint << endl;
        cout << "长度测量终点坐标：" << EndPoint << endl;



        //跳过保留长度部分
        is.ignore(384);



        //跳过伪彩色部分
        is.ignore(1024);


        //读取伪彩色信息
        //uchar Red[256];				//红色
        //uchar Green[256];			//绿色
        //uchar Blue[256];			//蓝色
        //uchar Alpha[256];			//不透明度

        //is.read((char *)(&Red), sizeof(Red));
        //is.read((char *)(&Green), sizeof(Green));
        //is.read((char *)(&Blue), sizeof(Blue));
        //is.read((char *)(&Alpha), sizeof(Alpha));

        /*cv::Mat ImgData(Width, Height, CV_32F);
        for (int i = 0; i < Width; ++i)
        {
            for (int j = 0; j < Height; ++j)
            {
                char* a = (char*)(&ImgData.at<float>(i, j));
                is.read(a, sizeof(float));

            }
        }*/

    #if 0
        //读取体数据   每个数据都是FLOAT类型
        vector<vector<vector<float>>> result(Width, vector<vector<float>>(Height, vector<float>(Depth, 0)));

        for (uint k = 0; k < Depth; ++k)
        {
            for (uint i = 0; i < Width; ++i)
            {
                for (uint j = 0; j < Height; ++j)
                {
                    float temp = 0;
                    is.read((char*)(&temp), sizeof(temp));
                    temp = round(temp * 255 / maxAttenuation);
                    result[i][j][k] = temp;
                }
            }
        }

    #endif

    #if 1
        /*vector<vector<vector<float>>> result(Width, vector<vector<float>>(Height, vector<float>(Depth, 0)));


        int cols = result.size();
        int rows = result[0].size();*/
        vector<Mat> all_image;

        for (uint k = 0; k < Depth; ++k)
        {
            Mat img(Height, Width, CV_32F);
            for (uint i = 0; i < Height; ++i)
            {
                for (uint j = 0; j < Width; ++j)
                {


                    char* a = (char*)(&img.at<float>(Height - 1 - i, j));
                    is.read(a, sizeof(float));
                    /*float temp = 0;
                    is.read((char*)(&temp), sizeof(temp));
                    temp = round(temp / maxAttenuation);
                    img.at<float>(Height - 1 - i, j)=temp;*/
                }
            }
            all_image.push_back(img);
        }


        Mat tmp;
        normalize(all_image[59], tmp, 0, 1, NORM_MINMAX);
        namedWindow("new", WINDOW_NORMAL);
        imshow("new", tmp);
        waitKey(0);
    #endif

        is.close();
}

void MainWindow::on_input_picture_clicked()
{
        QFileDialog fileDlg(this);
        fileDlg.setWindowTitle("Choose Pictures/Voxels");
        QStringList qstrFilters;//设置文件过滤器的list
        qstrFilters<<"Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm *.vols)";
        qstrFilters<<"Any files (*)";
        fileDlg.setNameFilters(qstrFilters);//设置文件过滤器
        fileDlg.setFileMode(QFileDialog::ExistingFiles);//设置能选择多个文件，如果是单个文件就写成QFileDialog::ExistingFile
        if(fileDlg.exec() == QDialog::Accepted)
        {
            vector<Mat> images; //储存原始图片
            vector<Mat> imgGray; //储存进行二值化后的灰度图片
            strPathList = fileDlg.selectedFiles();//得到用户选择的多个文件的路径的list
            string path=strPathList[0].toStdString();
            if(isvols(path))
            {
                Process_vols(path);
            }
            //QPixmap pixmapTemp;

            for(int i = 0;i<strPathList.count();i++)
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
                //main_AllImage_m.push_back(*img_G);

                //show_picture(cur_picture);
            }
        }
        else
        {
            QMessageBox mesg;
            mesg.warning(this,"警告","打开图片失败!");
            return;
        }
}

void MainWindow::on_pushButton_2_clicked()
{
    //获取txt
    //vector<Hexahedral3D*> temp;
    int max_lenth = ui->spinBox->value();
    int min_lenth = ui->spinBox_2->value();
    int interval = ui->spinBox_3->value(); //图片间隔设置为1
    //cout<<max_lenth<<" "<<min_lenth<<" "<<interval;
//    unsigned int max_lenth = 16;
//    unsigned int min_lenth = 16;
//    unsigned int interval = 1; //图片间隔设置为1
    //ui->statusbar->showMessage(tr("正在处理"));
    My_Voxel vox(interval);
    vox.AllImage_m=All_images;
    vox.cols = vox.AllImage_m[0].cols;
    vox.rows = vox.AllImage_m[0].rows;
    datetime = QTime::currentTime();
    QString outputtext = datetime.toString()+tr("  成功读取初始体数据");
    ui->history_output->append(outputtext);
    ui->progressBar->setValue(25);  // 当前进度
    OcTree My_Tree(vox, max_lenth, min_lenth); //建立初始六面体网格
    datetime = QTime::currentTime();
    outputtext = datetime.toString()+tr("  成功建立六面体网格");
    ui->history_output->append(outputtext);
    outputtext = "Maximum image size:"+QString::number(vox.getMaxLenthAll(),10);
    ui->history_output->append(outputtext);
    ui->progressBar->setValue(50);  // 当前进度
    My_Tree.build_adaptive_tree();
    outputtext = "Number of surface meshes:"+QString::number(My_Tree.nodes.size(),10);
    ui->history_output->append(outputtext);
    //cout << "Number of surface meshes:" << My_Tree.nodes.size() << endl;

    if(ui->output_text->isChecked())
    {
        //获取txt
        String path= ui->textpath->text().toStdString();//输入格式：.../文件名字.txt
        CreatTxt(path,My_Tree.m_node1, My_Tree.m_node2, My_Tree.m_node3);
        //输出日志
        datetime = QTime::currentTime();
        QString outputtext = datetime.toString()+tr("  成功输出txt文件");
        ui->history_output->append(outputtext);
    }
    datetime = QTime::currentTime();
    outputtext = datetime.toString()+tr("  已完成！");
    ui->history_output->append(outputtext);
    //ui->statusbar->showMessage(tr("已完成！"));
    ui->progressBar->setValue(100);  // 当前进度
}

void MainWindow::on_InputButton_clicked()
{
    int RowCont;
    RowCont=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(RowCont);
}

void MainWindow::on_deletButton_clicked()
{
    int rowIndex = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(rowIndex);
}


