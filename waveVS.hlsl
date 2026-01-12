//********************************************************************************
//
// waveVS.hlsl
//
//															Author :Riugo Honda
//															Date   :2025/09/30
//********************************************************************************

#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{

    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);

    Out.Position = mul(In.Position, wvp);
    Out.TexCoord = In.TexCoord;
    Out.Diffuse = In.Diffuse * Material.Diffuse;
    //Out.Depth = Out.Position.z;
    
    float4 worldNormal, normal;
    normal = float4(In.Normal.xyz, 0.0);
    worldNormal = mul(normal, World);
    worldNormal = normalize(worldNormal);

    Out.Normal.xyz = worldNormal.xyz;
    Out.WorldPosition = mul(In.Position, World);
}

