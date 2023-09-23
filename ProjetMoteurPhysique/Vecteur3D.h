#pragma once

#include <iostream>

constexpr double Pi = 3.1415926535897932384626433832795;

constexpr double Deg2Rad = Pi / 180;
constexpr double Rad2Deg = 180 / Pi;

template<typename T>
struct Vector3
{
	Vector3() = default;
	explicit Vector3(T V) :
		x(V),
		y(V),
		z(V)
	{
	};
	Vector3(T X, T Y, T Z) :
		x(X),
		y(Y),
		z(Z)
	{
	};

	Vector3 operator+(const Vector3& vec) const {
		return Vector3{ x + vec.x, y + vec.y, z + vec.z };
	};
	Vector3 operator-(const Vector3& vec) const {
		return Vector3{ x - vec.x, y - vec.y, z - vec.z };
	};
	Vector3 operator*(const Vector3& vec) const {
		return Vector3{ x * vec.x, y * vec.y, z * vec.z };
	};
	Vector3 operator*(T value) const {
		return Vector3{ x * value, y * value, z * value };
	};
	Vector3 operator/(const Vector3& vec) const {
		return Vector3{ x / vec.x, y / vec.y, z / vec.z };
	};
	Vector3 operator/(T value) const {
		return Vector3{ x / value, y / value, z / value };
	};

	Vector3& operator+=(const Vector3& vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;

		return *this;
	};
	Vector3& operator-=(const Vector3& vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;

		return *this;
	};
	Vector3& operator*=(const Vector3& vec) {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;

		return *this;
	};
	Vector3& operator*=(T value) {
		x *= value;
		y *= value;
		z *= value;

		return *this;
	};
	Vector3& operator/=(const Vector3& vec) {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;

		return *this;
	};
	Vector3& operator/=(T value) {
		x /= value;
		y /= value;
		z /= value;

		return *this;
	};

	T x, y, z;
};

template<typename T> Vector3<T> operator*(T value, const Vector3<T>& vec) {
	return Vector3{ vec.x * value, vec.y * value, vec.z * value };
};
template<typename T> Vector3<T> operator/(T value, const Vector3<T>& vec) {
	return Vector3{ vec.x / value, vec.y / value, vec.z / value };
};

template<typename T> std::ostream& operator<<(std::ostream& os, const Vector3<T>& vec) {
	return os << "Vector3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
};

using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;

