#pragma once
#include "Mesh.h"
#include "Material.h"
#include "Libs.h"




class MeshRenderer {
	friend class Graphics;
public:

	MeshRenderer();
	MeshRenderer(Mesh &mesh);
	~MeshRenderer();
	std::shared_ptr<Mesh> pmesh;
	std::shared_ptr<Material> pmat;
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