//********************************************************************************
//
// swarmenemybase.h[敵の基底クラス]
//
//															Author :Riugo Honda
//															Date   :2025/10/09
//********************************************************************************
#ifndef _SWARMENEMYBASE_H_
#define _SWARMENEMYBASE_H_

#include "main.h"
#include "gameobject.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "model_manager.h"
#include "shader_manager.h"


#define ENEMY_LIVINGFRAME (600) //約1０秒

class SwarmBaseEnemy : public GameObject
{
protected:


	//ModelRenderer* m_pModelRenderer = nullptr;

	int m_HP;
	float m_EnemySpeed = 0.03f;
	int m_Points;
	ModelTags m_ModelTag;
	Shader m_Shader;
	int m_FrameCount = 0;
	bool m_GetBig = false;
	Vector3 m_Velocity = { 0.0f , 0.0f , 0.0f };
	const float m_Radius = 0.6f;
public:
	~SwarmBaseEnemy() = default;

	virtual void Init() override {};
	virtual void Uninit() override {};

	//アップデートも基本プレイヤーを追いかけるだけなので基本的にここで一括でいい
	virtual void Update() override
	{
		/*if (!m_GetBig)
		{
			m_Scale += {0.025f, 0.025f, 0.025f};

			if (m_Scale.x >= 0.5f)
			{
				m_Scale = { 0.5f , 0.5f , 0.5f };
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
					Manager::GetSoundEffect()->PlaySE(SE_ENEMYDAMAGE);
					Manager::GetScene()->GetGameObject<Score>()->AddPoints(m_Points);
					m_IsDestroy = true;
					EnemyItemDrop();


					return;
				}
			}
		}

		m_Position += m_Velocity * m_EnemySpeed;

		Player* p_player = Manager::GetScene()->GetGameObject<Player>();

		Vector3 to_player = (p_player->GetPosition() - m_Position).normalized();

		Vector3 distance = p_player->GetPosition() - m_Position;
		float length = distance.length();

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
		if (m_FrameCount >= ENEMY_LIVINGFRAME)
		{
			m_IsDestroy = true;
		}*/
	}


	//全て同じ処理でドローするのでここで一括で書く
	virtual void Draw()	override
	{

		//Player* p_player = Manager::GetScene()->GetGameObject<Player>();

		//Vector3 vector = p_player->GetPosition() - m_Position;
		//float length = vector.length();

		//if (length > 30) return;

		//{//通常の描画
		//	ModelManager::SetShaders(m_ModelTag, m_Shader);

		//	//平行移動行列の作成（表示座標を決める）
		//	XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.m_x, m_Position.m_y, m_Position.m_z);

		//	//回転行列（Z回転）行列の作成
		//	XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.m_x, m_Rotation.m_y, m_Rotation.m_z);

		//	//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
		//	XMMATRIX	ScalingMatrix = XMMatrixScaling(m_Scale.m_x, m_Scale.m_y, m_Scale.m_z);

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

	void SetVelocity(Vector3 vel) { m_Velocity = vel; }
	void SetSpeed(float speed) { m_EnemySpeed = speed; }

	void DamageEnemy(int damage)
	{
		m_HP -= damage;
	}
	int GetEnemyHp() { return m_HP; }

	virtual void EnemyItemDrop() = 0;

};

#endif // !_ENEMYBASE_H_


