
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


cbuffer cMatrixBufSystem : register (b0){
	matrix mymatrix;
};
cbuffer cVectorBufSystem : register (b1){
    
};


cbuffer cMatrixBufUser : register(b2){
};
cbuffer cVectorBufUser : register(b3){
    float4 scale;
};


VSOut main(VSIn input)
{
    VSOut output;
    output.pos = mul(float4(input.pos * scale.x, 1), mymatrix);
    output.my_color = float4(input.normal, 1);
    output.normal = float4(input.normal, 1);
	return output ;
}
