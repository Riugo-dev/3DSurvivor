

//AppendStructuredBuffer<uint> AliveList : register(u0);
//RWByteAddressBuffer IndirectArgs : register(u1);

[numthreads(1, 1, 1)]
void main(uint3 id : SV_DispatchThreadID)
{
    //uint alive = AliveList.IncrementCounter();

    //IndirectArgs.Store(0, 4); // VertexCountPerInstance
    //IndirectArgs.Store(4, alive); // InstanceCount
    //IndirectArgs.Store(8, 0);
    //IndirectArgs.Store(12, 0);
}