#include "gsshaperectangeitem.h"
#include <QPainter>//绘图操作
#include <QDebug>
#include <iostream>
using namespace std;
//矩形
GsShapeRectangeItem::GsShapeRectangeItem(QRectF rectF, QGraphicsObject *parent)://构造函数的定义，接收一个QRectF类型的参数rectf和一个指向QGraphicsObject的父对象的指针parent
    GsShapeBaseItem(rectF,parent)//并调用了基类GsShapeBaseItem的构造函数

{


}

GsShapeRectangeItem::~GsShapeRectangeItem()//析构函数不带有任何参数，也没有返回值
{

}

bool GsShapeRectangeItem::hasSelected(QPointF pos)//函数定义，用于判断给定的点是否在矩形范围内
{
    return shape().contains(pos);
}

GsShapeType GsShapeRectangeItem::shapeType() const//函数定义，返回矩形的形状类型
{
    return Shape_Rectange;
}

void GsShapeRectangeItem::printSize() const
{

    auto width = m_firstPoint.x() - m_lastPoint.x();
    auto height = m_firstPoint.y() - m_lastPoint.y();
    if(width < 0) width = -width;
    if(height < 0) height = -height;
    //cout << "WIDTH: " << width << " HEIGHT: " << height << std::endl;
    cout << " x1: " << m_firstPoint.x() << "y1:" << m_lastPoint.y() << std::endl;
    cout << " x2: " << m_lastPoint.x() << "y2:" << m_firstPoint.y() << std::endl;

}


void GsShapeRectangeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)//函数定义，用于绘制矩形
{
    painter->setRenderHint(QPainter::Antialiasing);//用于绘图时的抗锯齿效果
    QColor color = Qt::red;//(rand()%255,rand()%255,rand()%255);//定义一个颜色变量，并赋值为Qt中的红色
    //painter->setBrush(color);
    painter->setPen(QPen(color,4,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));//设置绘画时的画笔样式，包括颜色、线宽、线的样式、线的端点和连接方式
    painter->drawRect(QRectF(m_firstPoint,m_lastPoint));//绘制一个矩形，矩形的大小由成员变量m_firstPoint和m_lastPoint指定
    this->printSize();
}
