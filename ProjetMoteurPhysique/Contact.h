#pragma once
#include "Vecteur3D.h"

class CorpsRigide;

class Contact
{
public:
    Vecteur3D contactPoint;
    Vecteur3D contactNormal;
    float penetration;
    CorpsRigide* corpsRigide[2];
    float restitution;
    float friction;
};
