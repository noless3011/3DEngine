#include "GlobalBuffers.h"



GlobalBuffers::GlobalBuffers(Microsoft::WRL::ComPtr<ID3D11Device>& _pDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext>& _pContext)
{
	pDevice = _pDevice;
	pContext = _pContext;
	cbd = {};
	scbd = {};
}

void GlobalBuffers::ChangeGlobalBuffer(std::variant<Matrix, Vector> _Data, std::string bufferName)
{
	Datas[bufferName] = _Data;
	matrices.clear();
	vectors.clear();
	for (const auto& Data : Datas) {
		if (std::get_if<Matrix>(&Data.second)) {
			matrices.push_back(std::get<Matrix>(Data.second));
		}
		if (std::get_if<Vector>(&Data.second)) {
			vectors.push_back(std::get<Vector>(Data.second));
		}

	}
}

void GlobalBuffers::AddGlobalBuffer(std::variant<Matrix, Vector> _Data, std::string bufferName)
{
	Datas.insert({ bufferName, _Data });
	matrices.clear();
	vectors.clear();
	for (const auto& Data : Datas) {
		if (std::get_if<Matrix>(&Data.second)) {
			matrices.push_back(std::get<Matrix>(Data.second));
		}
		if (std::get_if<Vector>(&Data.second)) {
			vectors.push_back(std::get<Vector>(Data.second));
		}

	}
}

GlobalBuffers::~GlobalBuffers()
{
}


void GlobalBuffersSystem::SetUpPipelineBuffers() 
{
	matrices.clear();
	vectors.clear();
	for (const auto& Data : Datas) {
		if (std::get_if<Matrix>(&Data.second)) {
			matrices.push_back(std::get<Matrix>(Data.second));
		}
		if (std::get_if<Vector>(&Data.second)) {
			vectors.push_back(std::get<Vector>(Data.second));
		}

	}




	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0;
	if (matrices.size() != 0) {
		cbd.ByteWidth = sizeof(Matrix) * matrices.size();
		cbd.StructureByteStride = sizeof(Matrix);
		scbd.pSysMem = matrices.data();
		CHECK_HRESULT(pDevice->CreateBuffer(&cbd, &scbd, &pMatrixConstantBuffers));
		pContext->VSSetConstantBuffers(matrix_slot_system, 1, pMatrixConstantBuffers.GetAddressOf());
	}


	if (vectors.size() != 0) {
		cbd.ByteWidth = sizeof(Vector) * vectors.size();
		cbd.StructureByteStride = sizeof(Vector);
		scbd.pSysMem = vectors.data();
		pDevice->CreateBuffer(&cbd, &scbd, &pVectorConstantBuffers);
		pContext->VSSetConstantBuffers(vector_slot_system, 1, pVectorConstantBuffers.GetAddressOf());
	}
}

void GlobalBuffersSystem::UpdatePipelineBuffers()//need changes
{
	D3D11_MAPPED_SUBRESOURCE newSubresource = {};
	if (pMatrixConstantBuffers.Get() == nullptr && matrices.size() != 0) {
		SetUpPipelineBuffers();
	}
	if (pMatrixConstantBuffers.Get() != nullptr && matrices.size() != 0) {
		pContext->Map(pMatrixConstantBuffers.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &newSubresource);
		memcpy(newSubresource.pData, matrices.data(), matrices.size() * sizeof(Matrix));
		pContext->Unmap(pMatrixConstantBuffers.Get(), 0);
		pContext->VSSetConstantBuffers(matrix_slot_system, 1, pMatrixConstantBuffers.GetAddressOf());
	} 
	
	if (pVectorConstantBuffers.Get() == nullptr && vectors.size() != 0) {
		SetUpPipelineBuffers();
	}
	if (pVectorConstantBuffers.Get() != nullptr || vectors.size() != 0) {
		pContext->Map(pVectorConstantBuffers.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &newSubresource);
		memcpy(newSubresource.pData, vectors.data(), vectors.size() * sizeof(Vector));
		pContext->Unmap(pVectorConstantBuffers.Get(), 0);
		pContext->VSSetConstantBuffers(vector_slot_system, 1, pVectorConstantBuffers.GetAddressOf());
	}
}



void GlobalBuffersUser::SetUpPipelineBuffers()
{
	matrices.clear();
	vectors.clear();
	for (const auto& Data : Datas) {
		if (std::get_if<Matrix>(&Data.second)) {
			matrices.push_back(std::get<Matrix>(Data.second));
		}
		if (std::get_if<Vector>(&Data.second)) {
			vectors.push_back(std::get<Vector>(Data.second));
		}

	}




	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0;
	if (matrices.size() != 0) {
		cbd.ByteWidth = sizeof(Matrix) * matrices.size();
		cbd.StructureByteStride = sizeof(Matrix);
		scbd.pSysMem = matrices.data();
		CHECK_HRESULT(pDevice->CreateBuffer(&cbd, &scbd, &pMatrixConstantBuffers));
		pContext->VSSetConstantBuffers(matrix_slot_user, 1, pMatrixConstantBuffers.GetAddressOf());
	}


	if (vectors.size() != 0) {
		cbd.ByteWidth = sizeof(Vector) * vectors.size();
		cbd.StructureByteStride = sizeof(Vector);
		scbd.pSysMem = vectors.data();
		pDevice->CreateBuffer(&cbd, &scbd, &pVectorConstantBuffers);
		pContext->VSSetConstantBuffers(vector_slot_user, 1, pVectorConstantBuffers.GetAddressOf());
	}
}

void GlobalBuffersUser::UpdatePipelineBuffers(){
	D3D11_MAPPED_SUBRESOURCE newSubresource = {};
	if (pMatrixConstantBuffers.Get() == nullptr && matrices.size() != 0) {
		SetUpPipelineBuffers();
	}
	if (pMatrixConstantBuffers.Get() != nullptr && matrices.size() != 0) {
		pContext->Map(pMatrixConstantBuffers.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &newSubresource);
		memcpy(newSubresource.pData, matrices.data(), matrices.size() * sizeof(Matrix));
		pContext->Unmap(pMatrixConstantBuffers.Get(), 0);
		pContext->VSSetConstantBuffers(matrix_slot_user, 1, pMatrixConstantBuffers.GetAddressOf());
	}

	if (pVectorConstantBuffers.Get() == nullptr && vectors.size() != 0) {
		SetUpPipelineBuffers();
	}
	if (pVectorConstantBuffers.Get() != nullptr || vectors.size() != 0) {
		pContext->Map(pVectorConstantBuffers.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &newSubresource);
		memcpy(newSubresource.pData, vectors.data(), vectors.size() * sizeof(Vector));
		pContext->Unmap(pVectorConstantBuffers.Get(), 0);
		pContext->VSSetConstantBuffers(vector_slot_user, 1, pVectorConstantBuffers.GetAddressOf());
	}
}



GlobalBuffersSystem::GlobalBuffersSystem(Microsoft::WRL::ComPtr<ID3D11Device>& _pDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext>& _pContext) {
	pDevice = _pDevice;
	pContext = _pContext;
	cbd = {};
	scbd = {};
}


GlobalBuffersUser::GlobalBuffersUser(Microsoft::WRL::ComPtr<ID3D11Device>& _pDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext>& _pContext) {
	pDevice = _pDevice;
	pContext = _pContext;
	cbd = {};
	scbd = {};
}