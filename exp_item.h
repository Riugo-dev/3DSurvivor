//********************************************************************************
//
// exp_item.h[弾]
//
//															Author :Riugo Honda
//															Date   :2025/09/01
//********************************************************************************

#ifndef _EXP_ITEM_H_
#define _EXP_ITEM_H_

#include "main.h"
#include "gameobject.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "model_manager.h"
#include "shader_manager.h"
#include "manager_soundeffect.h"

class ExpItem:public GameObject
{
protected:
	Shader m_Shader;

	//ModelRenderer* m_pModelRenderer = nullptr;

	int m_Exp = 0;

	int m_FrameCount = 0;
	
	ModelTags m_ModelTag;

	float m_GatherSpeed;

	bool m_IsGathering = false;

	/*Vector3 m_Position = { 0.0f , 0.0f , 0.0f };
	Vector3 m_Size = {1.0f , 1.0f ,1.0f};*/

public:
	//ExpItem();
	~ExpItem() = default;

	int GetExp() { return m_Exp; }

	void Init(Input*) override {}

	void Uninit() override{};

	void Update() override
	{
		m_Rotation.y += 0.1f;

		Player* player = Manager::GetScene()->GetGameObject<Player>();

		if (m_IsGathering)
		{
			Vector3 to_player = player->GetPosition() - m_Position;

			to_player = to_player.normalized();

			m_Position += to_player * m_GatherSpeed;
		}

		if(CircleCollider(player->GetPosition(), player->GetRadius()))
		{
			//SoundEffectManager::PlaySE(SE_EXP);

			player->GivePlayerExp(m_Exp);
			Manager::GetSoundEffect()->PlaySE(SE_EXPGET);
			m_IsDestroy = true;
		}

		if (m_FrameCount > 3000 && !m_IsGathering)
		{
			m_IsDestroy = true;
		}
		m_FrameCount++;

	}

	//全て同じ処理でドローするのでここで一括で書く
	void Draw() override
	{

		{//通常の描画
			//入力レイアウト設定
			//Renderer::GetDeviceContext()->IASetInputLayout(Manager::GetShaders()->GetShaderPointers(m_Shader)->GetVertexLayout());

			////シェーダ設定
			//Renderer::GetDeviceContext()->VSSetShader(Manager::GetShaders()->GetShaderPointers(m_Shader)->GetVertexShader(), NULL, 0);
			//Renderer::GetDeviceContext()->PSSetShader(Manager::GetShaders()->GetShaderPointers(m_Shader)->GetPixelShader(), NULL, 0);

			ModelManager::SetShaders(m_ModelTag, m_Shader);

			//平行移動行列の作成（表示座標を決める）
			XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

			//回転行列（Z回転）行列の作成
			XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

			//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
			XMMATRIX	ScalingMatrix = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);

			//ワールド行列の作成（ポリゴンの表示の仕方を指定する最終的な行列
			XMMATRIX	WorldMatrix = ScalingMatrix * RotationMatrix * TranslationMatrix;

			//マテリアル設定
			MATERIAL material{};
			material.Diffuse = { 1.0f , 1.0f , 1.0f , 1.0f };
			material.TextureEnable = false;
			Renderer::SetMaterial(material);



			Renderer::SetWorldMatrix(WorldMatrix);

			//m_pModelRenderer->Draw();

			ModelManager::ModelDraw(m_ModelTag);
		}


		{//輪郭線の描画
			//Renderer::GetDeviceContext()->IASetInputLayout(Manager::GetShaders()->GetShaderPointers(SHADER_TOONEDGE)->GetVertexLayout());

			////シェーダ設定
			//Renderer::GetDeviceContext()->VSSetShader(Manager::GetShaders()->GetShaderPointers(SHADER_TOONEDGE)->GetVertexShader(), NULL, 0);
			//Renderer::GetDeviceContext()->PSSetShader(Manager::GetShaders()->GetShaderPointers(SHADER_TOONEDGE)->GetPixelShader(), NULL, 0);

			ModelManager::SetShaders(m_ModelTag, SHADER_TOONEDGE);

			Renderer::SetCullMode(D3D11_CULL_FRONT);

			//描画
			//m_pModelRenderer->Draw();
			ModelManager::ModelDraw(m_ModelTag);

			Renderer::SetCullMode(D3D11_CULL_BACK);
		}
	}

	void SetGather(bool flag = true, float gatherspeed = 0.3f)
	{
		m_IsGathering = flag;
		m_GatherSpeed = gatherspeed;
	}
};

//経験値の幅の考え
//LowTier　５　～　２０　EXP
//MidTier　２１ ～　５０　EXP
//HighTier  ５１　～　１００　EXP
//経験値の幅は価値の高いものほど大きい
//また経験値アイテムは敵の強さによって使うスポナーを変えるべきかな
//例えば、強い適ほど高い確率でHighTierの経験値アイテムを落とす
#endif // !_EXP_ITEM_H
