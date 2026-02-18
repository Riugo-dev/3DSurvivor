//********************************************************************************
//
// manager_soundeffect.h[音声エフェクトマネージャー]
//
//															Author :Riugo Honda
//															Date   :2025/07/09
// -------------------------------------------------------------------------------
//															Last Edited:2025/07/09
//********************************************************************************
#include "main.h"
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
	m_pSoundEffects[SE_BOMB] = std::make_unique<Audio>();
	m_pSoundEffects[SE_BOMB]->Load("asset\\audio\\boom.wav");
	m_pSoundEffects[SE_ENEMYDAMAGE] = std::make_unique<Audio>();
	m_pSoundEffects[SE_ENEMYDAMAGE]->Load("asset\\audio\\enemy_down.wav");
	m_pSoundEffects[SE_PLAYERDAMAGE] = std::make_unique<Audio>();
	m_pSoundEffects[SE_PLAYERDAMAGE]->Load("asset\\audio\\player_damage.wav");
	m_pSoundEffects[SE_NEWRECORD] = std::make_unique<Audio>();
	m_pSoundEffects[SE_NEWRECORD]->Load("asset\\audio\\newRecord.wav");
	m_pSoundEffects[SE_BOOST] = std::make_unique<Audio>();
	m_pSoundEffects[SE_BOOST]->Load("asset\\audio\\speedup.wav");
	m_pSoundEffects[SE_HEAL] = std::make_unique<Audio>();
	m_pSoundEffects[SE_HEAL]->Load("asset\\audio\\item_heal.wav");
	m_pSoundEffects[SE_GATHER] = std::make_unique<Audio>();
	m_pSoundEffects[SE_GATHER]->Load("asset\\audio\\item_gather.wav");
	m_pSoundEffects[SE_EXPGET] = std::make_unique<Audio>();
	m_pSoundEffects[SE_EXPGET]->Load("asset\\audio\\exp_get.wav");
	m_pSoundEffects[SE_DOUBLEPOINTS] = std::make_unique<Audio>();
	m_pSoundEffects[SE_DOUBLEPOINTS]->Load("asset\\audio\\doublepoints.wav");
	m_pSoundEffects[SE_PAUSE] = std::make_unique<Audio>();
	m_pSoundEffects[SE_PAUSE]->Load("asset\\audio\\pause.wav");
	m_pSoundEffects[SE_LEVELUP] = std::make_unique<Audio>();
	m_pSoundEffects[SE_LEVELUP]->Load("asset\\audio\\level_up.wav");


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
