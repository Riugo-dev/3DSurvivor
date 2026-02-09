//********************************************************************************
//
// shurikenattack.cpp[球攻撃の管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/13
//********************************************************************************
#include "main.h"
#include "player.h"
#include "camera.h"
#include "manager.h"
#include "scene.h"
#include "attackbase_shuriken.h"

#include "shurikenattack.h"

//********************************************************************************
//マクロ定義
//********************************************************************************
#define COOLDOWN_LEVELONE (120)
#define COOLDOWN_LEVELTWO (120)
#define COOLDOWN_LEVELTHREE (90)
#define COOLDOWN_LEVELFOUR (90)
#define COOLDOWN_LEVELMAX (60)

//********************************************************************************
//関数
//********************************************************************************

ShurikenAttack::ShurikenAttack()
{
	m_AttackLevel = ATT_LVNONE;
	m_FrameCount = 0;
}

void ShurikenAttack::Update()
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

			Vector3 pos = player->GetPosition();

			BaseAttackShuriken* shuriken = Manager::GetScene()->AddGameObject<BaseAttackShuriken>();
			shuriken->SetLivingFrames(60);
			shuriken->SetShuriken(2.0f, 0.1f, pos, 0.0f);
			shuriken->SetAttackHP(2);
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

				BaseAttackShuriken* shuriken = Manager::GetScene()->AddGameObject<BaseAttackShuriken>();
				shuriken->SetLivingFrames(60);
				shuriken->SetShuriken(2.0f, 0.1f, pos, i * (XM_2PI / 2));
				shuriken->SetAttackHP(2);
			}
		}
	}
	break;
	case ATT_LV3:
	{
		if (m_FrameCount % COOLDOWN_LEVELTHREE == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				//プレイヤーの向いてる方向に合わせて弾の発射位置を変える・・・カメラ基準にすればよい
				Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();
				Player* player = Manager::GetScene()->Scene::GetGameObject<Player>();

				Vector3 pos = player->GetPosition();

				BaseAttackShuriken* shuriken = Manager::GetScene()->AddGameObject<BaseAttackShuriken>();
				shuriken->SetLivingFrames(60);
				shuriken->SetShuriken(2.0f, 0.1f, pos, i * (XM_2PI / 3));
				shuriken->SetAttackHP(2);
			}
		}
	}
	break;
	case ATT_LV4:
	{
		if (m_FrameCount % COOLDOWN_LEVELFOUR == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				//プレイヤーの向いてる方向に合わせて弾の発射位置を変える・・・カメラ基準にすればよい
				Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();
				Player* player = Manager::GetScene()->Scene::GetGameObject<Player>();

				Vector3 pos = player->GetPosition();

				BaseAttackShuriken* shuriken = Manager::GetScene()->AddGameObject<BaseAttackShuriken>();
				shuriken->SetLivingFrames(60);
				shuriken->SetShuriken(2.0f, 0.1f, pos, i * (XM_2PI / 4));
				shuriken->SetAttackHP(3);
			}
		}
	}
	break;
	case ATT_LV5:
	{
		if (m_FrameCount % COOLDOWN_LEVELMAX == 0)
		{
			for (int i = 0; i < 5; i++)
			{
				//プレイヤーの向いてる方向に合わせて弾の発射位置を変える・・・カメラ基準にすればよい
				Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();
				Player* player = Manager::GetScene()->Scene::GetGameObject<Player>();

				Vector3 pos = player->GetPosition();

				BaseAttackShuriken* shuriken = Manager::GetScene()->AddGameObject<BaseAttackShuriken>();
				shuriken->SetLivingFrames(60);
				shuriken->SetShuriken(2.0f, 0.2f, pos, i * (XM_2PI / 5));
				shuriken->SetAttackHP(4);
			}
		}
	}
	break;
	case ATT_LVMAX:
	{
		if (m_FrameCount % COOLDOWN_LEVELMAX == 0)
		{
			for (int i = 0; i < 6; i++)
			{
				//プレイヤーの向いてる方向に合わせて弾の発射位置を変える・・・カメラ基準にすればよい
				Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();
				Player* player = Manager::GetScene()->Scene::GetGameObject<Player>();

				Vector3 pos = player->GetPosition();

				BaseAttackShuriken* shuriken = Manager::GetScene()->AddGameObject<BaseAttackShuriken>();
				shuriken->SetLivingFrames(60);
				shuriken->SetShuriken(2.0f, 0.2f, pos, i * (XM_2PI / 6));
				shuriken->SetAttackHP(5);
			}
		}
	}
	break;
	default:
		break;
	}

	m_FrameCount++;

}

void ShurikenAttack::SetToNextLevel()
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