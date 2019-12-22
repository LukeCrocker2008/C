#include "mfalcon.h"
#include <QDebug>
#include <cmath>

MFalcon::MFalcon()
{
    dx = 0.0;
    dy = 0.0;
    x = 0.0;
    y = 0.0;
    w = 100.0;
    h = 100.0;
}

void MFalcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-w/2, -h/2, pic->scaled(w, h));
}

QRectF MFalcon::boundingRect() const
{
    qreal adjust = 1.0;
    return QRectF(-w/2 - adjust, -h/2 - adjust, w + adjust, h + adjust);
}

void MFalcon::advance(int step)
{
    if (engineOn == false)
        return;
    qreal th = this->rotation() * (3.14159/180); // Convert to radians
    x = this->pos().x();
    y = this->pos().y();
    dx = speed * cos(th - 3.14159/2);
    dy = -1 * speed * sin(th + 3.14159/2);

    x = x + dx;
    y = y + dy;

    setPos(x, y);
}

QPainterPath MFalcon::shape() const
{
    QPainterPath path;
    path.addRect(-w/2, -h/2, w, h);
    return path;
}

void MFalcon::setEngine(bool vel)
{        
    if(engineOn == false)
    {
        engineOn = true;
        if (vel == true)
            speed = speed + 0.25;
    } else {
        if(speed <= 0.0)
        {
            engineOn = false;
            speed = 0.0;
        }
    }
    if (vel == true)
        speed = speed + 0.25;
    else
        speed = speed - 0.25;
}

bool MFalcon::EngineOn()
{
    return engineOn;
}
