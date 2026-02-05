
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
    
    if(p.life > 0.0 && p.life < 5.0)
    {
        p.color = float4(1.0f , 1.0f , 0.0f , 1.0f);
    }
    else if (p.life < 20)
    {
        p.color = float4(0.7f, 0.2f, 0.0f, 1.0f);
    }
    else if (p.life < 60)
    {
        p.color = float4(0.5f, 0.0f, 0.0f, 1.0f);
    }
    
    Particles[Index] = p;
}