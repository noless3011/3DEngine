#pragma once
#include "Vector.h"
#include "Quarternion.h"


class Transform {
public:
	Vector3 position;
	Vector3 scale;
	Vector3 e_rotation;       // euler rotation
	Quarternion q_rotation;   // quarternion rotation
public:
	Transform(Vector3 _position, Vector3 _scale, Vector3 _e_rotation);
	Transform();
	Transform(Vector3 _position, Vector3 _scale, Quarternion _q_rotation);
	void TranslateTo(Vector3 new_position);
	void TranslateDir(Vector3 dir);
	void RotateTo(Vector3 new_e_rotation);
	void RotateAround(Vector3 axis, float angle);
	void ScaleTo(Vector3 new_scale);
private:

};