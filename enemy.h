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
	Enemy(Vector3 size = { 1.0f , 1.0f , 1.0f }, Vector3 position = { 2.0f , 0.0f , 2.0f });
	~Enemy();

	void Init(Input*) override;
	void Uninit() override;


	void Update() override;


	//全て同じ処理でドローするのでここで一括で書く
	void Draw()
	{
		//入力レイアウト設定
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		//シェーダ設定
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


		//平行移動行列の作成（表示座標を決める）
		XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.m_x, m_Position.m_y, m_Position.m_z);

		//回転行列（Z回転）行列の作成
		XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.m_x, m_Rotation.m_y + XM_PI, m_Rotation.m_z);

		//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
		XMMATRIX	ScalingMatrix = XMMatrixScaling(m_Scale.m_x, m_Scale.m_y, m_Scale.m_z);

		//ワールド行列の作成（ポリゴンの表示の仕方を指定する最終的な行列
		XMMATRIX	WorldMatrix = ScalingMatrix * RotationMatrix * TranslationMatrix;

		//マテリアル設定
		MATERIAL material{};
		material.Diffuse = { 1.0f , 1.0f , 1.0f , 1.0f };
		material.TextureEnable = false;
		Renderer::SetMaterial(material);



		Renderer::SetWorldMatrix(WorldMatrix);

		m_pModelRenderer->Draw();
	}

private:

};

#endif // !_ENEMY_H_


