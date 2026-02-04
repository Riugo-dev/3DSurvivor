
AppendStructuredBuffer<uint> DeadList : register(u0);


#define MAX_PARTICLE 65536

[numthreads(256 , 1 , 1)]
void main(uint3 id : SV_DispatchThreadID)
{
    uint index = id.x;
    
    if(index >= MAX_PARTICLE)
    {
        return;
    }
    
    DeadList.Append(index);
}