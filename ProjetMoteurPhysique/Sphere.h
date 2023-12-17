#pragma once
#include "Primitive.h"

class CorpsRigide;

class Sphere : public Primitive
{
public:
    Sphere(float _radius);
    
    float radius;
};
