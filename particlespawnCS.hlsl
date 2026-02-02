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
AppendStructuredBuffer<GPUParticle> g_Particle: register(u0);

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
    uint particleindex = id.x;
    uint totalparticles = SpawnCount * ParticleCount;
    
    if (particleindex >= totalparticles)
    {
        return;
    }
    
    uint spawnindex = particleindex / ParticleCount;
    uint localindex = particleindex % ParticleCount;
    
    float3 basepos = g_SpawnPosition[spawnindex];
    
    float rx = Rand(localindex * 3 + 1);
    float ry = Rand(localindex * 3 + 2);
    float rz = Rand(localindex * 3 + 3);
           
    float x = (rx * 100.0 - 50.0) / 500.0;
    float y = (ry * 100.0 + 50.0) / 500.0;
    float z = (rz * 100.0 - 50.0) / 500.0;
           
    GPUParticle p;
    p.position = basepos;
    p.velocity = float3(x, y, z);
    p.life = 0.0;
    p.maxLife = 60.0;
    p.color = float4(1.0, 0.7, 0.3, 1.0);
    //p.scale = float3(1, 1, 1);
    p.scale = float3(0.05, 0.05, 0.05);
    p.pad = 0;
    
    g_Particle.Append(p);
}
