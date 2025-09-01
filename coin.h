//********************************************************************************
//
// coin.h[コイン]
//
//															Author :Riugo Honda
//															Date   :2025/06/04
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/04
//********************************************************************************
#pragma once

#ifndef _COIN_H_
#define _COIN_H_

#include "gameobject.h"

class ModelRenderer;
class Player;

class Coin :public GameObject
{
private:

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ModelRenderer* m_pModelRenderer;

	Vector3 m_Velocity;
	int m_LivingFrame;
public:
	Coin(Vector3 size = { 1.0f , 1.0f , 1.0f }, Vector3 position = { 0.0f , 0.0f , 0.0f });
	~Coin();

	void Init(Input*) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;


private:

};

#endif // !_COIN_H_



