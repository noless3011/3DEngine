#include "GlobalBuffers.h"

GlobalBuffers::GlobalBuffers()
{
	cbd = {};
	scbd = {};
}

void GlobalBuffers::ChangeGlobalBuffer(std::variant<Matrix, Vector, float, int> Data, std::string bufferName)
{
	Datas[bufferName] = Data;
}

void GlobalBuffers::AddGlobalBuffer(std::variant<Matrix, Vector, float, int> Data, std::string bufferName)
{
	Datas.insert({ bufferName, Data });
}

GlobalBuffers::~GlobalBuffers()
{
}





void GlobalBuffers::SetUpPipelineBuffers(Microsoft::WRL::ComPtr<ID3D11Device> &pDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> &pContext)
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
	if (!matrices.empty()) {
		cbd.ByteWidth = sizeof(Matrix) * matrices.size();
		cbd.StructureByteStride = sizeof(Matrix);
		scbd.pSysMem = matrices.data();
		pDevice->CreateBuffer(&cbd, &scbd, &pMatrixConstantBuffers);
		pContext->VSSetConstantBuffers(0, 1, pMatrixConstantBuffers.GetAddressOf());
	}
	

	if (!vectors.empty()) {
		cbd.ByteWidth = sizeof(Vector) * vectors.size();
		cbd.StructureByteStride = sizeof(Vector);
		scbd.pSysMem = vectors.data();
		pDevice->CreateBuffer(&cbd, &scbd, &pVectorConstantBuffers);
		pContext->VSSetConstantBuffers(0, 1, pVectorConstantBuffers.GetAddressOf());
	}

	if (!floats.empty()) {
		cbd.ByteWidth = sizeof(float) * floats.size();
		cbd.StructureByteStride = sizeof(float);
		scbd.pSysMem = floats.data();
		pDevice->CreateBuffer(&cbd, &scbd, &pFloatConstantBuffers);
		pContext->VSSetConstantBuffers(0, 1, pFloatConstantBuffers.GetAddressOf());
	}

	if (!intergers.empty()) {
		cbd.ByteWidth = sizeof(int) * intergers.size();
		cbd.StructureByteStride = sizeof(int);
		scbd.pSysMem = intergers.data();
		pDevice->CreateBuffer(&cbd, &scbd, &pIntConstantBuffers);
		pContext->VSSetConstantBuffers(0, 1, pIntConstantBuffers.GetAddressOf());
	}
}

void GlobalBuffers::UpdatePipelineBuffers(Microsoft::WRL::ComPtr<ID3D11Device> &pDevice)//need changes
{
	

}
