#include "common.hlsl"
void main(in VS_IN In, out PS_IN Out)
{
    //インスタンシング
    float4x4 InstanceWorld =
    {
        In.Instance0,
        In.Instance1,
        In.Instance2,
        In.Instance3
    };
    
	//ここで頂点変換
	//頂点座標を出力
	//頂点変換処理  この処理は必ず必要
    float4 worldpos = mul(In.Position, InstanceWorld);
    float4 viewpos = mul(worldpos, View);
    Out.Position = mul(viewpos, Projection);
    
    //float4x4 wvp; //行列変数を作成
    //wvp = View /*mul(InstanceWorld, View)*/; //wvp = ワールド行列＊カメラ行列
    //wvp = mul(wvp, Projection); //wvp = wvp *プロジェクション行列
    //Out.Position = mul(In.Position, wvp); //変換結果を出力する
    
	//頂点法線をワールド行列で回転させる(頂点と同じ回転をさせる)
    float4 worldNormal, normal; //ローカル変数を作成
    normal = float4(In.Normal.xyz, 0.0); //入力法線ベクトルのwを0としてコピー（平行移動しないため)
    worldNormal = mul(normal, InstanceWorld); //コピーされた法線をワールド行列で回転する
    worldNormal = normalize(worldNormal); //回転後の法線を正規化する
    Out.Normal = worldNormal; //回転後の法線出力 In.Normalでなく回転後の法線を出力

    Out.Diffuse = In.Diffuse; //頂点の物をそのまま出力
	//受け取ったこの頂点のUV座標をそのまま出力
    Out.TexCoord = In.TexCoord;

	//ワールド変換した頂点座標を出力
    Out.WorldPosition = mul(In.Position, InstanceWorld);




}




