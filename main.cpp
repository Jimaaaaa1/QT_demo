#include "gsmainscene.h" //引入自定义的头文件
#include <QApplication> //管理应用程序
#include <QDesktopWidget>//访问桌面有关信息
#include <QGraphicsView>//用于显示图形
#include <QPixmap>//用于处理图像
#include <iostream>
#include "form.h"
using namespace std;



QScopedPointer<QGraphicsView>  view{nullptr};

int main(int argc, char *argv[]) //输入参数argc和argv，这是用于处理命令行参数的标准C++语法
{
    QApplication a(argc, argv);//创建一个QApplication实例，命名为a。QApplication用于初始化Qt应用程序，并处理事件

    //QSize desktopSize = qApp->desktop()->screenGeometry().size();//返回一个QSize对象，表示桌面的宽度和高度，获取桌面大小
    QImage image=QImage("D:/Work/QT/project/GraphicsShape-master/2.jpg");
    //image = image.scaledToWidth(desktopSize.width());
    QSize imageSize = image.size();
    view.reset(new QGraphicsView());//创建QGraphicsView对象view,用于显示图形
    QScopedPointer<GsMainScene> pScene(new GsMainScene(imageSize));//创建GsMainScene对象pScene，并传入桌面大小作为参数.
    view->setScene(pScene.data());//将场景pScene设置为view的场景
    view->resize(imageSize);//将view的大小调整为桌面大小
    view->show();//显示view
    Form f;
    f.show();
//    QScopedPointer<QGraphicsView>  view1(new QGraphicsView());
//    view->setParent(view1.get());
//    view1->show();

    return a.exec();//调用a.exec()，进入Qt应用程序的事件循环，并开始处理事件

}

