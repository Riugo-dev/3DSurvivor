//********************************************************************************
//
// enemy_manager.h[敵管理クラス]
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
	std::unordered_map<ModelTags, std::vector<BaseEnemy*>> map_Enemies;
	std::unordered_map<ModelTags, ID3D11Buffer*> map_InstanceBuffer;
public:
	~EnemyManager();

	//シングルトン処理
	static EnemyManager& GetInstance();

	void Init(GameTimer*);
	void Uninit();
	void SpawnEnemy();
	void DestroyFarEnemy();
	void RegisterEnemyInstance(ModelTags, BaseEnemy*);
	void Draw();
private:
	EnemyManager() {};

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

