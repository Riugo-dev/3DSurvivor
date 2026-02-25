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
#include "attackbase.h"
#include "model_manager.h"
#include "modelRenderer.h"
#include "shader_manager.h"
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


#include "enemy_manager.h"

#define ENEMY_DESTORY_LENGTH (50.0f)
#define ENEMY_MAX_NUM (600)

//********************************************************************************
//プライベート関数
//********************************************************************************

void EnemyManager::WaveOne()
{

	int enemycount = Manager::GetScene()->GetGameObjects<BaseEnemy>().size();

	if (enemycount > 200)
	{
		std::random_device rd;
		int enemyspawnedcount = rd() % 100 + 50;//スポーンさせる敵の数
		
		LevelOneEnemySpawner(enemyspawnedcount);
	}
	else
	{
		std::random_device rd;
		int enemyspawnedcount = rd() % 100 + 150;//スポーンさせる敵の数
		//int enemyspawnedcount = rd() % 5 + 50;//スポーンさせる敵の数

		LevelOneEnemySpawner(enemyspawnedcount);
	}
}

void EnemyManager::WaveTwo()
{
	int enemycount = Manager::GetScene()->GetGameObjects<BaseEnemy>().size();

	if (enemycount > 200)
	{
		std::random_device rd;
		int enemyspawnedcount = rd() % 100 + 50;//スポーンさせる敵の数
		
		int leveltwocount = rd() % 20 + 30;//レベル２エネミーのスポーン数
		int levelonecount = enemyspawnedcount - leveltwocount;//レベル1エネミーのスポーン数

		LevelOneEnemySpawner(levelonecount);
		LevelTwoEnemySpawner(leveltwocount);
	}
	else
	{
		std::random_device rd;
		int enemyspawnedcount = rd() % 100 + 150;//スポーンさせる敵の数
		//int enemyspawnedcount = rd() % 10 + 50;//スポーンさせる敵の数

		int leveltwocount = rd() % 50 + 80;//レベル２エネミーのスポーン数
		//int leveltwocount = rd() % 3 + 15;//レベル２エネミーのスポーン数

		int levelonecount = enemyspawnedcount - leveltwocount;//レベル1エネミーのスポーン数

		LevelOneEnemySpawner(levelonecount);
		LevelTwoEnemySpawner(leveltwocount);
	}
}

void EnemyManager::WaveThree()
{
	int enemycount = Manager::GetScene()->GetGameObjects<BaseEnemy>().size();

	if (enemycount > 200)
	{
		std::random_device rd;
		int enemyspawnedcount = rd() % 50 + 100;//スポーンさせる敵の数

		int levelthreecount = rd() % 20 + 30;
		int leveltwocount = rd() % 30 + 20;//レベル２エネミーのスポーン数
		int levelonecount = enemyspawnedcount - leveltwocount - levelthreecount;//レベル1エネミーのスポーン数

		LevelOneEnemySpawner(levelonecount);
		LevelTwoEnemySpawner(leveltwocount);
		LevelThreeEnemySpawner(levelthreecount);
	}
	else
	{
		std::random_device rd;
		//int enemyspawnedcount = rd() % 5 + 75;//スポーンさせる敵の数
		int enemyspawnedcount = rd() % 100 + 200;//スポーンさせる敵の数

		int levelthreecount = rd() % 30 + 30;
		//int levelthreecount = rd() % 3 + 15;

		int leveltwocount = rd() % 50 + 60;//レベル２エネミーのスポーン数
		//int leveltwocount = rd() % 7 + 17;//レベル２エネミーのスポーン数

		//int enemyspawnedcount = rd() % 50 + 375;//スポーンさせる敵の数

		//int levelthreecount = rd() % 50 + 25;

		//int leveltwocount = rd() % 70 + 100;//レベル２エネミーのスポーン数

		int levelonecount = enemyspawnedcount - leveltwocount - levelthreecount;//レベル1エネミーのスポーン数

		LevelOneEnemySpawner(levelonecount);
		LevelTwoEnemySpawner(leveltwocount);
		LevelThreeEnemySpawner(levelthreecount);
	}
}

