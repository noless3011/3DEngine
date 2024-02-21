


cbuffer cMatrixBuf : register (b0){
	matrix mymatrix;
};
cbuffer cVectorBuf : register (b1){
	float4 scale;
};


float4 main(float3 pos : Position) : SV_POSITION
{
	float x = 0.2;
	return mul(float4(pos * scale.x, 1) ,mymatrix) ;
}
