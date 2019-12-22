#include "defs.h"

#ifndef BALL_H
#define BALL_H

#include <QEvent>
#include <QGraphicsEllipseItem>
#include <stdlib.h>
#include <QGraphicsScene>
#include <QPainter>
#include <QSqlQuery>
#include <cmath>
#include <QtDebug>
#include <QTime>

class Ball : public QGraphicsEllipseItem
{

public:
    explicit Ball(QGraphicsEllipseItem* parent = Q_NULLPTR);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setSpeed(int spd);

protected:
    void advance(int step);

private:
    bool collided = false;
    qreal x;
    qreal y;
    qreal h;
    qreal w;
    qreal dx;
    qreal dy;
    int speed;
};

#endif // BALL_H
