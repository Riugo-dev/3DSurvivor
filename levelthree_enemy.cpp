//********************************************************************************
//
// levelthree_enemy.cpp[ƒŒƒxƒ‹3“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************
#include <random>
#include "lowtier_exp_item.h"
#include "midtier_exp_item.h"

#include "levelthree_enemy.h"

LevelThreeEnemy::LevelThreeEnemy()
{
	

	m_Scale = { 0.05f , 0.05f , 0.05f };

	m_Shader = SHADER_TOON;

	m_HP = 6 * 60;
	m_EnemySpeed = 0.03f;
	m_Points = 300;
	m_ModelTag = ENEMY_GREEN;
}

LevelThreeEnemy::~LevelThreeEnemy()
{
	
}

void LevelThreeEnemy::EnemyItemDrop()
{
	std::random_device rd;
	int drop = rd() % 100 + 1;

	if (drop <= 20)
	{
		Manager::GetScene()->AddGameObject<LowTierExpItem>(1)->SetPosition({ m_Position.m_x , 1.0f , m_Position.m_z });
	}
	else
	{
		Manager::GetScene()->AddGameObject<MidTierExpItem>(1)->SetPosition({ m_Position.m_x , 1.0f , m_Position.m_z });
	}
}
