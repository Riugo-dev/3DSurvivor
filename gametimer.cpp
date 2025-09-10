//********************************************************************************
//
// gametimer.h[弾]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************
#include "player.h"
#include "enemy_manager.h"

#include "gametimer.h"
//********************************************************************************
//定数の定義
//********************************************************************************
#define WAVEONECOOLTIME (10)
#define WAVETWOCOOLTIME (8)
#define WAVETHREECOOLTIME (6)
#define WAVEFOURCOOLTIME (4)
#define WAVEMAXCOOLTIME (2)

#define WAVEONE (120)
#define WAVETWO (240)
#define WAVETHREE (360)
#define WAVEFOUR (480)
#define WAVEMAX (600)
//********************************************************************************
//関数
//********************************************************************************

GameTimer::GameTimer(Player* player)
{
	m_pPlayer = player;

	m_CurrentTime = 0;
	m_CurrentWave = WAVE_ONE;
	m_EnemySpawnCoolTime = WAVEONECOOLTIME;
	m_FrameCount = 0;

}

GameTimer::~GameTimer()
{

}

void GameTimer::Update()
{
	m_FrameCount++;

	m_CurrentTime = m_FrameCount / 60;

	switch (m_CurrentWave)
	{
	case WAVE_ONE:
		if (m_CurrentTime % WAVEONECOOLTIME == 0)
		{
			//ここでエネミースポナーを呼び出す
		}

		if (m_CurrentTime >= WAVEONE)
		{
			m_CurrentWave = WAVE_TWO;
		}
		break;
	case WAVE_TWO:
		if (m_CurrentTime % WAVETWOCOOLTIME == 0)
		{
			//ここでエネミースポナーを呼び出す
		}

		if (m_CurrentTime >= WAVETWO)
		{
			m_CurrentWave = WAVE_THREE;
		}
		break;
	case WAVE_THREE:
		if (m_CurrentTime % WAVETHREECOOLTIME == 0)
		{
			//ここでエネミースポナーを呼び出す
		}

		if (m_CurrentTime >= WAVETHREE)
		{
			m_CurrentWave = WAVE_FOUR;
		}
		break;
	case WAVE_FOUR:
		if (m_CurrentTime % WAVEFOURCOOLTIME == 0)
		{
			//ここでエネミースポナーを呼び出す
		}

		if (m_CurrentTime >= WAVEFOUR)
		{
			m_CurrentWave = WAVE_MAX;
		}
		break;
	case WAVE_MAX:
		if (m_CurrentTime % WAVEMAXCOOLTIME == 0)
		{
			//ここでエネミースポナーを呼び出す
		}

		if (m_CurrentTime >= WAVEMAX)
		{
			m_CurrentWave = GAME_END;
		}
		break;
	case GAME_END:
		//ここに強制終了エネミーを出現させる
	default:
		break;
	}

}

void GameTimer::Draw()
{

}

Wave GameTimer::GetCurrentWave()
{
	return m_CurrentWave;
}
