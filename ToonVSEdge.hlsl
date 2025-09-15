
//ToonVS.hlsl

#include "common.hlsl"

void main(in VS_IN  In, out PS_IN  Out)
{
	//ワールドビュープロジェクション行列作成
	matrix	wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

	//モデルの変形
    float4 pos = In.Position;
    float4 norm = normalize(In.Normal) * 0.05f;//スケーリング
    norm.w = 0;
    pos += norm;	//頂点の移動
    Out.Position = mul(pos, wvp); //頂点変換
	
	//頂点法線をワールド行列で変換して出力
	float4	worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0f);
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);
	Out.Normal = worldNormal;

    Out.Diffuse.rgb = 0.0f;		//エッジ色の出力
    Out.Diffuse.a = 1.0f;		//頂点色のα
	Out.TexCoord = In.TexCoord;	//テクスチャ座標の出力

	//ワールド変換した頂点座標を出力
    Out.WorldPosition = mul(pos, World);

}


