#pragma once
#include "Vecteur3D.h"

class Matrix3x3;

class Quaternion
{
public:
    float w, i, j, k;
    Quaternion() = default;
    Quaternion(float w, float i, float j, float k);

    void Normalized();

    void operator*=(const Quaternion& vec);
    Quaternion& operator*(const Quaternion& vec);
    Quaternion& operator+(const Quaternion& vec);
    Quaternion& operator*(const double& scalaire);

    void RotateByVector(Vecteur3D& vecteur);
    void UpdateByAngularVelocity(Vecteur3D& rotation, float duration);
    Matrix3x3 TransformerEnMatriceRotation();
};
