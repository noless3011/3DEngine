#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

Camera::Camera(Vector3 _position, Vector3 _direction, Vector3 _up)
{
	position = _position;
	direction = _direction;
	up = _up;
}

DirectX::XMMATRIX Camera::CreateViewMatrix()
{
	DirectX::XMVECTOR pos = DirectX::XMVectorSet(position.x, position.y, position.z, 1);
	DirectX::XMVECTOR dir = DirectX::XMVectorSet(direction.x, direction.y, direction.z, 1);
	DirectX::XMVECTOR upDir = DirectX::XMVectorSet(up.x, up.y, up.z, 1);
	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookToRH(pos, dir, upDir));
	return viewMatrix;
}