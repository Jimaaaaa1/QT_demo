#include "gstempcanvaslayer.h"
#include "gscommondef.h"
#include <QDebug>//用于输出调试信息
#include <iostream>
using namespace std;
//是GsTempCanvasLayer的类的实现，这个类是一个自定义的QGraphicsObject子类，用于创建一个临时画布层，用于绘制形状
GsTempCanvasLayer::GsTempCanvasLayer(const QSizeF &size, QGraphicsObject *parent)://类的构造函数，接收一个大小参数和一个父对象参数。调用父类构造函数并传入父对象参数
    QGraphicsObject (parent),
    m_size(size)//初始化列表，初始化父类和成员变量m_size
{
    setCacheMode(DeviceCoordinateCache);//将缓存模式设置为DeviceCoordinateCache
    initCanvas();//调用initCanvas()函数进行画布的初始化
}

GsTempCanvasLayer::~GsTempCanvasLayer()//类的析构函数，清理内存，输出调试信息
{
    SAFE_DELETE(m_pTempPainter);//使用宏SAFE_DELETE删除m_pTempPainter指针所指向的对象
    SAFE_DELETE(m_pTempCanvas);//使用宏SAFE_DELETE删除m_pTempCanvas指针所指向的对象
    qDebug() << "--->>>Lynn<<<---" << __FUNCTION__;//输出调试信息，显示函数的名称
}

void GsTempCanvasLayer::clear()//清空画布的函数
{
    m_pTempCanvas->fill(Qt::transparent);//使用Qt的函数fill（）将画布填充为透明
    this->update();//使用Qt的函数update（）更新画布
}

QRectF GsTempCanvasLayer::boundingRect() const//用于返回图形项的边界矩形
{
    return  QRectF(0,0,m_size.width(),m_size.height());//返回以原点（0，0）为左上角，m_size为宽度和高度的矩形
}

void GsTempCanvasLayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)//重写QGraphicsObject的虚函数，用于绘制图形项
{
    painter->drawImage(0,0,*m_pTempCanvas);//使用QPainter的drawlmage（）函数绘制画布
}

void GsTempCanvasLayer::drawShape(GsShapeType type, QPointF p1, QPointF p2)//绘制形状的函数，接收形状类型和两个点作为参数
{
    m_pTempCanvas->fill(Qt::transparent);//清空画布，填充透明
    m_pTempPainter->setRenderHint(QPainter::Antialiasing, true);//设置绘制抗锯齿渲染
    m_pTempPainter->setCompositionMode(QPainter::CompositionMode_Source);//设置绘制的组合模式为Source
    m_pTempPainter->setPen(QPen(Qt::red,3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));//设置绘制的画笔属性
    switch(type){//根据形状类型进行不同的绘制操作
    case Shape_Line://用于直线形状
        m_pTempPainter->drawLine(p1,p2);//使用QPainter的drawLine（）函数绘制直线
        break;
    case Shape_Rectange://矩形
        m_pTempPainter->drawRect(QRectF(p1,p2));//使用QPainter的drawRect（）函数绘制矩形
        break;
    case Shape_Circle://对于圆形形状
        m_pTempPainter->drawEllipse(p1.x(),p1.y(),//使用QPainter的drawEllipse函数绘制圆形
                             qAbs(p2.y() - p1.y()),
                             qAbs(p2.y() - p1.y()));
        break;
    case Shape_Oval://椭圆
        m_pTempPainter->drawEllipse(QRectF(p1,p2));//使用QPainter的drawEllipse函数绘制椭圆
        break;
    default:
        break;
    }
    update();//使用update更新图形项
}

void GsTempCanvasLayer::initCanvas()//初始化画布的函数
{
    m_pTempCanvas = new QImage(m_size.toSize(),QImage::Format_ARGB32_Premultiplied);//使用Qlmage的构造函数创建一个画布
    m_pTempCanvas->fill(Qt::transparent);//使用Qt的函数fill（）将画布填充为透明
    m_pTempPainter = new QPainter(m_pTempCanvas);//创建一个QPainter对象，并指定画布为绘制的设备
}
