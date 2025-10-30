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
#include "controller.h"
#include "title.h"
#include "audio.h"


#include "levelone_enemy.h"
#include "leveltwo_enemy.h"
#include "levelthree_enemy.h"
#include "levelfour_enemy.h"
#include "levelfive_enemy.h"

#include "levelone_shooterenemy.h"
#include "leveltwo_shooterenemy.h"
#include "levelthree_shooterenemy.h"
#include "levelfour_shooterenemy.h"
#include "levelfive_shooterenemy.h"

#include "levelone_midboss.h"

#include "levelone_swarmenemy.h"


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

	for (int i = 4; i <= 18; i += 2)
	{
		Player* p_player = Manager::GetScene()->GetGameObject<Player>();

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);//実数の一様分布、指定した範囲 [a, b] の整数を等確率で返す

		for (float j = 0; j < 6; j+= 0.2)
		{
			int distance = i;//rd() % 7 + 7
			float angle = j;

			Vector3 spawnpoint;
			spawnpoint.m_x = p_player->GetPosition().m_x + cosf(angle) * distance;
			spawnpoint.m_y = 0.75f;
			spawnpoint.m_z = p_player->GetPosition().m_z + sinf(angle) * distance;

			int who = rd() % 10;

			switch (who)
			{
			case 0:
				Manager::GetScene()->AddGameObject<LevelOneEnemy>()->SetPosition(spawnpoint);
				break;
			case 1:
				Manager::GetScene()->AddGameObject<LevelTwoEnemy>()->SetPosition(spawnpoint);
				break;
			case 2: 
				Manager::GetScene()->AddGameObject<LevelThreeEnemy>()->SetPosition(spawnpoint);
				break;
			case 3:
				Manager::GetScene()->AddGameObject<LevelFourEnemy>()->SetPosition(spawnpoint);
				break;
			case 4:
				Manager::GetScene()->AddGameObject<LevelFiveEnemy>()->SetPosition(spawnpoint);
				break;
			case 5:
				spawnpoint.m_y = 0.0;
				Manager::GetScene()->AddGameObject<LevelOneShooterEnemy>()->SetPosition(spawnpoint);
				break;
			case 6:
				spawnpoint.m_y = 0.0;
				Manager::GetScene()->AddGameObject<LevelTwoShooterEnemy>()->SetPosition(spawnpoint);
				break;
			case 7:
				spawnpoint.m_y = 0.0;
				Manager::GetScene()->AddGameObject<LevelThreeShooterEnemy>()->SetPosition(spawnpoint);
				break;
			case 8:
				spawnpoint.m_y = 0.0;
				Manager::GetScene()->AddGameObject<LevelFourShooterEnemy>()->SetPosition(spawnpoint);
				break;
			case 9:
				spawnpoint.m_y = 0.0;
				Manager::GetScene()->AddGameObject<LevelFiveShooterEnemy>()->SetPosition(spawnpoint);
				break;
			}

			
		}
	}


	//AddGameObject<LevelOneEnemy>()->SetPosition({ 5.0f , 0.75f , -4.0f });
	//AddGameObject<LevelOneEnemy>()->SetPosition({ 5.0f , 0.75f , -2.0f });
	//AddGameObject<LevelOneEnemy>()->SetPosition({ 5.0f , 0.75f , 0.0f });
	//AddGameObject<LevelOneEnemy>()->SetPosition({ 5.0f , 0.75f , 2.0f });
	//AddGameObject<LevelOneEnemy>()->SetPosition({ 5.0f , 0.75f , 4.0f });

	//AddGameObject<LevelOneShooterEnemy>()->SetPosition({3.0f, 0.0f , -3.0f});
	//AddGameObject<LevelOneShooterEnemy>()->SetPosition({3.0f , 0.0f , -1.0f});
	////AddGameObject<LevelOneShooterEnemy>()->SetPosition({3.0f , 0.0f , 0.0f});
	//AddGameObject<LevelOneShooterEnemy>()->SetPosition({3.0f , 0.0f , 1.0f});
	//AddGameObject<LevelOneShooterEnemy>()->SetPosition({3.0f , 0.0f , 3.0f});

	//AddGameObject<LevelOneMidBoss>()->SetPosition({ 7.0f , 0.0f , 0.0f });

	//AddGameObject<LevelOneSwarmEnemy>()->SetPosition({ 6.0f , 1.5f , 3.0f });
	//AddGameObject<LevelOneSwarmEnemy>()->SetPosition({ 6.0f , 1.5f , -3.0f });
	//AddGameObject<LevelOneSwarmEnemy>()->SetPosition({ 6.0f , 3.0f , 4.0f });
	//AddGameObject<LevelOneSwarmEnemy>()->SetPosition({ 6.0f , 3.0f , -4.0f });

	//AddGameObject<LevelTwoEnemy>()->SetPosition({ 5.0f , 0.75f , -14.0f });
	//AddGameObject<LevelTwoEnemy>()->SetPosition({ 5.0f , 0.75f , -12.0f });
	//AddGameObject<LevelTwoEnemy>()->SetPosition({ 5.0f , 0.75f , -10.0f });
	//AddGameObject<LevelTwoEnemy>()->SetPosition({ 5.0f , 0.75f , -8.0f });
	//AddGameObject<LevelTwoEnemy>()->SetPosition({ 5.0f , 0.75f , -6.0f });

	//AddGameObject<LevelTwoShooterEnemy>()->SetPosition({ 3.0f, 0.0f , -14.0f });
	//AddGameObject<LevelTwoShooterEnemy>()->SetPosition({ 3.0f , 0.0f , -12.0f });
	//AddGameObject<LevelTwoShooterEnemy>()->SetPosition({ 3.0f , 0.0f , -10.0f });
	//AddGameObject<LevelTwoShooterEnemy>()->SetPosition({ 3.0f , 0.0f , -8.0f });
	//AddGameObject<LevelTwoShooterEnemy>()->SetPosition({ 3.0f , 0.0f , -6.0f });

	//AddGameObject<LevelThreeEnemy>()->SetPosition({ 9.0f , 1.75f , 14.0f });
	//AddGameObject<LevelThreeEnemy>()->SetPosition({ 9.0f , 1.75f , 12.0f });
	//AddGameObject<LevelThreeEnemy>()->SetPosition({ 9.0f , 1.75f , 10.0f });
	//AddGameObject<LevelThreeEnemy>()->SetPosition({ 9.0f , 1.75f , 8.0f });
	//AddGameObject<LevelThreeEnemy>()->SetPosition({ 9.0f , 1.75f , 6.0f });

	//AddGameObject<LevelThreeShooterEnemy>()->SetPosition({ 7.0f,  1.0f , 14.0f });
	//AddGameObject<LevelThreeShooterEnemy>()->SetPosition({ 7.0f , 1.0f , 12.0f });
	//AddGameObject<LevelThreeShooterEnemy>()->SetPosition({ 7.0f , 1.0f , 10.0f });
	//AddGameObject<LevelThreeShooterEnemy>()->SetPosition({ 7.0f , 1.0f , 8.0f });
	//AddGameObject<LevelThreeShooterEnemy>()->SetPosition({ 7.0f , 1.0f , 6.0f });

	//AddGameObject<LevelFourEnemy>()->SetPosition({ 9.0f , 1.75f , -14.0f });
	//AddGameObject<LevelFourEnemy>()->SetPosition({ 9.0f , 1.75f , -12.0f });
	//AddGameObject<LevelFourEnemy>()->SetPosition({ 9.0f , 1.75f , -10.0f });
	//AddGameObject<LevelFourEnemy>()->SetPosition({ 9.0f , 1.75f , -8.0f });
	//AddGameObject<LevelFourEnemy>()->SetPosition({ 9.0f , 1.75f , -6.0f });

	//AddGameObject<LevelFourShooterEnemy>()->SetPosition({ 7.0f,  1.0f , -14.0f });
	//AddGameObject<LevelFourShooterEnemy>()->SetPosition({ 7.0f , 1.0f , -12.0f });
	//AddGameObject<LevelFourShooterEnemy>()->SetPosition({ 7.0f , 1.0f , -10.0f });
	//AddGameObject<LevelFourShooterEnemy>()->SetPosition({ 7.0f , 1.0f , -8.0f });
	//AddGameObject<LevelFourShooterEnemy>()->SetPosition({ 7.0f , 1.0f , -6.0f });

	//AddGameObject<LevelFiveEnemy>()->SetPosition({ 5.0f , 0.75f , 14.0f });
	//AddGameObject<LevelFiveEnemy>()->SetPosition({ 5.0f , 0.75f , 12.0f });
	//AddGameObject<LevelFiveEnemy>()->SetPosition({ 5.0f , 0.75f , 10.0f });
	//AddGameObject<LevelFiveEnemy>()->SetPosition({ 5.0f , 0.75f , 8.0f });
	//AddGameObject<LevelFiveEnemy>()->SetPosition({ 5.0f , 0.75f , 6.0f });

	//AddGameObject<LevelFiveShooterEnemy>()->SetPosition({ 3.0f, 0.0f , 14.0f });
	//AddGameObject<LevelFiveShooterEnemy>()->SetPosition({ 3.0f , 0.0f , 12.0f });
	//AddGameObject<LevelFiveShooterEnemy>()->SetPosition({ 3.0f , 0.0f , 10.0f });
	//AddGameObject<LevelFiveShooterEnemy>()->SetPosition({ 3.0f , 0.0f , 8.0f });
	//AddGameObject<LevelFiveShooterEnemy>()->SetPosition({ 3.0f , 0.0f , 6.0f });


	/*for(int i = -12 ; i < 13 ; i+=6)
	{
		BaseAttackSlipDamage* slipdamage = AddGameObject<BaseAttackSlipDamage>();
		slipdamage->SetPosition({ (float)i , 5.0f , 5.0f });
		slipdamage->SetVelocity({ 0.0f , -0.25f , 0.0f });
		slipdamage->SetScale({ 0.5f , 0.5f ,0.5f });
		slipdamage->SetRadius(3.0f);
		slipdamage->SetLivingFrames(3000);
	}*/

	/*AddGameObject<LevelOneMidBoss>()->SetPosition({ 40.0f, 0.5f, 40.0f });*/

	/*AddGameObject<Score>(4);
	AddGameObject<HPUI>(4);
	AddGameObject<EXPUI>(4);*/
	AddGameObject<Pause>(4);
	AddGameObject<Fade>(4);
	AddGameObject<AttackManager>(5);
	GetGameObject<Fade>()->SetFade(FADE_IN);

	m_pModelManager = new ModelManager;

	m_State = GAME_FADEIN;

	//Manager::GetAudio()->Load("asset\\audio\\bgm.wav");
	Manager::GetAudio()->Load("asset\\audio\\Devine-Fencer.wav");
	Manager::GetAudio()->Play(true);
}

void Game::Uninit()
{
	Manager::GetAudio()->Uninit();
	delete m_pTimer;
	m_pTimer = nullptr;

	delete m_pModelManager;
	m_pModelManager = nullptr;

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



		if ((m_Input->GetKeyTrigger(KK_P) && !p_contorller->IsConnected()) || p_contorller->Controller_IsJustPressed(p_contorller->GetButtonForTrigger(XINPUT_GAMEPAD_START)))
		{
			m_State = GAME_PAUSE;

		}
	}
	else if (m_State == GAME_PAUSE)
	{
	

		if ((m_Input->GetKeyTrigger(KK_P) && !p_contorller->IsConnected()) || p_contorller->Controller_IsJustPressed(p_contorller->GetButtonForTrigger(XINPUT_GAMEPAD_START)))
		{
			m_State = GAME_PLAY;
		}

		if ((m_Input->GetKeyTrigger(KK_ENTER) && !p_contorller->IsConnected()) || p_contorller->Controller_IsJustPressed(p_contorller->GetButtonForTrigger(XINPUT_GAMEPAD_B)))
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

