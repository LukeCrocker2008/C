#include "astro.h"
#include <QDebug>
#include <stdlib.h>

Astro::Astro(qreal width, qreal height)
{
    pm[0] = QPixmap(":/images/1346943991.png");
    pm[1] = QPixmap(":/images/c10015.png");
    pic = new QPixmap(pm[qrand() % 2]);

    dx = 0.00;
    dy = 5.00;
    x = 0.0;
    y = 0.0;
    w = width;
    h = height;
}

void Astro::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-w/2, -h/2, pic->scaled(w, h));
}

QRectF Astro::boundingRect() const
{
    qreal adjust = 1.0;
    return QRectF(-w/2 - adjust, -h/2 - adjust, w + adjust, h + adjust);
}

void Astro::advance(int step)
{
    if (step == 0)
        return;
    x = this->pos().x();
    y = this->pos().y();

    x = x + dx;
    y = y + dy;

    setPos(x, y);
    if(this->pos().y() > 650)
    {
        delete this;
    }
}

QPainterPath Astro::shape() const
{
    QPainterPath path;
    path.addRect(-w/2, -h/2, w, h);
    return path;
}


