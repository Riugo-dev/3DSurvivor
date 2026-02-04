
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
AppendStructuredBuffer<uint> AliveListOut : register(u1);
AppendStructuredBuffer<uint> DeadList : register(u2);
ConsumeStructuredBuffer<uint> AliveListIn : register(u3);


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
    uint particleIndex;
    bool valid = AliveListIn.Consume(particleIndex);

    if (!valid)
        return;
    
    GPUParticle p = Particles[particleIndex];
    
    p.velocity.y += Gravity;
    p.position += p.velocity;
    p.life += FadeSpeed;
    
    if(p.life >= p.maxLife)
    {
        p.life = 0.0f;
        Particles[particleIndex] = p;
        DeadList.Append(particleIndex);

    }
    else
    {
        Particles[particleIndex] = p;
        AliveListOut.Append(particleIndex);
    }    
}