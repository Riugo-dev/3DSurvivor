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
#include "result_ui.h"
#include "title.h"
#include "player.h"
#include "score.h"
#include "controller.h"
#include "ranking.h"

#include "result.h"

Result::Result()
{
	//Renderer::Init();

	m_score = Manager::GetScene()->GetGameObject<Score>()->GetPoints();
	m_bonus = Manager::GetScene()->GetGameObject<Player>()->GetTotalEXP();

	m_Ranking = new Ranking;
}

Result::~Result()
{
	delete m_Ranking;
	m_Ranking = nullptr;
}

void Result::Uninit()
{
	//Manager::GetAudio()->Uninit();

	Scene::Uninit();
}

void Result::Init(Input*)
{
	ResultUI* p_reuslt = AddGameObject<ResultUI>(4);
	p_reuslt->SetScore(m_score);
	p_reuslt->SetBonusScore(m_bonus * 10);
	p_reuslt->CalcTotal();
	m_Ranking->SetRanking(p_reuslt->GetTotal());
	AddGameObject<Fade>(4)->SetFade(FADE_IN);
}

void Result::Update()
{
	if (Manager::GetScene()->GetGameObject<Fade>()->GetFade() == FADE_FIN)
	{
		Controller* p_contorller = Manager::GetController();

		if ((m_Input->GetKeyPress(KK_K) && m_Input->GetKeyPress(KK_F) && m_Input->GetKeyPress(KK_C) && m_Input->GetKeyTrigger(KK_ENTER)) || (p_contorller->Controller_IsButtonDown(XINPUT_GAMEPAD_START) && p_contorller->Controller_IsJustPressed(p_contorller->GetButtonForTrigger(XINPUT_GAMEPAD_B))))
		{
			m_Ranking->ResetRanking();
		}

		if ((m_Input->GetKeyTrigger(KK_ENTER) && !p_contorller->IsConnected()) || p_contorller->Controller_IsJustPressed(p_contorller->GetButtonForTrigger(XINPUT_GAMEPAD_B)))
		{
			if (GetGameObject<ResultUI>()->GetState() == RESULT)
			{
				GetGameObject<ResultUI>()->SetState(RANKING);
			}
			else if (GetGameObject<ResultUI>()->GetState() == RANKING && !GetGameObject<ResultUI>()->GetIsRising())
			{
				Manager::GetScene()->GetGameObject<Fade>()->SetFade(FADE_OUT);
				Manager::SetScene<Title>();
			}
		}

	}

	Scene::Update();
}
