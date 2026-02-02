#include "common.hlsl"

struct GPUParticle
{
    float3 position;
    float life;

    float3 velocity;
    float maxLife;

    float4 color;
};