//********************************************************************************
//
// levelfive_shooterenemy.h[ƒŒƒxƒ‹5ŽËŒ‚“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/10/07
//********************************************************************************
#include "main.h"
#include <random>
#include "hightier_exp_item.h"
#include "midtier_exp_item.h"

#include "levelfive_shooterenemy.h"

LevelFiveShooterEnemy::LevelFiveShooterEnemy()
{
	m_Scale = { 0.05f , 0.05f , 0.05f };

	m_Shader = SHADER_BLINNPHONG;

	m_HP = 5 * 60;
	m_Points = 450;
	m_ModelTag = SHOOTER_ENEMY_SILVER;

	m_ShotCoolDown = 120;
	m_Speed = 0.3f;
}

LevelFiveShooterEnemy::~LevelFiveShooterEnemy()
{
}

void LevelFiveShooterEnemy::EnemyItemDrop()
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
