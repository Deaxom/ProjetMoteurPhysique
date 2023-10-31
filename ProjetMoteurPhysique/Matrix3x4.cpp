#include "Matrix3x4.h"

Matrix3x4::Matrix3x4(std::array<float, 3 * 4> values) :
m_values(values)
{
}

float Matrix3x4::Determinant() const
{
    float det = Value(2,0) * Value(1,1) * Value(0,2) +
                Value(1,0) * Value(2,1) * Value(0,2) +
                Value(2,0) * Value(0,1) * Value(1,2) -
                Value(0,0) * Value(2,1) * Value(1,2) -
                Value(1,0) * Value(0,1) * Value(2,2) +
                Value(0,0) * Value(1,1) * Value(2,2);

    return det;
}

Matrix3x4 Matrix3x4::Inverse() const
{
    float det = Determinant();
    if (det == 0) return (*this);
    float invDet = 1.0f / det;

    Matrix3x4 result;
    result(0, 0) =  (Value(1, 1) * Value(2, 2) - Value(2, 1) * Value(1, 2)) * invDet;
    result(0, 1) = -(Value(0, 1) * Value(2, 2) - Value(0, 2) * Value(2, 1)) * invDet;
    result(0, 2) =  (Value(0, 1) * Value(1, 2) - Value(0, 2) * Value(1, 1)) * invDet;
    result(1, 0) = -(Value(1, 0) * Value(2, 2) - Value(1, 2) * Value(2, 0)) * invDet;
    result(1, 1) =  (Value(0, 0) * Value(2, 2) - Value(0, 2) * Value(2, 0)) * invDet;
    result(1, 2) = -(Value(0, 0) * Value(1, 2) - Value(1, 0) * Value(0, 2)) * invDet;
    result(2, 0) =  (Value(1, 0) * Value(2, 1) - Value(2, 0) * Value(1, 1)) * invDet;
    result(2, 1) = -(Value(0, 0) * Value(2, 1) - Value(2, 0) * Value(0, 1)) * invDet;
    result(2, 2) =  (Value(0, 0) * Value(1, 1) - Value(1, 0) * Value(0, 1)) * invDet;
    
    result.Value(0,3) = -1 * Value(0,3);
    result.Value(1,3) = -1 * Value(1,3);
    result.Value(2,3) = -1 * Value(2,3);
    
    return result;
}

void Matrix3x4::Invert()
{
    (*this) = (*this).Inverse();
}

void Matrix3x4::SetOrientationAndPos(const Quaternion& q, Vecteur3D& pos)
{
    Matrix3x4 result = (*this);
    result.Value(0,0) = 1 - (2*q.j*q.j + 2*q.k*q.k);
    result.Value(0,1) = 2*q.i*q.j + 2*q.k*q.w;
    result.Value(0,2) = 2*q.i*q.k - 2*q.j*q.w;
    result.Value(0,3) = pos.getX();
        
    result.Value(1,0) = 2*q.i*q.j - 2*q.k*q.w;
    result.Value(1,1) = 1 - (2*q.i*q.i + 2*q.k*q.k);
    result.Value(1,2) = 2*q.j*q.k + 2*q.i*q.w;
    result.Value(1,3) = pos.getY();
        
    result.Value(2,0) = 2*q.i*q.k + 2*q.j*q.w;
    result.Value(2,1) = 2*q.j*q.k - 2*q.i*q.w;
    result.Value(2,2) = 1 - (2*q.i*q.i + 2*q.j*q.j);
    result.Value(2,3) = pos.getZ();
    
    (*this) = result;
}

Vecteur3D Matrix3x4::TransformPosition(Vecteur3D& vec)
{
    return Transform(vec);
}

Vecteur3D Matrix3x4::transformInverse(Vecteur3D& vec)
{
    Vecteur3D temp = vec;
    temp.setX(temp.getX() - Value(0,3));
    temp.setY(temp.getY() - Value(1,3));
    temp.setZ(temp.getZ() - Value(2,3));

    Vecteur3D vector(temp.getX() * Value(0,0) + temp.getY() * Value(1,0) + temp.getZ() * Value(2,0),
        temp.getX() * Value(0,1) + temp.getY() * Value(1,1) + temp.getZ() * Value(2,1),
        temp.getX() * Value(0,2) + temp.getY() * Value(1,2) + temp.getZ() * Value(2,2)
    );
    
    return vector;
}

Vecteur3D Matrix3x4::transformDirection(Vecteur3D& vec) const
{
    Vecteur3D vector(vec.getX() * Value(0,0) + vec.getY() * Value(0,1) + vec.getZ() * Value(0,2),
                vec.getX() * Value(1,0) + vec.getY() * Value(1,1) + vec.getZ() * Value(1,2),
                vec.getX() * Value(2,0) + vec.getY() * Value(2,1) + vec.getZ() * Value(2,2));

    return vector;
}

float& Matrix3x4::Value(std::size_t i, std::size_t j)
{
    return m_values[i * 4 + j];
}

const float& Matrix3x4::Value(std::size_t i, std::size_t j) const
{
    return m_values[i * 4 + j];
}

float& Matrix3x4::operator()(std::size_t i, std::size_t j)
{
    return Value(i, j);
}

const float& Matrix3x4::operator()(std::size_t i, std::size_t j) const
{
    return Value(i, j);
}

Matrix3x4 Matrix3x4::operator*(const Matrix3x4& rhs) const
{
    Matrix3x4 result;
    for (std::size_t i = 0; i < 4; ++i)
    {
        for (std::size_t j = 0; j < 4; ++j)
        {
            float sum = 0.0f;
            for (std::size_t k = 0; k < 4; ++k)
                sum += Value(i, k) * rhs(k, j);

            result(i, j) = sum;
        }
    }

    return result;
}

Vecteur3D Matrix3x4::operator*(Vecteur3D& vec) const
{
    Vecteur3D result;
    result.setX(Value(0, 0) * vec.getX() + Value(0, 1) * vec.getY() + Value(0, 2) * vec.getZ() + Value(0, 3));
    result.setY(Value(1, 0) * vec.getX() + Value(1, 1) * vec.getY() + Value(1, 2) * vec.getZ() + Value(1, 3));
    result.setZ(Value(2, 0) * vec.getX() + Value(2, 1) * vec.getY() + Value(2, 2) * vec.getZ() + Value(2, 3));

    return result;
}

Vecteur3D Matrix3x4::Transform(Vecteur3D& vec) const
{
    return (*this) * vec;
}

std::ostream& operator<<(std::ostream& os, const Matrix3x4& mat)
{
    return os << "Matrix4(" << mat.Value(0, 0) << ", " << mat.Value(0, 1) << ", " << mat.Value(0, 2) << ", " << mat.Value(0, 3) << "\n"
              << "        " << mat.Value(1, 0) << ", " << mat.Value(1, 1) << ", " << mat.Value(1, 2) << ", " << mat.Value(1, 3) << "\n"
              << "        " << mat.Value(2, 0) << ", " << mat.Value(2, 1) << ", " << mat.Value(2, 2) << ", " << mat.Value(2, 3) << ")";
}