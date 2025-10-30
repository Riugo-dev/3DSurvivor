//********************************************************************************
//
// itemdrop_swarmenemy.cpp[アイテムドロップダッシュ敵クラス]
//
//															Author :Riugo Honda
//															Date   :2025/10/30
//********************************************************************************
#include <random>
#include "heal_item.h"
#include "vacuum_item.h"
#include "boost_item.h"

#include "itemdrop_swarmenemy.h"

ItemDropSwarmEnemy::ItemDropSwarmEnemy()
{

	m_Scale = { 0.05f , 0.05f , 0.05f };

	m_Shader = SHADER_BLINNPHONG;

	m_HP = 1 * 60;
	m_EnemySpeed = 0.01f;
	m_Points = 50;
	m_ModelTag = SWARM_ENEMY_SILVER;
}

ItemDropSwarmEnemy::~ItemDropSwarmEnemy()
{

}

void ItemDropSwarmEnemy::EnemyItemDrop()
{
	std::random_device rd;
	int drop = rd() % 90 + 1;

	if (drop >= 1 && drop < 31)
	{
		Manager::GetScene()->AddGameObject<HealItem>()->SetPosition({ m_Position.m_x , 1.0f , m_Position.m_z });
	}
	else if (drop >= 31 && drop < 71)
	{
		Manager::GetScene()->AddGameObject<VacuumItem>()->SetPosition({ m_Position.m_x , 1.0f , m_Position.m_z });
	}
	else
	{
		Manager::GetScene()->AddGameObject<BoostItem>()->SetPosition({ m_Position.m_x , 1.0f , m_Position.m_z });
	}
	
}
