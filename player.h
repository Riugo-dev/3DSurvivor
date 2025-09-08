//********************************************************************************
//
// player.h[プレイヤー]
//
//															Author :Riugo Honda
//															Date   :2025/05/14
// -------------------------------------------------------------------------------
//															Last Edited:2025/05/14
//********************************************************************************
#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "gameobject.h"

class ModelRenderer;

class Player:public GameObject
{
private:

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ModelRenderer* m_pModelRenderer;

	//経験値とレベル関係の名メモ
	//現在考えているのが武器のみで各種武器は５段階のレベリング
	//つまりマックスレベルを１６として開始レベルを１
	//一段階のレベル上昇で武器強化を武器取得を選べるようにする
	enum Level
	{
		LEVEL_ONE = 1,
		LEVEL_TWO,
		LEVEL_THREE,
		LEVEL_FOUR,
		LEVEL_FIVE,
		LEVEL_SIX,
		LEVEL_SEVEN,
		LEVEL_EIGHT,
		LEVEL_NINE,
		LEVEL_TEN,
		LEVEL_ELEVEN,
		LEVEL_TWELVE,
		LEVEL_THIRTEEN,
		LEVEL_FOURTEEN,
		LEVEL_FIFTEEN,
		LEVEL_MAX,
	};

	int NecessaryExpForNextLevel = 0;//次のレベルまでの必要経験値
	Level PlayerCurrentLevel = LEVEL_ONE;//現在のレベル表記用に使用
	int TotalExpOfPlayer = 0;//全体獲得経験値
	
public:
	Player(Vector3 size = { 1.0f , 1.0f , 1.0f }, Vector3 position = { 0.0f , 0.0f , 0.0f });
	~Player();

	void Init(Input*) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:

};

#endif // !_PLAYER_H_