void EnemyManager::WaveFour()
{
	int enemycount = Manager::GetScene()->GetGameObjects<BaseEnemy>().size();

	if (enemycount > 200)
	{
		std::random_device rd;
		int enemyspawnedcount = rd() % 50 + 100;//スポーンさせる敵の数

		int levelfourcount = rd() % 10 + 20;
		int levelthreecount = rd() % 20 + 30;
		int leveltwocount = 20;//レベル２エネミーのスポーン数

		int levelonecount = enemyspawnedcount - leveltwocount - levelthreecount - levelfourcount;//レベル1エネミーのスポーン数

		LevelOneEnemySpawner(levelonecount);
		LevelTwoEnemySpawner(leveltwocount);
		LevelThreeEnemySpawner(levelthreecount);
		LevelFourEnemySpawner(levelfourcount);
	}
	else
	{
		std::random_device rd;
		int enemyspawnedcount = rd() % 100 + 200;//スポーンさせる敵の数
		//int enemyspawnedcount = rd() % 10 + 75;//スポーンさせる敵の数

		int levelfourcount = rd() % 10 + 20;
		/*int levelfourcount = rd() % 3 + 15;*/

		int levelthreecount = rd() % 20 + 50;
		/*int levelthreecount = rd() % 7 + 13;*/


		int leveltwocount = rd() % 25 + 75;//レベル２エネミーのスポーン数
		//int leveltwocount = rd() % 2 + 15;//レベル２エネミーのスポーン数

		int levelonecount = enemyspawnedcount - leveltwocount - levelthreecount - levelfourcount;//レベル1エネミーのスポーン数

		LevelOneEnemySpawner(levelonecount);
		LevelTwoEnemySpawner(leveltwocount);
		LevelThreeEnemySpawner(levelthreecount);
		LevelFourEnemySpawner(levelfourcount);
	}
}

