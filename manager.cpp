//********************************************************************************
//
// manager.cpp[全体管理する]
//
//															Author :Riugo Honda
//															Date   :2025/04/23
// -------------------------------------------------------------------------------
//															Last Edited:2025/04/23
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "input.h"
#include "scene.h"
#include "title.h"
#include "game.h"
#include "texture.h"


#include "manager.h"
//********************************************************************************
//グローバル変数
//********************************************************************************
Scene* Manager::m_Scene = nullptr;
Scene* Manager::m_NextScene = nullptr;
Input* Manager::m_Input;
//********************************************************************************
//関数
//********************************************************************************
void Manager::Init()
{
	Renderer::Init();
    m_Input = new Input;
	


	m_Scene = new Title();
	m_Scene->Init(m_Input);
}


void Manager::Uninit()
{
	m_Scene->Uninit();

	Texture::ReleaseAll();

	delete m_Input;
	Renderer::Uninit();
}

void Manager::Update()
{
	m_Input->Update();

	m_Scene->Update();


	
}

void Manager::Draw()
{
	Renderer::Begin();

	m_Scene->Draw();

	Renderer::End();

	//画面遷移
	if (m_NextScene != nullptr)
	{
		m_Scene->Uninit();
		delete m_Scene;

		Texture::ReleaseAll();

		ModelRenderer::UnloadAll();

		m_Scene = m_NextScene;
		m_Scene->Init(m_Input);

		m_NextScene = nullptr;
	}
}
