//********************************************************************************
//
// levelone_midboss.h[レベル１敵クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/11
//********************************************************************************
#include "main.h"
#include <random>
#include "hightier_exp_item.h"
#include "exp_item_manager.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "attackbase.h"
#include "player.h"
#include "camera.h"
#include "score.h"
#include "hp_ui.h"
#include "explosion_particle.h"
#include "result.h"
#include "game.h"
#include "fade.h"
#include "manager_soundeffect.h"
#include <vector>

#include "levelone_midboss.h"


LevelOneMidBoss::~LevelOneMidBoss()
{
}

void LevelOneMidBoss::Init()
{
	m_Scale = { 0.05f , 0.05f , 0.05f };

	m_Shader = SHADER_TOON;

	m_HP = 150 * 60;
	m_EnemySpeed = 0.5f;
	m_Points = 5000;
	m_ModelTag = MIDBOSS_RED;
	m_ChargeTime = 60 * 6;
	m_RotationSpeed = 0.0f;
}

void LevelOneMidBoss::Uninit()
{
}

void LevelOneMidBoss::Update()
{
	if (!m_GetBig)
	{
		m_Scale += {0.025f, 0.025f, 0.025f};

		if (m_Scale.x >= 0.75f)
		{
			m_Scale = { 0.75f , 0.75f , 0.75f };
			m_GetBig = true;
		}

		return;
	}

	if (m_IsDestroy)return;

	std::vector<BaseAttack*> p_attacks = Manager::GetScene()->GetGameObjects<BaseAttack>();

	for (auto itr : p_attacks)
	{
		if (itr->GetDestroy())continue;


		if (itr->CircleCollider(m_Position, m_Radius))
		{
			m_HP -= itr->GetStrength();
			itr->SubtractHP();
			if (itr->GetAttackHP() <= 0) itr->SetDestroy(true);

			if (m_HP <= 0)
			{
				ExplosionParticle* boom = Manager::GetScene()->AddGameObject<ExplosionParticle>(2);
				boom->SetPosition(m_Position);
				boom->SetScale({ 0.3f , 0.3f , 0.3f });

				Manager::GetSoundEffect()->PlaySE(SE_ENEMYDAMAGE);
				Manager::GetScene()->GetGameObject<Score>()->AddPoints(m_Points);
				m_IsDestroy = true;
				MidBossItemDrop();

				return;
			}
		}
	}

	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	Vector3 to_player = (p_player->GetPosition() - m_Position).normalized();
	Vector3 playerpos = p_player->GetPosition();
	Vector3 distance = p_player->GetPosition() - m_Position;
	float length = distance.length();

	switch (m_State)
	{
	case CHARGING:
	{
		Vector3 distance = p_player->GetPosition() - m_Position;
		distance.y = 0.0f;
		float length = distance.length();

		if (length > 40)
		{
			m_State = WARPING;
			return;
		}

		if (m_FrameCount % 15 == 0)
		{
			m_RotationSpeed += 0.04;

		}

		m_Rotation.y += m_RotationSpeed;

		if (length < m_Scale.y * 2.5f)
		{
			if (!p_player->GetIsInvincible())
			{
				p_player->SetInvincibilty(true);
				Manager::GetScene()->GetGameObject<HPUI>()->SubtractHP();
				Manager::GetScene()->GetGameObject<Camera>()->CameraShake({ 0.0f, 0.3f , 0.0f });

				if (Manager::GetScene()->GetGameObject<HPUI>()->GetHP() <= 0)
				{
					Manager::SetScene<Result>();
					Manager::GetScene()->GetGameObject<Fade>()->SetFade(FADE_OUT);
					Game::SetGameState(GAME_FADEOUT);
				}
			}
		}

		m_FrameCount++;

		if (m_FrameCount == m_ChargeTime)
		{
			m_State = DASHING;

			m_Velocity = distance.normalized();
			m_Velocity.y = 0.0f;

			m_EndPoint = p_player->GetPosition();
			m_EndPoint += (m_Velocity * m_EnemySpeed) * 2.0f;
		}
	}
	break;
	case DASHING:
	{
		Vector3 distance = p_player->GetPosition() - m_Position;
		float length = distance.length();

		if (length > 28)
		{
			m_IsPlayerFar = true;
		}

		bool hitwall = false;


		if (m_IsPlayerFar)
		{
			m_Rotation.y += m_RotationSpeed;

			m_Position += m_Velocity * m_EnemySpeed * 3.0f;
		}
		else
		{
			m_Rotation.y += m_RotationSpeed;

			m_Position += m_Velocity * m_EnemySpeed;
		}


		if (length < m_Scale.y * 2.5f)
		{
			if (!p_player->GetIsInvincible())
			{
				p_player->SetInvincibilty(true);
				Manager::GetScene()->GetGameObject<HPUI>()->SubtractHP(2);
				Manager::GetScene()->GetGameObject<Camera>()->CameraShake({ 0.0f, 0.3f , 0.0f });

				if (Manager::GetScene()->GetGameObject<HPUI>()->GetHP() <= 0)
				{
					Manager::SetScene<Result>();
					Manager::GetScene()->GetGameObject<Fade>()->SetFade(FADE_OUT);
					Game::SetGameState(GAME_FADEOUT);
				}
			}
		}

		if (m_DashingIn)
		{
			if (length < 16.0f)
			{
				m_DashingIn = false;
			}
		}
		else
		{
			Vector3 nextdistance = distance + (m_Velocity * m_EnemySpeed);
			float nextlength = nextdistance.length();

			if (nextlength > 16.0f)
			{
				hitwall = true;
			}
		}


		if (hitwall)
		{
			m_State = CHARGING;
			m_FrameCount = 0;
			m_Rotation.y = 0;
			m_RotationSpeed = 0;
			m_IsPlayerFar = false;
			m_DashingIn = true;
		}
	}
	break;
	case WARPING:
	{
		// (2) ランダムな画面端の前あたりに再配置

		Vector3 offset = { 0.0f, 0.0f , 0.0f };

		int side = rand() % 4;
		switch (side)
		{
		case 0: offset = { LIMIT_X - 2.0f, 0.0f, RandomFloat(-LIMIT_Z + 2.0f, LIMIT_Z - 2.0f) }; break; // 右
		case 1: offset = { -LIMIT_X + 2.0f, 0.0f, RandomFloat(-LIMIT_Z + 2.0f, LIMIT_Z - 2.0f) }; break; // 左
		case 2: offset = { RandomFloat(-LIMIT_X + 2.0f, LIMIT_X - 2.0f), 0.0f, LIMIT_Z - 2.0f }; break; // 上
		case 3: offset = { RandomFloat(-LIMIT_X + 2.0f, LIMIT_X - 2.0f), 0.0f, -LIMIT_Z + 2.0f }; break; // 下
		}

		m_Position = p_player->GetPosition() + offset;

		// (3) 再出現後の初期設定
		m_State = WALKING;
		m_FrameCount = 0;
		m_RotationSpeed = 0.0f;
		m_Velocity = (p_player->GetPosition() - m_Position).normalized();

		return; // 今フレームはここで終了
	}
	break;
	case WALKING:
	{
		m_Position = m_Position + to_player * m_EnemySpeed / 3;

		float angle_y, angle_x, angle_z;


		angle_y = atan2(to_player.x, to_player.z);


		m_Rotation.y = angle_y;


		Vector3 distance = p_player->GetPosition() - m_Position;
		float length = distance.length();

		if (length <= 6)
		{
			m_State = CHARGING;
			m_FrameCount = 0;
			m_Rotation.y = 0;
			m_RotationSpeed = 0;
		}
	}
	break;
	}
}

