//********************************************************************************
//
// heal_item.h[回復アイテム]
//
//															Author :Riugo Honda
//															Date   :2025/10/24
//********************************************************************************
#include "main.h"
#include "hp_ui.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "manager_soundeffect.h"
#include <vector>

#include "heal_item.h"



HealItem::~HealItem()
{
}

void HealItem::Init()
{
	m_Scale = { 0.5f , 0.5f , 0.5f };

	m_Shader = SHADER_TOON;

	m_ModelTag = ITEM_HEAL;

	m_Radius = 0.625f;
}

void HealItem::Uninit()
{
}




void HealItem::Update()
{
	m_Rotation.y += 0.1f;

	Player* player = Manager::GetScene()->GetGameObject<Player>();
	

	if (CircleCollider(player->GetPosition(), player->GetRadius()))
	{
		SoundEffectManager::PlaySE(SE_HEAL);

		Manager::GetScene()->GetGameObject<HPUI>()->AddHP();

		m_IsDestroy = true;
	}

	if (m_FrameCount > 3000)
	{
		m_IsDestroy = true;
	}
	m_FrameCount++;
}

void HealItem::Draw()
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	Vector3 vector = p_player->GetPosition() - m_Position;
	float length = vector.length();

	if (length > 30) return;

	{//通常の描画
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
		ModelManager::SetShaders(m_ModelTag, SHADER_TOONEDGE);


		Renderer::SetCullMode(D3D11_CULL_FRONT);

		//描画
		//m_pModelRenderer->Draw();
		ModelManager::ModelDraw(m_ModelTag);

		Renderer::SetCullMode(D3D11_CULL_BACK);
	}
}
