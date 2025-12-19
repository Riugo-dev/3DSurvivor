//********************************************************************************
//
// enemy_bullet.h[敵の弾の基底クラス]
//
//															Author :Riugo Honda
//															Date   :2025/10/06
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "game.h"
#include "attackbase.h"
#include "player.h"
#include "camera.h"
#include "hp_ui.h"
#include "result.h"
#include "fade.h"
#include <vector>

#include "enemy_bullet.h"

EnemyBullet::EnemyBullet()
{
	m_ModelTag = BULLET;
	m_Shader = SHADER_BLINNPHONG;

	m_Scale = { 1.0f , 1.0f , 1.0f };
	m_Position = { 0.0f , 0.0f , 0.0f };
	m_Velocity = { 0.0f , 0.0f , 0.0f };
	m_LivingFrame = 0;
	m_LifeTime = 120;
	m_Hp = 1;

}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Init(Input*)
{
}

void EnemyBullet::Uninit()
{
}

void EnemyBullet::Update()
{
	m_Position += m_Velocity;

	std::vector<BaseAttack*> p_attacks = Manager::GetScene()->GetGameObjects<BaseAttack>();

	for (auto itr : p_attacks)
	{
		if (itr->GetDestroy())continue;

		/*Vector3 d = itr->GetPosition() - m_Position;
		float length = d.length();*/
		if (itr->CircleCollider(m_Position, m_Radius))
		{
			m_Hp -= itr->GetStrength();
			itr->SubtractHP();
			if (itr->GetAttackHP() <= 0) itr->SetDestroy(true);

			if (m_Hp <= 0)
			{
				m_IsDestroy = true;
			}


			return;
		}
	}
	
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	Vector3 to_player = (p_player->GetPosition() - m_Position).normalized();

	Vector3 distance = p_player->GetPosition() - m_Position;
	float length = distance.length();

	if (length < 1.3f)
	{
		if (!p_player->GetIsInvincible())
		{
			p_player->SetInvincibilty(true);
			Manager::GetScene()->GetGameObject<HPUI>()->SubtractHP();
			Manager::GetScene()->GetGameObject<Camera>()->CameraShake({ 0.0f, 0.3f , 0.0f });
			m_IsDestroy = true;

			if (Manager::GetScene()->GetGameObject<HPUI>()->GetHP() <= 0)
			{
				Manager::SetScene<Result>();
				Manager::GetScene()->GetGameObject<Fade>()->SetFade(FADE_OUT);
				Game::SetGameState(GAME_FADEOUT);
			}

			return;
		}
	}


	m_LivingFrame++;

	if (m_LivingFrame >= m_LifeTime)
	{
		m_IsDestroy = true;
	}
}

void EnemyBullet::Draw()
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
}

void EnemyBullet::SetBullet(Vector3 speed)
{
	m_Velocity = speed;
}
