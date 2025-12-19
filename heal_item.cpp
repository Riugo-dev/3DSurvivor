//********************************************************************************
//
// heal_item.h[‰ñ•œƒAƒCƒeƒ€]
//
//															Author :Riugo Honda
//															Date   :2025/10/24
//********************************************************************************
#include "main.h"
#include "hp_ui.h"
#include"manager_soundeffect.h"

#include "heal_item.h"


HealItem::HealItem()
{
	m_Scale = { 0.5f , 0.5f , 0.5f };

	m_Shader = SHADER_TOON;

	m_ModelTag = ITEM_HEAL;

	m_Radius = 0.625f;
}

HealItem::~HealItem()
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