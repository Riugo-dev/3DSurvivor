//********************************************************************************
//
// levelone_enemy.cpp[ƒŒƒxƒ‹2“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************
#include <random>
#include "lowtier_exp_item.h"
#include "midtier_exp_item.h"

#include "leveltwo_enemy.h"

LevelTwoEnemy::LevelTwoEnemy()
{

	m_Scale = { 0.05f , 0.05f , 0.05f };

	m_Shader = SHADER_TOON;

	m_HP = 3;
	m_EnemySpeed = 0.02f;
	m_Points = 200;
	m_ModelTag = ENEMY_BLUE;
}

LevelTwoEnemy::~LevelTwoEnemy()
{
	
}

void LevelTwoEnemy::EnemyItemDrop()
{
	std::random_device rd;
	int drop = rd() % 100 + 1;

	if (drop <= 80)
	{
		Manager::GetScene()->AddGameObject<LowTierExpItem>(1)->SetPosition({ m_Position.m_x , 1.0f , m_Position.m_z });
	}
	else
	{
		Manager::GetScene()->AddGameObject<MidTierExpItem>(1)->SetPosition({ m_Position.m_x , 1.0f , m_Position.m_z });
	}
}
