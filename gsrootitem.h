#ifndef GSROOTITEM_H
#define GSROOTITEM_H

#include <QGraphicsObject>
#include "gstempcanvaslayer.h"
#include "gscommondef.h"
#include "gsshapeitem.h"
#include "gsshapefactory.h"
#include <vector>
struct ShapeInfo
{
    QPointF firstPos;
    GsShapeType type;
};
struct STU_Rect {std::string labelName; QPoint x; QPoint y;int w;int h;};
class GsRootItem : public QGraphicsObject
{
public:
    std::vector<STU_Rect> vStuLine;
    std::vector<STU_Rect> vStuRect;
    std::vector<STU_Rect> vStuCirc;
    std::vector<STU_Rect> vStuOval;
    explicit GsRootItem(const QSizeF & size,QGraphicsObject * parent = nullptr);
    ~GsRootItem();

    void drawPress(int id,const QPointF &p);
    void drawMove(int id,const QPointF &lastPoint,const QPointF &curPoint);
    void drawRelease(int id, const QPointF &point);

    void setCurType(GsShapeType type){m_curType = type;}
    GsShapeType getCurType()const{
        return m_curType;
    }
    int type()const{return Type_RootItem;}

    void clear();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);


private:
    void drawRealShape(GsShapeType type,QPointF p1,QPointF p2);
private:
    QSizeF m_size;
    GsTempCanvasLayer * m_pTempLayer = nullptr;
    QMap<int,ShapeInfo> m_Objs;
    GsShapeType m_curType = Shape_Line;
    GsShapeFactory * m_pShapeFactory = nullptr;

};

#endif // GSROOTITEM_H
