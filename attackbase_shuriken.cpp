//********************************************************************************
//
// attackbase_shuriken.h[‹…UŒ‚‚ÌŠî’êƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/14
//********************************************************************************
#include "manager.h"
#include "scene.h"
#include "player.h"

#include "attackbase_shuriken.h"

BaseAttackShuriken::BaseAttackShuriken()
{
	m_ModelTag = SHURIKEN;

	m_Scale = { 1.0f , 1.0f ,1.0f };

	m_Shader = SHADER_BLINNPHONG;

	m_Velocity = { 0.0f , 0.0f , 0.0f };
	m_Position = { 0.0f , 0.0f , 0.0f };
	m_Scale = { 0.5f , 0.5f , 0.5f };

	m_FrameCount = 0;
	m_LivingFrames = 0;
	m_angle = 0.0f;
	m_rotationspeed = 1.0f;
	m_Strength = 1;
}

BaseAttackShuriken::~BaseAttackShuriken()
{
	
}

void BaseAttackShuriken::Update()
{
	Player* player = Manager::GetScene()->GetGameObject<Player>();

	Vector3 pos = player->GetPosition();

	m_angle += m_rotationspeed;

	m_Position.m_x = pos.m_x + cosf(m_angle) * m_radius;

	m_Position.m_z = pos.m_z + sinf(m_angle) * m_radius;

	m_Position.m_y = pos.m_y;

	m_Rotation.m_y += 2.0f;

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

	m_Position.m_x = pos.m_x + cosf(m_angle) * m_radius;

	m_Position.m_z = pos.m_z + sinf(m_angle) * m_radius;

	m_Position.m_y = pos.m_y;
}
