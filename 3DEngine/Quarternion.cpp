#include "stdafx.h"
#include "Quarternion.h"

Quarternion::~Quarternion()
{
}

Vector3 Quarternion::GetEuler()
{
	Vector3 euler;
	double sinr_cosp = 2 * (s * axis.x + axis.y * axis.z);
	double cosr_cosp = 1 - 2 * (axis.x * axis.x + axis.y * axis.y);
	euler.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = 2 * (s * axis.y - axis.z * axis.x);
	if (std::abs(sinp) >= 1)
		euler.y = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
	else
		euler.y = std::asin(sinp);

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (s * axis.z + axis.x * axis.y);
	double cosy_cosp = 1 - 2 * (axis.y * axis.y + axis.z * axis.z);
	euler.z = std::atan2(siny_cosp, cosy_cosp);

	return euler;
}

void Quarternion::RotateTo(Quarternion newRot, float rotateSpeed)
{
}

Quarternion Quarternion::normalized() {
	double norm = std::sqrt(s * s + axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
	return Quarternion(s / norm, Vector3(axis.x / norm, axis.y / norm, axis.z / norm));
}