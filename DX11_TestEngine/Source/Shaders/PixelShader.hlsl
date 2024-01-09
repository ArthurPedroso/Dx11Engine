struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
	float4 Color : COLOR;
};

cbuffer PS_ConstantBuffer
{
    row_major matrix  GeometryMVP;
    unsigned int RenderFlags;
	float3 GlobalLight;
};

float4 main(PS_INPUT psInput) : SV_TARGET
{
	return psInput.Color; 
	//return float4(sin(Pos.x / 1200), sin(Pos.y / 900), 0.0f, 1.0f);
}