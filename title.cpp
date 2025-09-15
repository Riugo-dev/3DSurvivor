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

#include "title.h"

void Title::Init(Input*)
{
	AddGameObject<Polygon2D>(2)->SetPosition({ SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 , 1.0f});
	AddGameObject<Fade>(2)->SetFade(FADE_IN);
}

void Title::Update()
{
	if (m_Input->GetKeyTrigger(KK_ENTER))
	{
		Manager::GetScene()->GetGameObject<Fade>()->SetFade(FADE_OUT);
		Manager::SetScene<Game>();
		
	}

	Manager::GetScene()->GetGameObject<Fade>()->Update();
}
