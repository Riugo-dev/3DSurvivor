//********************************************************************************
//
// unlitTextureVS.hlsl
//
//															Author :Riugo Honda
//															Date   :2025/04/23
// -------------------------------------------------------------------------------
//															Last Edited:2025/04/23
//********************************************************************************

#include "common.hlsl"

struct VS_IN
{
    float4 Position : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
};

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

void main(in VS_IN In, out PS_IN Out)
{

	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

	Out.Position = mul(In.Position, wvp);
	Out.TexCoord = In.TexCoord;
	Out.Diffuse = In.Diffuse * Material.Diffuse;

}

