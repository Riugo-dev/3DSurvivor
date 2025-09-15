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


#include "enemy_manager.h"
//********************************************************************************
//プライベート関数
//********************************************************************************

void EnemyManager::WaveOne()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 5 + 15;//スポーンさせる敵の数

	LevelOneEnemySpawner(enemyspawnedcount);
}

void EnemyManager::WaveTwo()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 10 + 20;//スポーンさせる敵の数

	int leveltwocount = rd() % 3 + 5;//レベル２エネミーのスポーン数

	int levelonecount = enemyspawnedcount - leveltwocount;//レベル1エネミーのスポーン数

	LevelOneEnemySpawner(levelonecount);
	LevelTwoEnemySpawner(leveltwocount);

}

void EnemyManager::WaveThree()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 5 + 25;//スポーンさせる敵の数

	int levelthreecount = rd() % 3 + 5;

	int leveltwocount = rd() % 7 + 7;//レベル２エネミーのスポーン数

	int levelonecount = enemyspawnedcount - leveltwocount - levelthreecount;//レベル1エネミーのスポーン数

	LevelOneEnemySpawner(levelonecount);
	LevelTwoEnemySpawner(leveltwocount);
	LevelThreeEnemySpawner(levelthreecount);
}

void EnemyManager::WaveFour()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 10 + 25;//スポーンさせる敵の数

	int levelfourcount = rd() % 3 + 5;

	int levelthreecount = rd() % 7 + 3;

	int leveltwocount = rd() % 2 + 5;//レベル２エネミーのスポーン数

	int levelonecount = enemyspawnedcount - leveltwocount - levelthreecount - levelfourcount;//レベル1エネミーのスポーン数

	LevelOneEnemySpawner(levelonecount);
	LevelTwoEnemySpawner(leveltwocount);
	LevelThreeEnemySpawner(levelthreecount);
	LevelFourEnemySpawner(levelfourcount);
}

void EnemyManager::WaveMax()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 5 + 30;//スポーンさせる敵の数

	int levelfivecount = rd() % 3 + 3;

	int levelfourcount = rd() % 7 + 5;

	int levelthreecount = rd() % 2 + 7;

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

	for (int i = 0; i < count; i++)
	{
		int leftright = rd() % 2;
		int fowardback = rd() % 2;

		int x = rd() % 5 + 4;
		int z = rd() % 5 + 4;

		Vector3 spawnpoint = p_player->GetPosition();

		spawnpoint.m_y += 1.0f;

		if (leftright == 0)
		{
			spawnpoint.m_x -= x;
		}
		else
		{
			spawnpoint.m_x += x;
		}

		if (fowardback == 0)
		{
			spawnpoint.m_z -= z;
		}
		else
		{
			spawnpoint.m_z += z;
		}

		Manager::GetScene()->AddGameObject<LevelOneEnemy>()->SetPosition(spawnpoint);
	}
}

void EnemyManager::LevelTwoEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;

	for (int i = 0; i < count; i++)
	{
		int leftright = rd() % 2;
		int fowardback = rd() % 2;

		int x = rd() % 5 + 4;
		int z = rd() % 5 + 4;

		Vector3 spawnpoint = p_player->GetPosition();
		spawnpoint.m_y += 1.0f;

		if (leftright == 0)
		{
			spawnpoint.m_x -= x;
		}
		else
		{
			spawnpoint.m_x += x;
		}

		if (fowardback == 0)
		{
			spawnpoint.m_z -= z;
		}
		else
		{
			spawnpoint.m_z += z;
		}

		Manager::GetScene()->AddGameObject<LevelTwoEnemy>()->SetPosition(spawnpoint);
	}
}

void EnemyManager::LevelThreeEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;

	for (int i = 0; i < count; i++)
	{
		int leftright = rd() % 2;
		int fowardback = rd() % 2;

		int x = rd() % 3 + 5;
		int z = rd() % 3 + 5;

		Vector3 spawnpoint = p_player->GetPosition();
		spawnpoint.m_y += 1.0f;

		if (leftright == 0)
		{
			spawnpoint.m_x -= x;
		}
		else
		{
			spawnpoint.m_x += x;
		}

		if (fowardback == 0)
		{
			spawnpoint.m_z -= z;
		}
		else
		{
			spawnpoint.m_z += z;
		}

		Manager::GetScene()->AddGameObject<LevelThreeEnemy>()->SetPosition(spawnpoint);
	}
}

void EnemyManager::LevelFourEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;

	for (int i = 0; i < count; i++)
	{
		int leftright = rd() % 2;
		int fowardback = rd() % 2;

		int x = rd() % 3 + 5;
		int z = rd() % 3 + 5;

		Vector3 spawnpoint = p_player->GetPosition();
		spawnpoint.m_y += 1.0f;

		if (leftright == 0)
		{
			spawnpoint.m_x -= x;
		}
		else
		{
			spawnpoint.m_x += x;
		}

		if (fowardback == 0)
		{
			spawnpoint.m_z -= z;
		}
		else
		{
			spawnpoint.m_z += z;
		}

		Manager::GetScene()->AddGameObject<LevelFourEnemy>()->SetPosition(spawnpoint);
	}
}

void EnemyManager::LevelFiveEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;

	for (int i = 0; i < count; i++)
	{
		int leftright = rd() % 2;
		int fowardback = rd() % 2;

		int x = rd() % 5 + 5;
		int z = rd() % 5 + 5;

		Vector3 spawnpoint = p_player->GetPosition();
		spawnpoint.m_y += 1.0f;

		if (leftright == 0)
		{
			spawnpoint.m_x -= x;
		}
		else
		{
			spawnpoint.m_x += x;
		}

		if (fowardback == 0)
		{
			spawnpoint.m_z -= z;
		}
		else
		{
			spawnpoint.m_z += z;
		}

		Manager::GetScene()->AddGameObject<LevelFiveEnemy>()->SetPosition(spawnpoint);
	}
}

void EnemyManager::GameEnderEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;

	if (Manager::GetScene()->GetGameObject<GameEnderEnemy>() == nullptr)
	{
		int leftright = rd() % 2;
		int fowardback = rd() % 2;

		int x = rd() % 5 + 5;
		int z = rd() % 5 + 5;

		Vector3 spawnpoint = p_player->GetPosition();
		spawnpoint.m_y += 1.0f;

		if (leftright == 0)
		{
			spawnpoint.m_x -= x;
		}
		else
		{
			spawnpoint.m_x += x;
		}

		if (fowardback == 0)
		{
			spawnpoint.m_z -= z;
		}
		else
		{
			spawnpoint.m_z += z;
		}

		Manager::GetScene()->AddGameObject<GameEnderEnemy>()->SetPosition(spawnpoint);
	}

}

//********************************************************************************
//関数
//********************************************************************************
EnemyManager::EnemyManager(GameTimer* timer)
{
	m_pGameTimer = timer;
}

EnemyManager::~EnemyManager()
{
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