void EnemyManager::WaveMax()
{

	int enemycount = Manager::GetScene()->GetGameObjects<BaseEnemy>().size();

	if (enemycount > 200)
	{
		std::random_device rd;
		int enemyspawnedcount = 150;//スポーンさせる敵の数
	
		int levelfivecount = rd() % 10 + 20;
		int levelfourcount = rd() % 20 + 30;
		int levelthreecount = rd() % 20 + 50;

		int leveltwocount = enemyspawnedcount - levelthreecount - levelfourcount;//レベル２エネミーのスポーン数

		LevelTwoEnemySpawner(leveltwocount);
		LevelThreeEnemySpawner(levelthreecount);
		LevelFourEnemySpawner(levelfourcount);
		LevelFiveEnemySpawner(levelfivecount);
	}
	else
	{
		std::random_device rd;
		int enemyspawnedcount = 300;//スポーンさせる敵の数
		//int enemyspawnedcount = rd() % 5 + 80;//スポーンさせる敵の数

		int levelfivecount = rd() % 10 + 20;
		//int levelfivecount = rd() % 3 + 13;

		int levelfourcount = rd() % 20 + 50;
		/*int levelfourcount = rd() % 7 + 15;*/

		int levelthreecount = rd() % 25 + 75;
		/*int levelthreecount = rd() % 2 + 17;*/

		int leveltwocount = enemyspawnedcount - levelthreecount - levelfourcount;//レベル２エネミーのスポーン数

		LevelTwoEnemySpawner(leveltwocount);
		LevelThreeEnemySpawner(levelthreecount);
		LevelFourEnemySpawner(levelfourcount);
		LevelFiveEnemySpawner(levelfivecount);
	}
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
		int distance = rd() % 35 + 9 - ((int)m_pGameTimer->GetCurrentWave());//rd() % 7 + 7
		//int distance = rd() % 10 + 8;//rd() % 7 + 7
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.x = p_player->GetPosition().x + cosf(angle) * distance;
		spawnpoint.y = 0.75f;
		spawnpoint.z = p_player->GetPosition().z + sinf(angle) * distance;

		LevelOneEnemy* enemy = Manager::GetScene()->AddGameObject<LevelOneEnemy>();
		enemy->Init();
		enemy->SetPosition(spawnpoint);
		AddEnemy(enemy);
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
		int distance = rd() % 35 + 10;
		//int distance = rd() % 15 + 8;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.x = p_player->GetPosition().x + cosf(angle) * distance;
		spawnpoint.y = 0.75f;
		spawnpoint.z = p_player->GetPosition().z + sinf(angle) * distance;

		LevelTwoEnemy* enemy = Manager::GetScene()->AddGameObject<LevelTwoEnemy>();
		enemy->Init();
		enemy->SetPosition(spawnpoint);
		AddEnemy(enemy);
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
		int distance = rd() % 30 + 14;
		//int distance = rd() % 15 + 9;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.x = p_player->GetPosition().x + cosf(angle) * distance;
		spawnpoint.y = 0.75f;
		spawnpoint.z = p_player->GetPosition().z + sinf(angle) * distance;

		LevelThreeEnemy* enemy = Manager::GetScene()->AddGameObject<LevelThreeEnemy>();
		enemy->Init();
		enemy->SetPosition(spawnpoint);
		AddEnemy(enemy);
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
		int distance = rd() % 30 + 16;
		//int distance = rd() % 15 + 10;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.x = p_player->GetPosition().x + cosf(angle) * distance;
		spawnpoint.y = 0.75f;
		spawnpoint.z = p_player->GetPosition().z + sinf(angle) * distance;

		LevelFourEnemy* enemy = Manager::GetScene()->AddGameObject<LevelFourEnemy>();
		enemy->Init();
		enemy->SetPosition(spawnpoint);
		AddEnemy(enemy);
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
		int distance = rd() % 30 + 18;
		//int distance = rd() % 15 + 11;
		float angle = randangle(mt);

		Vector3 spawnpoint;
		spawnpoint.x = p_player->GetPosition().x + cosf(angle) * distance;
		spawnpoint.y = 0.75f;
		spawnpoint.z = p_player->GetPosition().z + sinf(angle) * distance;

		LevelFiveEnemy* enemy = Manager::GetScene()->AddGameObject<LevelFiveEnemy>();
		enemy->Init();
		enemy->SetPosition(spawnpoint);
		AddEnemy(enemy);
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
		spawnpoint.x = p_player->GetPosition().x + cosf(angle) * distance;
		spawnpoint.y = 0.75f;
		spawnpoint.z = p_player->GetPosition().z + sinf(angle) * distance;

		GameEnderEnemy* enemy = Manager::GetScene()->AddGameObject<GameEnderEnemy>();
		enemy->Init();
		enemy->SetPosition(spawnpoint);
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

//********************************************************************************
//関数
//********************************************************************************
EnemyManager::EnemyManager(GameTimer* timer)
{
	m_pGameTimer = timer;
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	for (int tag = ENEMY_RED; tag < SHOOTER_ENEMY_RED; tag++)
	{
		map_Enemies[(ModelTags)tag] = EnemyInstanceGroup();

		auto& inst = map_Enemies[(ModelTags)tag];

		//エネミーの最大保持数確保...最大数以上に敵を追加させないようにコード追加
		inst.Enemies.reserve(ENEMY_MAX_NUM);
		inst.SendingData.reserve(ENEMY_MAX_NUM);

		//バッファの作成
		D3D11_BUFFER_DESC desc{};
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(InstanceData) * ENEMY_MAX_NUM;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &inst.InstanceBuffer);

		assert(inst.InstanceBuffer != nullptr);

		switch (tag)
		{
		case ENEMY_SILVER:
			inst.ShaderInfo = SHADER_INSTANCE_BLINNPHONG;
			break;
		default:
			inst.ShaderInfo = SHADER_INSTANCE_TOON;
			break;
		}

	}
}

