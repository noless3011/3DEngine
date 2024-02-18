#pragma once
#include "Libs.h"
#include "MyException.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>


class Graphics {
public:
	void Draw(float angle);
	void EndFrame();
public:
	Graphics(HWND hWnd, int width, int height);
	~Graphics();
	Graphics(const Graphics&) = delete;
	Graphics& operator = (const Graphics&) = delete;
private:
	int width{}, height{};
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapchain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRTV;
};