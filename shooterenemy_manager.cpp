//********************************************************************************
//
// shooterenemy_manager.h[敵管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/10/07
//********************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "shooterenemybase.h"
#include "levelone_shooterenemy.h"
#include "leveltwo_shooterenemy.h"
#include "levelthree_shooterenemy.h"
#include "levelfour_shooterenemy.h"
#include "levelfive_shooterenemy.h"
#include "gametimer.h"
#include <random>
#include <cmath>
#include <vector>


#include "shooterenemy_manager.h"

#define ENEMY_DESTORY_LENGTH (50.0f)
#define ENEMY_MAX_NUM (10)

//********************************************************************************
//プライベート関数
//********************************************************************************

void ShooterEnemyManager::WaveOne()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 5;//スポーンさせる敵の数
	
	if (enemyspawnedcount == 0) return;

	LevelOneEnemySpawner(enemyspawnedcount);
}

void ShooterEnemyManager::WaveTwo()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 5;//スポーンさせる敵の数

	if (enemyspawnedcount == 0) return;

	int leveltwocount = rd() % 3;//レベル２エネミーのスポーン数

	int levelonecount = enemyspawnedcount - leveltwocount;//レベル1エネミーのスポーン数

	LevelOneEnemySpawner(levelonecount);
	LevelTwoEnemySpawner(leveltwocount);

}

void ShooterEnemyManager::WaveThree()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 5 + 5;//スポーンさせる敵の数

	int levelthreecount = rd() % 3;

	int leveltwocount = rd() % 2;//レベル２エネミーのスポーン数

	int levelonecount = enemyspawnedcount - leveltwocount - levelthreecount;//レベル1エネミーのスポーン数

	LevelOneEnemySpawner(levelonecount);
	LevelTwoEnemySpawner(leveltwocount);
	LevelThreeEnemySpawner(levelthreecount);
}

void ShooterEnemyManager::WaveFour()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 3 + 7;//スポーンさせる敵の数

	int levelfourcount = rd() % 2;

	int levelthreecount = rd() % 2;

	int leveltwocount =  3;//レベル２エネミーのスポーン数

	int levelonecount = enemyspawnedcount - leveltwocount - levelthreecount - levelfourcount;//レベル1エネミーのスポーン数

	LevelOneEnemySpawner(levelonecount);
	LevelTwoEnemySpawner(leveltwocount);
	LevelThreeEnemySpawner(levelthreecount);
	LevelFourEnemySpawner(levelfourcount);
}

void ShooterEnemyManager::WaveMax()
{
	std::random_device rd;
	int enemyspawnedcount = 10;//スポーンさせる敵の数

	int levelfivecount = rd() % 2 + 1;

	int levelfourcount = rd() % 2 + 2;

	int levelthreecount =  3;

	int leveltwocount = enemyspawnedcount - levelthreecount - levelfourcount;//レベル２エネミーのスポーン数

	LevelTwoEnemySpawner(leveltwocount);
	LevelThreeEnemySpawner(levelthreecount);
	LevelFourEnemySpawner(levelfourcount);
	LevelFiveEnemySpawner(levelfivecount);
}


void ShooterEnemyManager::LevelOneEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);

	for (int i = 0; i < count; i++)
	{
		int distance = rd() % 4 + 8;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.1f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<LevelOneShooterEnemy>()->SetPosition(spawnpoint);
	}
}

void ShooterEnemyManager::LevelTwoEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);

	for (int i = 0; i < count; i++)
	{
		int distance = rd() % 4 + 8;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.1f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<LevelTwoShooterEnemy>()->SetPosition(spawnpoint);
	}
}

void ShooterEnemyManager::LevelThreeEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);

	for (int i = 0; i < count; i++)
	{
		int distance = rd() % 4 + 8;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.1f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<LevelThreeShooterEnemy>()->SetPosition(spawnpoint);
	}
}

void ShooterEnemyManager::LevelFourEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);

	for (int i = 0; i < count; i++)
	{
		int distance = rd() % 4 + 8;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.1f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<LevelFourShooterEnemy>()->SetPosition(spawnpoint);
	}
}

void ShooterEnemyManager::LevelFiveEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);

	for (int i = 0; i < count; i++)
	{
		int distance = rd() % 4 + 8;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.1f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<LevelFiveShooterEnemy>()->SetPosition(spawnpoint);
	}
}


void ShooterEnemyManager::DestroyFarEnemy()
{


	std::vector<ShooterBaseEnemy*> p_enemys = Manager::GetScene()->GetGameObjects<ShooterBaseEnemy>();
	if (p_enemys.size() < ENEMY_MAX_NUM) return;

	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	for (auto itr : p_enemys)
	{
		Vector3 vector = p_player->GetPosition() - itr->GetPosition();

		float length = vector.length();

		if (length > ENEMY_DESTORY_LENGTH)
		{
			itr->SetDestroy(true);
		}
	}


}

//********************************************************************************
//関数
//********************************************************************************
ShooterEnemyManager::ShooterEnemyManager(GameTimer* timer)
{
	m_pGameTimer = timer;
}

ShooterEnemyManager::~ShooterEnemyManager()
{
}

void ShooterEnemyManager::SpawnEnemy()
{

	std::vector<ShooterBaseEnemy*> p_enemys = Manager::GetScene()->GetGameObjects<ShooterBaseEnemy>();
	if (p_enemys.size() > ENEMY_MAX_NUM) return;

	switch (m_pGameTimer->GetCurrentWave())
	{
	case WAVE_ONE:
		WaveOne();
		break;
	case WAVE_TWO:
		WaveTwo();
		break;
	case WAVE_THREE:
		WaveThree();
		break;
	case WAVE_FOUR:
		WaveFour();
		break;
	case WAVE_MAX:
		WaveMax();
		break;
	}
}


