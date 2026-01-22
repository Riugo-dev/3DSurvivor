//********************************************************************************
//
// unlitTexturePS.hlsl
//
//															Author :Riugo Honda
//															Date   :2025/04/23
// -------------------------------------------------------------------------------
//															Last Edited:2025/04/23
//********************************************************************************

#include "common.hlsl"


Texture2D		g_Texture : register(t0);
SamplerState	g_SamplerState : register(s0);

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

    if (Material.TextureEnable)
    {
        outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
        outDiffuse *= In.Diffuse;
    }
    else
    {
        outDiffuse = In.Diffuse;
    }


}
