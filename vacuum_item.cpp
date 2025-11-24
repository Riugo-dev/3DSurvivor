//********************************************************************************
//
// vacuum_item.h[‰ñ•œƒAƒCƒeƒ€]
//
//															Author :Riugo Honda
//															Date   :2025/10/24
//********************************************************************************

#include "hp_ui.h"
#include <vector>
#include "exp_item.h"

#include "vacuum_item.h"
#include"manager_soundeffect.h"

VacuumItem::VacuumItem()
{
	m_Scale = { 0.45f , 0.45f , 0.45f };

	m_Shader = SHADER_BLINNPHONG;

	m_ModelTag = ITEM_VACUUM;

	m_Radius = 0.625f;
}

VacuumItem::~VacuumItem()
{
}




void VacuumItem::Update()
{
	m_Rotation.m_y += 0.1f;

	Player* player = Manager::GetScene()->GetGameObject<Player>();

	if (CircleCollider(player->GetPosition(), player->GetRadius()))
	{
		SoundEffectManager::PlaySE(SE_GATHER);

		std::vector<ExpItem*> items = Manager::GetScene()->GetGameObjects<ExpItem>();

		for (auto itr : items)
		{
			itr->SetGather();
		}

		m_IsDestroy = true;
	}

	if (m_FrameCount > 3000)
	{
		m_IsDestroy = true;
	}
	m_FrameCount++;
}