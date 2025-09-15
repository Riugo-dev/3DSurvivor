//********************************************************************************
//
// game.cpp[gameクラス]
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

#include "camera.h"
#include "field.h"
#include "player.h"
#include "enemy.h"
#include "polygon.h"
#include "coin.h"
#include "box.h"
#include "skydome.h"
#include "gametimer.h"
#include "score.h"
#include "hp_ui.h"
#include "stage_field.h"
#include "modelRenderer.h"
#include "pause.h"
#include "bulletattack.h"
#include "swordattack.h"
#include "shurikenattack.h"
#include "attack_manager.h"
#include "fade.h"

#include "title.h"

#include "game.h"
//********************************************************************************
//グローバル変数
//********************************************************************************
GameState Game::m_State;

//********************************************************************************
//関数
//********************************************************************************


void Game::Init(Input* input)
{
	
	m_Input = input;
	m_pTimer = new GameTimer;

	Renderer::Init();

	//m_GameObjects.push_back(new Camera(g_Input));
	AddGameObject<Camera>(0)->Init(input);
	AddGameObject<SkyDome>()->SetPosition({ 0.0f , 0.0f , 0.0f });
	//AddGameObject<Field>();
	AddGameObject<Player>()->Init(input);
	AddGameObject<StageField>();

	AddGameObject<Score>(4);
	AddGameObject<HPUI>(4);
	AddGameObject<Pause>(4);
	AddGameObject<AttackManager>(4);
	AddGameObject<Fade>(4);

	GetGameObject<Fade>()->SetFade(FADE_IN);



	m_State = GAME_FADEIN;
}

void Game::Uninit()
{
	delete m_pTimer;
	m_pTimer = nullptr;

	Scene::Uninit();

	ModelRenderer::UnloadAll();
}

void Game::Update()
{

	if(m_State == GAME_PLAY)
	{
		Scene::Update();

		m_pTimer->Update();



		if (m_Input->GetKeyTrigger(KK_P))
		{
			m_State = GAME_PAUSE;
		}
	}
	else if (m_State == GAME_PAUSE)
	{
	

		if (m_Input->GetKeyTrigger(KK_P))
		{
			m_State = GAME_PLAY;
		}

		if (m_Input->GetKeyTrigger(KK_ENTER))
		{
			Manager::SetScene<Title>();
			GetGameObject<Fade>()->SetFade(FADE_OUT);
			m_State = GAME_FADEOUT;
		}
	}
	else if (m_State == PLAYER_LEVELUP)
	{
		GetGameObject<AttackManager>()->Update();
	}
	else if(m_State == GAME_FADEIN)
	{
		GetGameObject<Fade>()->Update();
	

		if (GetGameObject<Fade>()->GetFade() == FADE_FIN)
		{
			m_State = PLAYER_LEVELUP;

			GetGameObject<Fade>()->SetFade(FADE_NONE);

			GetGameObject<AttackManager>()->Update();

		}
	}
	else if (m_State == GAME_FADEOUT)
	{
		GetGameObject<Fade>()->Update();


		if (GetGameObject<Fade>()->GetFade() == FADE_FIN)
		{
			Scene::Update();


		}
	}

	
	
}

void Game::Draw()
{
	Scene::Draw();
}

