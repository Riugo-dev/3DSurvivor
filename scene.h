//********************************************************************************
//
// scene.h[sceneの基底クラス]
//
//															Author :Riugo Honda
//															Date   :2025/06/25
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/25
//********************************************************************************
#pragma once

#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include <list>
#include "gameobject.h"

class Input;

typedef enum
{
	SCENE_NONE = -1,
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT,
}SceneType;

class Scene
{
private:
	Input* m_Input;
	SceneType m_type;
	std::list<GameObject*> m_GameObjects[6];//リストを三個分作る-> 0がカメラ,1が3Dオブジェクト, 2がエフェクト,3が2Dオブシェクト,4 攻撃関連の保存
public:
	virtual ~Scene() {};

	virtual void Init(Input*);		//初期化
	virtual void Uninit();	//終了処理
	virtual void Update();	//更新処理
	virtual void Draw();		//描画処理

	Input* GetInput() { return m_Input; }

	SceneType GetSceneType() { return m_type; }
	void SetSceneType(SceneType type) { m_type = type; }

	template <typename T>//テンプレート
	T* AddGameObject(int Layer = 1)
	{
		T* gameobject = new T;

		m_GameObjects[Layer].push_back(gameobject);
		return gameobject;

	}

	template <typename ObjectType>//テンプレート
	ObjectType* GetGameObject()
	{
		for (auto& list : m_GameObjects)
		{
			for (auto itr : list)
			{
				ObjectType* find = dynamic_cast<ObjectType*>(itr);

				if (find != nullptr)
				{
					return find;
				}
			}
		}

		return nullptr;

	}

	//テンプレートでのエラーの原因を見つけ出すのはかなり難しいため書くとき最新の注意を払うこと
	template <typename ObjectType>//テンプレート
	std::vector<ObjectType*> GetGameObjects()
	{
		std::vector<ObjectType*> finds;//見つけた同方オブジェクトを保存するヴェクター
		for (auto& list : m_GameObjects)
		{
			for (auto itr : list)
			{
				ObjectType* find = dynamic_cast<ObjectType*>(itr);

				if (find != nullptr)
				{
					finds.push_back(find);
				}
			}
		}

		return finds;

	}

	
};


#endif // !_SCENE_H_


