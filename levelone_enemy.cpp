//********************************************************************************
//
// levelone_enemy.h[ƒŒƒxƒ‹‚P“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************
#include "main.h"
#include <random>
#include "lowtier_exp_item.h"



#include "levelone_enemy.h"

LevelOneEnemy::LevelOneEnemy()
{

	m_Scale = { 0.05f , 0.05f , 0.05f };

	m_Shader = SHADER_TOON;

	m_HP = 1 * 60;
	m_EnemySpeed = 0.01f;
	m_Points = 100;
	m_ModelTag = ENEMY_RED;
}

LevelOneEnemy::~LevelOneEnemy()
{
	
}

void LevelOneEnemy::EnemyItemDrop()
{
	std::random_device rd;
	int drop = rd() % 100 + 1;

	if (drop <= 80)
	{
		Manager::GetScene()->AddGameObject<LowTierExpItem>(1)->SetPosition({ m_Position.m_x , 1.0f , m_Position.m_z});
	}
}
