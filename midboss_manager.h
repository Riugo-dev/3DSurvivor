//********************************************************************************
//
// midboss_manager.h[ìGä«óùÉNÉâÉX]
//
//															Author :Riugo Honda
//															Date   :2025/10/12
//********************************************************************************

#ifndef _MIDBOSS_MANAGER_H_
#define _MIDBOSS_MANAGER_H_



class MidBossManager
{
private:
	class GameTimer* m_pGameTimer;
public:
	MidBossManager(GameTimer*);
	~MidBossManager();

	void SpawnEnemy();
	void DestroyFarEnemy();
private:
	/*void WaveOne();
	void WaveTwo();
	void WaveThree();
	void WaveFour();
	void WaveMax();*/

	void LevelOneEnemySpawner(int);
	/*void LevelTwoEnemySpawner(int);
	void LevelThreeEnemySpawner(int);
	void LevelFourEnemySpawner(int);
	void LevelFiveEnemySpawner(int);*/
};

#endif // !_MIDBOSS_MANAGER_H_
