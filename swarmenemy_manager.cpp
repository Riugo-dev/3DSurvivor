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

//void SwarmEnemyManager::WaveOne()
//{
//	std::random_device rd;
//	int enemyspawnedcount = rd() % 5;//スポーンさせる敵の数
//
//	if (enemyspawnedcount == 0) return;
//
//	LevelOneEnemySpawner(enemyspawnedcount);
//}

//void SwarmEnemyManager::WaveTwo()
//{
//	std::random_device rd;
//	int enemyspawnedcount = rd() % 5;//スポーンさせる敵の数
//
//	if (enemyspawnedcount == 0) return;
//
//	int leveltwocount = rd() % 3;//レベル２エネミーのスポーン数
//
//	int levelonecount = enemyspawnedcount - leveltwocount;//レベル1エネミーのスポーン数
//
//	LevelOneEnemySpawner(levelonecount);
//	LevelTwoEnemySpawner(leveltwocount);
//
//}
//
//void SwarmEnemyManager::WaveThree()
//{
//	std::random_device rd;
//	int enemyspawnedcount = rd() % 5 + 5;//スポーンさせる敵の数
//
//	int levelthreecount = rd() % 3;
//
//	int leveltwocount = rd() % 2;//レベル２エネミーのスポーン数
//
//	int levelonecount = enemyspawnedcount - leveltwocount - levelthreecount;//レベル1エネミーのスポーン数
//
//	LevelOneEnemySpawner(levelonecount);
//	LevelTwoEnemySpawner(leveltwocount);
//	LevelThreeEnemySpawner(levelthreecount);
//}
//
//void SwarmEnemyManager::WaveFour()
//{
//	std::random_device rd;
//	int enemyspawnedcount = rd() % 3 + 7;//スポーンさせる敵の数
//
//	int levelfourcount = rd() % 2;
//
//	int levelthreecount = rd() % 2;
//
//	int leveltwocount = 3;//レベル２エネミーのスポーン数
//
//	int levelonecount = enemyspawnedcount - leveltwocount - levelthreecount - levelfourcount;//レベル1エネミーのスポーン数
//
//	LevelOneEnemySpawner(levelonecount);
//	LevelTwoEnemySpawner(leveltwocount);
//	LevelThreeEnemySpawner(levelthreecount);
//	LevelFourEnemySpawner(levelfourcount);
//}
//
//void SwarmEnemyManager::WaveMax()
//{
//	std::random_device rd;
//	int enemyspawnedcount = 10;//スポーンさせる敵の数
//
//	int levelfivecount = rd() % 2 + 1;
//
//	int levelfourcount = rd() % 2 + 2;
//
//	int levelthreecount = 3;
//
//	int leveltwocount = enemyspawnedcount - levelthreecount - levelfourcount;//レベル２エネミーのスポーン数
//
//	LevelTwoEnemySpawner(leveltwocount);
//	LevelThreeEnemySpawner(levelthreecount);
//	LevelFourEnemySpawner(levelfourcount);
//	LevelFiveEnemySpawner(levelfivecount);
//}


void SwarmEnemyManager::LevelOneEnemySpawner(int count)
{
	//Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	//Vector3 to_player = (p_player->GetPosition() - m_Position).normalized();

	//float angle_y, angle_x, angle_z;


	//angle_y = atan2(to_player.m_x, to_player.m_z);
	///*angle_x = atan2(to_player.m_y, to_player.m_z);
	//angle_z = atan2(to_player.m_x, to_player.m_y);*/

	////m_Rotation.m_y = angle_y;
	///*m_Rotation.m_x = angle_x;
	//m_Rotation.m_z = angle_z;*/


	//Vector3 distance = p_player->GetPosition() - m_Position;
	//float length = distance.length();

	//std::random_device rd;

	//for (int i = 0; i < count; i++)
	//{
	//	int leftright = rd() % 2;
	//	int fowardback = rd() % 2;

	//	int x = rd() % 5 + 5;
	//	int z = rd() % 5 + 5;

	//	Vector3 spawnpoint = p_player->GetPosition();

	//	spawnpoint.m_y = 0.0f;


	//	if (leftright == 0)
	//	{
	//		spawnpoint.m_x -= x;
	//	}
	//	else
	//	{
	//		spawnpoint.m_x += x;
	//	}

	//	if (fowardback == 0)
	//	{
	//		spawnpoint.m_z -= z;
	//	}
	//	else
	//	{
	//		spawnpoint.m_z += z;
	//	}

	//	Manager::GetScene()->AddGameObject<LevelOneSwarmEnemy>()->SetPosition(spawnpoint);
	//}
}

