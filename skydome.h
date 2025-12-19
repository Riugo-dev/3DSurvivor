//********************************************************************************
//
// skydome.h[空]
//
//															Author :Riugo Honda
//															Date   :2025/06/11
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/14
//********************************************************************************
#pragma once

#ifndef _SKYDOME_H_
#define _SKYDOME_H_

#include "gameobject.h"
#include "model_manager.h"

//class ModelRenderer;

class SkyDome :public GameObject
{
private:

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	//ModelRenderer* m_pModelRenderer;
	ModelTags m_ModelTag;

public:
	SkyDome(Vector3 size = { 100.0f , 100.0f , 100.0f }, Vector3 position = { 0.0f , -10.0f , 0.0f });
	~SkyDome();

	void Init(Input*) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:

};

#endif // !_SKYDOME_H_

