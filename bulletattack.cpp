//********************************************************************************
//
// bulletattack.cpp[球攻撃の管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/13
//********************************************************************************
#include "main.h"
#include "player.h"
#include "camera.h"
#include "manager.h"
#include "scene.h"
#include "attackbase_bullet.h"

#include "bulletattack.h"

//********************************************************************************
//マクロ定義
//********************************************************************************
#define COOLDOWN_LEVELONE (60)
#define COOLDOWN_LEVELTWO (60)
#define COOLDOWN_LEVELTHREE (45)
#define COOLDOWN_LEVELFOUR (45)
#define COOLDOWN_LEVELMAX (30)

//********************************************************************************
//関数
//********************************************************************************

BulletAttack::BulletAttack()
{
	m_AttackLevel = ATT_LVNONE;
	m_FrameCount = 0;
}

void BulletAttack::Update()
{
	switch (m_AttackLevel)
	{
	case ATT_LV1:
	{
		if (m_FrameCount % COOLDOWN_LEVELONE == 0)
		{
			//プレイヤーの向いてる方向に合わせて弾の発射位置を変える・・・カメラ基準にすればよい
			Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();
			Player* player = Manager::GetScene()->Scene::GetGameObject<Player>();

			Vector3 pos = player->GetPosition() + (p_camera->GetFoward() * 0.05f);
			pos.y += 0.5f;

			Vector3 vel = p_camera->GetFoward() * 0.5f;

			BaseAttackBullet* bullet = Manager::GetScene()->AddGameObject<BaseAttackBullet>();
			bullet->SetPosition(pos);
			bullet->SetVelocity(vel);
			bullet->SetLivingFrames(60);
		}
	}
		break;
	case ATT_LV2:
	{
		if (m_FrameCount % COOLDOWN_LEVELTWO == 0)
		{
			for (int i = 0; i < 2; i++)
			{
				//プレイヤーの向いてる方向に合わせて弾の発射位置を変える・・・カメラ基準にすればよい
				Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();
				Player* player = Manager::GetScene()->Scene::GetGameObject<Player>();


				Vector3 pos = player->GetPosition();
				pos.y += 0.5f;
				pos += player->GetRight().normalized() * i * 1.25f;

				Vector3 vel = p_camera->GetFoward() * 0.5f;

				BaseAttackBullet* bullet = Manager::GetScene()->AddGameObject<BaseAttackBullet>();
				bullet->SetPosition(pos);
				bullet->SetVelocity(vel);
				bullet->SetLivingFrames(60);
			}
		}
	}
		break;
	case ATT_LV3:
	{
		if (m_FrameCount % COOLDOWN_LEVELTHREE == 0)
		{
			for (int i = -1; i < 2; i++)
			{
				//プレイヤーの向いてる方向に合わせて弾の発射位置を変える・・・カメラ基準にすればよい
				Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();
				Player* player = Manager::GetScene()->Scene::GetGameObject<Player>();

				Vector3 pos = player->GetPosition();
				pos.y += 0.5f;
				pos += player->GetRight().normalized() * i * 1.25f;

				Vector3 vel = p_camera->GetFoward() * 0.5f;

				BaseAttackBullet* bullet = Manager::GetScene()->AddGameObject<BaseAttackBullet>();
				bullet->SetPosition(pos);
				bullet->SetVelocity(vel);
				bullet->SetLivingFrames(60);
			}
		}
	}
		break;
	case ATT_LV4:
	{
		if (m_FrameCount % COOLDOWN_LEVELFOUR == 0)
		{
			for (int i = -1; i < 3; i++)
			{
				//プレイヤーの向いてる方向に合わせて弾の発射位置を変える・・・カメラ基準にすればよい
				Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();
				Player* player = Manager::GetScene()->Scene::GetGameObject<Player>();


				Vector3 pos = player->GetPosition();
				pos.y += 0.5f;
				pos += player->GetRight().normalized() * i * 1.25f;

				Vector3 vel = p_camera->GetFoward() * 0.5f;

				BaseAttackBullet* bullet = Manager::GetScene()->AddGameObject<BaseAttackBullet>();
				bullet->SetPosition(pos);
				bullet->SetVelocity(vel);
				bullet->SetLivingFrames(60);
			}
		}
	}
		break;
	case ATT_LV5:
	{
		if (m_FrameCount % COOLDOWN_LEVELMAX == 0)
		{
			for (int i = -2; i < 3; i++)
			{
				//プレイヤーの向いてる方向に合わせて弾の発射位置を変える・・・カメラ基準にすればよい
				Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();
				Player* player = Manager::GetScene()->Scene::GetGameObject<Player>();

				Vector3 pos = player->GetPosition();
				pos.y += 0.5f;
				pos += player->GetRight().normalized() * i * 1.25f;

				Vector3 vel = p_camera->GetFoward() * 0.5f;

				BaseAttackBullet* bullet = Manager::GetScene()->AddGameObject<BaseAttackBullet>();
				bullet->SetPosition(pos);
				bullet->SetVelocity(vel);
				bullet->SetLivingFrames(60);
			}
		}
	}
		break;
	case ATT_LVMAX:
	{
		if (m_FrameCount % COOLDOWN_LEVELMAX == 0)
		{
			for (int i = -3; i < 4; i++)
			{
				//プレイヤーの向いてる方向に合わせて弾の発射位置を変える・・・カメラ基準にすればよい
				Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();
				Player* player = Manager::GetScene()->Scene::GetGameObject<Player>();

				Vector3 pos = player->GetPosition();
				pos.y += 0.5f;
				pos += player->GetRight().normalized() * i * 1.25f;

				Vector3 vel = p_camera->GetFoward() * 0.5f;

				BaseAttackBullet* bullet = Manager::GetScene()->AddGameObject<BaseAttackBullet>();
				bullet->SetPosition(pos);
				bullet->SetVelocity(vel);
				bullet->SetLivingFrames(60);
			}
		}
	}
		break;
	defualt:
		break;
	}

	m_FrameCount++;

}

void BulletAttack::SetToNextLevel()
{
	switch (m_AttackLevel)
	{
	case ATT_LVNONE:
		m_AttackLevel = ATT_LV1;
		break;
	case ATT_LV1:
		m_AttackLevel = ATT_LV2;
		break;
	case ATT_LV2:
		m_AttackLevel = ATT_LV3;
		break;
	case ATT_LV3:
		m_AttackLevel = ATT_LV4;
		break;
	case ATT_LV4:
		m_AttackLevel = ATT_LV5;
		break;
	case ATT_LV5:
		m_AttackLevel = ATT_LVMAX;
		break;
	case ATT_LVMAX:
		break;
	}
}
