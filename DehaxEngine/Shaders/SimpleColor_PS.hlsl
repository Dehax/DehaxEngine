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
	float3 normalizedLight = normalize((float3)vLightDir);
	float3 norm = normalize(input.Norm);
	float4 finalColor;
	finalColor.x = dot(normalizedLight, norm) * modelColor.x;
	finalColor.y = dot(normalizedLight, norm) * modelColor.y;
	finalColor.z = dot(normalizedLight, norm) * modelColor.z;
	finalColor.a = 1;

	return finalColor;
}