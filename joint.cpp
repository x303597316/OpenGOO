#include "joint.h"
#include "tools.h"

Joint::Joint(Goo *a, Goo *b, b2World *world, QObject *parent):
    QObject(parent)
{
    b2DistanceJointDef jDef;
    jDef.Initialize(a->getBody(),b->getBody(),a->getVPosition(),b->getVPosition());
    jDef.dampingRatio=1.0;
    jDef.frequencyHz=10;
    jDef.collideConnected=true;
    joint=(b2DistanceJoint*)world->CreateJoint(&jDef);
    this->a=a;
    this->b=b;
}

void Joint::paint(QPainter &p){
    status();
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(4);
    p.setPen(pen);
    QPoint a=toPoint(joint->GetBodyA()->GetPosition());
    QPoint b=toPoint(joint->GetBodyB()->GetPosition());
    p.drawLine(a,b);
    p.drawLine(a.x()-2,a.y()-2,b.x()+2,b.y()+2);
    p.drawLine(a.x()-1,a.y()-1,b.x()+1,b.y()+1);
    p.drawLine(a.x()-3,a.y()-3,b.x()+3,b.y()+3);
    p.drawLine(a.x()-4,a.y()-4,b.x()+4,b.y()+4);
    p.drawLine(a.x()+4,a.y()+4,b.x()-4,b.y()-4);
    p.drawLine(a.x()+3,a.y()+3,b.x()-3,b.y()-3);
    p.drawLine(a.x()+1,a.y()+1,b.x()-1,b.y()-1);
    p.drawLine(a.x()+2,a.y()+2,b.x()-2,b.y()-2);
}

void Joint::status(){
    float dx=(joint->GetBodyA()->GetPosition().x-joint->GetBodyB()->GetPosition().x);
    float dy=(joint->GetBodyA()->GetPosition().y-joint->GetBodyB()->GetPosition().y);
    float l=sqrt(dx*dx+dy*dy);
    float force= joint->GetReactionForce(1.0/60.0).Length();
    if (l<50 || l>200 || force>1000) {
        a->destroyLink(b);
        b->destroyLink(a);
        emit destroyJoint(this);
    }
}

b2Joint* Joint::getJoint(){
    return joint;
}
