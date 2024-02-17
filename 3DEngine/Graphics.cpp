#include "Graphics.h"
//#pragma comment(lib, "d3d11.lib")



void Graphics::Draw()
{
	FLOAT color[3] = { 0, 0, 0 };
	struct Vertex {
		float x;
		float y;
	};
	
	Vertex vertices[3] = {
		{0, 0.1},
		{0.1, -0.1},
		{-0.1, -0.1}
	};

	pContext->ClearRenderTargetView(pRTV.Get(), color);
	
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
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
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	CHECK_HRESULT(D3DReadFileToBlob(L"PixelShader.cso", &pBlob));
	CHECK_HRESULT(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));
	pContext->PSSetShader(pPixelShader.Get(), nullptr, 0);


	//Get the shader
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	
	CHECK_HRESULT(D3DReadFileToBlob(L"VertexShader.cso", &pBlob));
	CHECK_HRESULT(pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, pVertexShader.GetAddressOf()));
	pContext->VSSetShader(pVertexShader.Get(), 0, 0);

	

	//Create and set the Input Layout
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0,
		  D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
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

void Graphics::EndFrame()
{
	HRESULT hr = pSwapchain->Present(1, 0);
	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_HUNG) {
		CHECK_HRESULT(pDevice->GetDeviceRemovedReason());
	}
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
	pDevice->CreateRenderTargetView(pResource.Get(), nullptr, &pRTV);

}

Graphics::~Graphics()
{
}
