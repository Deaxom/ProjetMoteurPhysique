#include "Matrix3x3.h"
#include <cmath>

Matrix3x3::Matrix3x3(std::array<float, 3 * 3> value) :
m_values(value)
{
}

float Matrix3x3::Determinant() const
{
    float det = Value(0, 0) * (Value(1, 1) * Value(2, 2) - Value(2, 1) * Value(1, 2)) -
            Value(0, 1) * (Value(1, 0) * Value(2, 2) - Value(1, 2) * Value(2, 0)) +
            Value(0, 2) * (Value(1, 0) * Value(2, 1) - Value(1, 1) * Value(2, 0));

    return det;
}

Matrix3x3 Matrix3x3::Inverse() const
{
    float det = Determinant();
    
    if (det == 0.f) return (*this);
    float invDet = 1.0f / det;
	
    Matrix3x3 result;
    result(0, 0) =  (Value(1, 1) * Value(2, 2) - Value(2, 1) * Value(1, 2)) * invDet;
    result(0, 1) = -(Value(0, 1) * Value(2, 2) - Value(0, 2) * Value(2, 1)) * invDet;
    result(0, 2) =  (Value(0, 1) * Value(1, 2) - Value(0, 2) * Value(1, 1)) * invDet;
    result(1, 0) = -(Value(1, 0) * Value(2, 2) - Value(1, 2) * Value(2, 0)) * invDet;
    result(1, 1) =  (Value(0, 0) * Value(2, 2) - Value(0, 2) * Value(2, 0)) * invDet;
    result(1, 2) = -(Value(0, 0) * Value(1, 2) - Value(1, 0) * Value(0, 2)) * invDet;
    result(2, 0) =  (Value(1, 0) * Value(2, 1) - Value(2, 0) * Value(1, 1)) * invDet;
    result(2, 1) = -(Value(0, 0) * Value(2, 1) - Value(2, 0) * Value(0, 1)) * invDet;
    result(2, 2) =  (Value(0, 0) * Value(1, 1) - Value(1, 0) * Value(0, 1)) * invDet;
	
    return result;
}

void Matrix3x3::Invert()
{
    (*this) = (*this).Inverse();
}

Matrix3x3 Matrix3x3::Transpose() const
{
    Matrix3x3 mat;
    for (std::size_t i = 0; i < 3; ++i)
    {
        for (std::size_t j = 0; j < 3; ++j)
            mat(j, i) = Value(i, j);
    }

    return mat;
}

void Matrix3x3::SetOrientation(const Quaternion& q)
{
    Matrix3x3 result;
    result.Value(0,0) = 1 - (2*q.j*q.j + 2*q.k*q.k);
    result.Value(0,1) = 2*q.i*q.j + 2*q.k*q.w;
    result.Value(0,2) = 2*q.i*q.k - 2*q.j*q.w;
    result.Value(1,0) = 2*q.i*q.j - 2*q.k*q.w;
    result.Value(1,1) = 1 - (2*q.i*q.i + 2*q.k*q.k);
    result.Value(1,2) = 2*q.j*q.k + 2*q.i*q.w;
    result.Value(2,0) = 2*q.i*q.k + 2*q.j*q.w;
    result.Value(2,1) = 2*q.j*q.k + 2*q.i*q.w;
    result.Value(2,2) = 1 - (2*q.i*q.i + 2*q.j*q.j);
    (*this) = result;
}

float& Matrix3x3::Value(std::size_t i, std::size_t j)
{
    return m_values[i * 3 + j];
}

const float& Matrix3x3::Value(std::size_t i, std::size_t j) const
{
    return Value(i, j);
}

float& Matrix3x3::operator()(std::size_t i, std::size_t j)
{
    return Value(i, j);
}

const float& Matrix3x3::operator()(std::size_t i, std::size_t j) const
{
    return Value(i, j);
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& rhs) const
{
    Matrix3x3 result;
    for (std::size_t i = 0; i < 3; ++i)
    {
        for (std::size_t j = 0; j < 3; ++j)
        {
            float sum = 0.0f;
            for (std::size_t k = 0; k < 3; ++k)
                sum += Value(i, k) * rhs(k, j);

            result(i, j) = sum;
        }
    }

    return result;
}

void Matrix3x3::operator*=(const Matrix3x3& rhs)
{
    (*this) = (*this) * rhs;
}

Vecteur3D Matrix3x3::operator*(Vecteur3D& vec) const
{
    Vecteur3D result;
    result.setX(Value(0, 0) * vec.getX() + Value(0, 1) * vec.getY() + Value(0, 2) * vec.getZ());
    result.setY(Value(1, 0) * vec.getX() + Value(1, 1) * vec.getY() + Value(1, 2) * vec.getZ());
    result.setZ(Value(2, 0) * vec.getX() + Value(2, 1) * vec.getY() + Value(2, 2) * vec.getZ());

    return result;
}

Vecteur3D Matrix3x3::Transform(Vecteur3D& vec) const
{
    return (*this) * vec;
}

#pragma region si necessaire

Matrix3x3 Matrix3x3::Identity()
{
    return Matrix3x3({
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    });
}

Matrix3x3 Matrix3x3::Rotate(float degreeAngle)
{
    float sinAngle = std::sin(degreeAngle * Deg2Rad);
    float cosAngle = std::cos(degreeAngle * Deg2Rad);

    return Matrix3x3({
        cosAngle, -sinAngle, 0.0f,
        sinAngle,  cosAngle, 0.0f,
        0.0f,          0.0f, 1.0f
    });
}

Matrix3x3 Matrix3x3::Scale(Vecteur3D& scale)
{
    return Matrix3x3({
        static_cast<float>(scale.getX()), 0.0f,    0.0f,
        0.0f,    static_cast<float>(scale.getY()), 0.0f,
        0.f,     0.0f,    static_cast<float>(scale.getZ()),
    });
}

#pragma endregion

Matrix3x3 Matrix3x3::Translate(Vecteur3D& translation)
{
    return Matrix3x3({
        1.0f, 0.0f, static_cast<float>(translation.getX()),
        0.0f, 1.0f, static_cast<float>(translation.getY()),
        0.0f, 0.0f, static_cast<float>(translation.getZ()),
    });
}

std::ostream& operator<<(std::ostream& os, const Matrix3x3& mat)
{
    return os << "Matrix3x3(" << mat.Value(0, 0) << ", " << mat.Value(0, 1) << ", " << mat.Value(0, 2) << ",\n"
              << "        " << mat.Value(1, 0) << ", " << mat.Value(1, 1) << ", " << mat.Value(1, 2) << ",\n"
              << "        " << mat.Value(2, 0) << ", " << mat.Value(2, 1) << ", " << mat.Value(2, 2) << ")";
}
