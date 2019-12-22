#include "ball.h"

Ball::Ball(QGraphicsEllipseItem* parent)
{
    dx = 1.00;
    dy = 1.00;
    x = 0.0;
    y = 0.0;
    w = 20.0;
    h = 20.0;
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(-w/2, -h/2, w, h);
}

QRectF Ball::boundingRect() const
{
    qreal adjust = 1.0;
    return QRectF(-w/2 - adjust, -h/2 - adjust, w + adjust, h + adjust);
}

void Ball::advance(int step)
{
    qreal velY = dy;
    qreal velX = dx;
    qreal angle = atan2(dy, dx);
    if(!scene()->collidingItems(this).isEmpty() && !collided)
    {
        QList<QGraphicsItem *> colliding_items = collidingItems();

        for(int i = 0; i < colliding_items.size(); i++)
        {
            if(colliding_items[i]->rotation() == 90)
            {
                if(dy >= 0 && dx < 0)
                {
                    dy = dy*sin(angle) + 0.5;
                    dx = dx*cos(angle) + 0.5;
                }
                else if((dy < 0 && dx < 0)){
                    dy = -dy*sin(angle) - 0.5;
                    dx = dx*cos(angle) + 0.5;
                }
                else if((dy < 0 && dx >= 0)){
                    dy = -dy*sin(angle) - 0.5;
                    dx = -dx*cos(angle) - 0.5;
                } else {
                    dy = dy*sin(angle) + 0.5;
                    dx = -dx*cos(angle) - 0.5;
                }
            } else      // Rotation == 0
            {
                if(dy >= 0 && dx < 0)
                {
                    dy = -dy*sin(angle) - 0.5;
                    dx = -dx*cos(angle) - 0.5;
                }
                else if((dy < 0 && dx < 0)){
                    dy = dy*sin(angle) + 0.5;
                    dx = -dx*cos(angle) - 0.5;
                }
                else if((dy < 0 && dx >= 0)){
                    dy = dy*sin(angle) + 0.5;
                    dx = dx*cos(angle) + 0.5;
                } else {
                    dy = -dy*sin(angle) - 0.5;
                    dx = dx*cos(angle) + 0.5;
                }
            }
           }
        collided = true;
    } else {
        collided = false;
    }

    if (step == 0)
        return;
    x = this->pos().rx();
    y = this->pos().ry();

    x = x + speed*dx;
    y = y + speed*(dy);

    setPos(x, y);
//    for(int i = 0; i<(300000); i++)
//    {
//        if(velY == dy && velX == dx)
//            collided = false;
//    }
    if(y >= YMAX || y < -YMAX)
    {
        scene()->removeItem(this);
    }
}

QPainterPath Ball::shape() const
{
    QPainterPath path;
    path.addRect(-w/2, -h/2, w, h);
    return path;
}

void Ball::setSpeed(int spd)
{
    speed = spd;
}
