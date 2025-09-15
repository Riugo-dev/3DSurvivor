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
std::vector<Audio*>	SoundEffectManager::m_SoundEffects;
//********************************************************************************
//関数
//********************************************************************************
SoundEffectManager::SoundEffectManager()
{
	m_SoundEffects.push_back(new Audio());
	m_SoundEffects.back()->Load("asset\\audio\\爆発SE.wav");
	m_SoundEffects.push_back(new Audio());
	m_SoundEffects.back()->Load("asset\\audio\\ShotSE.wav");
	m_SoundEffects.push_back(new Audio());
	m_SoundEffects.back()->Load("asset\\audio\\パーティクル集合音.wav");
	m_SoundEffects.push_back(new Audio());
	m_SoundEffects.back()->Load("asset\\audio\\出現音.wav");
	m_SoundEffects.push_back(new Audio());
	m_SoundEffects.back()->Load("asset\\audio\\コイン獲得音.wav");
}

SoundEffectManager::~SoundEffectManager()
{
	for (auto itr : m_SoundEffects)
	{
		itr->Uninit();
		delete itr;
		itr = nullptr;
	}

	m_SoundEffects.clear();
}

void SoundEffectManager::PlaySE(SoundEffect se)
{
	switch (se)
	{
	case SE_EXPLOSION:
		m_SoundEffects[0]->Play();
		break;
	case SE_SHOT:
		m_SoundEffects[1]->Play();
		break;
	case SE_PARTICLEGATHER:
		m_SoundEffects[2]->Play();
		break;
	case SE_SPAWN:
		m_SoundEffects[3]->Play();
		break;
	case SE_COINGET:
		m_SoundEffects[4]->Play();
		break;
	}
}
