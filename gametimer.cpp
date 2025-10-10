//********************************************************************************
//
// gametimer.h[弾]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************
#include "player.h"
#include "enemy_manager.h"
#include "shooterenemy_manager.h"
#include "swarmenemy_manager.h"


#include "gametimer.h"
//********************************************************************************
//定数の定義
//********************************************************************************
//フレーム換算
#define WAVEONECOOLTIME (600)
#define WAVETWOCOOLTIME (600)
#define WAVETHREECOOLTIME (480)
#define WAVEFOURCOOLTIME (480)
#define WAVEMAXCOOLTIME (420)

//秒換算
#define WAVEONE (60)
#define WAVETWO (120)
#define WAVETHREE (180)
#define WAVEFOUR (240)
#define WAVEMAX (300)
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
	m_pShooterEnemyManager = new ShooterEnemyManager(this);
	m_pSwarmEnemyManager = new SwarmEnemyManager(this);
}

GameTimer::~GameTimer()
{
	delete m_pSwarmEnemyManager;
	m_pSwarmEnemyManager = nullptr;

	delete m_pShooterEnemyManager;
	m_pShooterEnemyManager = nullptr;

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

	if (m_CurrentTime % 50 == 0 && m_CurrentTime >= 50)
	{
		m_pSwarmEnemyManager->SpawnEnemy();
	}
}

void GameTimer::Draw()
{

}

Wave GameTimer::GetCurrentWave()
{
	return m_CurrentWave;
}
