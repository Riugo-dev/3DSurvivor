//********************************************************************************
//
// manager_soundeffect.h[音声エフェクトマネージャー]
//
//															Author :Riugo Honda
//															Date   :2025/07/09
// -------------------------------------------------------------------------------
//															Last Edited:2025/07/09
//********************************************************************************
#include "audio.h"

#include "manager_soundeffect.h"

//********************************************************************************
//グローバル変数
//********************************************************************************
std::unordered_map<SoundEffect, std::unique_ptr<Audio>>	SoundEffectManager::m_pSoundEffects;
//********************************************************************************
//関数
//********************************************************************************
SoundEffectManager::SoundEffectManager()
{
	m_pSoundEffects[SE_BULLETSHOT] = std::make_unique<Audio>();
	m_pSoundEffects[SE_BULLETSHOT]->Load("asset\\audio\\bulletshot.wav");
	m_pSoundEffects[SE_SWORDTHROW] = std::make_unique<Audio>();
	m_pSoundEffects[SE_SWORDTHROW]->Load("asset\\audio\\swordthrow.wav");
	m_pSoundEffects[SE_SHURIKENTHROW] = std::make_unique<Audio>();
	m_pSoundEffects[SE_SHURIKENTHROW]->Load("asset\\audio\\shurikenthrow.wav");
	m_pSoundEffects[SE_ENEMYDAMAGE] = std::make_unique<Audio>();
	m_pSoundEffects[SE_ENEMYDAMAGE]->Load("asset\\audio\\enemydamage.wav");
	m_pSoundEffects[SE_NEWRECORD] = std::make_unique<Audio>();
	m_pSoundEffects[SE_NEWRECORD]->Load("asset\\audio\\newRecord.wav");
}

SoundEffectManager::~SoundEffectManager()
{
	m_pSoundEffects.clear();
}

void SoundEffectManager::PlaySE(SoundEffect se)
{
	if (m_pSoundEffects.count(se))
	{
		m_pSoundEffects[se]->Play();
	}
}
