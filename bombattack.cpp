//********************************************************************************
//
// bombattack.cpp[球攻撃の管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/13
//********************************************************************************
#include "main.h"
#include "player.h"
#include "camera.h"
#include "manager.h"
#include "scene.h"
#include "attackbase_slipdamage.h"
#include <random>
#include <cmath>
#include <vector>

#include "bombattack.h"

//********************************************************************************
//マクロ定義
//********************************************************************************
#define COOLDOWN_LEVELONE (60 * 6)
#define COOLDOWN_LEVELTWO (60 * 6)
#define COOLDOWN_LEVELTHREE (60 * 6)
#define COOLDOWN_LEVELFOUR (60 * 6)
#define COOLDOWN_LEVELMAX (60 * 6)

//********************************************************************************
//関数
//********************************************************************************

BombAttack::BombAttack()
{
	m_AttackLevel = ATT_LVNONE;
	m_FrameCount = 0;
}

void BombAttack::Update()
{
	switch (m_AttackLevel)
	{
	case ATT_LV1:
	{
		if (m_FrameCount % COOLDOWN_LEVELONE == 0)
		{
			Player* p_player = Manager::GetScene()->GetGameObject<Player>();

			std::random_device rd;
			std::mt19937 mt(rd());

			std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);
			float angle = randangle(mt);

			Vector3 spawnpoint;

			std::uniform_real_distribution<float> randdist(-10.0f, 10.0f);
			float distance = randdist(mt);

			Vector3 bombpos = p_player->GetPosition();

			bombpos.x = bombpos.x + cosf(angle) * distance;
			bombpos.y = 5.0f;
			bombpos.z = bombpos.z + sinf(angle) * distance;

			BaseAttackSlipDamage* bomb = Manager::GetScene()->AddGameObject<BaseAttackSlipDamage>();
			bomb->SetPosition(bombpos);
			bomb->SetVelocity({ 0.0f , -0.25f , 0.0f });
			bomb->SetScale({ 0.25f , 0.25f ,0.25f });
			bomb->SetLivingFrames(60 * 5);
			bomb->SetRadius(2.0f);
		}
	}
	break;
	case ATT_LV2:
	{
		if (m_FrameCount % COOLDOWN_LEVELTWO == 0)
		{
			Player* p_player = Manager::GetScene()->GetGameObject<Player>();

			std::random_device rd;
			std::mt19937 mt(rd());

			for (int i = 0; i < 2; i++)
			{
				

				std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);
				float angle = randangle(mt);

				Vector3 spawnpoint;

				std::uniform_real_distribution<float> randdist(-10.0f, 10.0f);
				float distance = randdist(mt);

				Vector3 bombpos = p_player->GetPosition();

				bombpos.x = bombpos.x + cosf(angle) * distance;
				bombpos.y = 5.0f;
				bombpos.z = bombpos.z + sinf(angle) * distance;

				BaseAttackSlipDamage* bomb = Manager::GetScene()->AddGameObject<BaseAttackSlipDamage>();
				bomb->SetPosition(bombpos);
				bomb->SetVelocity({ 0.0f , -0.25f , 0.0f });
				bomb->SetScale({ 0.25f , 0.25f ,0.25f });
				bomb->SetLivingFrames(60 * 5);
				bomb->SetRadius(2.0f);
			}
		}
	}
	break;
	case ATT_LV3:
	{
		if (m_FrameCount % COOLDOWN_LEVELTHREE == 0)
		{
			Player* p_player = Manager::GetScene()->GetGameObject<Player>();

			std::random_device rd;
			std::mt19937 mt(rd());

			for (int i = 0; i < 3; i++)
			{


				std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);
				float angle = randangle(mt);

				Vector3 spawnpoint;

				std::uniform_real_distribution<float> randdist(-15.0f, 15.0f);
				float distance = randdist(mt);

				Vector3 bombpos = p_player->GetPosition();

				bombpos.x = bombpos.x + cosf(angle) * distance;
				bombpos.y = 5.0f;
				bombpos.z = bombpos.z + sinf(angle) * distance;

				BaseAttackSlipDamage* bomb = Manager::GetScene()->AddGameObject<BaseAttackSlipDamage>();
				bomb->SetPosition(bombpos);
				bomb->SetVelocity({ 0.0f , -0.25f , 0.0f });
				bomb->SetScale({ 0.25f , 0.25f ,0.25f });
				bomb->SetLivingFrames(60 * 5);
				bomb->SetRadius(2.5f);
			}
		}
	}
	break;
	case ATT_LV4:
	{
		if (m_FrameCount % COOLDOWN_LEVELFOUR == 0)
		{
			Player* p_player = Manager::GetScene()->GetGameObject<Player>();

			std::random_device rd;
			std::mt19937 mt(rd());

			for (int i = 0; i < 4; i++)
			{


				std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);
				float angle = randangle(mt);

				Vector3 spawnpoint;

				std::uniform_real_distribution<float> randdist(-15.0f, 15.0f);
				float distance = randdist(mt);

				Vector3 bombpos = p_player->GetPosition();

				bombpos.x = bombpos.x + cosf(angle) * distance;
				bombpos.y = 5.0f;
				bombpos.z = bombpos.z + sinf(angle) * distance;

				BaseAttackSlipDamage* bomb = Manager::GetScene()->AddGameObject<BaseAttackSlipDamage>();
				bomb->SetPosition(bombpos);
				bomb->SetVelocity({ 0.0f , -0.25f , 0.0f });
				bomb->SetScale({ 0.25f , 0.25f ,0.25f });
				bomb->SetLivingFrames(60 * 5);
				bomb->SetRadius(2.5f);
			}
		}
	}
	break;
	case ATT_LVMAX:
	{
		if (m_FrameCount % COOLDOWN_LEVELMAX == 0)
		{
			Player* p_player = Manager::GetScene()->GetGameObject<Player>();

			std::random_device rd;
			std::mt19937 mt(rd());

			for (int i = 0; i < 5; i++)
			{


				std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);
				float angle = randangle(mt);

				Vector3 spawnpoint;

				std::uniform_real_distribution<float> randdist(-15.0f, 15.0f);
				float distance = randdist(mt);

				Vector3 bombpos = p_player->GetPosition();

				bombpos.x = bombpos.x + cosf(angle) * distance;
				bombpos.y = 5.0f;
				bombpos.z = bombpos.z + sinf(angle) * distance;

				BaseAttackSlipDamage* bomb = Manager::GetScene()->AddGameObject<BaseAttackSlipDamage>();
				bomb->SetPosition(bombpos);
				bomb->SetVelocity({ 0.0f , -0.25f , 0.0f });
				bomb->SetScale({ 0.25f , 0.25f ,0.25f });
				bomb->SetLivingFrames(60 * 5);
				bomb->SetRadius(3.0f);
			}
		}
	}
	break;
defualt:
	break;
	}

	m_FrameCount++;

}

void BombAttack::SetToNextLevel()
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
