struct VS_INPUT
{
    float3 Pos : POSITION;
    float3 Normal : NORMAL;
    float4 Color : COLOR;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 Normal : NORMAL;
    float4 Color : COLOR;
};

cbuffer VS_ConstantBuffer
{
    row_major matrix  GeometryMVP;
    unsigned int RenderFlags;
    float3 GlobalLight;
};



VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    output.Pos = mul(float4(input.Pos.x, input.Pos.y, input.Pos.z, 1.0f), GeometryMVP);
    output.Normal = input.Normal;
    output.Color = input.Color;
	return output;
}