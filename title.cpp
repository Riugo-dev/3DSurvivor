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

#include "title.h"

void Title::Init(Input*)
{
	AddGameObject<Polygon2D>(2)->SetPosition({ SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 , 1.0f});
}

void Title::Update()
{
	if (m_Input->GetKeyTrigger(KK_ENTER))
	{
		Manager::SetScene<Game>();
	}
}
