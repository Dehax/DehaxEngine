cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
	float4 vLightDir;
	float4 modelColor;
}

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float3 Norm : TEXCOORD0;
};

float4 PS(PS_INPUT input) : SV_TARGET
{
	float4 finalColor = saturate(dot((float3)vLightDir, input.Norm) * modelColor);
	finalColor.a = 1;

	return finalColor;
}