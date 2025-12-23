//********************************************************************************
//
// enemy_manager.h[敵管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************

#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

class BaseEnemy;


class EnemyManager
{
private:
	class GameTimer* m_pGameTimer;
	std::unordered_map<ModelTags, std::vector<BaseEnemy*>> map_Enemies;
	struct InstanceBufferData
	{
		ID3D11Buffer* Buffer = nullptr;
		ID3D11ShaderResourceView* EnemySRV = nullptr;
		std::vector<Vector3> EnemyPosData;
		ModelRenderer* Model = nullptr;
		ID3D11VertexShader* VertexShader = nullptr;
		ID3D11PixelShader* PixelShader = nullptr;
		ID3D11InputLayout* InputLayout = nullptr;
	};
	std::unordered_map < ModelTags, InstanceBufferData> map_InstanceBuffers;

public:
	~EnemyManager();

	//シングルトン処理
	static EnemyManager& GetInstance();

	void Init(GameTimer*);
	void Uninit();
	void SpawnEnemy();
	void DestroyFarEnemy();
	void Update();
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

	void RegisterToInstanceData();
	void UpdateInstanceBuffers();
	void DrawInstanceBuffers();
	void RegisterInstance(ModelTags , Vector3);
	const char* GetModelNameByTag(ModelTags);
};

#endif // !_ENEMY_MANAGER_H_

