//********************************************************************************
//
// levelone_shooterenemy.cpp[ƒŒƒxƒ‹‚PŽËŒ‚“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/10/06
//********************************************************************************
#include <random>
#include "lowtier_exp_item.h"

#include "levelone_shooterenemy.h"

LevelOneShooterEnemy::LevelOneShooterEnemy()
{
	m_Scale = { 0.05f , 0.05f , 0.05f };

	m_Shader = SHADER_TOON;

	m_HP = 1;
	m_Points = 50;
	m_ModelTag = SHOOTER_ENEMY_RED;

	m_ShotCoolDown = 180;
	m_Speed = 0.1f;
}

LevelOneShooterEnemy::~LevelOneShooterEnemy()
{
}

void LevelOneShooterEnemy::EnemyItemDrop()
{
	std::random_device rd;
	int drop = rd() % 100 + 1;

	if (drop <= 80)
	{
		Manager::GetScene()->AddGameObject<LowTierExpItem>(1)->SetPosition({ m_Position.m_x , 1.0f , m_Position.m_z });
	}
}
