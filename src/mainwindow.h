#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include "Voxel.h"
#include "OcTree.h"

#ifndef INITIAL_OPENGL
#define INITIAL_OPENGL
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType)
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void CreatTxt(string& pathName,const vector<Hexahedral3D*>& m_node1, const vector<Hexahedral3D*>& m_node2, const vector<Hexahedral3D*>& m_node3);
    //void show_picture(int index);
    vector<Mat> All_images;
    bool isvols(string path);//判断是否是vols格式
    void Process_vols(string strpath);//处理vols格式
private slots:
    void on_input_picture_clicked();

    void on_pushButton_2_clicked();

    void on_deletButton_clicked();

    void on_InputButton_clicked();

private:
    unsigned int max_lenth;//网格最大值
    unsigned int min_lenth;//网格最小值
    unsigned int interval;//图片间隔
    QTime datetime;//时间
    QStringList strPathList;//读取图片路径
    unsigned int cur_picture;//当前显示的图片
    Ui::MainWindow *ui;

};


#endif // MAINWINDOW_H
