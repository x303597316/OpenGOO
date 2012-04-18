#include "ropejoint.h"

#include <qmath.h>
#include <QDebug>
#include <QPen>
#include "tools.h"

RopeJoint::RopeJoint(Goo *a, Goo *b, b2World *world, QObject *parent) :
    Joint(a,b,world,true,parent)
{
    this->world=world;
    initialize(world);
    type=ROPE;
}

RopeJoint::~RopeJoint(){
    for (int i=0;i<joints.length();i++){
        world->DestroyJoint(joints[i]);
    }
    joints.clear();
    for (int i=0;i<bodies.length();i++){
        world->DestroyBody(bodies[i]);
    }
    bodies.clear();


}


void RopeJoint::initialize(b2World *world){
    b2RopeJointDef jDef;
    jDef.bodyA=a->getBody();
    jDef.bodyB=b->getBody();
    jDef.localAnchorA=a->getVPosition();
    jDef.localAnchorB=b->getVPosition();
    jDef.maxLength=100;
    joint=(b2RopeJoint*)world->CreateJoint(&jDef);

}

void RopeJoint::paint(QPainter &p){
    if (!a->isLinked(b) || !b->isLinked(a)) emit this->destroyJoint(this);
    QPen pen(Qt::black,3);
    p.setPen(pen);
    for (int i=0;i<bodies.length()-1;i++){
        p.drawLine(toPoint(bodies[i]->GetPosition()),toPoint(bodies[i+1]->GetPosition()));
    }
    p.drawLine(a->getPPosition(),b->getPPosition());
}


