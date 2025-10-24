//********************************************************************************
//
// levelone_midboss.h[ƒŒƒxƒ‹‚P“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************
#include <random>
#include "hightier_exp_item.h"

#include "levelone_midboss.h"

LevelOneMidBoss::LevelOneMidBoss()
{
	m_Scale = { 0.05f , 0.05f , 0.05f };

	m_Shader = SHADER_TOON;

	m_HP = 150 * 60;
	m_EnemySpeed = 0.5f;
	m_Points = 5000;
	m_ModelTag = MIDBOSS_RED;
	m_ChargeTime = 60 * 6;
	m_RotationSpeed = 0.0f;
}

LevelOneMidBoss::~LevelOneMidBoss()
{
}

void LevelOneMidBoss::MidBossItemDrop()
{
	std::random_device rd;
	int drop = rd() % 100 + 1;

	if (drop <= 20)
	{
		Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition({ m_Position.m_x + 0.25f , 1.0f , m_Position.m_z});
		Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition({ m_Position.m_x - 0.25f , 1.0f , m_Position.m_z});
	}
	else
	{
		Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition({ m_Position.m_x , 1.0f , m_Position.m_z });
	}
}
