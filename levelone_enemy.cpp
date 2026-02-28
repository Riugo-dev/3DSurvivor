//********************************************************************************
//
// levelone_enemy.h[レベル１敵クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************
#include "main.h"
#include <random>
#include "lowtier_exp_item.h"
#include "exp_item_manager.h"
#include "attackbase.h"
#include "player.h"
#include "camera.h"
#include "score.h"
#include "hp_ui.h"
#include "explosion_particle.h"
#include "result.h"
#include "game.h"
#include "fade.h"
#include "enemy_manager.h"
#include "manager_soundeffect.h"
#include "explosion_gpuparticle.h"
#include "enemydamage_ui.h"
#include <vector>


#include "levelone_enemy.h"


LevelOneEnemy::~LevelOneEnemy()
{
	
}

void LevelOneEnemy::Init()
{
	m_Scale = { 0.05f , 0.05f , 0.05f };

	//m_Shader = SHADER_TOON;
	m_Shader = SHADER_INSTANCE_TOON;

	m_HP = 1 * 60;
	m_EnemySpeed = 0.01f;
	m_Points = 100;
	m_ModelTag = ENEMY_RED;

	m_pPlayer = Manager::GetScene()->GetGameObject<Player>();

}

void LevelOneEnemy::Uninit()
{
	m_pPlayer = nullptr;
	m_Attacks.clear();
}

void LevelOneEnemy::Update()
{
	if (!m_GetBig)
	{
		m_Scale += {0.025f , 0.025f , 0.025f};

		if (m_Scale.x >= 0.5f)
		{
			m_Scale = {0.5f , 0.5f , 0.5f};
			m_GetBig = true;
		}

		return;
	}

	if (m_IsDestroy)return;
	
	//std::vector<BaseAttack*> p_attacks = Manager::GetScene()->GetGameObjects<BaseAttack>();

	for (auto itr : m_Attacks)
	{
		if (itr->GetDestroy())continue;

		/*Vector3 d = itr->GetPosition() - m_Position;
		float length = d.length();*/


		if (itr->CircleCollider(m_Position , m_Radius))
		{
			m_HP -= itr->GetStrength();
			itr->SubtractHP();
			EnemyDamageUI::GetInstance()->SpawnDamageUI(itr->GetStrength(), m_Position);
			if (itr->GetAttackHP() <= 0) itr->SetDestroy(true);

			if(m_HP <= 0)
			{
				/*ExplosionParticle* boom = Manager::GetScene()->AddGameObject<ExplosionParticle>(2);
				boom->SetPosition(m_Position);
				boom->SetScale({ 0.1f , 0.1f , 0.1f });*/

				GPUExplosionParticle::GetInstance()->SpawnExplosion(m_Position);

				Manager::GetScene()->GetGameObject<Score>()->AddPoints(m_Points);
				m_IsDestroy = true;
				EnemyItemDrop();

				Manager::GetSoundEffect()->PlaySE(SE_ENEMYDAMAGE);

				return;
			}


		}
	}

	

	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	Vector3 to_player = (p_player->GetPosition() - m_Position).normalized();

	m_Position = m_Position + to_player * m_EnemySpeed;

	float angle_y, angle_x, angle_z;


	angle_y = atan2(to_player.x, to_player.z);
	/*angle_x = atan2(to_player.y, to_player.z);
	angle_z = atan2(to_player.x, to_player.y);*/

	m_Rotation.y = angle_y;
	/*m_Rotation.x = angle_x;
	m_Rotation.z = angle_z;*/


	Vector3 distance = p_player->GetPosition() - m_Position;
	float length = distance.length();

	if (length < m_Scale.y * 2.5f)
	{
		if(!p_player->GetIsInvincible())
		{
			p_player->SetInvincibilty(true);
			Manager::GetScene()->GetGameObject<HPUI>()->SubtractHP();
			Manager::GetScene()->GetGameObject<Camera>()->CameraShake({ 1.0f, 1.0f , 1.0f });

			if (Manager::GetScene()->GetGameObject<HPUI>()->GetHP() <= 0)
			{
				Manager::SetScene<Result>();
				Manager::GetScene()->GetGameObject<Fade>()->SetFade(FADE_OUT);
				Game::SetGameState(GAME_FADEOUT);
			}
		}
	}

	m_FrameCount++;
	if (m_FrameCount >= ENEMY_LIVINGFRAME)
	{
		m_IsDestroy = true;
	}
}

void LevelOneEnemy::Draw()
{
	//Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	//Vector3 vector = p_player->GetPosition() - m_Position;
	//float length = vector.length();

	//if (length > 30) return;

	//{//通常の描画
	//	ModelManager::SetShaders(m_ModelTag, m_Shader);

	//	//平行移動行列の作成（表示座標を決める）
	//	XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	//	//回転行列（Z回転）行列の作成
	//	XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

	//	//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
	//	XMMATRIX	ScalingMatrix = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);

	//	//ワールド行列の作成（ポリゴンの表示の仕方を指定する最終的な行列
	//	XMMATRIX	WorldMatrix = ScalingMatrix * RotationMatrix * TranslationMatrix;

	//	//マテリアル設定
	//	MATERIAL material{};
	//	material.Diffuse = { 1.0f , 1.0f , 1.0f , 1.0f };
	//	material.TextureEnable = false;
	//	Renderer::SetMaterial(material);



	//	Renderer::SetWorldMatrix(WorldMatrix);

	//	//m_pModelRenderer->Draw();
	//	ModelManager::ModelDraw(m_ModelTag);
	//}


	//{//輪郭線の描画
	//	ModelManager::SetShaders(m_ModelTag, SHADER_TOONEDGE);


	//	Renderer::SetCullMode(D3D11_CULL_FRONT);

	//	//描画
	//	//m_pModelRenderer->Draw();
	//	ModelManager::ModelDraw(m_ModelTag);

	//	Renderer::SetCullMode(D3D11_CULL_BACK);
	//}
}

void LevelOneEnemy::EnemyItemDrop()
{
	std::random_device rd;
	int drop = rd() % 100 + 1;

	if (drop <= 80)
	{
		LowTierExpItem* item =  Manager::GetScene()->AddGameObject<LowTierExpItem>();
		item->Init();
		item->SetPosition({ m_Position.x , 1.0f , m_Position.z });
		ExpItemManager::GetInstance()->AddExpItem(item);
	}
}
