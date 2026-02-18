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
	void spawnregular();
	void spawnlaterwaves();
};

#endif // !_SWARMENEMY_MANAGER_H_
