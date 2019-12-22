#ifndef ASTRO_H
#define ASTRO_H

#include <QEvent>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QColor>
#include <QPainter>
#include <QRect>

class Astro : public QGraphicsItem
{
public:
    explicit Astro(qreal width, qreal height);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


protected:
    void advance(int step);

private:
    QPixmap pm[2];
    QPixmap* pic;
    qreal dx, dy;
    qreal x, y;
    qreal w, h;
};


#endif // ASTRO_H
