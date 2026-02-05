#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

struct PS_IN
{
    float4 Position : SV_POSITION;
    float4 Diffuse : COLOR;
    float2 TexCoord : TEXCOORD0;
};


void main(in PS_IN In , out float4 outDiffuse : SV_Target) 
{
    float4 tex = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse = tex * In.Diffuse;
}