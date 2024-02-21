#pragma once
#include "Libs.h"

struct Vector {
	DirectX::XMVECTOR vector;
};

struct Matrix {
	DirectX::XMMATRIX matrix;
};


class GlobalBuffers {
	friend class Graphics;
public:
	GlobalBuffers(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pContext);
	void ChangeGlobalBuffer(std::variant<Matrix, Vector, float, int> Data, std::string bufferName);
	void AddGlobalBuffer(std::variant<Matrix, Vector, float, int> Data, std::string bufferName);
	~GlobalBuffers();
	GlobalBuffers(const GlobalBuffers&) = delete;
	GlobalBuffers& operator = (const GlobalBuffers&) = delete;
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;

	void SetUpPipelineBuffers();
	void UpdatePipelineBuffers();
	std::unordered_map<std::string, std::variant<Matrix, Vector, float, int>> Datas;
	std::vector<Matrix> matrices;
	std::vector<Vector> vectors;
	std::vector<float> floats;
	std::vector<int> intergers;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pMatrixConstantBuffers;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVectorConstantBuffers;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pFloatConstantBuffers;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIntConstantBuffers;
	D3D11_BUFFER_DESC cbd;
	D3D11_SUBRESOURCE_DATA scbd;
};

