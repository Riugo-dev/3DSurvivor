//********************************************************************************
//
// levelfour_shooterenemy.h[ƒŒƒxƒ‹4ŽËŒ‚“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/10/07
//********************************************************************************

#include <random>
#include "hightier_exp_item.h"
#include "midtier_exp_item.h"

#include "levelfour_shooterenemy.h"

LevelFourShooterEnemy::LevelFourShooterEnemy()
{
	m_Scale = { 0.05f , 0.05f , 0.05f };

	m_Shader = SHADER_TOON;

	m_HP = 4 * 60;
	m_Points = 350;
	m_ModelTag = SHOOTER_ENEMY_PURPLE;

	m_ShotCoolDown = 150;
	m_Speed = 0.25f;
}

LevelFourShooterEnemy::~LevelFourShooterEnemy()
{
}

void LevelFourShooterEnemy::EnemyItemDrop()
{
	std::random_device rd;
	int drop = rd() % 100 + 1;

	if (drop <= 20)
	{
		Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition({ m_Position.m_x , 1.0f , m_Position.m_z });
	}
	else
	{
		Manager::GetScene()->AddGameObject<MidTierExpItem>(1)->SetPosition({ m_Position.m_x , 1.0f , m_Position.m_z });
	}
}
