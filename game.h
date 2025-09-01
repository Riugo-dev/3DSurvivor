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
public:
	void Init(Input*) override;		//‰Šú‰»
	void Update() override;
};

#endif // !_GAME_H_


