#include "common.hlsl"

struct GPUParticle
{
    float3 position;
    float life;

    float3 velocity;
    float maxLife;

    float4 color;
    float3 scale;
    float pad;
};

StructuredBuffer<GPUParticle> Particles : register(t0);


cbuffer CameraCB : register(b8)
{
    float3 CameraRight;
    float pad0;
    float3 CameraUp;
    float pad1;
    float4x4 ViewProj;
};

struct VS_IN
{
    uint ParticleID : SV_InstanceID;
    uint VertexID : SV_VertexID;
};

struct PS_IN
{
    float4 Position : SV_POSITION;
    float4 Diffuse : COLOR;
    float2 TexCoord : TEXCOORD0;
};

void main(in VS_IN In , out PS_IN Out)
{
    GPUParticle p = Particles[In.ParticleID];
    
    if (p.life <= 0)
    {
        Out.Position = float4(-10, -10, -10, 0);
        Out.Diffuse = float4(0, 0, 0, 0);
        Out.TexCoord = float2(0, 0);
        return;
    }
    
    float2 quad[4] =
    {
        float2(-1, -1),
        float2(-1, 1),
        float2(1, -1),
        float2(1, 1),
    };

    float2 uv[4] =
    {
        float2(0, 1),
        float2(0, 0),
        float2(1, 1),
        float2(1, 0)
    };
    
    float2 q = quad[In.VertexID];

    float3 offset = CameraRight * q.x * p.scale + CameraUp * q.y * p.scale;

    float3 worldPos = p.position + offset;

    Out.Position = mul(float4(worldPos, 1.0f), ViewProj);
    Out.Diffuse = p.color;
    Out.TexCoord = uv[In.VertexID];
}