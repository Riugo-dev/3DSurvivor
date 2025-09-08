//********************************************************************************
//
// enemybase.h[敵の基底クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/08
//********************************************************************************
#ifndef _ENEMYBASE_H_
#define _ENEMYBASE_H_

#include "main.h"
#include "gameobject.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "modelRenderer.h"
#include "player.h"

class BaseEnemy : public GameObject
{
protected:
	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ModelRenderer* m_pModelRenderer = nullptr;

public:
	virtual ~BaseEnemy() = default;

	void Init(Input*) override {};
	void Uninit() override {};

	//アップデートも基本プレイヤーを追いかけるだけなので基本的にここで一括でいい
	void Update() override 
	{
		Player* player = Manager::GetScene()->GetGameObject<Player>();




		Vector3 distance = player->GetPosition() - m_Position;
		float length = distance.length();

		if (length < m_Scale.m_y * 1.5f)
		{
			if(!player->GetIsInvincible())
			{
				player->DamagePlayer();
			}
		}
	}


	//全て同じ処理でドローするのでここで一括で書く
	void Draw()	override
	{
		//入力レイアウト設定
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		//シェーダ設定
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


		//平行移動行列の作成（表示座標を決める）
		XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.m_x, m_Position.m_y, m_Position.m_z);

		//回転行列（Z回転）行列の作成
		XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.m_x, m_Rotation.m_y + XM_PI, m_Rotation.m_z);

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
};

#endif // !_ENEMYBASE_H_

