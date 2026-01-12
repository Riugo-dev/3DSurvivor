//********************************************************************************
//
// wavePS.hlsl
//
//															Author :Riugo Honda
//															Date   :2025/09/30
//********************************************************************************

#include "common.hlsl"


Texture2D g_Texture : register(t0);
Texture2D g_EnvTexture : register(t1);

SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    //視線ベクトル
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    
    //法線ベクトル
    float3 normal = normalize(In.Normal.xyz);
    
    //反射ベクトル
    float3 refv = reflect(eyev.xyz, normal);
    refv = normalize(refv);
    
    //環境マッピングテクスチャ座標（パノラマ）
    float2 envTexCoord;
    envTexCoord.x = atan2(refv.x, refv.z) / (3.14 * 2);
    envTexCoord.y = acos(refv.y) / 3.14;
    
    if (Material.TextureEnable)
    {
        outDiffuse = g_EnvTexture.Sample(g_SamplerState, envTexCoord.xy);
        outDiffuse *= In.Diffuse;
    }
    else
    {
        outDiffuse = In.Diffuse;
    }

    //フレネル反射
    float f0 = 0.1f;
    float d = dot(-eyev, normal);
    float fresnel = f0 + (1.0f - f0) * pow((1.0f - d), 5.0f);
    
    outDiffuse.a = fresnel;

}
