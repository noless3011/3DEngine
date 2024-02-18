#pragma once
#include "Mesh.h"
#include "Libs.h"
#include "MyException.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>



class MeshRenderer {
	friend class Graphics;
public:
	MeshRenderer();
	MeshRenderer(Mesh _mesh);
	~MeshRenderer();
	Mesh mesh;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	UINT strides;
	UINT offsets;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	D3D11_PRIMITIVE_TOPOLOGY topology;

private:
	void SetUpPipelinePtr(Microsoft::WRL::ComPtr<ID3D11Device> &pDevice);
};