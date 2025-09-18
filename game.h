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

typedef enum
{
	GAME_PLAY = 0,
	PLAYER_LEVELUP,
	GAME_PAUSE,
	GAME_RESULT,
	GAME_FADEIN,
	GAME_FADEOUT,
}GameState;

class Game :public Scene
{
private:
	class ModelManager* m_pModelManager;
	class Pause* m_pPause;
	Input* m_Input;
	class GameTimer* m_pTimer;
	static GameState m_State;
	ID3D11ShaderResourceView* m_TexturePause;//ˆê’â~ˆê–‡ŠG
	ID3D11ShaderResourceView* m_TextureBackGround;//ˆê’â~”wŒi
public:
	void Init(Input*) override;		//‰Šú‰»
	void Uninit() override;

	void Update() override;
	void Draw() override;

	GameTimer* GetGameTimer() { return m_pTimer; }

	static GameState GetGameState() { return m_State; }
	static void SetGameState(GameState state) { m_State = state; }

};

#endif // !_GAME_H_


