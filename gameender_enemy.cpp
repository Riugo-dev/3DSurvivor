//********************************************************************************
//
// gameender_enemy.h[Ž€_“GƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************
#include "main.h"
#include "hightier_exp_item.h"

#include "gameender_enemy.h"

GameEnderEnemy::GameEnderEnemy()
{

	m_Scale = { 0.5f , 0.5f , 0.5f };

	m_Shader = SHADER_BLINNPHONG;

	m_HP = 100 * 60;
	m_EnemySpeed = 0.4f;
	m_Points = 10000 ;
	m_ModelTag = ENEMY_BLACK;
}

GameEnderEnemy::~GameEnderEnemy()
{
	
}

void GameEnderEnemy::EnemyItemDrop()
{
	Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(0.25f, 0.5f, 0.25f));
	Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(-0.25f, 0.5f, -0.25f));
	Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(0.25f, 0.5f, -0.25f));
	Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(-0.25f, 0.5f, 0.25f));
	Manager::GetScene()->AddGameObject<HighTierExpItem>(1)->SetPosition(m_Position + Vector3(-0.0f, 0.5f, 0.0f));

}

