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
	GlobalBuffers() = default;
	GlobalBuffers(Microsoft::WRL::ComPtr<ID3D11Device>& pDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pContext);
	void ChangeGlobalBuffer(std::variant<Matrix, Vector> Data, std::string bufferName);
	void AddGlobalBuffer(std::variant<Matrix, Vector> Data, std::string bufferName);
	~GlobalBuffers();
	GlobalBuffers(const GlobalBuffers&) = delete;
	GlobalBuffers& operator = (const GlobalBuffers&) = delete;

protected:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	virtual void SetUpPipelineBuffers() = 0;
	virtual void UpdatePipelineBuffers() = 0;
	std::unordered_map<std::string, std::variant<Matrix, Vector>> Datas;
	std::vector<Matrix> matrices;
	std::vector<Vector> vectors;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pMatrixConstantBuffers;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVectorConstantBuffers;
	D3D11_BUFFER_DESC cbd;
	D3D11_SUBRESOURCE_DATA scbd;
};


class GlobalBuffersSystem : public GlobalBuffers {
	friend class Graphics;
protected:
	GlobalBuffersSystem() = default;
	UINT vector_slot_system = 1;
	UINT matrix_slot_system = 0;
	void SetUpPipelineBuffers() override;
	void UpdatePipelineBuffers() override;
public:
	GlobalBuffersSystem(Microsoft::WRL::ComPtr<ID3D11Device>& _pDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext>& _pContext);
};

class GlobalBuffersUser : public GlobalBuffers {
	friend class Graphics;
protected:
	GlobalBuffersUser() = default;
	UINT vector_slot_user = 3;
	UINT matrix_slot_user = 2;
	void SetUpPipelineBuffers() override;
	void UpdatePipelineBuffers() override;
public:
	GlobalBuffersUser(Microsoft::WRL::ComPtr<ID3D11Device>& _pDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext>& _pContext);
};
