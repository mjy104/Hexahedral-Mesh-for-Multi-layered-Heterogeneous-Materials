#include "QtWidgetsApplication2.h"
#include <QtWidgets/QApplication>

//***********************************
//说明：一个简单的VTK例子
//时间：2020.08.10
//作者：BOO
//********************************


int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QtWidgetsApplication2  w;
	w.show();

	return a.exec();
}