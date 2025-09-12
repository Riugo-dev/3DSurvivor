//********************************************************************************
//
// game.cpp[gameÉNÉâÉX]
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

#include "title.h"

#include "game.h"

//********************************************************************************
//ä÷êî
//********************************************************************************


void Game::Init(Input* input)
{
	
	m_Input = input;
	m_pTimer = new GameTimer;

	Renderer::Init();

	//m_GameObjects.push_back(new Camera(g_Input));
	AddGameObject<Camera>(0)->Init(input);
	AddGameObject<SkyDome>()->SetPosition({ 0.0f , 0.0f , 0.0f });
	AddGameObject<Field>();
	AddGameObject<Player>()->Init(input);
	
	AddGameObject<Score>(4);
	AddGameObject<HPUI>(4);
}

void Game::Uninit()
{
	delete m_pTimer;
	m_pTimer = nullptr;

	Scene::Uninit();
}

void Game::Update()
{
	Scene::Update();

	m_pTimer->Update();

	if (m_Input->GetKeyTrigger(KK_ENTER))
	{
		Manager::SetScene<Title>();
	}
}