void EnemyManager::Uninit()
{
	for (auto& itr : map_Enemies)
	{
		EnemyInstanceGroup& inst = itr.second;
		
		inst.InstanceBuffer->Release();
		inst.Enemies.clear();
	}
}

void EnemyManager::AddEnemy(BaseEnemy* enemy)
{
	auto& inst = map_Enemies[enemy->GetModelTag()];
	inst.Enemies.push_back(enemy);

	////エネミーの情報を登録
	//for (auto& itr : map_Enemies)
	//{
	//	auto tag = itr.first;
	//	EnemyInstanceGroup& inst = itr.second;

	//	if (tag == enemy->GetModelTag())
	//	{
	//		inst.Enemies.push_back(enemy);
	//	}
	//}
}

void EnemyManager::UpdateInstanceBuffer(EnemyInstanceGroup& group)
{//ドローの直前で更新する

	//もしエネミーが死んでるor死ぬ予定なら消す
	group.Enemies.erase
	(
		std::remove_if
		(
			group.Enemies.begin(),
			group.Enemies.end(),
			[](BaseEnemy* enemy)
			{
				return enemy == nullptr || enemy->GetDestroy();
			}
		),
		group.Enemies.end()
	);

	group.SendingData.clear();

	std::vector<BaseAttack*> p_attacks = Manager::GetScene()->GetGameObjects<BaseAttack>();

	for (auto& itr : group.Enemies)
	{
		InstanceData inst{};
		inst.Position = { itr->GetPosition().x , itr->GetPosition().y , itr->GetPosition().z , 1.0f};
		inst.Rotation = { itr->GetRotation().x , itr->GetRotation().y , itr->GetRotation().z , 0.0f};
		inst.Scale = { itr->GetScale().x , itr->GetScale().y , itr->GetScale().z , 1.0f};

		itr->UpdateAttacks(p_attacks);

		group.SendingData.push_back(inst);
	}

	//もし送るデータが無ければ戻る
	if (group.SendingData.empty()) return;

	D3D11_MAPPED_SUBRESOURCE mapped{};
	HRESULT hr = Renderer::GetDeviceContext()->Map(group.InstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);

	assert(SUCCEEDED(hr));

	memcpy(mapped.pData, group.SendingData.data(), sizeof(InstanceData) * group.SendingData.size());

	Renderer::GetDeviceContext()->Unmap(group.InstanceBuffer, 0);

	assert(!group.SendingData.empty());

}

void EnemyManager::Update()
{
	for (auto& itr : map_Enemies)
	{
		EnemyInstanceGroup& inst = itr.second;

		UpdateInstanceBuffer(inst);
	}
}

