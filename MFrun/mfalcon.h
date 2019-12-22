#ifndef MFALCON_H
#define MFALCON_H

#include <QTime>
#include <QEvent>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QColor>
#include <QPainter>
#include <QRect>

class MFalcon : public QGraphicsItem
{
public:
    explicit MFalcon();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setEngine(bool vel);
    bool EngineOn();

protected:
    void advance(int step);

private:
    bool engineOn = false;
    qreal speed;
    QPixmap* pic = new QPixmap(":/images/star-wars-millenium-falcon.png");
    qreal dx, dy;
    qreal x, y;
    qreal w, h;
    int index;
};


#endif // MFALCON_H
