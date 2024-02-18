

cbuffer cBuf
{
	matrix rotate;

};


float4 main(float2 pos : Position) : SV_POSITION
{
	
	return mul(float4(pos, 1, 1), rotate)  ;
}
