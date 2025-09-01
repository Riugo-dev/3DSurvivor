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

