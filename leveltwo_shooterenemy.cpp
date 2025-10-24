//********************************************************************************
//
// leveltwo_shooterenemy.cpp[ƒŒƒxƒ‹2ŽËŒ‚“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/10/07
//********************************************************************************
#include <random>
#include "lowtier_exp_item.h"
#include "midtier_exp_item.h"

#include "leveltwo_shooterenemy.h"

LevelTwoShooterEnemy::LevelTwoShooterEnemy()
{
	m_Scale = { 0.05f , 0.05f , 0.05f };

	m_Shader = SHADER_TOON;

	m_HP = 2 * 60;
	m_Points = 150;
	m_ModelTag = SHOOTER_ENEMY_BLUE;

	m_ShotCoolDown = 180;
	m_Speed = 0.15f;
}

LevelTwoShooterEnemy::~LevelTwoShooterEnemy()
{
}

void LevelTwoShooterEnemy::EnemyItemDrop()
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
