//********************************************************************************
//
// shadowvolume.cpp[影付きモデル]
//
//															Author :Riugo Honda
//															Date   :2025/11/14
//********************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "texture.h"
#include "scene.h"
#include "camera.h"
#include "modelRenderer.h"
#include "shader_manager.h"
#include "input.h"
#include "model_manager.h"
#include "bullet.h"
#include "polygon.h"
#include "player.h"

#include "shadowvolume.h"

//********************************************************************************
//関数
//********************************************************************************
ShadowVolume::ShadowVolume(Vector3 size, Vector3 position)
{
	

	//m_EnvTexture = Texture::Load("asset\\model\\sky.jpg");

	m_Polygon2D = new Polygon2D();
	m_Polygon2D->Initialize(0.0f, 0.0f , SCREEN_WIDTH , SCREEN_HEIGHT , "asset\\texture\\black.png");

	m_ModelTag = SHADOW;

	m_Shader = SHADER_DIRECTIONLIGHTING;

	m_Scale = size;
	m_Position = position;
	m_Rotation = { 0.0f , 0.0f , 0.0f };

}

ShadowVolume::~ShadowVolume()
{
	delete m_pModelRenderer;

	m_Polygon2D->Uninit();
	delete m_Polygon2D;

	//m_VertexLayout->Release();
	//m_VertexShader->Release();
	//m_PixelShader->Release();
}

void ShadowVolume::Init()
{
	//m_pInput = p_input;
}

void ShadowVolume::Uninit()
{
	
}

void ShadowVolume::Update()
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	if (p_player == nullptr)return;

	m_Position.x = p_player->GetPosition().x;
	m_Position.z = p_player->GetPosition().z;
}

void ShadowVolume::Draw()
{


	ModelManager::SetShaders(m_ModelTag, SHADER_DIRECTIONLIGHTING);

	//テクスチャ設定
	//Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &m_EnvTexture);


	//平行移動行列の作成（表示座標を決める）
	XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	//回転行列（Z回転）行列の作成
	XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y + XM_PI, m_Rotation.z);

	//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
	XMMATRIX	ScalingMatrix = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);

	//ワールド行列の作成（ポリゴンの表示の仕方を指定する最終的な行列
	XMMATRIX	WorldMatrix = ScalingMatrix * RotationMatrix * TranslationMatrix;


	Renderer::SetWorldMatrix(WorldMatrix);

	Renderer::SetStencilShadowWrite();

	ModelManager::ModelDraw(m_ModelTag);

	Renderer::SetStencilShadowRead();

	//影ポリゴン描画
    m_Polygon2D->Draw();

	Renderer::SetStencilShadowNone();

}

