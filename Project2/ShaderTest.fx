﻿//////////////////////////////////////////////////
// 作成日:2016/9/20
// 更新日:2016/9/20
// 制作者:Got
//////////////////////////////////////////////////

// バーテックスシェーダー
float4 VS(float4 Pos : POSITION) : SV_POSITION
{
	return Pos;
}

// ピクセルシェーダー
float4 PS(float4 Pos : SV_POSITION) : SV_Target
{
	return float4(1.0f, 1.0f, 0.0f, 1.0f);
}
