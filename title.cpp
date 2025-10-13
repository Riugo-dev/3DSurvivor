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
#include "polygon.h"
#include "fade.h"
#include "controller.h"
#include "audio.h"

#include "title.h"

void Title::Init(Input*)
{
	AddGameObject<Polygon2D>(2)->SetPosition({ SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 , 1.0f});
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

	Manager::GetScene()->GetGameObject<Fade>()->Update();
}
