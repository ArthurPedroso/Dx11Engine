struct GS_INPUT
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
	float4 Color : COLOR;
};

struct GSOutput
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
	float4 Color : COLOR;
};

cbuffer GS_ConstantBuffer
{
	row_major matrix  GeometryMVP;
	unsigned int RenderFlags;
	float3 GlobalLight;
};

[maxvertexcount(3)]
void main(triangle GS_INPUT input[3] : SV_TARGET, inout TriangleStream< GSOutput > output)
{
	float3 vecA;
	float3 vecB;
	float3 faceNormal;
	GSOutput element;

	vecA = (input[0].Pos.xyz - input[1].Pos.xyz);
	vecB = (input[2].Pos.xyz - input[1].Pos.xyz);
	
	faceNormal = normalize(float3((vecA.y * vecB.z) - (vecA.z * vecB.y),
								  (vecA.z * vecB.x) - (vecA.x * vecB.z),
								  (vecA.x * vecB.y) - (vecA.y * vecB.x))) * -1.0f;

	for (int i = 0; i < 3; i++)
	{
		element.Pos = input[i].Pos;
		element.Normal = faceNormal;
		element.Color = input[i].Color * (clamp(length(faceNormal - GlobalLight), 0.1f, 2.0f) / 2.0f);
		output.Append(element);
	}
}