//********************************************************************************
//
// shadowvolume.h[影付きモデル]
//
//															Author :Riugo Honda
//															Date   :2025/11/14
//********************************************************************************
#pragma once

#ifndef _SHADOWVOLUME_H_
#define _SHADOWVOLUME_H_

#include "gameobject.h"

class ModelRenderer;

class ShadowVolume :public GameObject
{
private:

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ID3D11ShaderResourceView* m_EnvTexture{};

	ModelRenderer* m_pModelRenderer;

	ModelTags m_ModelTag;

	class Polygon2D* m_Polygon2D;
public:
	ShadowVolume(Vector3 size = { 1.0f , 1.0f , 1.0f }, Vector3 position = { 2.0f , -0.5f , 2.0f });
	~ShadowVolume();

	void Init(Input*) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:

};

#endif // !_SHADOWVOLUME_H_




