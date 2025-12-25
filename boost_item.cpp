//********************************************************************************
//
// boost_item.cpp[ダッシュアイテム]
//
//															Author :Riugo Honda
//															Date   :2025/10/29
//********************************************************************************
#include "main.h"
#include "hp_ui.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "manager_soundeffect.h"
#include <vector>

#include "boost_item.h"

BoostItem::~BoostItem()
{
}

void BoostItem::Init()
{
	m_Scale = { 0.25f , 0.25f , 0.25f };

	m_Shader = SHADER_TOON;

	m_ModelTag = ITEM_BOOST;

	m_Radius = 0.75f;
}

void BoostItem::Uninit()
{
}




void BoostItem::Update()
{
	m_Rotation.m_y += 0.1f;

	Player* player = Manager::GetScene()->GetGameObject<Player>();


	if (CircleCollider(player->GetPosition(), player->GetRadius()))
	{
		SoundEffectManager::PlaySE(SE_BOOST);

		player->SetBoost();

		m_IsDestroy = true;
	}

	if (m_FrameCount > 3000)
	{
		m_IsDestroy = true;
	}
	m_FrameCount++;
}

void BoostItem::Draw()
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	Vector3 vector = p_player->GetPosition() - m_Position;
	float length = vector.length();

	if (length > 30) return;

	{//通常の描画
		ModelManager::SetShaders(m_ModelTag, m_Shader);

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
