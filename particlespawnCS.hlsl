#include "common.hlsl"

struct GPUParticle
{
    float3 position;
    float life;

    float3 velocity;
    float maxLife;

    float4 color;
};

#define PARTICLES_PER_EXPLOSION (1000)

StructuredBuffer<float3> g_SpawnPosition : register(t0);
AppendStructuredBuffer<GPUParticle> g_ParticleAppend : register(u0);

cbuffer SpawnBuffer : register(b8)
{
    uint SpawnCount; //V‹K‚Ì”š”­”
};

[numthreads(256, 1 , 1)]
void main(uint3 id : SV_DispatchThreadID)
{
    uint particleindex = id.x;
    uint totalparticles = SpawnCount * PARTICLES_PER_EXPLOSION;
    
    if (paticleindex >= totalparticles)
    {
        return;
    }
    
    uint explosionindex = particleindex / PARTICLES_PER_EXPLOSION;
    uint localindex = particleindex % PARTICLES_PER_EXPLOSION;
    
    float3 basepos = g_SpawnPosition[explosionindex];
    
    uint seed = particleindex * 747796405u + explosionindex * 912367u;

    float rx = frac(sin(seed * 12.9898) * 43758.5453);
    float ry = frac(sin(seed * 78.233) * 43758.5453);
    float rz = frac(sin(seed * 39.425) * 43758.5453);

    float3 dir = normalize(float3(rx * 2 - 1, ry * 2 - 1, rz * 2 - 1));
    
    GPUParticle p;
    p.position = basepos;
    p.velocity = dir * lerp(0.5, 3.0, ry);
    p.life = 1.0;
    p.maxLife = 1.0;
    p.color = float4(1.0, 0.7, 0.3, 1.0);
    
    g_ParticleAppend.Append(p);
}
