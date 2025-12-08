//********************************************************************************
//
// enemy_manager.h[敵管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "enemybase.h"
#include "model_manager.h"
#include "modelRenderer.h"
#include "levelone_enemy.h"
#include "leveltwo_enemy.h"
#include "levelthree_enemy.h"
#include "levelfour_enemy.h"
#include "levelfive_enemy.h"
#include "gameender_enemy.h"
#include "bullet.h"
#include "gametimer.h"
#include <random>
#include <cmath>
#include <vector>
#include <map>


#include "enemy_manager.h"

#define ENEMY_DESTORY_LENGTH (50.0f)
#define ENEMY_MAX_NUM (350)

//********************************************************************************
//プライベート関数
//********************************************************************************

void EnemyManager::WaveOne()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 5 + 50;//スポーンさせる敵の数

	LevelOneEnemySpawner(enemyspawnedcount);
}

void EnemyManager::WaveTwo()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 10 + 50;//スポーンさせる敵の数

	int leveltwocount = rd() % 3 + 15;//レベル２エネミーのスポーン数

	int levelonecount = enemyspawnedcount - leveltwocount;//レベル1エネミーのスポーン数

	LevelOneEnemySpawner(levelonecount);
	LevelTwoEnemySpawner(leveltwocount);

}

void EnemyManager::WaveThree()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 5 + 75;//スポーンさせる敵の数

	int levelthreecount = rd() % 3 + 15;

	int leveltwocount = rd() % 7 + 17;//レベル２エネミーのスポーン数

	int levelonecount = enemyspawnedcount - leveltwocount - levelthreecount;//レベル1エネミーのスポーン数

	LevelOneEnemySpawner(levelonecount);
	LevelTwoEnemySpawner(leveltwocount);
	LevelThreeEnemySpawner(levelthreecount);
}

void EnemyManager::WaveFour()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 10 + 75;//スポーンさせる敵の数

	int levelfourcount = rd() % 3 + 15;

	int levelthreecount = rd() % 7 + 13;

	int leveltwocount = rd() % 2 + 15;//レベル２エネミーのスポーン数

	int levelonecount = enemyspawnedcount - leveltwocount - levelthreecount - levelfourcount;//レベル1エネミーのスポーン数

	LevelOneEnemySpawner(levelonecount);
	LevelTwoEnemySpawner(leveltwocount);
	LevelThreeEnemySpawner(levelthreecount);
	LevelFourEnemySpawner(levelfourcount);
}

void EnemyManager::WaveMax()
{
	std::random_device rd;
	int enemyspawnedcount = rd() % 5 + 80;//スポーンさせる敵の数

	int levelfivecount = rd() % 3 + 13;

	int levelfourcount = rd() % 7 + 15;

	int levelthreecount = rd() % 2 + 17;

	int leveltwocount = enemyspawnedcount - levelthreecount - levelfourcount;//レベル２エネミーのスポーン数

	LevelTwoEnemySpawner(leveltwocount);
	LevelThreeEnemySpawner(levelthreecount);
	LevelFourEnemySpawner(levelfourcount);
	LevelFiveEnemySpawner(levelfivecount);
}

void EnemyManager::WaveEnd()
{
	GameEnderEnemySpawner(1);
}

void EnemyManager::LevelOneEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);//実数の一様分布、指定した範囲 [a, b] の整数を等確率で返す

	for (int i = 0; i < count; i++)
	{
		int distance = rd() % 10 + 8;//rd() % 7 + 7
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.75f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<LevelOneEnemy>()->SetPosition(spawnpoint);
	}
}

void EnemyManager::LevelTwoEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);

	for (int i = 0; i < count; i++)
	{
		int distance = rd() % 15 + 8;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.75f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<LevelTwoEnemy>()->SetPosition(spawnpoint);
	}
}

void EnemyManager::LevelThreeEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);

	for (int i = 0; i < count; i++)
	{
		int distance = rd() % 15 + 9;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.75f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<LevelThreeEnemy>()->SetPosition(spawnpoint);
	}
}

void EnemyManager::LevelFourEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);

	for (int i = 0; i < count; i++)
	{
		int distance = rd() % 15 + 10;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.75f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<LevelFourEnemy>()->SetPosition(spawnpoint);
	}
}

void EnemyManager::LevelFiveEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);

	for (int i = 0; i < count; i++)
	{
		int distance = rd() % 15 + 11;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.75f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<LevelFiveEnemy>()->SetPosition(spawnpoint);
	}
}

void EnemyManager::GameEnderEnemySpawner(int count)
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);


	if (Manager::GetScene()->GetGameObject<GameEnderEnemy>() == nullptr)
	{
		int distance = rd() % 7 + 8;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
		spawnpoint.m_y = 0.75f;
		spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

		Manager::GetScene()->AddGameObject<GameEnderEnemy>()->SetPosition(spawnpoint);

	}

}

void EnemyManager::RegisterToInstanceData()
{//ここで各登録されたエネミーをデータとして登録する
	for (auto& itr : map_Enemies)
	{
		ModelTags tag = itr.first;
		std::vector<BaseEnemy*> enemies = itr.second;

		if (enemies.empty()) continue;

		for (auto enemy : enemies)//エネミーのベクターを回す
		{
			RegisterInstance(tag, enemy->GetWorldMatrix());
		}
	}

	for (auto& itr : map_Enemies)
	{
		itr.second.clear();
	}
}

