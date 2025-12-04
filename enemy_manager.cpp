//********************************************************************************
//
// enemy_manager.h[敵管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "enemybase.h"
#include "levelone_enemy.h"
#include "leveltwo_enemy.h"
#include "levelthree_enemy.h"
#include "levelfour_enemy.h"
#include "levelfive_enemy.h"
#include "gameender_enemy.h"
#include "bullet.h"
#include "gametimer.h"
#include <random>
#include <cmath>
#include <vector>
#include <map>


#include "enemy_manager.h"

#define ENEMY_DESTORY_LENGTH (50.0f)
#define ENEMY_MAX_NUM (350)

//********************************************************************************
//プライベート関数
//********************************************************************************

void EnemyManager::WaveOne()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 5 + 50;//スポーンさせる敵の数

	LevelOneEnemySpawner(enemyspawnedcount);
}

void EnemyManager::WaveTwo()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 10 + 50;//スポーンさせる敵の数

	int leveltwocount = rd() % 3 + 15;//レベル２エネミーのスポーン数

	int levelonecount = enemyspawnedcount - leveltwocount;//レベル1エネミーのスポーン数

	LevelOneEnemySpawner(levelonecount);
	LevelTwoEnemySpawner(leveltwocount);

}

void EnemyManager::WaveThree()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 5 + 75;//スポーンさせる敵の数

	int levelthreecount = rd() % 3 + 15;

	int leveltwocount = rd() % 7 + 17;//レベル２エネミーのスポーン数

	int levelonecount = enemyspawnedcount - leveltwocount - levelthreecount;//レベル1エネミーのスポーン数

	LevelOneEnemySpawner(levelonecount);
	LevelTwoEnemySpawner(leveltwocount);
	LevelThreeEnemySpawner(levelthreecount);
}

void EnemyManager::WaveFour()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 10 + 75;//スポーンさせる敵の数

	int levelfourcount = rd() % 3 + 15;

	int levelthreecount = rd() % 7 + 13;

	int leveltwocount = rd() % 2 + 15;//レベル２エネミーのスポーン数

	int levelonecount = enemyspawnedcount - leveltwocount - levelthreecount - levelfourcount;//レベル1エネミーのスポーン数

	LevelOneEnemySpawner(levelonecount);
	LevelTwoEnemySpawner(leveltwocount);
	LevelThreeEnemySpawner(levelthreecount);
	LevelFourEnemySpawner(levelfourcount);
}

void EnemyManager::WaveMax()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 5 + 80;//スポーンさせる敵の数

	int levelfivecount = rd() % 3 + 13;

	int levelfourcount = rd() % 7 + 15;

	int levelthreecount = rd() % 2 + 17;

	int leveltwocount = enemyspawnedcount - levelthreecount - levelfourcount;//レベル２エネミーのスポーン数

	LevelTwoEnemySpawner(leveltwocount);
	LevelThreeEnemySpawner(levelthreecount);
	LevelFourEnemySpawner(levelfourcount);
	LevelFiveEnemySpawner(levelfivecount);
}

void EnemyManager::WaveEnd()
{
	GameEnderEnemySpawner(1);
}

void EnemyManager::LevelOneEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);//実数の一様分布、指定した範囲 [a, b] の整数を等確率で返す

	for (int i = 0; i < count; i++)
	{
		int distance = rd() % 10 + 8;//rd() % 7 + 7
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.75f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<LevelOneEnemy>()->SetPosition(spawnpoint);
	}
}

void EnemyManager::LevelTwoEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);

	for (int i = 0; i < count; i++)
	{
		int distance = rd() % 15 + 8;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.75f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<LevelTwoEnemy>()->SetPosition(spawnpoint);
	}
}

void EnemyManager::LevelThreeEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);

	for (int i = 0; i < count; i++)
	{
		int distance = rd() % 15 + 9;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.75f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<LevelThreeEnemy>()->SetPosition(spawnpoint);
	}
}

void EnemyManager::LevelFourEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);

	for (int i = 0; i < count; i++)
	{
		int distance = rd() % 15 + 10;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.75f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<LevelFourEnemy>()->SetPosition(spawnpoint);
	}
}

void EnemyManager::LevelFiveEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);

	for (int i = 0; i < count; i++)
	{
		int distance = rd() % 15 + 11;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.75f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<LevelFiveEnemy>()->SetPosition(spawnpoint);
	}
}

void EnemyManager::GameEnderEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);


	if (Manager::GetScene()->GetGameObject<GameEnderEnemy>() == nullptr)
	{
		int distance = rd() % 7 + 8;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.75f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<GameEnderEnemy>()->SetPosition(spawnpoint);
	}

}

void EnemyManager::DestroyFarEnemy()
{
	

	std::vector<BaseEnemy*> p_enemys = Manager::GetScene()->GetGameObjects<BaseEnemy>();
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

void EnemyManager::RegisterEnemyInstance(ModelTags tags, BaseEnemy* penemy)
{
	map_Enemies[tags].push_back(penemy);
}

void EnemyManager::Draw()
{
	for (auto itr : map_Enemies)
	{
		ModelTags tag = itr.first;
		std::vector <BaseEnemy*> enemies = itr.second;


	}
}

//********************************************************************************
//関数
//********************************************************************************

EnemyManager::~EnemyManager()
{
}

EnemyManager& EnemyManager::GetInstance()
{
	static EnemyManager instance;
	return instance;
}

void EnemyManager::Init(GameTimer* timer)
{//初期化処理
	m_pGameTimer = timer;
}

void EnemyManager::Uninit()
{//終了処理
}

void EnemyManager::SpawnEnemy()
{
	

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
	case GAME_END:
		//ここに強制終了エネミーを出現させる
		WaveEnd();
		break;
	}
}


