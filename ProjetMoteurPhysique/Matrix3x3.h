#pragma once

#include "Vecteur3D.h"
#include <array>
#include <iostream>

#include "Quaternion.h"

constexpr float Pi = 3.1415926535897932384626433832795f;

constexpr float Deg2Rad = Pi / 180.f;
constexpr float Rad2Deg = 180.f / Pi;

class Matrix3x3
{
public:
    Matrix3x3() = default;
    Matrix3x3(std::array<float, 3 * 3> value);

    // Determine si la Matrice possede un Inverse ou non
    // 0 = matrice "singuliere" donc pas d'inverse
    float Determinant() const;

    Matrix3x3 Inverse() const;
    void Invert();
    
    Matrix3x3 Transpose() const;

    void SetOrientation(const Quaternion& q);

    // Transform operator
    Vecteur3D operator*(Vecteur3D& vec) const;
    Vecteur3D Transform(Vecteur3D& vec) const;

    float& Value(std::size_t i, std::size_t j);
    const float& Value(std::size_t i, std::size_t j) const;

    float& operator()(std::size_t i, std::size_t j);
    const float& operator()(std::size_t i, std::size_t j) const;

    Matrix3x3 operator*(const Matrix3x3& rhs) const;
    void operator*=(const Matrix3x3& rhs);

#pragma region si necessaire
    // autres
    static Matrix3x3 Identity();
    // revoir ce qui est demandé
    static Matrix3x3 Rotate(float degreeAngle);
    static Matrix3x3 Scale(Vecteur3D& scale);
#pragma endregion
    
    static Matrix3x3 Translate(Vecteur3D& translation);

private:
    std::array<float, 3*3> m_values;
};

// Opérateur de flux, permet d'écrire un Matrix3 directement dans std::cout (ou autre flux de sortie)
std::ostream& operator<<(std::ostream& os, const Matrix3x3& mat);