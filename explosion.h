//********************************************************************************
//
// explosion.h[爆発エフェクト]
//
//															Author :Riugo Honda
//															Date   :2025/06/11
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/14
//********************************************************************************
#pragma once

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "gameobject.h"

class Explosion :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_WorldBuffer;

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ID3D11ShaderResourceView* m_Texture;

	int m_movement_x;
	int m_movement_y;

	int m_Frame_x;
	int m_Frame_y;
	int m_Frame_max;
	int m_Frame_count;

	XMFLOAT3 m_VertexPosition[24] = {};

public:
	Explosion(Vector3 size = { 5.0f , 5.0f , 5.0f }, Vector3 position = { 0.0f , 0.0f , 0.0f }, int movementx = 0, int movementy = 0, Vector3 rotation = { 0.0f , 0.0f , 0.0f });
	~Explosion();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:

};

#endif // !_EXPLOSION_H_
