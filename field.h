//********************************************************************************
//
// field.h[フィールド]
//
//															Author :Riugo Honda
//															Date   :2025/05/14
// -------------------------------------------------------------------------------
//															Last Edited:2025/05/14
//********************************************************************************
#pragma once

#ifndef _FIELD_H_
#define _FIELD_H_

#include "gameobject.h"

class Field:public GameObject
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

	XMFLOAT3 m_VertexPosition[24] = {};

public:
	Field(Vector3 size = { 10.0f , 10.0f , 10.0f}, Vector3 position = { 0.0f , 0.0f , 0.0f}, int movementx = 0, int movementy = 0, Vector3 rotation = { 0.0f , 0.0f , 0.0f });
	~Field();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:

};

#endif // !_FIELD_H_
