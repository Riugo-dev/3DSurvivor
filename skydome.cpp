//********************************************************************************
//
// skydome.cpp[空]
//
//															Author :Riugo Honda
//															Date   :2025/06/11
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/14
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "modelRenderer.h"

#include "skydome.h"

//********************************************************************************
//関数
//********************************************************************************
SkyDome::SkyDome(Vector3 size, Vector3 position)
{
	/*m_pModelRenderer = new ModelRenderer();
	m_pModelRenderer->Load("asset\\model\\sky.obj");*/

	m_ModelTag = SKYDOME;

	m_Scale = size;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

}

SkyDome::~SkyDome()
{
	/*delete m_pModelRenderer;*/


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void SkyDome::Init(Input* p_input)
{
	//m_pInput = p_input;
}

void SkyDome::Uninit()
{

}

void SkyDome::Update()
{
	m_Rotation.m_z += 0.001;
	
}

void SkyDome::Draw()
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

	Renderer::SetWorldMatrix(WorldMatrix);

	//マテリアル設定
	MATERIAL material{};
	material.Diffuse = { 1.0f , 1.0f , 1.0f , 1.0f };
	material.TextureEnable = false;
	Renderer::SetMaterial(material);

	//m_pModelRenderer->Draw();
	ModelManager::ModelDraw(m_ModelTag);
}


