//********************************************************************************
//
// audio.h[音クラス]
//
//															Author :Riugo Honda
//															Date   :2025/10/14
//********************************************************************************

#pragma once

#include <xaudio2.h>
#include "component.h"

//読み込めるのはWAVファイルのみ

class Audio : public Component
{
private:
	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	IXAudio2SourceVoice*	m_SourceVoice{};
	BYTE*					m_SoundData{};

	int						m_Length{};
	int						m_PlayLength{};

	static float					m_Volume;

public:
	static void InitMaster();
	static void UninitMaster();

	using Component::Component;

	void Uninit();

	void Load(const char *FileName);
	void Play(bool Loop = false);

	void AddVolume(float);
	void LowerVolume(float);
	void SetVolumeMax();
	void SetVolumeZero();

	float GetVolume();
};

