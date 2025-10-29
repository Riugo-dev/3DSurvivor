//********************************************************************************
//
// heal_item.h[‰ñ•œƒAƒCƒeƒ€]
//
//															Author :Riugo Honda
//															Date   :2025/10/24
//********************************************************************************
#include "hp_ui.h"

#include "heal_item.h"
#include"manager_soundeffect.h"

HealItem::HealItem()
{
	m_Scale = { 1.25f , 1.25f , 1.25f };

	m_Shader = SHADER_BLINNPHONG;

	m_ModelTag = HEAL_ITEM;

	m_Radius = 0.625f;
}

HealItem::~HealItem()
{
}




void HealItem::Update()
{
	m_Rotation.m_y += 0.1f;

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