void EnemyManager::Draw()
{
	for (auto& itr : map_Enemies)
	{
		ModelTags tag = itr.first;
		EnemyInstanceGroup& inst = itr.second;

		//インスタンスが無ければ処理を飛ばす
		if (inst.SendingData.empty()) continue;

		assert(!inst.SendingData.empty());

		
		{//通常のインスタンス描画
			ModelManager::SetShaders(tag, inst.ShaderInfo);

			//残りのドロー処理をここに書く
			UINT strides[2] = { sizeof(VERTEX_3D) , sizeof(InstanceData) };
			UINT offsets[2] = { 0 , 0 };

			MODEL* model = ModelManager::GetModelRenderers(tag)->GetModel();

			assert(model->VertexBuffer != nullptr);
			assert(model->IndexBuffer != nullptr);

			ID3D11Buffer* buffers[2]{ model->VertexBuffer , inst.InstanceBuffer };

			Renderer::GetDeviceContext()->IASetVertexBuffers(0, 2, buffers, strides, offsets);

			

			Renderer::GetDeviceContext()->IASetIndexBuffer(model->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

			Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


			for (int i = 0; i < model->SubsetNum; i++)
			{
				assert(model->SubsetArray[i].IndexNum > 0);

				//マテリアルの固定
				Renderer::SetMaterial(model->SubsetArray[i].Material.Material);

				//実際の描画
				Renderer::GetDeviceContext()->DrawIndexedInstanced(model->SubsetArray[i].IndexNum, inst.SendingData.size(), model->SubsetArray[i].StartIndex, 0, 0);
			}
		}

		{//エッジのインスタンス描画
			ModelManager::SetShaders(tag, SHADER_INSTANCE_EDGE);

			//残りのドロー処理をここに書く
			UINT strides[2] = { sizeof(VERTEX_3D) , sizeof(InstanceData) };
			UINT offsets[2] = { 0 , 0 };

			Renderer::SetCullMode(D3D11_CULL_FRONT);

			MODEL* model = ModelManager::GetModelRenderers(tag)->GetModel();

			assert(model->VertexBuffer != nullptr);
			assert(model->IndexBuffer != nullptr);

			ID3D11Buffer* buffers[2]{ model->VertexBuffer , inst.InstanceBuffer };

			Renderer::GetDeviceContext()->IASetVertexBuffers(0, 2, buffers, strides, offsets);

			Renderer::GetDeviceContext()->IASetIndexBuffer(model->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

			Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			for (int i = 0; i < model->SubsetNum; i++)
			{
				assert(model->SubsetArray[i].IndexNum > 0);

				//マテリアルの固定
				Renderer::SetMaterial(model->SubsetArray[i].Material.Material);

				//実際の描画
				Renderer::GetDeviceContext()->DrawIndexedInstanced(model->SubsetArray[i].IndexNum, inst.SendingData.size(), model->SubsetArray[i].StartIndex, 0, 0);
			}

			Renderer::SetCullMode(D3D11_CULL_BACK);

		}

	}
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

//--------別途のドロー処理（確認用）
//for (auto test : inst.Enemies)
//{
//	if (test->GetDestroy())continue;

//	ModelManager::SetShaders(tag, test->GetShader());

//	//平行移動行列の作成（表示座標を決める）
//	XMMATRIX	TranslationMatrix = XMMatrixTranslation(test->GetPosition().x, test->GetPosition().y, test->GetPosition().z);

//	//回転行列（Z回転）行列の作成
//	XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(test->GetRotation().x, test->GetRotation().y, test->GetRotation().z);

//	//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
//	XMMATRIX	ScalingMatrix = XMMatrixScaling(test->GetScale().x, test->GetScale().y, test->GetScale().z);

//	//ワールド行列の作成（ポリゴンの表示の仕方を指定する最終的な行列
//	XMMATRIX	WorldMatrix = ScalingMatrix * RotationMatrix * TranslationMatrix;

//	//マテリアル設定
//	MATERIAL material{};
//	material.Diffuse = { 1.0f , 1.0f , 1.0f , 1.0f };
//	material.TextureEnable = false;
//	Renderer::SetMaterial(material);



//	Renderer::SetWorldMatrix(WorldMatrix);

//	ModelManager::ModelDraw(tag);

//	//UINT strides = sizeof(VERTEX_3D);
//	//UINT offsets = 0;

//	//MODEL* model = ModelManager::GetModelRenderers(tag)->GetModel();

//	//assert(model->VertexBuffer != nullptr);
//	//assert(model->IndexBuffer != nullptr);

//	////ID3D11Buffer* buffers[2]{ model->VertexBuffer , inst.InstanceBuffer };

//	//Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &model->VertexBuffer, &strides, &offsets);
//	////Renderer::GetDeviceContext()->IASetVertexBuffers(0, 2, buffers, strides, offsets);

//	//Renderer::GetDeviceContext()->IASetIndexBuffer(model->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

//	//Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

//	//for (int i = 0; i < model->SubsetNum; i++)
//	//{
//	//	assert(model->SubsetArray[i].IndexNum > 0);

//	//	//マテリアルの固定
//	//	Renderer::SetMaterial(model->SubsetArray[i].Material.Material);

//	//	Renderer::GetDeviceContext()->DrawIndexed(model->SubsetArray[i].IndexNum, model->SubsetArray[i].StartIndex, 0);
//	//}
//}