void EnemyManager::UpdateInstanceBuffers()
{
	for (auto& itr : map_InstanceBuffers)
	{
		ModelTags tag = itr.first;
		InstanceBufferData& inst = itr.second;

		if (inst.Data.empty()) continue;//データが無ければ処理を飛ばす

		D3D11_MAPPED_SUBRESOURCE ms;
		
		Renderer::GetDeviceContext()->Map(inst.Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
		memcpy(ms.pData, inst.Data.data(), sizeof(INSTANCE) * inst.Data.size());
		Renderer::GetDeviceContext()->Unmap(inst.Buffer, 0);

	}
}

void EnemyManager::DrawInstanceBuffers()
{
	for (auto& itr : map_InstanceBuffers)
	{
		ModelTags tag = itr.first;
		InstanceBufferData& inst = itr.second;

		//インスタンスが無ければ描画処理を飛ばす
		if (inst.Data.empty() || inst.Buffer == nullptr) continue;

		int instancecount = (int)inst.Data.size();

		ModelRenderer* renderer = ModelManager::GetModel(tag);

		if (!renderer) continue;

		ModelManager::SetShaders(tag, SHADER_INSTANCETOON);

		renderer->DrawInstanced(instancecount, inst.Buffer);

	}

	for (auto& itr : map_InstanceBuffers)
	{
		itr.second.Data.clear();
	}

}

void EnemyManager::RegisterInstance(ModelTags model, XMMATRIX world)
{
	//送りやすいようにデータを格納
	INSTANCE inst;
	inst.WorldMatrix = XMMatrixTranspose(world);//座標データを転置して格納

	map_InstanceBuffers[model].Data.push_back(inst);
}

std::string EnemyManager::GetModelNameByTag(ModelTags tags)
{
	switch (tags)
	{
	case ENEMY_RED:
		return "asset\\model\\EnemyTypeRed.obj";
		break;
	case ENEMY_BLUE:
		return "asset\\model\\EnemyTypeBlue.obj";
		break;
	case ENEMY_GREEN:
		return "asset\\model\\EnemyTypeGreen.obj";
		break;
	case ENEMY_PURPLE:
		return "asset\\model\\EnemyTypePurple.obj";
		break;
	case ENEMY_SILVER:
		return "asset\\model\\EnemyTypeSilver.obj";
		break;
	case ENEMY_BLACK:
		return "asset\\model\\EnemyTypeBlack.obj";
		break;
	default:
		return NULL;
		break;
	}
}

void EnemyManager::DestroyFarEnemy()
{
	

	std::vector<BaseEnemy*> p_enemys = Manager::GetScene()->GetGameObjects<BaseEnemy>();
	if (p_enemys.size() < ENEMY_MAX_NUM) return;

	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	for (auto itr : p_enemys)
	{
		Vector3 vector = p_player->GetPosition() - itr->GetPosition();
		
		float length = vector.length();

		if (length > ENEMY_DESTORY_LENGTH)
		{
			itr->SetDestroy(true);
		}
	}


}

void EnemyManager::RegisterEnemyInstance(ModelTags tags, BaseEnemy* penemy)
{
	map_Enemies[tags].push_back(penemy);
}

void EnemyManager::Draw()
{
	//イスタンスバッファのデータ登録
	RegisterToInstanceData();

	//インスタンスバッファの更新処理
	UpdateInstanceBuffers();

	//インスタンシングしたものの描画
	DrawInstanceBuffers();
}

//********************************************************************************
//関数
//********************************************************************************

EnemyManager::~EnemyManager()
{
}

EnemyManager& EnemyManager::GetInstance()
{
	static EnemyManager instance;
	return instance;
}

void EnemyManager::Init(GameTimer* timer)
{//初期化処理
	m_pGameTimer = timer;
	
	//各バッファの最大数を確保
	const int maxinstance = 500;

	for (int tag = ENEMY_RED ; tag < SHOOTER_ENEMY_RED ; tag++)
	{
		map_InstanceBuffers[(ModelTags)tag] = InstanceBufferData();

		auto& inst = map_InstanceBuffers[(ModelTags)tag];

		//バッファの作成
		D3D11_BUFFER_DESC desc{};
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(INSTANCE) * maxinstance;//ワールド行列のバイトサイズ＊データの個数
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &inst.Buffer);

	}

}

void EnemyManager::Uninit()
{//終了処理
}

void EnemyManager::SpawnEnemy()
{
	

	switch (m_pGameTimer->GetCurrentWave())
	{
	case WAVE_ONE:
		WaveOne();
		break;
	case WAVE_TWO:
		WaveTwo();
		break;
	case WAVE_THREE:
		WaveThree();
		break;
	case WAVE_FOUR:
		WaveFour();
		break;
	case WAVE_MAX:
		WaveMax();
		break;
	case GAME_END:
		//ここに強制終了エネミーを出現させる
		WaveEnd();
		break;
	}
}


