//********************************************************************************
//
// attackbase_sword.h[ãÖçUåÇÇÃäÓíÍÉNÉâÉX]
//
//															Author :Riugo Honda
//															Date   :2025/09/14
//********************************************************************************
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "manager_soundeffect.h"

#include "attackbase_sword.h"

BaseAttackSword::BaseAttackSword()
{

	m_ModelTag = SWORD;

	m_Scale = { 1.0f , 1.0f ,1.0f };

	m_Shader = SHADER_BLINNPHONG;

	m_Velocity = { 0.0f , 0.0f , 0.0f };
	m_Position = { 0.0f , 0.0f , 0.0f };
	m_Scale = { 0.5f , 0.5f , 0.5f };

	m_FrameCount = 0;
	m_LivingFrames = 0;
	m_angle = 0.0f;
	m_rotationspeed = 1.0f;

	SoundEffectManager::PlaySE(SE_SWORDTHROW);
}

BaseAttackSword::~BaseAttackSword()
{
	
}

void BaseAttackSword::Update()
{
	float dt = 0.1f;

	m_Velocity.m_y += m_gravity * dt;
	m_Position += m_Velocity * dt;
	m_Rotation.m_z += 1.0f;

	if (m_Position.m_y <= -1.0f)
	{
		m_IsDestroy = true;
	}
}

void BaseAttackSword::SetSword(Vector3 vel, Vector3 pos, float angle)
{
	m_Velocity = vel;
	

	m_angle = angle;

	m_Position = pos;

}

