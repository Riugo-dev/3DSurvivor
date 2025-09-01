//********************************************************************************
//
//	box.h[箱]
//
//															Author :Riugo Honda
//															Date   :2025/05/21
// -------------------------------------------------------------------------------
//															Last Edited:2025/05/21
//********************************************************************************
#pragma once

#ifndef _BOX_H_
#define _BOX_H_

#include "gameobject.h"

class ModelRenderer;

class Box :public GameObject
{
private:

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ModelRenderer* m_pModelRenderer;


public:
	Box(Vector3 size = { 10.0f , 10.0f , 10.0f }, Vector3 position = { 10.0f , 0.0f , 0.0f });
	~Box();

	void Init(Input*) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:

};

#endif // !_BOX_H_


