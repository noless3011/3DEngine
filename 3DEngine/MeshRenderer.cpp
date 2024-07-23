#include "stdafx.h"
#include "Graphics.h"

MeshRenderer::MeshRenderer()
{
	pmesh = std::make_unique<Mesh>();
}

MeshRenderer::MeshRenderer(Mesh& mesh)
{
	pmesh = std::make_shared<Mesh>(mesh);
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::SetUpPipelinePtr(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice)
{
	D3D11_BUFFER_DESC bd = {};
	bd.ByteWidth = sizeof(Vertex) * pmesh->vertexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA subData = {};
	Vertex* vertexArray = pmesh->vertexList.data();

	subData.pSysMem = vertexArray;
	pDevice->CreateBuffer(&bd, &subData, &pVertexBuffer);
	strides = sizeof(Vertex);
	offsets = 0;

	topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	CHECK_HRESULT(D3DReadFileToBlob(L"PixelShader.cso", &pBlob));
	CHECK_HRESULT(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));

	CHECK_HRESULT(D3DReadFileToBlob(L"VertexShader.cso", &pBlob));
	CHECK_HRESULT(pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, pVertexShader.GetAddressOf()));

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	CHECK_HRESULT(pDevice->CreateInputLayout(layout, 2, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), pInputLayout.GetAddressOf()));
}