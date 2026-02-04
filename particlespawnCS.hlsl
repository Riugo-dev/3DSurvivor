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

RWStructuredBuffer<GPUParticle> Particles : register(u0);
AppendStructuredBuffer<uint> AliveList : register(u1);
ConsumeStructuredBuffer<uint> DeadList : register(u2);


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
    
    uint particleIndex;
    bool valid = DeadList.Consume(particleIndex);
   
    if(!valid)
        return;
    
    float seed = (particleIndex * 12.9898 + localID * 78.233);
    float rx = Rand(sin(seed) * 43758.5453);
    float ry = Rand(sin(seed * 1.3) * 43758.5453);
    float rz = Rand(sin(seed * 1.7) * 43758.5453);
           
    float x = (rx * 100.0 - 50.0) / 500.0;
    float y = (ry * 100.0 + 50.0) / 500.0;
    float z = (rz * 100.0 - 50.0) / 500.0;
           
    GPUParticle p;
    p.position = g_SpawnPosition[idx];
    p.velocity = float3(x, y, z);
    p.life = 0.01;
    p.maxLife = 60.0;
    p.color = float4(1.0, 0.7, 0.3, 1.0);
    //p.scale = float3(1, 1, 1);
    p.scale = float3(0.05, 0.05, 0.05);
    p.pad = 0;
    
    Particles[particleIndex] = p;
    
    AliveList.Append(particleIndex);
}
