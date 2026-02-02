//********************************************************************************
//
// scene.cpp[sceneの基底クラス]
//
//															Author :Riugo Honda
//															Date   :2025/06/25
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/25
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "gameobject.h"
#include "camera.h"
#include "input.h"
#include "game.h"
#include "gametimer.h"
#include "exp_item_manager.h"
#include "explosion_gpuparticle.h"

#include "scene.h"



//********************************************************************************
//関数
//********************************************************************************
void Scene::Init(Input* input)
{
	
}


void Scene::Uninit()
{
	

	for (auto& list : m_GameObjects)
	{
		for (auto itr :list)
		{
			itr->Uninit();

			delete itr;
			itr = nullptr;
		}

		/*m_GameObjects[i].clear();*/
		list.clear();
	}
}

void Scene::Update()
{
	for ( auto& list : m_GameObjects)
	{
		for (auto itr : list)
		{
			itr->Update();//ポリモーフィズム
		}
	}

	for ( auto& list : m_GameObjects)
	{
		for (auto itr = list.begin(); itr != list.end();)
		{
			if ((*itr)->GetDestroy()) {
				(*itr)->Uninit();
				delete* itr;
				itr = list.erase(itr);
				
			}
			else
			{
				++itr;
			}
		}
	}


}

void Scene::Draw()
{

	//Z値ソート
	Camera* camera = GetGameObject<Camera>();
	if(camera != nullptr)
	{
		Vector3 cameraPosition = camera->GetPosition();
		Vector3 cameraFoward = camera->GetFoward();


		//ラムダ式のかっこの中にアンパサンドを入れることでローカル変数にもアクセスできるようになる
		m_GameObjects[2].sort([&](GameObject* object1, GameObject* object2)
			{
				return object1->GetZ(cameraPosition, cameraFoward) > object2->GetZ(cameraPosition, cameraFoward);
			});
	}

	for (int i = 0; i < 6; i++/* auto& list : m_GameObjects*/)
	{
		for (auto itr : /*list*/  m_GameObjects[i])
		{
			itr->Draw();

		}

		if (i == 1 )
		{
			if (Manager::GetScene()->GetSceneType() == SCENE_GAME)
			{
				Game* game = dynamic_cast<Game*>(Manager::GetScene());

				game->GetGameTimer()->Draw();

				ExpItemManager::GetInstance()->Draw();

				/*if(game->GetGameState() == GAME_PLAY)
				{
					
				}*/
			}
		}
		else if (i == 2)
		{
			if (Manager::GetScene()->GetSceneType() == SCENE_GAME)
			{
				GPUExplosionParticle::GetInstance()->Draw();
			}
		}

	}

}