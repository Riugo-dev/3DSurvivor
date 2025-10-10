//********************************************************************************
//
// shooterenemy_manager.h[ìGä«óùÉNÉâÉX]
//
//															Author :Riugo Honda
//															Date   :2025/10/07
//********************************************************************************

#ifndef _SHOOTERENEMY_MANAGER_H_
#define _SHOOTERENEMY_MANAGER_H_



class ShooterEnemyManager
{
private:
	class GameTimer* m_pGameTimer;
public:
	ShooterEnemyManager(GameTimer*);
	~ShooterEnemyManager();

	void SpawnEnemy();
	void DestroyFarEnemy();
private:
	void WaveOne();
	void WaveTwo();
	void WaveThree();
	void WaveFour();
	void WaveMax();

	void LevelOneEnemySpawner(int);
	void LevelTwoEnemySpawner(int);
	void LevelThreeEnemySpawner(int);
	void LevelFourEnemySpawner(int);
	void LevelFiveEnemySpawner(int);
};

#endif // !_SHOOTERENEMY_MANAGER_H_