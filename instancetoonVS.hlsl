#include "common.hlsl"

StructuredBuffer<float3> Position : register(t2);

void main(in VS_IN In, out PS_IN Out)
{
    float3 instancePos = Position[In.InstanceId];
    
    float4 worldPos = In.Position;
    worldPos.xyz += instancePos;
    
    worldPos = mul(worldPos, World);
    worldPos = mul(worldPos, View);
    Out.Position = mul(worldPos, Projection);
    
    Out.TexCoord = In.TexCoord;
    Out.Diffuse = In.Diffuse * Material.Diffuse;
}