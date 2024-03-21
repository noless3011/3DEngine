
cbuffer cMatrixBufSystem : register(b0)
{ 
    
};
cbuffer cVectorBufSystem : register(b1)
{
    
};


cbuffer cMatrixBufUser : register(b2)
{
};
cbuffer cVectorBufUser : register(b3)
{
    float4 test;
};


float4 main(float4 pos : SV_Position, float4 normal : NORMAL) : SV_TARGET0
{
	
	return test;
}