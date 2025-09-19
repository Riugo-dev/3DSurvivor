//********************************************************************************
//
// manager_soundeffect.h[音声エフェクトマネージャー]
//
//															Author :Riugo Honda
//															Date   :2025/07/09
// -------------------------------------------------------------------------------
//															Last Edited:2025/07/09
//********************************************************************************
#pragma once

#ifndef _SOUNDEFFECT_MANAGER_
#define _SOUNDEFFECT_MANAGER_

#include <unordered_map>
#include <memory>

class Audio;

typedef enum
{
	SE_NONE = -1,
	SE_BULLETSHOT,
	SE_SWORDTHROW,
	SE_SHURIKENTHROW,
	SE_ENEMYDAMAGE,
	SE_NEWRECORD,
}SoundEffect;

class SoundEffectManager
{
private:
	static std::unordered_map<SoundEffect , std::unique_ptr<Audio>> m_pSoundEffects;

public:
	SoundEffectManager();
	~SoundEffectManager();
		

	static void PlaySE(SoundEffect);
};

#endif // !_SOUNDEFFECT_MANAGER_
