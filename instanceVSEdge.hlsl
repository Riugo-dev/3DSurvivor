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

matrix MakeRotation(float3 rot)
{
    float cosx = cos(rot.x);
    float cosy = cos(rot.y);
    float cosz = cos(rot.z);
    
    float sinx = sin(rot.x);
    float siny = sin(rot.y);
    float sinz = sin(rot.z);
    
    matrix Rotx =
    {
        1, 0, 0, 0,
        0, cosx, sinx, 0,
        0, -sinx, cosx, 0,
        0, 0, 0, 1
    };
    
    matrix Roty =
    {
        cosy, 0, -siny, 0,
        0, 1, 0, 0,
        siny, 0, cosy, 0,
        0, 0, 0, 1
    };
    
    matrix Rotz =
    {
        cosz, sinz, 0, 0,
        -sinz, cosz, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    
    return mul(Rotz, mul(Roty, Rotx)); //ZYX
    
}

void main(in VS_IN In, out PS_IN Out)
{
     //スケール
    matrix Scale =
    {
        In.Inst_Scale.x, 0, 0, 0,
        0, In.Inst_Scale.y, 0, 0,
        0, 0, In.Inst_Scale.z, 0,
        0, 0, 0, 1
    };
    
    //回転
    matrix Rotation = MakeRotation(In.Inst_Rotation);
    
    //平行移動
    matrix Translation =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        In.Inst_Position.x, In.Inst_Position.y, In.Inst_Position.z, 1
    };
    
    matrix World = mul(Scale, mul(Rotation, Translation));
    matrix WVP = mul(World, mul(View, Projection));
    
    //法線方向に押し出し（エッジ）
    float3 normal = normalize(mul(float4(In.Normal.xyz, 0.0f), World).xyz);
    float4 pos = float4(In.Position.xyz , 1.0f);
    pos.xyz += normal * 0.05f;
    
    Out.Position = mul(pos, WVP);
    Out.WorldPosition = mul(pos, World);
    Out.Normal = float4(normal, 1.0f);
    
    Out.Diffuse = float4(0, 0, 0, 1);//エッジの色
    Out.TexCoord = In.TexCoord;
    
}