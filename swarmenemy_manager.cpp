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
#include "swarmenemybase.h"
#include "levelone_swarmenemy.h"
#include "itemdrop_swarmenemy.h"
#include "gametimer.h"
#include <random>
#include <cmath>
#include <vector>


#include "swarmenemy_manager.h"

#define ENEMY_DESTORY_LENGTH (50.0f)
#define ENEMY_MAX_NUM (10)

//********************************************************************************
//プライベート関数
//********************************************************************************



//********************************************************************************
//関数
//********************************************************************************
SwarmEnemyManager::SwarmEnemyManager(GameTimer* timer)
{
	m_pGameTimer = timer;
}

SwarmEnemyManager::~SwarmEnemyManager()
{
}

void SwarmEnemyManager::SpawnEnemy()
{

	std::vector<SwarmBaseEnemy*> p_enemys = Manager::GetScene()->GetGameObjects<SwarmBaseEnemy>();
	if (p_enemys.size() > 0) return;

	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);

	int distance = 25;
	float angle = randangle(mt);
	int itemenemy = rd() % 25;
	int count = 0;

	Vector3 spawnpoint;
	
	spawnpoint.x = p_player->GetPosition().x + cosf(angle) * distance;
	spawnpoint.y = 0.5f;
	spawnpoint.z = p_player->GetPosition().z + sinf(angle) * distance;

	Vector3 vel = p_player->GetPosition() - spawnpoint;
	vel = vel.normalized();

	float angle_y = atan2(vel.x, vel.z);

	for(int z = -2 ; z < 3 ; z++)
	{
		for (int x = -2; x < 3; x++)
		{
			if (count == itemenemy)
			{
				ItemDropSwarmEnemy* enemy = Manager::GetScene()->AddGameObject<ItemDropSwarmEnemy>();
				enemy->Init();
				enemy->SetPosition({ spawnpoint.x + x , spawnpoint.y , spawnpoint.z + z });
				enemy->SetVelocity(vel);
				enemy->SetSpeed(0.2f);
				enemy->SetRotation({ 0.0f , angle_y , 0.0f });
			}
			else
			{
				LevelOneSwarmEnemy* enemy = Manager::GetScene()->AddGameObject<LevelOneSwarmEnemy>();
				enemy->Init();
				enemy->SetPosition({ spawnpoint.x + x , spawnpoint.y , spawnpoint.z + z });
				enemy->SetVelocity(vel);
				enemy->SetSpeed(0.2f);
				enemy->SetRotation({ 0.0f , angle_y , 0.0f });
			}

			count++;
		}
	}

}


