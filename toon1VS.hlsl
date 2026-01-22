#include "common.hlsl"

struct VS_IN
{
    float4 Position : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
};

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

void main(in VS_IN In, out PS_IN Out)
{
	//ここで頂点変換
	//頂点座標を出力
	//頂点変換処理  この処理は必ず必要
    matrix wvp; //行列変数を作成
    wvp = mul(World, View); //wvp = ワールド行列＊カメラ行列
    wvp = mul(wvp, Projection); //wvp = wvp *プロジェクション行列
    Out.Position = mul(In.Position, wvp); //変換結果を出力する

	//頂点法線をワールド行列で回転させる(頂点と同じ回転をさせる)
    float4 worldNormal, normal; //ローカル変数を作成
    normal = float4(In.Normal.xyz, 0.0); //入力法線ベクトルのwを0としてコピー（平行移動しないため)
    worldNormal = mul(normal, World); //コピーされた法線をワールド行列で回転する
    worldNormal = normalize(worldNormal); //回転後の法線を正規化する
    Out.Normal = worldNormal; //回転後の法線出力 In.Normalでなく回転後の法線を出力

    Out.Diffuse = In.Diffuse; //頂点の物をそのまま出力
	//受け取ったこの頂点のUV座標をそのまま出力
    Out.TexCoord = In.TexCoord;

	//ワールド変換した頂点座標を出力
    Out.WorldPosition = mul(In.Position, World);




}
