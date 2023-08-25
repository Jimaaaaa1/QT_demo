#include "gsmainscene.h" //导入头文件
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPixmapCache>
#include <QDebug>
#include "gsshapebaseitem.h"
#include <QPixmap>
#include <iostream>
#include <QPainter>
#include "util.h"
using namespace std;

GsRootItem * m_pRootItem;
GsMainScene::GsMainScene(const QSizeF &size, QObject *parent) //GsMainScene类的构造函数，它接收一个QSizeF类型的参数size和一个可选的QObject类型的指针parent
    : QGraphicsScene(QRectF(0, 0, size.width(), size.height()), parent)//调用QGraphicsScene构造函数，传入一个QRectF类型的矩形区域和父对象parent
{

    m_pRootItem = new GsRootItem(size);//创建一个GsRootItem类对象，并使用size初始化构造函数
    m_pRootItem->setOpacity(0.3);//设置m_pRootItem的不透明度为0.3
    addPixmap(QPixmap("D:/Work/QT/project/GraphicsShape-master/2.jpg"));
    addItem(m_pRootItem);//将m_pRootItem添加到场景中
//    QPixmapCache::setCacheLimit(204800);
     QPixmapCache::setCacheLimit(204);//设置QPixmapCache的缓存限制为204，控制缓存的大小
     ::m_pRootItem = m_pRootItem;

}

GsMainScene::~GsMainScene()//空析构函数
{
}

void GsMainScene::mousePressEvent(QGraphicsSceneMouseEvent *e)//重写mousePressEvent事件处理方法。当鼠标按下时触发该事件
{
    scenePress(1,e->scenePos());//调用scenePress方法处理鼠标按下事件，并传入参数id（为1）和鼠标按下的场景坐标
    QGraphicsScene::mousePressEvent(e);//调用QGraphicsScene的mousePressEvent方法，以将事件传递给基类处理
}

void GsMainScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)//重写mouseMoveEvent事件处理方法，当鼠标移动时触发该事件
{
    sceneMove(1,e->lastScenePos(),e->scenePos());//调用sceneMove方法处理鼠标移动时间，并传入参数id（为1）、上一个场景坐标和当前场景坐标
    QGraphicsScene::mouseMoveEvent(e);//调用QGraphicsScene的mouseMoveEvent方法，以将事件传递给基类处理
}

void GsMainScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)//重写mouseReleaseEvent事件处理方法，当鼠标释放时触发该事件。
{
    sceneRelease(1,e->scenePos());//调用sceneRelease方法处理鼠标施放时间，并传入参数id（为1）和鼠标释放的场景坐标
    QGraphicsScene::mouseReleaseEvent(e);//调用QGraphicsScene的mouseReleaseEvent方法，以将事件传递给基类处理
}

void GsMainScene::keyPressEvent(QKeyEvent *e)//重写keyPressEvent事件处理方法。当按下键盘案件时触发该事件
{
    QPixmap pixmap = QPixmap("D:/Work/QT/project/GraphicsShape-master/2.jpg");
    switch (e->key()) {//根据按下的键盘案件进行判断
    case Qt::Key_1:
        m_pRootItem->setCurType(Shape_Line);//设置m_pRootltem的当前形状类型为直线
        break;
    case Qt::Key_2:
        m_pRootItem->setCurType(Shape_Rectange);//矩形
        break;
    case Qt::Key_3:
        m_pRootItem->setCurType(Shape_Circle);//圆形
        break;
    case Qt::Key_4:
        m_pRootItem->setCurType(Shape_Oval);//椭圆
        break;
    case Qt::Key_Up:
        view->scale(1.2,1.2);
        //m_pRootItem->setScale(m_pRootItem->scale() + 0.1);//设置m_pRootltem的缩放比例减少0.1
        update();
        break;
    case Qt::Key_Down:
        view->scale(1/1.2,1/1.2);
        //m_pRootItem->setScale(m_pRootItem->scale() - 0.1);//设置m_pRootltem的缩放比例减少0.1
        update();
        break;
    case Qt::Key_Delete:
        m_pRootItem->clear();//清空m_pRootltem上的所有图形项
        break;
    default:
        break;
    }
}

bool GsMainScene::scenePress(int id, const QPointF &pos)//自定义函数scenePress，用于处理按下场景事件。它接收一个id和点的坐标pos
{
    if(!isHitItem(pos)){
        m_pRootItem->drawPress(id,pos);
    }
    return true;
}

bool GsMainScene::sceneMove(int id, const QPointF &prepos, const QPointF &pos)
{
    m_pRootItem->drawMove(id,prepos,pos);
    return true;
}

bool GsMainScene::sceneRelease(int id, const QPointF &pos)
{
    m_pRootItem->drawRelease(id,pos);
//    int width = m_pRootItem->
    return true;
}

bool GsMainScene::isHitItem(QPointF p)//定义了判断是否点击了图形项的函数isHitItem
{
    QList<QGraphicsItem*> items = this->items(p);//通过调用场景的items函数获取鼠标点击位置的图形项列表
    foreach (QGraphicsItem * item,items) {//遍历列表中的每个图形项
        GsShapeBaseItem * i = dynamic_cast<GsShapeBaseItem*>(item);//使用dynamic_cast转换为GsShapeBaseItem类
        if(!i){//判断是否为图形项类型
            continue;
        }
        if(i->type() == Type_ShapeItem){
            if(i->hasSelected(p)){//hasSelected函数判断点击位置是否在图形项内
                return true;
            }
            return true;
        }
    }
    return false;
}




