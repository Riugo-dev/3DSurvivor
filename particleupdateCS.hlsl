#include "common.hlsl"

struct GPUParticle
{
    float3 position;
    float life;

    float3 velocity;
    float maxLife;

    float4 color;
};

RWStructuredBuffer<GPUParticle> g_Particles : register(u0);

cbuffer UpdateBuffer : register(b8)
{
    float Gravity;
    float FadeSpeed;
    float padding[2];
}

[numthreads(256, 1 , 1)]
void main(uint3 id : SV_DispatchThreadID)
{
    uint index = id.x;
    
    //if (index >= g_Particles.Length)
    //    return;
    
    GPUParticle p = g_Particles[index];
    
    if(p.life <= 0.0f)
    {
        return;
    }
    
    p.velocity.y += Gravity;
    p.position += p.velocity;
    p.life -= FadeSpeed;
    
    g_Particles[index] = p;
    
}