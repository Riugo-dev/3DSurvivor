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
#include "title_ui.h"
#include "fade.h"
#include "controller.h"
#include "audio.h"

#include "model_manager.h"
#include "camera.h"
#include "skydome.h"
#include "player.h"
#include "meshField.h"
#include "wave.h"
#include "petal_particle.h"
#include "shadowvolume.h"

#include "title.h"

void Title::Init(Input* input)
{
	Renderer::Init();

	AddGameObject<Camera>(0)->Init(input);
	GetGameObject<Camera>()->SetCameraMode(CAMERA_MODE_TITLE);
	
	AddGameObject<SkyDome>()->SetPosition({ 0.0f , 0.0f , 0.0f });
	
	AddGameObject<Player>()->Init(input);
	GetGameObject<Player>()->SetMode(TITLE);

	AddGameObject<Wave>()->Init(nullptr);
	GetGameObject<Wave>()->SetPosition({ 0.0f , -1.0f , 0.0f });

	AddGameObject<TitleUI>(2);
	AddGameObject<Fade>(2)->SetFade(FADE_IN);

	AddGameObject<PetalParticle>();
	//AddGameObject<ShadowVolume>()->SetPosition({ 0.0f , -0.5f , 0.0f });
	
	MeshField* meshfield = AddGameObject<MeshField>(0);

	Manager::GetAudio()->Load("asset\\audio\\titlebgm.wav");
	Manager::GetAudio()->Play(true);

	m_pModelManager = new ModelManager;
	m_pModelManager->InitTitle();
}

void Title::Uninit()
{
	Manager::GetAudio()->Uninit();

	delete m_pModelManager;
	m_pModelManager = nullptr;

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

	if (m_Input->GetKeyPress(KK_UP) || Manager::GetController()->Controller_IsButtonDown(XINPUT_GAMEPAD_DPAD_UP))
	{
		Manager::GetAudio()->AddVolume(0.01f);
		//Manager::GetAudio()->SetVolumeMax();
	}

	if (m_Input->GetKeyPress(KK_DOWN) || Manager::GetController()->Controller_IsButtonDown(XINPUT_GAMEPAD_DPAD_DOWN))
	{
		Manager::GetAudio()->LowerVolume(0.01f);
		//Manager::GetAudio()->SetVolumeZero();
	}


	Scene::Update();
}
