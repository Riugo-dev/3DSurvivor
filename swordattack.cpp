//********************************************************************************
//
// swordattack.cpp[球攻撃の管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/13
//********************************************************************************
#include "player.h"
#include "camera.h"
#include "manager.h"
#include "scene.h"
#include "attackbase_sword.h"
#include <random>

#include "swordattack.h"

//********************************************************************************
//マクロ定義
//********************************************************************************
#define COOLDOWN_LEVELONE (180)
#define COOLDOWN_LEVELTWO (120)
#define COOLDOWN_LEVELTHREE (120)
#define COOLDOWN_LEVELFOUR (90)
#define COOLDOWN_LEVELMAX (90)

//********************************************************************************
//関数
//********************************************************************************

SwordAttack::SwordAttack()
{
	m_AttackLevel = ATT_LVNONE;
	m_FrameCount = 0;
}

void SwordAttack::Update()
{
	switch (m_AttackLevel)
	{
	case ATT_LV1:
	{
		if (m_FrameCount % COOLDOWN_LEVELONE == 0)
		{
			for (int i = 0; i < 5; i++)
			{
				//プレイヤーの向いてる方向に合わせて弾の発射位置を変える・・・カメラ基準にすればよい
				Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();
				Player* player = Manager::GetScene()->Scene::GetGameObject<Player>();

				Vector3 pos = player->GetPosition();

				BaseAttackSword* sword = Manager::GetScene()->AddGameObject<BaseAttackSword>();

				std::random_device rd;
				int angle = rd() % 360;
				//angle = i * (XM_2PI / 2);
				//float angleXZ = angle * XM_2PI;

				Vector3 vel = { 0.5f , 0.0f , 0.5f };
				vel.m_x = cosf(angle) * vel.m_x;
				vel.m_z = sinf(angle) * vel.m_z;
				vel.m_y = 2.0f;
				//sword->SetScale({ 1.01f , 1.01f , 1.01f });
				sword->SetSword(vel, pos, 0.0f);
				sword->SetStrength(5 * 60);

			}
		}
	}
	break;
	case ATT_LV2:
	{
		if (m_FrameCount % COOLDOWN_LEVELTWO == 0)
		{
			for (int i = 0; i < 10; i++)
			{
				//プレイヤーの向いてる方向に合わせて弾の発射位置を変える・・・カメラ基準にすればよい
				Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();
				Player* player = Manager::GetScene()->Scene::GetGameObject<Player>();

				Vector3 pos = player->GetPosition();

				BaseAttackSword* sword = Manager::GetScene()->AddGameObject<BaseAttackSword>();

				std::random_device rd;
				int angle = rd() % 360;
				//angle = i * (XM_2PI / 2);
				//float angleXZ = angle * XM_2PI;

				Vector3 vel = { 0.5f , 0.0f , 0.5f };
				vel.m_x = cosf(angle) * vel.m_x;
				vel.m_z = sinf(angle) * vel.m_z;
				vel.m_y = 2.0f;
				//sword->SetScale({ 1.01f , 1.01f , 1.01f });
				sword->SetSword(vel, pos, 0.0f);
				sword->SetStrength(6 * 60);
			}
		}
	}
	break;
	case ATT_LV3:
	{
		if (m_FrameCount % COOLDOWN_LEVELTHREE == 0)
		{
			for (int i = 0; i < 15; i++)
			{
				//プレイヤーの向いてる方向に合わせて弾の発射位置を変える・・・カメラ基準にすればよい
				Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();
				Player* player = Manager::GetScene()->Scene::GetGameObject<Player>();

				Vector3 pos = player->GetPosition();

				BaseAttackSword* sword = Manager::GetScene()->AddGameObject<BaseAttackSword>();

				std::random_device rd;
				int angle = rd() % 360;
				//angle = i * (XM_2PI / 2);
				//float angleXZ = angle * XM_2PI;

				Vector3 vel = { 0.5f , 0.0f , 0.5f };
				vel.m_x = cosf(angle) * vel.m_x;
				vel.m_z = sinf(angle) * vel.m_z;
				vel.m_y = 2.0f;
				//sword->SetScale({ 1.01f , 1.01f , 1.01f });
				sword->SetSword(vel, pos, 0.0f);
				sword->SetStrength(7 * 60);
			}
		}
	}
	break;
	case ATT_LV4:
	{
		if (m_FrameCount % COOLDOWN_LEVELFOUR == 0)
		{
			for (int i = 0; i < 20; i++)
			{
				//プレイヤーの向いてる方向に合わせて弾の発射位置を変える・・・カメラ基準にすればよい
				Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();
				Player* player = Manager::GetScene()->Scene::GetGameObject<Player>();

				Vector3 pos = player->GetPosition();

				BaseAttackSword* sword = Manager::GetScene()->AddGameObject<BaseAttackSword>();

				std::random_device rd;
				int angle = rd() % 360;
				//angle = i * (XM_2PI / 2);
				//float angleXZ = angle * XM_2PI;

				Vector3 vel = { 0.5f , 0.0f , 0.5f };
				vel.m_x = cosf(angle) * vel.m_x;
				vel.m_z = sinf(angle) * vel.m_z;
				vel.m_y = 2.0f;
				//sword->SetScale({ 1.01f , 1.01f , 1.01f });
				sword->SetSword(vel, pos, 0.0f);
				sword->SetStrength(8 * 60);
			}
		}
	}
	break;
	case ATT_LVMAX:
	{
		if (m_FrameCount % COOLDOWN_LEVELMAX == 0)
		{
			for (int i = 0; i < 25; i++)
			{
				//プレイヤーの向いてる方向に合わせて弾の発射位置を変える・・・カメラ基準にすればよい
				Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();
				Player* player = Manager::GetScene()->Scene::GetGameObject<Player>();

				Vector3 pos = player->GetPosition();

				BaseAttackSword* sword = Manager::GetScene()->AddGameObject<BaseAttackSword>();

				std::random_device rd;
				int angle = rd() % 360;

				Vector3 vel = { 0.5f , 0.0f , 0.5f };
				vel.m_x = cosf(angle) * vel.m_x;
				vel.m_z = sinf(angle) * vel.m_z;
				vel.m_y = 2.0f;
				//sword->SetScale({ 1.01f , 1.01f , 1.01f });
				sword->SetSword(vel, pos, 0.0f);
				sword->SetStrength(9 * 60);
			}
		}
	}
	break;
	default:
		break;
	}

	m_FrameCount++;

}

void SwordAttack::SetToNextLevel()
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
		m_AttackLevel = ATT_LVMAX;
		break;
	case ATT_LVMAX:
		break;
	}
}