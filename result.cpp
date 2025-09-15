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

#include "result.h"

Result::Result()
{
	m_score = Manager::GetScene()->GetGameObject<Score>()->GetPoints();
	m_bonus = Manager::GetScene()->GetGameObject<Player>()->GetTotalEXP();
}

void Result::Init(Input*)
{
	ResultUI* p_reuslt = AddGameObject<ResultUI>(4);
	p_reuslt->SetScore(m_score);
	p_reuslt->SetBonusScore(m_bonus);
	p_reuslt->CalcTotal();
	AddGameObject<Fade>(4)->SetFade(FADE_IN);
}

void Result::Update()
{
	if (m_Input->GetKeyTrigger(KK_ENTER))
	{
		Manager::GetScene()->GetGameObject<Fade>()->SetFade(FADE_OUT);
		Manager::SetScene<Title>();

	}

	Scene::Update();
}
