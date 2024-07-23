#pragma once
#include "Vector.h"
#include "Clock.h"
#define M_PI 3.14159265358979323846

class Quarternion {
public:
	float s;
	Vector3 axis;

	//default constructor
	Quarternion() : s(0), axis(Vector3(1, 0, 0)) {}

	//parameterize constructor
	Quarternion(float _s, Vector3 _axis) : s(_s), axis(_axis) {}

	//parameterize constructor
	Quarternion(float _s, float _x, float _y, float _z) {}

	//copy constructor
	Quarternion(const Quarternion& other) : s(other.s), axis(other.axis) {}

	//destructor
	~Quarternion();

	Vector3 GetEuler();
	void RotateTo(Quarternion newRot, float rotateSpeed);
	Quarternion normalized();
};