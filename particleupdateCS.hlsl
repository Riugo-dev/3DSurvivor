
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


RWStructuredBuffer<GPUParticle> Particles : register(u0);

#define MAX_PARTICLE 65536

cbuffer UpdateBuffer : register(b8)
{
    float Gravity;
    float FadeSpeed;
    uint AliveCounts;
    float padding;
}

[numthreads(256, 1 , 1)]
void main(uint3 id : SV_DispatchThreadID)
{
    uint Index = id.x;
    //if (Index >= MAX_PARTICLE)
    //    return;
    
    GPUParticle p = Particles[Index];
    
    if (p.life <= 0.0f)
    {
        p.color.a = 0;
        Particles[id.x] = p;
        return;
    }

    
    p.velocity.y += Gravity;
    p.position += p.velocity;
    p.life += FadeSpeed;
    
    Particles[Index] = p;
}