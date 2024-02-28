
struct VSOut 
{
    float4 pos : SV_Position;
    float4 my_color : COLOR;
    float4 normal : Normal;
};

struct VSIn
{
    float3 pos : Position;
    float3 normal : normal;
};


cbuffer cMatrixBuf : register (b0){
	matrix mymatrix;
};
cbuffer cVectorBuf : register (b1){
    float4 color1;
    float4 scale;
    
};


VSOut main(VSIn input)
{
    VSOut output;
    output.pos = mul(float4(input.pos, 1), mymatrix);
    output.my_color = float4(input.normal, 1);
    output.normal = float4(input.normal, 1);
	return output ;
}
