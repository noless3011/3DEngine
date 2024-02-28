#pragma once
#include <DirectXMath.h>
#include "Vector.h"
#include "Transform.h"



class Camera {
	friend class GlobalBuffer;
public:
	Camera();
	~Camera();
	Camera(Vector3 _position, Vector3 _direction, Vector3 _up);
	Vector3 position = Vector3();
	Vector3 direction = Vector3(1, 0, 0);
	Vector3 up = Vector3(0, 1, 0);
private:
	DirectX::XMMATRIX CreateViewMatrix();
};