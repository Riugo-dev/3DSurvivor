//********************************************************************************
//
// manager.h[全体管理する]
//
//															Author :Riugo Honda
//															Date   :2025/04/23
// -------------------------------------------------------------------------------
//															Last Edited:2025/04/23
//********************************************************************************
#pragma once

class Input;

class Manager
{
private:
	static class Scene* m_Scene;
	static class Scene* m_NextScene;
	static Input* m_Input;
	static class Controller* m_pController;
public:
	static void Init();		//初期化
	static void Uninit();	//終了処理
	static void Update();	//更新処理
	static void Draw();		//描画処理

	static Scene* GetScene() { return m_Scene; }
	static Controller* GetController() { return m_pController; }
	
	template <typename S>
	static void SetScene()
	{//あくまでの次のシーンの予約
		m_NextScene = new S;
	}
};