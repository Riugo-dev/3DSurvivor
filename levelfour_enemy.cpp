//********************************************************************************
//
// levelfour_enemy.cpp[ƒŒƒxƒ‹4“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************
#include <random>
#include "midtier_exp_item.h"
#include "hightier_exp_item.h"

#include "levelfour_enemy.h"

LevelFourEnemy::LevelFourEnemy()
{

	m_Scale = { 0.5f , 0.5f , 0.5f };

	m_Shader = SHADER_TOON;

	m_HP = 8;
	m_EnemySpeed = 0.04f;
	m_Points = 40;
	m_ModelTag = ENEMY_PURPLE;
}

LevelFourEnemy::~LevelFourEnemy()
{
	
}

void LevelFourEnemy::EnemyItemDrop()
{
	std::random_device rd;
	int drop = rd() % 100 + 1;

	if (drop <= 20)
	{
		Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(0.0f, 0.5f, 0.0f));
	}
	else
	{
		Manager::GetScene()->AddGameObject<MidTierExpItem>(1)->SetPosition(m_Position + Vector3(0.0f, 0.5f, 0.0f));
	}
}

