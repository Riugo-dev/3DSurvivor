//********************************************************************************
//
// enemy_manager.h[ìGä«óùÉNÉâÉX]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************

#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_



class EnemyManager
{
private:
	class GameTimer* m_pGameTimer;
public:
	EnemyManager(GameTimer*);
	~EnemyManager();

	void SpawnEnemy();
private:
	void WaveOne();
	void WaveTwo();
	void WaveThree();
	void WaveFour();
	void WaveMax();
	void WaveEnd();

	void LevelOneEnemySpawner(int);
	void LevelTwoEnemySpawner(int);
	void LevelThreeEnemySpawner(int);
	void LevelFourEnemySpawner(int);
	void LevelFiveEnemySpawner(int);
	void GameEnderEnemySpawner(int);

};

#endif // !_ENEMY_MANAGER_H_

