//********************************************************************************
//
// player.cpp[プレイヤー]
//
//															Author :Riugo Honda
//															Date   :2025/05/14
// -------------------------------------------------------------------------------
//															Last Edited:2025/05/14
//********************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "modelRenderer.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "scene.h"

#include "player.h"

#define INVINCIBLEFRAME_AFTERDAMAGE (90)

//********************************************************************************
//関数
//********************************************************************************
Player::Player(Vector3 size, Vector3 position) 
{
	m_pModelRenderer = new ModelRenderer();
	m_pModelRenderer->Load("asset\\model\\player.obj");

	m_Scale = size;
	m_Position = position;
	m_Rotation = { 0.0f , 0.0f , 0.0f };

	m_NecessaryExpForNextLevel = 100;//次のレベルまでの必要経験値
	m_PlayerCurrentLevel = LEVEL_ONE;//現在のレベル表記用に使用
	m_TotalExpOfPlayer = 0;//全体獲得経験値

	m_HP = 5;
	m_InvinceibleFrameCount = 0;
	m_IsInvinceble = false;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");
	
}

Player::~Player()
{ 
	delete m_pModelRenderer;
	

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Player::Init(Input* p_input)
{
	m_pInput = p_input;
}

void Player::Uninit()
{

}

void Player::Update()
{
	Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();

	if (m_pInput->GetKeyPress(KK_A))
	{
		//m_Position += Vector3(-1.0f, 0.0f, 0.0f);
		m_Position += -p_camera->GetRight() * 0.1f;
	}
	
	if (m_pInput->GetKeyPress(KK_D))
	{
		//m_Position += Vector3(1.0f, 0.0f, 0.0f);
		m_Position += p_camera->GetRight() * 0.1f;
	}
	
	if (m_pInput->GetKeyPress(KK_W))
	{
		//m_Position += Vector3(0.0f, 0.0f, 1.0f);
		m_Position += p_camera->GetFoward() * 0.1f;
	}
	
	if (m_pInput->GetKeyPress(KK_S))
	{
		//m_Position += Vector3(0.0f, 0.0f, -1.0f);
		m_Position += -p_camera->GetFoward() * 0.1f;
	}

	Vector3 rotation = p_camera->GetRotation();
	m_Rotation.m_y = rotation.m_y;

	if (m_pInput->GetKeyTrigger(KK_SPACE))
	{
		Manager::GetScene()->AddGameObject<Bullet>();

		//エルミーと用
		/*Bullet* bullet = Manager::AddGameObject<Bullet>();
		bullet->SetPosition(m_Position);
		
		Enemy* enemy = Manager::GetGameObject<Enemy>();
		bullet->Shot(m_Position, enemy->GetPosition());*/
	}

	if (m_IsInvinceble)
	{
		m_InvinceibleFrameCount++;

		if (m_InvinceibleFrameCount >= INVINCIBLEFRAME_AFTERDAMAGE)
		{
			m_InvinceibleFrameCount = 0;
			m_IsInvinceble = false;
		}
	}

	/*m_Rotation.m_x += 0.1f;
	m_Rotation.m_y += 0.1f;*/
	//m_Rotation.z += 0.1f;

	//updateposition();
}

void Player::Draw()
{


	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	//平行移動行列の作成（表示座標を決める）
	XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.m_x , m_Position.m_y , m_Position.m_z);

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

void Player::GivePlayerExp(int gainingexp)
{
	if (m_PlayerCurrentLevel == LEVEL_MAX) return;

	m_TotalExpOfPlayer += gainingexp;

	if (m_TotalExpOfPlayer > m_NecessaryExpForNextLevel)
	{
		m_NecessaryExpForNextLevel = m_NecessaryExpForNextLevel + m_NecessaryExpForNextLevel * 1.1f;

		switch (m_PlayerCurrentLevel)
		{
		case LEVEL_ONE:
			m_PlayerCurrentLevel = LEVEL_TWO;
			break;
		case LEVEL_TWO:
			m_PlayerCurrentLevel = LEVEL_THREE;
			break;
		case LEVEL_THREE:
			m_PlayerCurrentLevel = LEVEL_FOUR;
			break;
		case LEVEL_FOUR:
			m_PlayerCurrentLevel = LEVEL_FIVE;
			break;
		case LEVEL_FIVE:
			m_PlayerCurrentLevel = LEVEL_SIX;
			break;
		case LEVEL_SIX:
			m_PlayerCurrentLevel = LEVEL_SEVEN;
			break;
		case LEVEL_SEVEN:
			m_PlayerCurrentLevel = LEVEL_EIGHT;
			break;
		case LEVEL_EIGHT:
			m_PlayerCurrentLevel = LEVEL_NINE;
			break;
		case LEVEL_NINE:
			m_PlayerCurrentLevel = LEVEL_TEN;
			break;
		case LEVEL_TEN:
			m_PlayerCurrentLevel = LEVEL_ELEVEN;
			break;
		case LEVEL_ELEVEN:
			m_PlayerCurrentLevel = LEVEL_TWELVE;
			break;
		case LEVEL_TWELVE:
			m_PlayerCurrentLevel = LEVEL_THIRTEEN;
			break;
		case LEVEL_THIRTEEN:
			m_PlayerCurrentLevel = LEVEL_FOURTEEN;
			break;
		case LEVEL_FOURTEEN:
			m_PlayerCurrentLevel = LEVEL_FIFTEEN;
			break;
		case LEVEL_FIFTEEN:
			m_PlayerCurrentLevel = LEVEL_MAX;
			break;
		}

		//ここのタイミングレベルアップのアイテム選択をさせる

		//もし過剰な経験値をもらってた場合の処理をここで行う
		GivePlayerExp(0);
	}
}

void Player::DamagePlayer()
{
	m_HP--;

	if (m_HP <= 0)
	{
		//ここでゲームオーバー処理追加

	}

	m_IsInvinceble = true;
	m_InvinceibleFrameCount = 0;
}
