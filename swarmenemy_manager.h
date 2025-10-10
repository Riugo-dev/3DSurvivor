//********************************************************************************
//
// swarmenemy_manager.h[ìGä«óùÉNÉâÉX]
//
//															Author :Riugo Honda
//															Date   :2025/10/09
//********************************************************************************

#ifndef _SWARMENEMY_MANAGER_H_
#define _SWARMENEMY_MANAGER_H_



class SwarmEnemyManager
{
private:
	class GameTimer* m_pGameTimer;
public:
	SwarmEnemyManager(GameTimer*);
	~SwarmEnemyManager();

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

#endif // !_SWARMENEMY_MANAGER_H_
