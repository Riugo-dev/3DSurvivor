//********************************************************************************
//
// game.h[gameƒNƒ‰ƒX]
//
//															Author :Riugo Honda
//															Date   :2025/06/25
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/25
//********************************************************************************
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"

class Input;

class Game :public Scene
{
private:
	Input* m_Input;
	class GameTimer* m_pTimer;
public:
	void Init(Input*) override;		//‰Šú‰»
	void Uninit() override;

	void Update() override;

	GameTimer* GetGameTimer() { return m_pTimer; }
};

#endif // !_GAME_H_


