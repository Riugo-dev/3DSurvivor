//********************************************************************************
//
// attackbase_bullet.h[‹…UŒ‚‚ÌŠî’êƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************
#include "manager_soundeffect.h"
#include "attackbase_bullet.h"

BaseAttackBullet::BaseAttackBullet()
{
	
	m_ModelTag = BULLET;

	m_Scale = { 1.0f , 1.0f ,1.0f };

	m_Shader = SHADER_BLINNPHONG;

	m_Velocity = { 0.0f , 0.0f , 0.0f };
	m_Position = { 0.0f , 0.0f , 0.0f };

	m_FrameCount = 0;
	m_LivingFrames = 0;
	m_Strength = 1;

	SoundEffectManager::PlaySE(SE_BULLETSHOT);
}

BaseAttackBullet::~BaseAttackBullet()
{
	
}

void BaseAttackBullet::Update()
{
	m_Position += m_Velocity;

	if (m_FrameCount >= m_LivingFrames)
	{
		m_IsDestroy = true;
	}
	m_FrameCount++;
}
