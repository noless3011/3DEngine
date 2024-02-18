
#include "Graphics.h"



MeshRenderer::MeshRenderer()
{
	mesh = Mesh();

}

MeshRenderer::MeshRenderer(Mesh _mesh)
{
	mesh = _mesh;

}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::SetUpPipelinePtr(Microsoft::WRL::ComPtr<ID3D11Device> &pDevice)
{
	D3D11_BUFFER_DESC bd = {};
	bd.ByteWidth = sizeof(Vertex) * mesh.vertexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA subData = {};
	Vertex* vertexArray = mesh.vertexList.data();

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
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		  D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	CHECK_HRESULT(pDevice->CreateInputLayout(layout, 1, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), pInputLayout.GetAddressOf()));

}
