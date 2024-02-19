#pragma once
#include "Libs.h"
#include "MyException.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "MeshRenderer.h"
#include "GlobalBuffers.h"


class Graphics {
	friend class MeshRenderer;
	friend class Window;
public:
	void DrawTest(float angle);
	void Draw(MeshRenderer meshRenderer);
	void EndFrame();
	GlobalBuffers& globalBuffers();
public:
	Graphics(HWND hWnd, int width, int height);
	~Graphics();
	Graphics(const Graphics&) = delete;
	Graphics& operator = (const Graphics&) = delete;
private:
	std::unique_ptr<GlobalBuffers> pGlobalBuffers;
	int width{}, height{};
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapchain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRTV;


	
};