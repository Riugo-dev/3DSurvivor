#include "common.hlsl"

struct VS_IN
{
    float4 Position : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
    
    //----インスタンスデータ-------
    float3 Inst_Position : INSTANCE_POS;
    float3 Inst_Scale : INSTANCE_SCALE;
    float3 Inst_Rotation : INSTANCE_ROT;
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
    
    return mul(Rotz, mul(Roty, Rotx));//ZYX
    
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
    
    matrix World =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 5, 1
    };
    
    //matrix World = mul(Scale, Rotation);
    //World = mul(World, Translation);
    
    matrix WVP = mul(World, View);
    WVP = mul(WVP, Projection);
    
    Out.Position = mul(In.Position, WVP);
    Out.WorldPosition = mul(In.Position, World);
    
    float4 normal = float4(In.Normal.xyz, 0.0f);
    Out.Normal = normalize(mul(normal, Rotation));
    
    Out.Diffuse = In.Diffuse;
    Out.TexCoord = In.TexCoord;
}