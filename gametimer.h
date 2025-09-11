//********************************************************************************
//
// gametimer.h[’e]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************

#ifndef _GAMETIMER_H_
#define _GAMETIMER_H_



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
	class EnemyManager* m_pEnemyManager;
	int m_FrameCount;
	int m_CurrentTime;
	int m_PreviousTime;
	int m_EnemySpawnCoolTime;
	Wave m_CurrentWave = WAVE_ONE;
	
public:
	GameTimer();
	~GameTimer();

	void Update();
	void Draw();

	Wave GetCurrentWave();
};


#endif // !_GAMETIMER_H_
