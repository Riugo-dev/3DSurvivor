//********************************************************************************
//
// swarmenemy_manager.h[敵管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/10/09
//********************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "midbossbase.h"
#include "levelone_midboss.h"
#include "gametimer.h"
#include <random>
#include <cmath>
#include <vector>


#include "midboss_manager.h"

//#define ENEMY_DESTORY_LENGTH (50.0f)
#define ENEMY_MAX_NUM (1)

//********************************************************************************
//プライベート関数
//********************************************************************************




void MidBossManager::LevelOneEnemySpawner(int count)
{

}


//********************************************************************************
//関数
//********************************************************************************
MidBossManager::MidBossManager(GameTimer* timer)
{
	m_pGameTimer = timer;
}

MidBossManager::~MidBossManager()
{
}

void MidBossManager::SpawnEnemy()
{

	std::vector<BaseMidBoss*> p_enemys = Manager::GetScene()->GetGameObjects<BaseMidBoss>();
	if (p_enemys.size() > 0) return;

	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);

	int distance = 25;
	float angle = randangle(mt);

	Vector3 spawnpoint;

	spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
	spawnpoint.m_y = 0.0f;
	spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

	Vector3 vel = p_player->GetPosition() - spawnpoint;
	vel = vel.normalized();

	float angle_y = atan2(vel.m_x, vel.m_z);

	LevelOneMidBoss* enemy = Manager::GetScene()->AddGameObject<LevelOneMidBoss>();
	enemy->SetPosition({ spawnpoint.m_x , spawnpoint.m_y , spawnpoint.m_z });

}


