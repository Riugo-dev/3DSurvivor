//********************************************************************************
//
// exp_item.h[弾]
//
//															Author :Riugo Honda
//															Date   :2025/09/01
//********************************************************************************

#ifndef _EXP_ITEM_H_
#define _EXP_ITEM_H_

#include "main.h"
#include "gameobject.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "model_manager.h"

class ExpItem:public GameObject
{
protected:
	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ID3D11VertexShader* m_VertexShaderEdge; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShaderEdge; //ピクセルシェーダーオブジェクト

	//ModelRenderer* m_pModelRenderer = nullptr;

	int m_Exp = 0;

	int m_FrameCount = 0;
	
	ModelTags m_ModelTag;

	/*Vector3 m_Position = { 0.0f , 0.0f , 0.0f };
	Vector3 m_Size = {1.0f , 1.0f ,1.0f};*/

public:
	//ExpItem();
	~ExpItem() = default;

	int GetExp() { return m_Exp; }

	void Init(Input*) override {}

	void Uninit() override{};

	void Update() override
	{
		m_Rotation.m_y += 0.1f;

		Player* player = Manager::GetScene()->GetGameObject<Player>();

		Vector3 distance = player->GetPosition() - m_Position;
		float length = distance.length();

		if (length < m_Scale.m_y * 1.65f)
		{
			player->GivePlayerExp(m_Exp);

			m_IsDestroy = true;
		}

		if (m_FrameCount > 3000)
		{
			m_IsDestroy = true;
		}
		m_FrameCount++;

	}

	//全て同じ処理でドローするのでここで一括で書く
	void Draw() override
	{

		{//通常の描画
			//入力レイアウト設定
			Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

			//シェーダ設定
			Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
			Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


			//平行移動行列の作成（表示座標を決める）
			XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.m_x, m_Position.m_y, m_Position.m_z);

			//回転行列（Z回転）行列の作成
			XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.m_x, m_Rotation.m_y, m_Rotation.m_z);

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

			//m_pModelRenderer->Draw();

			ModelManager::ModelDraw(m_ModelTag);
		}


		{//輪郭線の描画
			//頂点シェーダーをセット
			Renderer::GetDeviceContext()->VSSetShader(m_VertexShaderEdge, NULL, 0);
			//ピクセルシェーダーをセット
			Renderer::GetDeviceContext()->PSSetShader(m_PixelShaderEdge, NULL, 0);

			Renderer::SetCullMode(D3D11_CULL_FRONT);

			//描画
			//m_pModelRenderer->Draw();
			ModelManager::ModelDraw(m_ModelTag);

			Renderer::SetCullMode(D3D11_CULL_BACK);
		}
	}
};

//経験値の幅の考え
//LowTier　５　～　２０　EXP
//MidTier　２１ ～　５０　EXP
//HighTier  ５１　～　１００　EXP
//経験値の幅は価値の高いものほど大きい
//また経験値アイテムは敵の強さによって使うスポナーを変えるべきかな
//例えば、強い適ほど高い確率でHighTierの経験値アイテムを落とす
#endif // !_EXP_ITEM_H
