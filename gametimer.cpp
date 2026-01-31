//********************************************************************************
//
// gametimer.h[弾]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************
#include "main.h"
#include "player.h"
#include "enemybase.h"
#include "enemy_manager.h"
#include "shooterenemy_manager.h"
#include "swarmenemy_manager.h"
#include "midboss_manager.h"
#include <vector>

#include "gametimer.h"
//********************************************************************************
//定数の定義
//********************************************************************************
//フレーム換算
#define WAVEONECOOLTIME (1800)
#define WAVETWOCOOLTIME (1800)
#define WAVETHREECOOLTIME (1800)
#define WAVEFOURCOOLTIME (1800)
#define WAVEMAXCOOLTIME (1800)

//秒換算
#define WAVEONE (50)
#define WAVETWO (110)
#define WAVETHREE (170)
#define WAVEFOUR (230)
#define WAVEMAX (290)

#define SWARMCOOLTIME (50)
#define MIDBOSSCOOLTIME (120)
//********************************************************************************
//グローバル変数
//********************************************************************************


//********************************************************************************
//関数
//********************************************************************************

GameTimer::GameTimer()
{
	m_CurrentTime = 0;
	m_CurrentWave = WAVE_ONE;
	m_FrameCount = 0;

	m_pEnemyManager = new EnemyManager(this);
	m_pEnemyManager->Init();
	m_pShooterEnemyManager = new ShooterEnemyManager(this);
	m_pSwarmEnemyManager = new SwarmEnemyManager(this);
	m_pMidBossManager = new MidBossManager(this);
}

GameTimer::~GameTimer()
{
	delete m_pMidBossManager;
	m_pMidBossManager = nullptr;

	delete m_pSwarmEnemyManager;
	m_pSwarmEnemyManager = nullptr;

	delete m_pShooterEnemyManager;
	m_pShooterEnemyManager = nullptr;

	m_pEnemyManager->Uninit();
	delete m_pEnemyManager;
	m_pEnemyManager = nullptr;
}

void GameTimer::Update()
{
	
	switch (m_CurrentWave)
	{
	case WAVE_ONE:
		if (m_FrameCount % WAVEONECOOLTIME == 0)
		{
			//ここでエネミースポナーを呼び出す
			m_pEnemyManager->SpawnEnemy();
			m_pShooterEnemyManager->SpawnEnemy();
		}
		else if (Manager::GetScene()->GetGameObjects<BaseEnemy>().size() <= 1 && m_FrameCount % WAVEONECOOLTIME <= 1500)
		{
			m_pEnemyManager->SpawnEnemy();
		}

		if (m_CurrentTime >= WAVEONE)
		{
			m_CurrentWave = WAVE_TWO;

			m_pEnemyManager->DestroyFarEnemy();
			m_pShooterEnemyManager->DestroyFarEnemy();
		}
		break;
	case WAVE_TWO:
		if (m_FrameCount % WAVETWOCOOLTIME == 0)
		{
			//ここでエネミースポナーを呼び出す
			m_pEnemyManager->SpawnEnemy();
			m_pShooterEnemyManager->SpawnEnemy();
		}
		else if (Manager::GetScene()->GetGameObjects<BaseEnemy>().size() <= 1 && m_FrameCount % WAVEONECOOLTIME <= 1500)
		{
			m_pEnemyManager->SpawnEnemy();
		}

		if (m_CurrentTime >= WAVETWO)
		{
			m_CurrentWave = WAVE_THREE;


			m_pEnemyManager->DestroyFarEnemy();
			m_pShooterEnemyManager->DestroyFarEnemy();
		}
		break;
	case WAVE_THREE:
		if (m_FrameCount % WAVETHREECOOLTIME == 0)
		{
			//ここでエネミースポナーを呼び出す
			m_pEnemyManager->SpawnEnemy();
			m_pShooterEnemyManager->SpawnEnemy();
		}
		else if (Manager::GetScene()->GetGameObjects<BaseEnemy>().size() <= 1 && m_FrameCount % WAVEONECOOLTIME <= 1500)
		{
			m_pEnemyManager->SpawnEnemy();
		}

		if (m_CurrentTime >= WAVETHREE)
		{
			m_CurrentWave = WAVE_FOUR;


			m_pEnemyManager->DestroyFarEnemy();
			m_pShooterEnemyManager->DestroyFarEnemy();
		}
		break;
	case WAVE_FOUR:
		if (m_FrameCount % WAVEFOURCOOLTIME == 0)
		{
			//ここでエネミースポナーを呼び出す
			m_pEnemyManager->SpawnEnemy();
			m_pShooterEnemyManager->SpawnEnemy();
		}
		else if (Manager::GetScene()->GetGameObjects<BaseEnemy>().size() <= 1 && m_FrameCount % WAVEONECOOLTIME <= 1500)
		{
			m_pEnemyManager->SpawnEnemy();
		}

		if (m_CurrentTime >= WAVEFOUR)
		{
			m_CurrentWave = WAVE_MAX;


			m_pEnemyManager->DestroyFarEnemy();
			m_pShooterEnemyManager->DestroyFarEnemy();
		}
		break;
	case WAVE_MAX:
		if (m_FrameCount % WAVEMAXCOOLTIME == 0)
		{
			//ここでエネミースポナーを呼び出す
			m_pEnemyManager->SpawnEnemy();
			m_pShooterEnemyManager->SpawnEnemy();
		}
		else if (Manager::GetScene()->GetGameObjects<BaseEnemy>().size() <= 1 && m_FrameCount % WAVEONECOOLTIME <= 1500)
		{
			m_pEnemyManager->SpawnEnemy();
		}

		if (m_CurrentTime >= WAVEMAX)
		{
			m_CurrentWave = GAME_END;


			m_pEnemyManager->DestroyFarEnemy();
			m_pShooterEnemyManager->DestroyFarEnemy();
		}
		break;
	case GAME_END:
		//ここに強制終了エネミーを出現させる
		m_pEnemyManager->SpawnEnemy();
	default:
		break;
	}

	

	m_FrameCount++;

	m_CurrentTime = m_FrameCount / 60;

	if (m_CurrentTime % SWARMCOOLTIME == 0 && m_CurrentTime >= SWARMCOOLTIME)
	{
		m_pSwarmEnemyManager->SpawnEnemy();
	}

	if (m_CurrentTime % MIDBOSSCOOLTIME == 0 && m_CurrentTime >= MIDBOSSCOOLTIME)
	{
		m_pMidBossManager->SpawnEnemy();
	}

	m_pEnemyManager->Update();

}

void GameTimer::Draw()
{
	m_pEnemyManager->Draw();
}

Wave GameTimer::GetCurrentWave()
{
	return m_CurrentWave;
}
