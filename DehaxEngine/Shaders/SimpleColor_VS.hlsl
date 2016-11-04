cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
	float4 vLightDir;
	float4 modelColor;
}

struct VS_INPUT
{
	float4 Pos : POSITION;
	float3 Norm : NORMAL;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float3 Norm : TEXCOORD0;
	float3 ViewVec : TEXCOORD1;
};

PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;
	output.Pos = mul(input.Pos, World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	output.Norm = input.Norm;

	return output;
}