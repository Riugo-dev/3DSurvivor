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

StructuredBuffer<float3> g_SpawnPosition : register(t0);
AppendStructuredBuffer<GPUParticle> Particles : register(u0);


#define MAX_PARTICLE 65536

cbuffer SpawnBuffer : register(b8)
{
    uint SpawnCount; //V‹K‚Ì”š”­
    uint ParticleCount;
    float2 pad;
};

float Rand(uint seed)
{
    return frac(sin(seed * 12.9898) * 43758.5453);
}

[numthreads(256, 1 , 1)]
void main(uint3 id : SV_DispatchThreadID)
{
    uint idx = id.x;
    uint totalspawn = SpawnCount * ParticleCount;
    if (idx >= totalspawn)
    {
        return;
    }
    
    uint explosionID = idx / ParticleCount;
    uint localID = idx % ParticleCount;
    
    float3 basepos = g_SpawnPosition[explosionID];
    
    float rx = Rand(localID * 3 + 1);
    float ry = Rand(localID * 3 + 2);
    float rz = Rand(localID * 3 + 3);
           
    float x = (rx * 100.0 - 50.0) / 500.0;
    float y = (ry * 100.0 + 50.0) / 500.0;
    float z = (rz * 100.0 - 50.0) / 500.0;
           
    GPUParticle p;
    p.position = g_SpawnPosition[explosionID];
    p.velocity = float3(x, y, z);
    p.life = 0.01;
    p.maxLife = 60.0;
    p.color = float4(1.0, 1.0, 1.0, 1.0);
    //p.scale = float3(1, 1, 1);
    p.scale = float3(0.1, 0.1, 0.1);
    //p.scale = float3(0.05, 0.05, 0.05);
    p.pad = 0;
    
    Particles.Append(p);
}
