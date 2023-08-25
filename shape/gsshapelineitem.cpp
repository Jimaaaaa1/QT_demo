#include "gsshapelineitem.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QVector2D>
//直线
GsShapeLineItem::GsShapeLineItem(QRectF rectF, QGraphicsObject *parent):
    GsShapeBaseItem(rectF,parent)
{
}

GsShapeLineItem::~GsShapeLineItem()
{

}

bool GsShapeLineItem::hasSelected(QPointF pos)
{    
    QPainterPath path;//is point in line
    QVector<QPointF> qvector;
    qvector.append(QPointF(m_firstPoint.x()-5,m_firstPoint.y()));
    qvector.append(QPointF(m_firstPoint.x()+5,m_firstPoint.y()));
    qvector.append(QPointF(m_lastPoint.x()+5,m_lastPoint.y()));
    qvector.append(QPointF(m_lastPoint.x()-5,m_lastPoint.y()));

    QPolygonF ploygon(qvector);
    path.addPolygon(ploygon);

    return path.contains(pos);
}

GsShapeType GsShapeLineItem::shapeType() const
{
    return Shape_Line;
}

void GsShapeLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QColor color = Qt::red;//(rand()%255,rand()%255,rand()%255);
    painter->setPen(QPen(color,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    //painter->setBrush(color);
    painter->drawLine(m_firstPoint,m_lastPoint);
}
