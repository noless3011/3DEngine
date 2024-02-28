#include "Camera.h"

DirectX::XMMATRIX Camera::CreateViewMatrix()
{
    DirectX::XMVECTOR pos = DirectX::XMVectorSet(position.x, position.y, position.z, 1);
    DirectX::XMVECTOR dir = DirectX::XMVectorSet(direction.x, direction.y, direction.z, 1);
    DirectX::XMVECTOR upDir = DirectX::XMVectorSet(up.x, up.y, up.z, 1);
    DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookToRH(pos, dir, upDir));
    return viewMatrix;
}