//void SwarmEnemyManager::LevelTwoEnemySpawner(int count)
//{
//	Player* p_player = Manager::GetScene()->GetGameObject<Player>();
//
//	std::random_device rd;
//
//	for (int i = 0; i < count; i++)
//	{
//		int leftright = rd() % 2;
//		int fowardback = rd() % 2;
//
//		int x = rd() % 5 + 5;
//		int z = rd() % 5 + 5;
//
//		Vector3 spawnpoint = p_player->GetPosition();
//		spawnpoint.m_y = 0.0f;
//
//
//		if (leftright == 0)
//		{
//			spawnpoint.m_x -= x;
//		}
//		else
//		{
//			spawnpoint.m_x += x;
//		}
//
//		if (fowardback == 0)
//		{
//			spawnpoint.m_z -= z;
//		}
//		else
//		{
//			spawnpoint.m_z += z;
//		}
//
//		Manager::GetScene()->AddGameObject<LevelTwoSwarmEnemy>()->SetPosition(spawnpoint);
//	}
//}
//
//void SwarmEnemyManager::LevelThreeEnemySpawner(int count)
//{
//	Player* p_player = Manager::GetScene()->GetGameObject<Player>();
//
//	std::random_device rd;
//
//	for (int i = 0; i < count; i++)
//	{
//		int leftright = rd() % 2;
//		int fowardback = rd() % 2;
//
//		int x = rd() % 5 + 5;
//		int z = rd() % 5 + 5;
//
//		Vector3 spawnpoint = p_player->GetPosition();
//		spawnpoint.m_y = 0.0f;
//
//		if (leftright == 0)
//		{
//			spawnpoint.m_x -= x;
//		}
//		else
//		{
//			spawnpoint.m_x += x;
//		}
//
//		if (fowardback == 0)
//		{
//			spawnpoint.m_z -= z;
//		}
//		else
//		{
//			spawnpoint.m_z += z;
//		}
//
//		Manager::GetScene()->AddGameObject<LevelThreeSwarmEnemy>()->SetPosition(spawnpoint);
//	}
//}
//
//void SwarmEnemyManager::LevelFourEnemySpawner(int count)
//{
//	Player* p_player = Manager::GetScene()->GetGameObject<Player>();
//
//	std::random_device rd;
//
//	for (int i = 0; i < count; i++)
//	{
//		int leftright = rd() % 2;
//		int fowardback = rd() % 2;
//
//		int x = rd() % 5 + 6;
//		int z = rd() % 5 + 6;
//
//		Vector3 spawnpoint = p_player->GetPosition();
//		spawnpoint.m_y = 0.0f;
//
//		if (leftright == 0)
//		{
//			spawnpoint.m_x -= x;
//		}
//		else
//		{
//			spawnpoint.m_x += x;
//		}
//
//		if (fowardback == 0)
//		{
//			spawnpoint.m_z -= z;
//		}
//		else
//		{
//			spawnpoint.m_z += z;
//		}
//
//		Manager::GetScene()->AddGameObject<LevelFourSwarmEnemy>()->SetPosition(spawnpoint);
//	}
//}
//
//void SwarmEnemyManager::LevelFiveEnemySpawner(int count)
//{
//	Player* p_player = Manager::GetScene()->GetGameObject<Player>();
//
//	std::random_device rd;
//
//	for (int i = 0; i < count; i++)
//	{
//		int leftright = rd() % 2;
//		int fowardback = rd() % 2;
//
//		int x = rd() % 5 + 6;
//		int z = rd() % 5 + 6;
//
//		Vector3 spawnpoint = p_player->GetPosition();
//		spawnpoint.m_y = 0.0f;
//
//		if (leftright == 0)
//		{
//			spawnpoint.m_x -= x;
//		}
//		else
//		{
//			spawnpoint.m_x += x;
//		}
//
//		if (fowardback == 0)
//		{
//			spawnpoint.m_z -= z;
//		}
//		else
//		{
//			spawnpoint.m_z += z;
//		}
//
//		Manager::GetScene()->AddGameObject<LevelFiveSwarmEnemy>()->SetPosition(spawnpoint);
//	}
//}
//
//
//void SwarmEnemyManager::DestroyFarEnemy()
//{
//
//
//	std::vector<SwarmBaseEnemy*> p_enemys = Manager::GetScene()->GetGameObjects<SwarmBaseEnemy>();
//	if (p_enemys.size() < ENEMY_MAX_NUM) return;
//
//	Player* p_player = Manager::GetScene()->GetGameObject<Player>();
//
//	for (auto itr : p_enemys)
//	{
//		Vector3 vector = p_player->GetPosition() - itr->GetPosition();
//
//		float length = vector.length();
//
//		if (length > ENEMY_DESTORY_LENGTH)
//		{
//			itr->SetDestroy(true);
//		}
//	}
//
//
//}

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

	Vector3 spawnpoint;
	
	spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
	spawnpoint.m_y = 0.5f;
	spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

	Vector3 vel = p_player->GetPosition() - spawnpoint;
	vel = vel.normalized();

	float angle_y = atan2(vel.m_x, vel.m_z);

	for(int z = -2 ; z < 3 ; z++)
	{
		for (int x = -2; x < 3; x++)
		{
			
			LevelOneSwarmEnemy* enemy = Manager::GetScene()->AddGameObject<LevelOneSwarmEnemy>();
			enemy->SetPosition({ spawnpoint.m_x + x , spawnpoint.m_y , spawnpoint.m_z + z });
			enemy->SetVelocity(vel);
			enemy->SetSpeed(0.2f);
			enemy->SetRotation({ 0.0f , angle_y , 0.0f });
		}
	}

}


