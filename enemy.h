//********************************************************************************
//
// enemy.h[エネミー]
//
//															Author :Riugo Honda
//															Date   :2025/06/04
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/04
//********************************************************************************
#pragma once

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "gameobject.h"

class ModelRenderer;

class Enemy :public GameObject
{
private:

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ModelRenderer* m_pModelRenderer;


public:
	Enemy(Vector3 size = { 0.5f , 0.5f , 0.5f }, Vector3 position = { 2.0f , 0.0f , 2.0f });
	~Enemy();

	void Init() override;
	void Uninit() override;


	void Update() override;


	//全て同じ処理でドローするのでここで一括で書く
	void Draw()override;

private:

};

#endif // !_ENEMY_H_


