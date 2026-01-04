//********************************************************************************
//
// bullet.h[弾]
//
//															Author :Riugo Honda
//															Date   :2025/06/04
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/04
//********************************************************************************
#pragma once

#ifndef _BULLET_H_
#define _BULLET_H_

#include "gameobject.h"

class ModelRenderer;
class Player;

class Bullet :public GameObject
{
private:

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ModelRenderer* m_pModelRenderer;

	Vector3 m_Velocity;
	int m_LivingFrame;

	//弾のエルミート曲線軌道用
	Vector3 m_StartPosition;
	Vector3 m_EndPosition;
	Vector3 m_StartVector;
	Vector3 m_EndVector;
	float m_Time;
public:
	Bullet(Vector3 size = { 1.0f , 1.0f , 1.0f }, Vector3 position = { 0.0f , 0.0f , 0.0f });
	~Bullet();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void Shot(Vector3 startpos, Vector3 endpos)
	{
		m_StartPosition = startpos;
		m_EndPosition = endpos;
		m_StartVector = { 20.0f , 20.0f , 0.0f };
		m_EndVector = { 20.0f , -20.0f , 0.0f };
		m_Time = 0.0f;
	}
private:

};

#endif // !_BULLET_H_


