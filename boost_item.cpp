//********************************************************************************
//
// boost_item.cpp[ダッシュアイテム]
//
//															Author :Riugo Honda
//															Date   :2025/10/29
//********************************************************************************
#include "hp_ui.h"
#include"manager_soundeffect.h"

#include "boost_item.h"

BoostItem::BoostItem()
{
	m_Scale = { 0.25f , 0.25f , 0.25f };

	m_Shader = SHADER_TOON;

	m_ModelTag = ITEM_BOOST;

	m_Radius = 0.75f;
}

BoostItem::~BoostItem()
{
}




void BoostItem::Update()
{
	m_Rotation.m_y += 0.1f;

	Player* player = Manager::GetScene()->GetGameObject<Player>();


	if (CircleCollider(player->GetPosition(), player->GetRadius()))
	{
		//SoundEffectManager::PlaySE(SE_HEAL);

		player->SetBoost();

		m_IsDestroy = true;
	}

	if (m_FrameCount > 3000)
	{
		m_IsDestroy = true;
	}
	m_FrameCount++;
}