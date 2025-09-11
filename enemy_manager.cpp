//********************************************************************************
//
// enemy_manager.h[敵管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "enemybase.h"
#include "levelone_enemy.h"
#include "bullet.h"
#include "gametimer.h"
#include <random>


#include "enemy_manager.h"
//********************************************************************************
//グローバル変数
//********************************************************************************

//********************************************************************************
//関数
//********************************************************************************
EnemyManager::EnemyManager()
{

}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::SpawnEnemy()
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	//GameTimer* p_timer = Manager::GetScene()->GetGameTimer();

	//後々引数でスポーンの調整ができるようにしておく

	std::random_device rd;
	int enemyspawnedcount = rd() % 5 + 5; 

	for (int i = 0; i < enemyspawnedcount; i++)
	{
		int leftright = rd() % 2;
		int fowardback = rd() % 2;

		int x = rd() % 3 + 3;
		int z = rd() % 3 + 3;

		Vector3 spawnpoint = p_player->GetPosition();

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

	//switch (p_timer->GetCurrentWave())
	//{
	//case WAVE_ONE:
	//	
	//	break;
	//case WAVE_TWO:
	//	
	//	break;
	//case WAVE_THREE:
	//	
	//	break;
	//case WAVE_FOUR:
	//	
	//	break;
	//case WAVE_MAX:
	//	
	//	break;
	//case GAME_END:
	//	//ここに強制終了エネミーを出現させる
	//}
}


