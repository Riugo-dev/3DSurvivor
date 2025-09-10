//********************************************************************************
//
// gametimer.h[’e]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************

#ifndef _GAMETIMER_H_
#define _GAMETIMER_H_

#include "main.h"

class Player;

typedef enum
{
	WAVE_ONE = 1,
	WAVE_TWO,
	WAVE_THREE,
	WAVE_FOUR,
	WAVE_MAX,
	GAME_END,
}Wave;

class GameTimer
{
private:
	int m_FrameCount = 0;
	int m_CurrentTime = 0;
	int m_EnemySpawnCoolTime = 0;

	
	Wave m_CurrentWave = WAVE_ONE;
	Player* m_pPlayer = nullptr;

public:
	GameTimer(Player*);
	~GameTimer();

	void Update();
	void Draw();

	Wave GetCurrentWave();
};


#endif // !_GAMETIMER_H_
