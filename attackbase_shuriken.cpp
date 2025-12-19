//********************************************************************************
//
// attackbase_shuriken.h[‹…UŒ‚‚ÌŠî’êƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/14
//********************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "manager_soundeffect.h"

#include "attackbase_shuriken.h"

BaseAttackShuriken::BaseAttackShuriken()
{
	m_ModelTag = SHURIKEN;

	m_Scale = { 1.0f , 1.0f ,1.0f };

	m_Shader = SHADER_TOON;

	m_Velocity = { 0.0f , 0.0f , 0.0f };
	m_Position = { 0.0f , 0.0f , 0.0f };
	m_Scale = { 0.5f , 0.5f , 0.5f };

	m_FrameCount = 0;
	m_LivingFrames = 0;
	m_angle = 0.0f;
	m_rotationspeed = 1.0f;
	m_Strength = 1 * 60;

	m_Radius = 1.0f;

	SoundEffectManager::PlaySE(SE_SHURIKENTHROW);
}

BaseAttackShuriken::~BaseAttackShuriken()
{
	
}

void BaseAttackShuriken::Update()
{
	Player* player = Manager::GetScene()->GetGameObject<Player>();

	Vector3 pos = player->GetPosition();

	m_angle += m_rotationspeed;

	m_Position.x = pos.x + cosf(m_angle) * m_radius;

	m_Position.z = pos.z + sinf(m_angle) * m_radius;

	m_Position.y = pos.y;

	m_Rotation.y += 2.0f;

	if (m_FrameCount >= m_LivingFrames)
	{
		m_IsDestroy = true;
	}
	m_FrameCount++;
}


void BaseAttackShuriken::SetShuriken(float rad, float speed, Vector3 pos, float angle)
{
	m_radius = rad;
	m_rotationspeed = speed;

	m_angle = angle;

	m_Position.x = pos.x + cosf(m_angle) * m_radius;

	m_Position.z = pos.z + sinf(m_angle) * m_radius;

	m_Position.y = pos.y;
}