void LevelOneMidBoss::Draw()
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	Vector3 vector = p_player->GetPosition() - m_Position;
	float length = vector.length();

	if (length > 30) return;

	{//通常の描画
		ModelManager::SetShaders(m_ModelTag, m_Shader);

		//平行移動行列の作成（表示座標を決める）
		XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

		//回転行列（Z回転）行列の作成
		XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
		XMMATRIX	ScalingMatrix = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);

		//ワールド行列の作成（ポリゴンの表示の仕方を指定する最終的な行列
		XMMATRIX	WorldMatrix = ScalingMatrix * RotationMatrix * TranslationMatrix;

		//マテリアル設定
		MATERIAL material{};
		material.Diffuse = { 1.0f , 1.0f , 1.0f , 1.0f };
		material.TextureEnable = false;
		Renderer::SetMaterial(material);



		Renderer::SetWorldMatrix(WorldMatrix);

		//m_pModelRenderer->Draw();
		ModelManager::ModelDraw(m_ModelTag);
	}


	{//輪郭線の描画
		ModelManager::SetShaders(m_ModelTag, SHADER_TOONEDGE);


		Renderer::SetCullMode(D3D11_CULL_FRONT);

		//描画
		//m_pModelRenderer->Draw();
		ModelManager::ModelDraw(m_ModelTag);

		Renderer::SetCullMode(D3D11_CULL_BACK);
	}
}

void LevelOneMidBoss::MidBossItemDrop()
{
	std::random_device rd;
	int drop = rd() % 100 + 1;

	if (drop <= 20)
	{
		HighTierExpItem* item1 = Manager::GetScene()->AddGameObject<HighTierExpItem>();
		item1->Init();
		item1->SetPosition(m_Position + Vector3(0.25f, 0.5f, 0.0f));
		ExpItemManager::GetInstance()->AddExpItem(item1);

		HighTierExpItem* item2 = Manager::GetScene()->AddGameObject<HighTierExpItem>();
		item2->Init();
		item2->SetPosition(m_Position + Vector3(-0.25f, 0.5f, 0.0f));
		ExpItemManager::GetInstance()->AddExpItem(item2);
	}
	else
	{
		HighTierExpItem* item = Manager::GetScene()->AddGameObject<HighTierExpItem>();
		item->Init();
		item->SetPosition({ m_Position.x , 1.0f , m_Position.z });
		ExpItemManager::GetInstance()->AddExpItem(item);
	}
}
