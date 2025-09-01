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

#include "title.h"

#include "game.h"

//********************************************************************************
//関数
//********************************************************************************


void Game::Init(Input* input)
{
	
	m_Input = input;

	Renderer::Init();

	//m_GameObjects.push_back(new Camera(g_Input));
	AddGameObject<Camera>(0)->Init(input);
	AddGameObject<SkyDome>()->SetPosition({ 0.0f , 0.0f , 0.0f });
	AddGameObject<Field>();
	AddGameObject<Player>()->Init(input);
	AddGameObject<Enemy>()->SetPosition({ 0.0f,0.0f,6.0f });
	AddGameObject<Enemy>()->SetPosition({ 4.0f,0.0f,6.0f });
	AddGameObject<Enemy>()->SetPosition({ -4.0f,0.0f,6.0f });
	AddGameObject<Coin>()->SetPosition({ -4.0f,1.5f,3.0f }); 
	AddGameObject<Coin>()->SetPosition({ 0.0f,1.5f,3.0f });
	AddGameObject<Coin>()->SetPosition({ 4.0f,1.5f,3.0f });
	AddGameObject<Box>();
	


	AddGameObject<Polygon2D>(2);//これは元となる関数を全て自動的に作っているだけなのでロード時間は増えるのであまり多用しすぎないほうが良い

}

void Game::Update()
{
	Scene::Update();

	if (m_Input->GetKeyTrigger(KK_ENTER))
	{
		Manager::SetScene<Title>();
	}
}
