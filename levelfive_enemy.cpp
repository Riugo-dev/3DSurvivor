//********************************************************************************
//
// levelfive_enemy.h[ƒŒƒxƒ‹5“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************
#include "main.h"
#include <random>
#include "hightier_exp_item.h"

#include "levelfive_enemy.h"

LevelFiveEnemy::LevelFiveEnemy()
{
	
	m_Scale = { 0.05f , 0.05f , 0.05f };

	m_Shader = SHADER_BLINNPHONG;

	m_HP = 1 * 600;
	m_EnemySpeed = 0.05f;
	m_Points = 1000;
	m_ModelTag = ENEMY_SILVER;
}

LevelFiveEnemy::~LevelFiveEnemy()
{
	
}

void LevelFiveEnemy::EnemyItemDrop()
{
	std::random_device rd;
	int drop = rd() % 100 + 1;

	if (drop <= 20)
	{
		Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(0.25f, 0.5f, 0.0f));
		Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(-0.25f, 0.5f, 0.0f));
	}
	else
	{
		Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition({ m_Position.m_x , 1.0f , m_Position.m_z });
	}
}

