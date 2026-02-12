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
#include "texture.h"
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
#include "exp_ui.h"
#include "stage_field.h"
#include "pause.h"
#include "bulletattack.h"
#include "swordattack.h"
#include "shurikenattack.h"
#include "attack_manager.h"
#include "fade.h"
#include "model_manager.h"
#include "manager_soundeffect.h"
#include "exp_item_manager.h"
#include "explosion_gpuparticle.h"
#include "enemydamage_ui.h"
#include "controller.h"
#include "title.h"
#include "audio.h"


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
	SetSceneType(SCENE_GAME);
	//Renderer::Init();

	//m_GameObjects.push_back(new Camera(g_Input));
	AddGameObject<Camera>(0)->Init();
	//AddGameObject<SkyDome>()->SetPosition({ 0.0f , 0.0f , 0.0f });
	//AddGameObject<Field>();
	AddGameObject<Player>()->Init();
	AddGameObject<StageField>();


	AddGameObject<Score>(4);
	AddGameObject<HPUI>(4);
	AddGameObject<EXPUI>(4);
	AddGameObject<Pause>(4);
	AddGameObject<Fade>(4);
	AddGameObject<AttackManager>(5);
	GetGameObject<Fade>()->SetFade(FADE_IN);

	m_pModelManager = new ModelManager;
	m_pModelManager->Init();

	m_State = GAME_FADEIN;

	ExpItemManager::GetInstance();//とりあえず初期化

	GPUExplosionParticle::GetInstance();

	EnemyDamageUI::GetInstance();

	//Manager::GetAudio()->Load("asset\\audio\\bgm.wav");
	Manager::GetAudio()->Load("asset\\audio\\Devine-Fencer.wav");
	Manager::GetAudio()->Play(true);
}

void Game::Uninit()
{

	Manager::GetAudio()->Uninit();

	EnemyDamageUI::GetInstance()->DestroyInstance();

	GPUExplosionParticle::GetInstance()->DestroyInstance();

	ExpItemManager::GetInstance()->DestroySelf();//終了処理

	delete m_pTimer;
	m_pTimer = nullptr;

	delete m_pModelManager;
	m_pModelManager = nullptr;

	//Renderer::Uninit();

	Scene::Uninit();

	//Texture::ReleaseAll();

	//ModelRenderer::UnloadAll();
}

void Game::Update()
{

	Controller* p_contorller = Manager::GetController();

	if(m_State == GAME_PLAY)
	{
		Scene::Update();

		m_pTimer->Update();

		ExpItemManager::GetInstance()->Update();

		GPUExplosionParticle::GetInstance()->Update();

		EnemyDamageUI::GetInstance()->Update();

		if ((m_Input->GetKeyTrigger(KK_P) && !p_contorller->IsConnected()) || p_contorller->Controller_IsJustPressed(p_contorller->GetButtonForTrigger(XINPUT_GAMEPAD_START)))
		{
			m_State = GAME_PAUSE;
			Manager::GetSoundEffect()->PlaySE(SE_PAUSE);
		}
	}
	else if (m_State == GAME_PAUSE)
	{
	

		if ((m_Input->GetKeyTrigger(KK_P) && !p_contorller->IsConnected()) || p_contorller->Controller_IsJustPressed(p_contorller->GetButtonForTrigger(XINPUT_GAMEPAD_START)))
		{
			m_State = GAME_PLAY;
		}
#ifdef _DEBUG
		if ((m_Input->GetKeyTrigger(KK_ENTER) && !p_contorller->IsConnected()) || p_contorller->Controller_IsJustPressed(p_contorller->GetButtonForTrigger(XINPUT_GAMEPAD_B)))
		{
			Manager::SetScene<Title>();
			GetGameObject<Fade>()->SetFade(FADE_OUT);
			m_State = GAME_FADEOUT;
		}
#endif
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

	//m_pTimer->Draw();
}

