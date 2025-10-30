//********************************************************************************
//
// midboss_base.h[中ボスの基底クラス]
//
//															Author :Riugo Honda
//															Date   :2025/10/12
//********************************************************************************

#ifndef _MIDBOSS_BASE_H_
#define _MIDBOSS_BASE_H_

#include "main.h"
#include "gameobject.h"
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
#include "model_manager.h"
#include "shader_manager.h"
#include "manager_soundeffect.h"
#include <vector>

enum MidBossState
{
	CHARGING = 0,
	DASHING,
	WARPING,
	WALKING,


};

#define LIMIT_X (18.0f)
#define LIMIT_Z (15.0f)

class BaseMidBoss : public GameObject
{
protected:
	int m_HP;
	int m_Points;
	ModelTags m_ModelTag;
	Shader m_Shader;
	int m_FrameCount = 0;
	bool m_GetBig = false;
	Vector3 m_Velocity = { 0.0f , 0.0f , 0.0f };
	float m_EnemySpeed = 0.03f;
	int m_ChargeTime;
	float m_RotationSpeed;
	Vector3 m_EndPoint;
	MidBossState m_State;
	bool m_IsPlayerFar = false;
	bool m_DashingIn = true;
	const float m_Radius = 1.5f;
public:
	~BaseMidBoss() = default;

	void Init(Input*) override {};
	void Uninit() override {};

	//アップデートも基本プレイヤーを追いかけるだけなので基本的にここで一括でいい
	void Update() override
	{
		if (!m_GetBig)
		{
			m_Scale += {0.025f, 0.025f, 0.025f};

			if (m_Scale.m_x >= 0.75f)
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
			distance.m_y = 0.0f;
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

			m_Rotation.m_y += m_RotationSpeed;

			if (length < m_Scale.m_y * 2.5f)
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
				m_Velocity.m_y = 0.0f;

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
				m_Rotation.m_y += m_RotationSpeed;

				m_Position += m_Velocity * m_EnemySpeed *3.0f;
			}
			else
			{
				m_Rotation.m_y += m_RotationSpeed;

				m_Position += m_Velocity * m_EnemySpeed;
			}
			

			if (length < m_Scale.m_y * 2.5f)
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
				m_Rotation.m_y = 0;
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
			m_Position = m_Position + to_player * m_EnemySpeed /3;

			float angle_y, angle_x, angle_z;


			angle_y = atan2(to_player.m_x, to_player.m_z);


			m_Rotation.m_y = angle_y;


			Vector3 distance = p_player->GetPosition() - m_Position;
			float length = distance.length();

			if (length <= 6)
			{
				m_State = CHARGING;
				m_FrameCount = 0;
				m_Rotation.m_y = 0;
				m_RotationSpeed = 0;
			}
		}
			break;
		}
	
	}


	//全て同じ処理でドローするのでここで一括で書く
	void Draw()	override
	{

		Player* p_player = Manager::GetScene()->GetGameObject<Player>();

		Vector3 vector = p_player->GetPosition() - m_Position;
		float length = vector.length();

		if (length > 30) return;

		{//通常の描画
			ModelManager::SetShaders(m_ModelTag, m_Shader);

			//平行移動行列の作成（表示座標を決める）
			XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.m_x, m_Position.m_y, m_Position.m_z);

			//回転行列（Z回転）行列の作成
			XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.m_x, m_Rotation.m_y, m_Rotation.m_z);

			//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
			XMMATRIX	ScalingMatrix = XMMatrixScaling(m_Scale.m_x, m_Scale.m_y, m_Scale.m_z);

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

	void SetVelocity(Vector3 vel) { m_Velocity = vel; }
	void SetSpeed(float speed) { m_EnemySpeed = speed; }

	void DamageEnemy(int damage)
	{
		m_HP -= damage;
	}
	int GetEnemyHp() { return m_HP; }

	virtual void MidBossItemDrop() = 0;

};

#endif // !_MIDBOSS_BASE_H_
