struct PixelIn
{
	float4 pos : SV_Position;
	float4 col : COLOR;
	float2 tex : TEXCOORD0;
};

struct PixelOut
{
	float4 col : COLOR;
};

Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s);

float4 main(PixelIn input) : SV_TARGET
{
	PixelOut output;
output.col = txDiffuse.Sample(samLinear, input.tex) * input.col;

return output.col;
}
