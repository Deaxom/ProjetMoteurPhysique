#include "Quaternion.h"
#include <cmath>

void Quaternion::Normalized()
{
    float d = w*w+i*i+j*j+k*k;

    if (d == 0)
    {
        w = 1;
        return;
    }

    d = 1.f / sqrt(d);

    w *= d;
    i *= d;
    j *= d;
    k *= d;
}

void Quaternion::operator*=(const Quaternion& q)
{
    w = w * q.w - i * q.i - j * q.j - k * q.k;
    i = w * q.i + i * q.w + j * q.k - k * q.j;
    j = w * q.j + j * q.w + k * q.i - i * q.k;
    k = w * q.k + k * q.w + i * q.j - j * q.i;
}

Quaternion& Quaternion::operator*(const Quaternion& q)
{
    Quaternion& v = (*this);
    v.w = v.w * q.w - v.i * q.i - v.j * q.j - v.k * q.k;
    v.i = v.w * q.i + v.i * q.w + v.j * q.k - v.k * q.j;
    v.j = v.w * q.j + v.j * q.w + v.k * q.i - v.i * q.k;
    v.k = v.w * q.k + v.k * q.w + v.i * q.j - v.j * q.i;

    return v;
}

void Quaternion::RotateByVector(Vecteur3D& vecteur)
{
    Quaternion q(0, vecteur.getX(), vecteur.getY(), vecteur.getZ());
    (*this) *= q;
}

void Quaternion::UpdateByAngularVelocity(Vecteur3D& rotation, float duration)
{
    Quaternion q(0, rotation.getX() * duration, rotation.getY() * duration, rotation.getZ() * duration);
    q *= (*this);
    w += q.w * 0.5f;
    i += q.i * 0.5f;
    j += q.j * 0.5f;
    k += q.k * 0.5f;
}


