//********************************************************************************
//
// title.cpp[titleƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/06/25
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/25
//********************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "game.h"
#include "title_ui.h"
#include "fade.h"
#include "controller.h"
#include "audio.h"

#include "title.h"

void Title::Init(Input*)
{
	AddGameObject<TitleUI>(2);
	AddGameObject<Fade>(2)->SetFade(FADE_IN);
	Manager::GetAudio()->Load("asset\\audio\\titlebgm.wav");
	Manager::GetAudio()->Play(true);
}

void Title::Uninit()
{
	Manager::GetAudio()->Uninit();

	Scene::Uninit();
}

void Title::Update()
{
	if(Manager::GetScene()->GetGameObject<Fade>()->GetFade() == FADE_FIN)
	{
		Controller* p_contorller = Manager::GetController();

		if ((m_Input->GetKeyTrigger(KK_ENTER) && !p_contorller->IsConnected()) || p_contorller->Controller_IsJustPressed(p_contorller->GetButtonForTrigger(XINPUT_GAMEPAD_B)))
		{
			Manager::GetScene()->GetGameObject<Fade>()->SetFade(FADE_OUT);
			Manager::SetScene<Game>();

		}
	}

	if (m_Input->GetKeyPress(KK_UP) || Manager::GetController()->Controller_IsButtonDown(XINPUT_GAMEPAD_DPAD_UP))
	{
		Manager::GetAudio()->AddVolume(0.01f);
		//Manager::GetAudio()->SetVolumeMax();
	}

	if (m_Input->GetKeyPress(KK_DOWN) || Manager::GetController()->Controller_IsButtonDown(XINPUT_GAMEPAD_DPAD_DOWN))
	{
		Manager::GetAudio()->LowerVolume(0.01f);
		//Manager::GetAudio()->SetVolumeZero();
	}


	Manager::GetScene()->GetGameObject<Fade>()->Update();
}
