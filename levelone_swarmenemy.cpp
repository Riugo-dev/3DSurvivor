//********************************************************************************
//
// levelone_swarmenemy.h[レベル１ダッシュ敵クラス]
//
//															Author :Riugo Honda
//															Date   :2025/10/09
//********************************************************************************
#include "main.h"
#include <random>
#include "lowtier_exp_item.h"

#include "levelone_swarmenemy.h"

LevelOneSwarmEnemy::LevelOneSwarmEnemy()
{

	m_Scale = { 0.05f , 0.05f , 0.05f };

	m_Shader = SHADER_TOON;

	m_HP = 1 * 60;
	m_EnemySpeed = 0.01f;
	m_Points = 50;
	m_ModelTag = SWARM_ENEMY_RED;
}

LevelOneSwarmEnemy::~LevelOneSwarmEnemy()
{

}

void LevelOneSwarmEnemy::EnemyItemDrop()
{
	std::random_device rd;
	int drop = rd() % 100 + 1;

	if (drop <= 80)
	{
		Manager::GetScene()->AddGameObject<LowTierExpItem>(1)->SetPosition({ m_Position.x , 1.0f , m_Position.z });
	}
}
