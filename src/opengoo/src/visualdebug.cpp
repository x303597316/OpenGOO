#include "og_world.h"
#include "og_physicsbody.h"

#include <QPainter>
#include <QTime>

extern bool _E404;
extern QTime _time;
extern OGButton _buttonMenu;
extern QList<OGPhysicsBody*> _balls;

int _n = 0;
int _sumtime = 0;
int _fps = 60;

void visualDebug(QPainter* painter, OGWorld *world, qreal zoom)
{
    const qreal K = 10.0;

    _sumtime += _time.elapsed();

    _time.restart();

    qreal winX = painter->window().x();
    qreal winY = painter->window().y();

    QPen pen(Qt::yellow,  2.0/zoom);

    painter->setOpacity(1);
    painter->setPen(pen);

    // menu
    qreal btnW = _buttonMenu.size().width()/zoom;
    qreal btnH = _buttonMenu.size().height()/zoom;
    qreal btnX = winX + _buttonMenu.position().x()/zoom;
    qreal btnY = winY + _buttonMenu.position().y()/zoom;
    QRectF rect(btnX, btnY, btnW, btnH);

    painter->drawRect(rect);
    painter->drawEllipse(QPointF(0, 0), 10.0/zoom, 10.0/zoom); // center of word

    // level exit
    if (world->leveldata()->levelexit.radius)
    {
        qreal x, y;

        x = world->leveldata()->levelexit.pos.x();
        y = world->leveldata()->levelexit.pos.y()*(-1.0);
        QRectF rect(x, y, 10.0 , 10.0);

        rect.moveCenter(rect.topLeft());
        painter->fillRect(rect, Qt::yellow);
    }

    // pipe
    for (int i=0; i < world->leveldata()->pipe.vertex.size()-1; i++)
    {
        qreal x1, x2, y1, y2;

        x1 = world->leveldata()->pipe.vertex.at(i).x();
        y1 = world->leveldata()->pipe.vertex.at(i).y()*(-1.0);
        x2 = world->leveldata()->pipe.vertex.at(i+1).x();
        y2 = world->leveldata()->pipe.vertex.at(i+1).y()*(-1.0);

        painter->drawLine(QPointF(x1, y1), QPointF(x2, y2));
    }

    for (int i=0; i < world->scenedata()->circle.size(); i++)
    {
        qreal x, y, radius;

        x = world->scenedata()->circle.at(i)->position.x();
        y = world->scenedata()->circle.at(i)->position.y()*(-1.0);
        radius = world->scenedata()->circle.at(i)->radius;

        QPointF pos(x, y);
        painter->drawEllipse(pos, radius, radius);
    }

    for (int i=0; i < _balls.size(); i++)
    {
        qreal x, y, radius;

        x = _balls.at(i)->body->GetPosition().x*K;
        y = _balls.at(i)->body->GetPosition().y*K*(-1.0);
        radius = _balls.at(i)->shape->GetRadius()*K;

        painter->drawEllipse(QPointF(x, y), radius, radius);
    }

    if (_E404)
    {
        painter->setOpacity(0.25);
        painter->fillRect(painter->window(), Qt::black);
        painter->setOpacity(1);
        painter->setPen(Qt::white);
        painter->setFont(QFont("Times", 36, QFont::Bold));
        painter->drawText(painter->window()
                          , Qt::AlignCenter
                          , "UNIMPLEMENTED!!!\nEsc to return"
                          );
    }

    if(_n++ > 60)
    {
        if (_sumtime == 0)
        {
            _fps = 60;
        }
        else
        {
            _fps = qRound(60000.0/_sumtime);
        }

    _n = 0;
    _sumtime = 0;
    }

    painter->setPen(Qt::white);

    painter->setFont(QFont("Verdana", qRound(12.0/zoom), QFont::Bold));
    painter->drawText(winX + 20.0/zoom, winY + 20.0/zoom, QString::number(_fps));
}