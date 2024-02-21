#include "GlobalBuffers.h"



GlobalBuffers::GlobalBuffers(Microsoft::WRL::ComPtr<ID3D11Device>& _pDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext>& _pContext)
{
	pDevice = _pDevice;
	pContext = _pContext;
	cbd = {};
	scbd = {};
}

void GlobalBuffers::ChangeGlobalBuffer(std::variant<Matrix, Vector, float, int> _Data, std::string bufferName)
{
	Datas[bufferName] = _Data;
	matrices.clear();
	vectors.clear();
	floats.clear();
	intergers.clear();
	for (const auto& Data : Datas) {
		if (std::get_if<Matrix>(&Data.second)) {
			matrices.push_back(std::get<Matrix>(Data.second));
		}
		if (std::get_if<Vector>(&Data.second)) {
			vectors.push_back(std::get<Vector>(Data.second));
		}
		if (std::get_if<float>(&Data.second)) {
			floats.push_back(std::get<float>(Data.second));
		}
		if (std::get_if<int>(&Data.second)) {
			intergers.push_back(std::get<int>(Data.second));
		}

	}
}

void GlobalBuffers::AddGlobalBuffer(std::variant<Matrix, Vector, float, int> _Data, std::string bufferName)
{
	Datas.insert({ bufferName, _Data });
	matrices.clear();
	vectors.clear();
	floats.clear();
	intergers.clear();
	for (const auto& Data : Datas) {
		if (std::get_if<Matrix>(&Data.second)) {
			matrices.push_back(std::get<Matrix>(Data.second));
		}
		if (std::get_if<Vector>(&Data.second)) {
			vectors.push_back(std::get<Vector>(Data.second));
		}
		if (std::get_if<float>(&Data.second)) {
			floats.push_back(std::get<float>(Data.second));
		}
		if (std::get_if<int>(&Data.second)) {
			intergers.push_back(std::get<int>(Data.second));
		}

	}
}

GlobalBuffers::~GlobalBuffers()
{
}





void GlobalBuffers::SetUpPipelineBuffers()
{
	matrices.clear();
	vectors.clear();
	floats.clear();
	intergers.clear();
	for (const auto& Data : Datas) {
		if (std::get_if<Matrix>(&Data.second)) {
			matrices.push_back(std::get<Matrix>(Data.second));
		}
		if (std::get_if<Vector>(&Data.second)) {
			vectors.push_back(std::get<Vector>(Data.second));
		}
		if (std::get_if<float>(&Data.second)) {
			floats.push_back(std::get<float>(Data.second));
		}
		if (std::get_if<int>(&Data.second)) {
			intergers.push_back(std::get<int>(Data.second));
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
		pContext->VSSetConstantBuffers(0, 1, pMatrixConstantBuffers.GetAddressOf());
	}



	if (vectors.size() != 0) {
		cbd.ByteWidth = sizeof(Vector) * vectors.size();
		cbd.StructureByteStride = sizeof(Vector);
		scbd.pSysMem = vectors.data();
		pDevice->CreateBuffer(&cbd, &scbd, &pVectorConstantBuffers);
		pContext->VSSetConstantBuffers(1, 1, pVectorConstantBuffers.GetAddressOf());
	}


	/*if (floats.size() != 0) {
		cbd.ByteWidth = sizeof(float) * floats.size();
		cbd.StructureByteStride = sizeof(float);
		scbd.pSysMem = floats.data();
		pDevice->CreateBuffer(&cbd, &scbd, &pFloatConstantBuffers);
		pContext->VSSetConstantBuffers(0, 1, pFloatConstantBuffers.GetAddressOf());
	}


	if (intergers.size() != 0) {
		cbd.ByteWidth = sizeof(int) * intergers.size();
		cbd.StructureByteStride = sizeof(int);
		scbd.pSysMem = intergers.data();
		pDevice->CreateBuffer(&cbd, &scbd, &pIntConstantBuffers);
		pContext->VSSetConstantBuffers(0, 1, pIntConstantBuffers.GetAddressOf());
	}*/
}

void GlobalBuffers::UpdatePipelineBuffers()//need changes
{
	D3D11_MAPPED_SUBRESOURCE newSubresource = {};
	if (pMatrixConstantBuffers.Get() == nullptr && matrices.size() != 0) {
		SetUpPipelineBuffers();
	}
	if (pMatrixConstantBuffers.Get() != nullptr && matrices.size() != 0) {
		pContext->Map(pMatrixConstantBuffers.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &newSubresource);
		memcpy(newSubresource.pData, matrices.data(), matrices.size() * sizeof(Matrix));
		pContext->Unmap(pMatrixConstantBuffers.Get(), 0);
		pContext->VSSetConstantBuffers(0, 1, pMatrixConstantBuffers.GetAddressOf());
	} 
	
	if (pVectorConstantBuffers.Get() == nullptr && vectors.size() != 0) {
		SetUpPipelineBuffers();
	}
	if (pVectorConstantBuffers.Get() != nullptr || vectors.size() != 0) {
		pContext->Map(pVectorConstantBuffers.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &newSubresource);
		memcpy(newSubresource.pData, vectors.data(), vectors.size() * sizeof(Vector));
		pContext->Unmap(pVectorConstantBuffers.Get(), 0);
		pContext->VSSetConstantBuffers(1, 1, pVectorConstantBuffers.GetAddressOf());
	}
	
	/*if (pFloatConstantBuffers.Get() == nullptr && floats.size() != 0) {
		SetUpPipelineBuffers();
	}
	if (pFloatConstantBuffers.Get() != nullptr || floats.size() != 0) {
		pContext->Map(pFloatConstantBuffers.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &newSubresource);
		memcpy(newSubresource.pData, floats.data(), floats.size() * sizeof(float));
		pContext->Unmap(pFloatConstantBuffers.Get(), 0);
		pContext->VSSetConstantBuffers(0, 1, pFloatConstantBuffers.GetAddressOf());
	}
	

	if (pIntConstantBuffers.Get() == nullptr && intergers.size() != 0) {
		SetUpPipelineBuffers();
	}
	if (pIntConstantBuffers.Get() != nullptr || intergers.size() != 0) {
		pContext->Map(pIntConstantBuffers.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &newSubresource);
		memcpy(newSubresource.pData, intergers.data(), intergers.size() * sizeof(int));
		pContext->Unmap(pIntConstantBuffers.Get(), 0);
		pContext->VSSetConstantBuffers(0, 1, pIntConstantBuffers.GetAddressOf());
	}*/
	

}
