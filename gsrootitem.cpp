#include "gsrootitem.h"
#include <QDebug>//用于输出调试信息
#include "gsshapebaseitem.h"
#include "gsshapelineitem.h"
#include <QGraphicsScene>
#include <QDebug>
//实现了一个名为GsRootltem的类，他是QGraphicsObject的子类，并在QGraphicsScene中充当根项。GsRootltem类用于管理画布上的绘制操作和图形项。
GsRootItem::GsRootItem(const QSizeF &size, QGraphicsObject *parent)://类的构造函数，接收一个大小参数和一个父对象参数。调用父类构造函数并传入父对象参数
    QGraphicsObject (parent),
    m_size(size)//初始化列表，初始化父类和成员变量m_size
{
    m_pTempLayer = new GsTempCanvasLayer(size,this);//创建一个GsTempCanvasLayer类的对象，作为临时画布层，传入构造函数中的尺寸，并将当前对象设置为其父项
    m_pTempLayer->setZValue(10);//将临时画布层的Z值设置为10，用于调整其在场景中的图层顺序。

    m_pShapeFactory = new GsShapeFactory();//创建一个GsShapeFactory类的对象，用于创建图形项
}

GsRootItem::~GsRootItem()//GsRootltem类的析构函数
{
    SAFE_DELETE(m_pShapeFactory);//释放m_pShapeFactory对象的内存
}

void GsRootItem::drawPress(int id, const QPointF &p)//绘制操作按下时的处理函数，根据给定的标识符id和坐标p
{
    ShapeInfo info;//创建一个ShapeInfo结构体对象，并插入到m_Objs容器中
    info.firstPos = p;
    info.type = getCurType();
    m_Objs.insert(id,info);
}

void GsRootItem::drawMove(int id, const QPointF &lastPoint, const QPointF &curPoint)//绘制操作移动时的处理函数。
{
    if(!m_Objs.contains(id)){//如果容器m_Objs中存在给定的id，就获取对应的ShapeInfo对象，通过调用临时画布层的drawShape（）方法绘制形状
        return;
    }
    ShapeInfo info = m_Objs.value(id);
    m_pTempLayer->drawShape(info.type,info.firstPos,curPoint);
}

void GsRootItem::drawRelease(int id, const QPointF &point)//绘制操作释放时的处理函数
{
    if(!m_Objs.contains(id)){//如果容器m_Objs中存在给定的id，就获取对应的ShapeInfo对象
        return;
    }
    ShapeInfo info = m_Objs.value(id);
    drawRealShape(info.type,info.firstPos,point);//调用drawRealShape（）方法绘制真是的形状
    m_Objs.remove(id);//然后从从其中移除该对象，并清空临时画布层
    m_pTempLayer->clear();
}

void GsRootItem::clear()//清空画布上的所有图形项。遍历子项列表。
{
    QList<QGraphicsItem*> items = this->childItems();
    QList<QGraphicsItem*>::iterator it = items.begin();
    while(it != items.end()){
        QGraphicsItem* item = *it++;
        if(item->type() == Type_ShapeItem){//如果子项是图形项，则删除该子项。
            delete item;
            item = nullptr;
        }
    }
}

QRectF GsRootItem::boundingRect() const //返回画布的边界矩形
{
    return  QRectF(0,0,m_size.width(),m_size.height());
}

void GsRootItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)//绘制函数，将画布以白色矩形填充
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::white);
    painter->drawRect(this->boundingRect());
}
void GsRootItem::drawRealShape(GsShapeType type, QPointF p1, QPointF p2)//根据给定的图形类型和两个点的坐标，绘制真实的形状。首先根据坐标计算绘制区域的矩形，然后使用图形工厂对象创建相应的图形项。
{
    //计算图形绘制区域
    QRectF rect;
    rect.setX(qMin(p1.x(),p2.x()));
    rect.setY(qMin(p1.y(),p2.y()));
    if(type == Shape_Circle){
        rect.setWidth(qAbs(p1.y() - p2.y()));
        rect.setHeight(qAbs(p1.y() - p2.y()));
    }
    else{
        rect.setWidth(qAbs(p1.x() - p2.x()));
        rect.setHeight(qAbs(p1.y() - p2.y()));
    }
    rect.adjust(-5,-5,5,5);
    GsShapeBaseItem * item = m_pShapeFactory->getShapeItem(type,rect,this);
    item->drawShape(p1,p2);//最后调用图形项的drawShape（）方法绘制形状。

    STU_Rect tmpRect;
    tmpRect.labelName = type;
    tmpRect.x.setX(std::min({p1.x(), p2.x()}));
    tmpRect.x.setY(std::min({p1.y(), p2.y()}));
    tmpRect.y.setX(std::max({p1.x(), p2.x()}));
    tmpRect.y.setY(std::max({p1.y(), p2.y()}));
    tmpRect.w = tmpRect.y.x() - tmpRect.x.x();
    tmpRect.h = tmpRect.y.y() - tmpRect.x.y();
    switch (type) {
    case Shape_Line:
        vStuLine.push_back(tmpRect);
        break;
    case Shape_Rectange:
        vStuRect.push_back(tmpRect);
        break;
    case Shape_Circle:
        vStuCirc.push_back(tmpRect);
        break;
    case Shape_Oval:
        vStuOval.push_back(tmpRect);
        break;
    default:
        break;
    }
    //vStuRect.pop_back();
    //vStuRect.swap();
    qDebug()<<vStuLine.size()<<vStuRect.size()<<vStuCirc.size()<<vStuOval.size();
}
