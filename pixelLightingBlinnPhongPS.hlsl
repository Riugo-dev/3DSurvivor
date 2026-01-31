
#include "common.hlsl"

Texture2D g_Texture : register(t0); //テクスチャ０番
SamplerState g_SamplerState : register(s0); //サンプラー０番

struct PS_IN
{
    float4 Position : SV_POSITION;
    float4 WorldPosition : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
    //float4 WorldPosition : TEXCOORD0;
    //float4 Normal : TEXCOORD1;
    //float4 Diffuse : TEXCOORD2;
    //float2 TexCoord : TEXCOORD3;
    //float VertexLight : TEXCOORD1;//頂点ライティングの結果
    //float3 LightDir : TEXCOORD2;//VSで計算したキャラ基準のライト方向
};

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//ピクセルの法線を正規化
	float4 normal = normalize(In.Normal);
	float light = -dot(normal.xyz, Light.Direction.xyz); //光源計算をする
    light = saturate(light);
	
	 // ベースカラー（テクスチャ有無で分岐）
    //float4 baseColor;
    if (Material.TextureEnable == 1)
    {
        // テクスチャ使用
        outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
        outDiffuse.rgb *= Material.Diffuse.rgb;
        outDiffuse.a = Material.Diffuse.a; // αはマテリアル側を使用
    }
    else
    {
        // テクスチャ無し → マテリアルカラーのみ
        outDiffuse = Material.Diffuse;
    }
	
	//カメラからピクセルへ向かうベクトル
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev); //正規化する
//    eyev = normalize(-eyev); //図解通り版

	//ハーフベクトルの作成
    float3 halfv = eyev + Light.Direction.xyz; //視線とライトベクトルを加算
    halfv = normalize(halfv); //正規化する
 //   float3 halfv = eyev + (-Light.Direction.xyz); //図解通り版

    float specular = -dot(halfv, normal.xyz); //ハーフベクトルと法線の内積を計算
 //   float specular = dot(halfv, normal.xyz); //図解通り版
	specular = saturate(specular);//サチュレートする
	specular = pow(specular, 30);

	outDiffuse.rgb += specular;//スペキュラ値をデフューズとして足しこむ



}


//    outDiffuse.rgb *= (In.Diffuse.rgb * light + Light.Ambient.rgb); //明るさを乗算
