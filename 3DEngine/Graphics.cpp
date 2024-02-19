#include "Graphics.h"
//#pragma comment(lib, "d3d11.lib")

namespace dx = DirectX;

void Graphics::DrawTest(float angle)
{
	FLOAT color[3] = { 1, 0, 0 };
	struct Vertex {
		float x;
		float y;
		float z;
	};
	
	Vertex vertices[3] = {
		{0, 0.5, 1},
		{0.5, -0.5, 1},
		{-0.5, -0.5, 1}
	};

	struct ConstantBuffer {
		dx::XMMATRIX matrix;
	};
	const ConstantBuffer rotate = {
		dx::XMMatrixTranspose(dx::XMMatrixRotationZ(angle))
	};
	const ConstantBuffer translate = {
		dx::XMMatrixTranspose(dx::XMMatrixTranslation(sin(angle), 0, 0))
	};

	const ConstantBuffer bufferArray[] = {
		rotate,
		translate
	};
	
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;

	D3D11_BUFFER_DESC cbd = {};
	cbd.ByteWidth = sizeof(bufferArray);
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0;
	cbd.StructureByteStride = sizeof(ConstantBuffer);
	D3D11_SUBRESOURCE_DATA scbd = {};
	scbd.pSysMem = &bufferArray;
	CHECK_HRESULT(pDevice->CreateBuffer(&cbd, &scbd, &pConstantBuffer));
	pContext->VSSetConstantBuffers(0, 1, pConstantBuffer.GetAddressOf());
	pContext->ClearRenderTargetView(pRTV.Get(), color);
	
	
	D3D11_BUFFER_DESC bd = {};
	bd.ByteWidth = sizeof(Vertex) * std::size(vertices);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA subData = {};
	subData.pSysMem = vertices;
	(pDevice->CreateBuffer(&bd, &subData, &pVertexBuffer));
	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	pContext->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &strides, &offsets);

	//Select the primitive topology for the pipeline
	D3D11_PRIMITIVE_TOPOLOGY topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	pContext->IASetPrimitiveTopology(topology);
	
	

	//Set the pixel (fragment) shader

	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	CHECK_HRESULT(D3DReadFileToBlob(L"PixelShader.cso", &pBlob));
	CHECK_HRESULT(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));
	pContext->PSSetShader(pPixelShader.Get(), nullptr, 0);


	//Get the shader
	
	
	CHECK_HRESULT(D3DReadFileToBlob(L"VertexShader.cso", &pBlob));
	CHECK_HRESULT(pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, pVertexShader.GetAddressOf()));
	pContext->VSSetShader(pVertexShader.Get(), 0, 0);

	
	


	//Create and set the Input Layout
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0,
		  D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	
	CHECK_HRESULT(pDevice->CreateInputLayout(layout, 1, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), pInputLayout.GetAddressOf()));
	pContext->IASetInputLayout(pInputLayout.Get());


	//set the render target view and viewport
	pContext->OMSetRenderTargets(1, pRTV.GetAddressOf(), nullptr);

	D3D11_VIEWPORT viewport = {};
	viewport.Width = 800;
	viewport.Height = 600;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MaxDepth = 1;
	viewport.MinDepth = 0;
	pContext->RSSetViewports(1, &viewport);

	pContext->Draw(3, 0);
}

void Graphics::Draw(MeshRenderer meshRenderer)
{
	pGlobalBuffers->SetUpPipelineBuffers(pDevice, pContext);
	MeshRenderer copyMeshRenderer = meshRenderer;
	copyMeshRenderer.SetUpPipelinePtr(pDevice);
	FLOAT color[3] = { 1, 0, 0 };
	pContext->ClearRenderTargetView(pRTV.Get(), color);
	pContext->IASetVertexBuffers(0, 1, copyMeshRenderer.pVertexBuffer.GetAddressOf(), &copyMeshRenderer.strides, &copyMeshRenderer.offsets);
	pContext->IASetPrimitiveTopology(copyMeshRenderer.topology);
	pContext->PSSetShader(copyMeshRenderer.pPixelShader.Get(), nullptr, 0);
	pContext->VSSetShader(copyMeshRenderer.pVertexShader.Get(), 0, 0);
	pContext->IASetInputLayout(copyMeshRenderer.pInputLayout.Get());
	pContext->OMSetRenderTargets(1, pRTV.GetAddressOf(), nullptr);
	

	UINT vertexNumber = copyMeshRenderer.pmesh->vertexList.size();
	pContext->Draw(vertexNumber, 0);

}

void Graphics::EndFrame()
{
	HRESULT hr = pSwapchain->Present(1, 0);
	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_HUNG) {
		CHECK_HRESULT(pDevice->GetDeviceRemovedReason());
	}
}

GlobalBuffers& Graphics::globalBuffers()
{
	return *pGlobalBuffers;
}

Graphics::Graphics(HWND hWnd, int width, int height) : width(width), height(height) {
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
	// If the project is in a debug build, enable the debug layer.
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.Flags = 0;
	CHECK_HRESULT(D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, creationFlags, nullptr, 0, D3D11_SDK_VERSION,
		&sd, &pSwapchain, &pDevice, nullptr, &pContext
	));
	
	
	Microsoft::WRL::ComPtr<ID3D11Resource> pResource = nullptr;
	pSwapchain->GetBuffer(0, __uuidof(ID3D11Resource), &pResource);
	CHECK_HRESULT(pDevice->CreateRenderTargetView(pResource.Get(), nullptr, &pRTV));

	D3D11_VIEWPORT viewport = {};
	viewport.Width = 800;
	viewport.Height = 600;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MaxDepth = 1;
	viewport.MinDepth = 0;
	pContext->RSSetViewports(1, &viewport);
	pGlobalBuffers = std::make_unique<GlobalBuffers>();
	pGlobalBuffers->SetUpPipelineBuffers(pDevice, pContext);
}

Graphics::~Graphics()
{
}
