//********************************************************************************
//
// levelthree_shooterenemy.cpp[ƒŒƒxƒ‹3ŽËŒ‚“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/10/07
//********************************************************************************

#include <random>
#include "lowtier_exp_item.h"
#include "midtier_exp_item.h"

#include "levelthree_shooterenemy.h"

LevelThreeShooterEnemy::LevelThreeShooterEnemy()
{
	m_Scale = { 0.05f , 0.05f , 0.05f };

	m_Shader = SHADER_TOON;

	m_HP = 3;
	m_Points = 30;
	m_ModelTag = SHOOTER_ENEMY_GREEN;

	m_ShotCoolDown = 150;
	m_Speed = 0.2f;
}

LevelThreeShooterEnemy::~LevelThreeShooterEnemy()
{
}

void LevelThreeShooterEnemy::EnemyItemDrop()
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
