//********************************************************************************
//
// unlitTexInstancedVS.hlsl
//
//															Author :Riugo Honda
//															Date   :2026/02/10
// -------------------------------------------------------------------------------
//															Last Edited:2026/02/10
//********************************************************************************

#include "common.hlsl"

struct VS_IN
{
    float4 Position : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
    
      //----インスタンスデータ-------
    float4 Inst_Position : INSTANCE_POS;
    float4 Inst_Scale : INSTANCE_SCALE;
    float4 Inst_Rotation : INSTANCE_ROT;
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

cbuffer CameraCB : register(b8)
{
    float3 CameraRight;
    float pad0;
    float3 CameraUp;
    float pad1;
    float4x4 ViewProj;
};

void main(in VS_IN In, out PS_IN Out)
{
    
    float2 billboard = In.Position.xy;
    
    float3 WorldPosition = In.Inst_Position.xyz + CameraRight * (billboard.x * In.Inst_Scale.x) + CameraUp * (billboard.y * In.Inst_Scale.y);

    Out.Position = mul(float4(WorldPosition, 1), ViewProj);
    Out.TexCoord = In.TexCoord;
    Out.Diffuse = In.Diffuse * Material.Diffuse;

}

