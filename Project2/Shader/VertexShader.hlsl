cbuffer View : register (b0)
{
	matrix wMat;
	float4 color;
	float4 rect;
	float vWidth;
	float vHeight;
	float tWidth;
	float tHeight;
}


struct VertexIn
{
	float4 pos : POSITION;
	float4 col : COLOR;
	float2 tex : TEXCOORD0;
};

struct VertexOut
{
	float4 pos : SV_Position;
	float4 col : COLOR;
	float2 tex : TEXCOORD0;
};

VertexOut main(VertexIn input)
{
	VertexOut output;
	input.tex.x += (0.5f / vWidth);
	input.tex.y += (0.5f / vHeight);
	output.pos = mul(input.pos, wMat);
	output.pos.x = output.pos.x / vWidth * 2.0f - 1.0f;
	output.pos.y = 1.0f - output.pos.y / vHeight * 2.0f;

	output.col = input.col * color;

	output.tex = (input.tex * float2(rect.z - rect.x, rect.w - rect.y) + float2(rect.x, rect.y)) / float2(tWidth, tHeight);

	return output;
}