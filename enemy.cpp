//********************************************************************************
//
// enemy.cpp[エネミー]
//
//															Author :Riugo Honda
//															Date   :2025/06/04
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/04
//********************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "modelRenderer.h"
#include "input.h"
#include "bullet.h"

#include "enemy.h"

//********************************************************************************
//関数
//********************************************************************************
Enemy::Enemy(Vector3 size, Vector3 position)
{
	m_pModelRenderer = new ModelRenderer();
	m_pModelRenderer->Load("asset\\model\\EnemyTypeRed.obj");

	m_Scale = size;
	m_Position = position;
	m_Rotation = { 0.0f , /*(3.141569f / 180.0f) * 180.0f*/0.0f , 0.0f };

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

}

Enemy::~Enemy()
{
	delete m_pModelRenderer;


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Enemy::Init(Input* p_input)
{
	//m_pInput = p_input;
}

void Enemy::Uninit()
{

}

void Enemy::Update()
{
	//Camera* p_camera = Manager::GetGameObject<Camera>();

	//if (m_pInput->GetKeyPress(KK_A))
	//{
	//	//m_Position += Vector3(-1.0f, 0.0f, 0.0f);
	//	m_Position += -p_camera->GetRight() * 0.1f;
	//}

	//if (m_pInput->GetKeyPress(KK_D))
	//{
	//	//m_Position += Vector3(1.0f, 0.0f, 0.0f);
	//	m_Position += p_camera->GetRight() * 0.1f;
	//}

	//if (m_pInput->GetKeyPress(KK_W))
	//{
	//	//m_Position += Vector3(0.0f, 0.0f, 1.0f);
	//	m_Position += p_camera->GetFoward() * 0.1f;
	//}

	//if (m_pInput->GetKeyPress(KK_S))
	//{
	//	//m_Position += Vector3(0.0f, 0.0f, -1.0f);
	//	m_Position += -p_camera->GetFoward() * 0.1f;
	//}

	//Vector3 rotation = p_camera->GetRotation();
	//m_Rotation.m_y = rotation.m_y;

	/*m_Rotation.m_x += 0.1f;
	m_Rotation.m_y += 0.1f;*/
	//m_Rotation.z += 0.1f;

	//updateposition();
}

void Enemy::Draw()
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