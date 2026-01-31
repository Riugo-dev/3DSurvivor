#include	"common.hlsl"
Texture2D g_Texture : register(t0); //テクスチャ０番
Texture2D g_TextureToon : register(t1); //テクスチャ1番
SamplerState g_SamplerState : register(s0); //サンプラー０番

struct PS_IN
{
    float4 Position : SV_POSITION;
    float4 WorldPosition : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
    //float4 WorldPosition : TEXCOORD0;
    //float4 Normal : TEXCOORD1;
    //float4 Diffuse : TEXCOORD2;
    //float2 TexCoord : TEXCOORD3;
    //float VertexLight : TEXCOORD1;//頂点ライティングの結果
    //float3 LightDir : TEXCOORD2;//VSで計算したキャラ基準のライト方向
};

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//光源からピクセルへのベクトル
    float4 lv = In.WorldPosition - Light.Position;
	//物体と光源の距離
    float4 ld = length(lv);
	//ベクトルの正規化
    lv = normalize(lv);

	//減衰の計算
    float ofs = 1.0f - (1.0f / Light.PointLightParam.x) * ld;
	//減衰率0未満は0にする。
    ofs = max(0, ofs);
    
   	//ピクセルの法線を正規化
    float4 normal = normalize(In.Normal);
	//光源計算
    float light = -dot(normal.xyz, lv.xyz);
    //明るさをクランプしておく
    light = clamp(light, 0.01f, 0.99f);
    //lightをテクスチャ座標xとしてテクスチャから明るさ値を取得
    float4 toon = g_TextureToon.Sample(g_SamplerState, float2(light, 0.01f));
    toon *= ofs; //明るさを減衰させる

	//テクスチャのピクセル色を取得
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.rgb *= toon.rgb * In.Diffuse.rgb + Light.Ambient.rgb;
    outDiffuse.a *= In.Diffuse.a;
  

    //ここから下はエッジの処理
    
    
    
    
    
    
    
}





