//********************************************************************************
//
// shooterenemybase.h[射撃敵の基底クラス]
//
//															Author :Riugo Honda
//															Date   :2025/10/05
//********************************************************************************
#ifndef _SHOOTERENEMYBASE_H_
#define _SHOOTERENEMYBASE_H_

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
#include "enemy_bullet.h"
#include <vector>

#define ENEMY_LIVINGFRAME (7200) //約 120 秒

class ShooterBaseEnemy : public GameObject
{
protected:


	//ModelRenderer* m_pModelRenderer = nullptr;

	int m_HP;
	int m_ShotCoolDown = 120;
	int m_Points;
	ModelTags m_ModelTag;
	Shader m_Shader;
	int m_FrameCount = 0;
	bool m_GetBig = false;
	float m_Speed = 0.5f;
	const float m_Radius = 0.9f;
public:
	~ShooterBaseEnemy() = default;

	void Init(Input*) override {};
	void Uninit() override {};

	//アップデートも基本プレイヤーを追いかけるだけなので基本的にここで一括でいい
	void Update() override
	{
		if (!m_GetBig)
		{
			m_Scale += {0.03f, 0.03f, 0.03f};

			if (m_Scale.m_x >= 0.6f)
			{
				m_Scale = { 0.6f , 0.6f , 0.6f };
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
					boom->SetScale({ 0.1f , 0.1f , 0.1f });

					Manager::GetScene()->GetGameObject<Score>()->AddPoints(m_Points);
					m_IsDestroy = true;
					EnemyItemDrop();


					return;
				}
			}
		}



		Player* p_player = Manager::GetScene()->GetGameObject<Player>();

		Vector3 to_player = (p_player->GetPosition() - m_Position).normalized();

		float angle_y, angle_x, angle_z;

		angle_y = atan2(to_player.m_x, to_player.m_z);

		m_Rotation.m_y = angle_y;
		Vector3 distance = p_player->GetPosition() - m_Position;
		float length = distance.length();

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

		if ( m_FrameCount % m_ShotCoolDown == 0)
		{

			to_player *= m_Speed;
			to_player.m_y = 0.0f;
			//エネミーの弾射出コードをここに書く
			EnemyBullet* bullet = Manager::GetScene()->AddGameObject<EnemyBullet>();
			bullet->SetPosition({m_Position.m_x , 1.25f , m_Position.m_z});
			bullet->SetBullet(to_player);
		}

		if (m_FrameCount >= ENEMY_LIVINGFRAME)
		{
			m_IsDestroy = true;
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


	void DamageEnemy(int damage)
	{
		m_HP -= damage;
	}
	int GetEnemyHp() { return m_HP; }

	virtual void EnemyItemDrop() = 0;

};


#endif // !_SHOOTERENEMYBASE_H_
