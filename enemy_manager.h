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

	ID3D11Buffer* m_InstanceBuffer;
	ID3D11ShaderResourceView* m_EnemySRV;
	//必要なこと
	//失敗したときのインスタンシング同様全てのエネミー用のバッファとシェーダーリソースビュー
	//Initの作成及びシングルトン設計化
	//動画②も観て明日中に完成

public:
	EnemyManager(GameTimer*);
	~EnemyManager();

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

