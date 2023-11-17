#pragma once

#include "Vecteur3D.h"
#include <array>
#include <iostream>

#include "Quaternion.h"

constexpr float Pi = 3.1415926535897932384626433832795f;

constexpr float Deg2Rad = Pi / 180.f;
constexpr float Rad2Deg = 180.f / Pi;

class Matrix3x4
{
public:
    Matrix3x4() = default;

    /// structure =
    /// 01|02|03|04
    /// 05|06|07|08
    /// 09|10|11|12
    Matrix3x4(std::array<float, 3 * 4> values);

    // Determine si la Matrice possede un Inverse ou non
    // 0 = matrice "singuliere" donc pas d'inverse
    float Determinant() const;

    Matrix3x4 Inverse() const;
    void Invert();
    void SetOrientationAndPos(const Quaternion& q, Vecteur3D& pos);

    Vecteur3D TransformPosition(Vecteur3D& vec);
    Vecteur3D transformInverse(Vecteur3D& vec);
    Vecteur3D transformDirection(Vecteur3D& vec) const;

    float& Value(std::size_t i, std::size_t j);
    const float& Value(std::size_t i, std::size_t j) const;
    float* getMatrice();

    float& operator()(std::size_t i, std::size_t j);
    const float& operator()(std::size_t i, std::size_t j) const;

    Matrix3x4 operator*(const Matrix3x4& rhs) const;
    
    Vecteur3D operator*(Vecteur3D& vec) const;
    Vecteur3D Transform(Vecteur3D& vec) const;

    //Changer de base
    Vecteur3D LocalAuMonde(Vecteur3D& local) const;
    Vecteur3D MondeALocal(Vecteur3D& monde);

private:
    std::array<float, 3 * 4> m_values;
};

// Opérateur de flux, permet d'écrire un Matrix4 directement dans std::cout (ou autre flux de sortie)
std::ostream& operator<<(std::ostream& os, const Matrix3x4& mat);
