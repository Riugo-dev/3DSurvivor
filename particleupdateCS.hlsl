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

StructuredBuffer<GPUParticle> g_Input : register(t0);
AppendStructuredBuffer<GPUParticle> g_Output : register(u0);

#define MAX_PARTICLE 65536

cbuffer UpdateBuffer : register(b8)
{
    float Gravity;
    float FadeSpeed;
    uint AliveCount;
    float padding;
}

[numthreads(256, 1 , 1)]
void main(uint3 id : SV_DispatchThreadID)
{
    uint index = id.x;
    
    if (index >= AliveCount)
        return;
    
    GPUParticle p = g_Input[index];
    
    if(p.life >= p.maxLife)
    {
        return;
    }
    
    p.velocity.y += Gravity;
    p.position += p.velocity;
    p.life += FadeSpeed;
    
    g_Output.Append(p);
    
}