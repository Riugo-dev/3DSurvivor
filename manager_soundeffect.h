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

#include <vector>

class Audio;

typedef enum
{
	SE_NONE = -1,
	SE_EXPLOSION,
	SE_SHOT,
	SE_PARTICLEGATHER,
	SE_SPAWN,
	SE_COINGET,
}SoundEffect;

class SoundEffectManager
{
private:
	static std::vector<Audio*> m_SoundEffects;

public:
	SoundEffectManager();
	~SoundEffectManager();
		

	static void PlaySE(SoundEffect);
};

#endif // !_SOUNDEFFECT_MANAGER_
