//********************************************************************************
//
// enemy_manager.h[ìGä«óùÉNÉâÉX]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************

#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include <vector>

class EnemyManager
{
private:
	class GameTimer* m_pGameTimer;
	struct EnemyInstanceGroup
	{
		std::vector<class BaseEnemy*> Enemies;
		std::vector<InstanceData> SendingDate;
		ID3D11Buffer* InstanceBuffer = nullptr;
	};

	std::unordered_map<ModelTags, EnemyInstanceGroup> map_Enemies;

public:
	EnemyManager(GameTimer*);
	~EnemyManager();

	void Init();

	void AddEnemy(class BaseEnemy*);
	void UpdateInstanceBuffer(EnemyInstanceGroup& group);
	void Update();
	void Draw();

	void SpawnEnemy();
	void DestroyFarEnemy();
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

