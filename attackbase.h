//********************************************************************************
//
// attackbase.h[攻撃の基底クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/012
//********************************************************************************
#ifndef _ATTACKBASE_H_
#define _ATTACKBASE_H_

#include "main.h"
#include "gameobject.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "modelRenderer.h"
#include "player.h"
#include <vector>

typedef enum
{
	ATT_LV1 = 1,
	ATT_LV2,
	ATT_LV3,
	ATT_LV4,
	ATT_LVMAX,
}AttaclLevel;

class BaseAttack : public GameObject
{
protected:
	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ID3D11VertexShader* m_VertexShaderEdge; //輪郭線用頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShaderEdge; //輪郭線用ピクセルシェーダーオブジェクト

	ModelRenderer* m_pModelRenderer = nullptr;

	int m_HP;//攻撃事態のHP（貫通することを考慮して）
	Vector3 m_Velocity;
	int m_FrameCount;
	int m_LivingFrames;

	AttaclLevel m_AttackLevel;
	int m_Strength;//攻撃の威力
public:
	virtual ~BaseAttack() = default;

	void Init(Input*)override {};
	void Uninit() override {};
	virtual void Update() = 0;

	//全て同じ処理でドローするのでここで一括で書く
	void Draw()	override
	{
		{//通常の描画
			//入力レイアウト設定
			Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

			//シェーダ設定
			Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
			Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


			//平行移動行列の作成（表示座標を決める）
			XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.m_x, m_Position.m_y, m_Position.m_z);

			//回転行列（Z回転）行列の作成
			XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.m_x, m_Rotation.m_y, m_Rotation.m_z);

			//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
			XMMATRIX	ScalingMatrix = XMMatrixScaling(m_Scale.m_x, m_Scale.m_y, m_Scale.m_z);

			//ワールド行列の作成（ポリゴンの表示の仕方を指定する最終的な行列
			XMMATRIX	WorldMatrix = ScalingMatrix * RotationMatrix * TranslationMatrix;

			//マテリアル設定
			MATERIAL material{};
			material.Diffuse = { 1.0f , 1.0f , 1.0f , 1.0f };
			material.TextureEnable = false;
			Renderer::SetMaterial(material);



			Renderer::SetWorldMatrix(WorldMatrix);

			m_pModelRenderer->Draw();
		}


		{//輪郭線の描画
			//頂点シェーダーをセット
			Renderer::GetDeviceContext()->VSSetShader(m_VertexShaderEdge, NULL, 0);
			//ピクセルシェーダーをセット
			Renderer::GetDeviceContext()->PSSetShader(m_PixelShaderEdge, NULL, 0);

			Renderer::SetCullMode(D3D11_CULL_FRONT);

			//描画
			m_pModelRenderer->Draw();

			Renderer::SetCullMode(D3D11_CULL_BACK);
		}
	}

	Vector3 GetVelocity() { return m_Velocity; }
	void SetVelocity(Vector3 vel) { m_Velocity = vel;}

	void SetLivingFrames(int frames) { m_LivingFrames = frames; }
};

#endif // !_ATTACKBASE_H_

