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
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "scene.h"
#include "game.h"
#include "controller.h"
#include "model_manager.h"
#include "shader_manager.h"

#include "player.h"

#define INVINCIBLEFRAME_AFTERDAMAGE (90)

//********************************************************************************
//関数
//********************************************************************************
Player::Player(Vector3 size, Vector3 position) 
{
	m_Scale = size;
	m_Position = { -3.5f , 0.5f , 0.0f };
	m_Rotation = { 0.0f , 0.0f , 0.0f };

	m_NecessaryExpForNextLevel = 100;//次のレベルまでの必要経験値
	m_PlayerCurrentLevel = LEVEL_ONE;//現在のレベル表記用に使用
	m_TotalExpOfPlayer = 0;//全体獲得経験値

	m_HP = 5;
	m_InvinceibleFrameCount = 0;
	m_IsInvinceble = false;
	m_ModelTag = PLAYER;
}

Player::~Player()
{ 
	
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
	Controller* p_controller = Manager::GetController();

	if ((m_pInput->GetKeyPress(KK_A) && !p_controller->IsConnected()) || p_controller->Controller_LeftStickIsLeft())
	{
		//m_Position += Vector3(-1.0f, 0.0f, 0.0f);
		m_Position += -p_camera->GetRight() * 0.1f;
	}
	
	if ((m_pInput->GetKeyPress(KK_D) && !p_controller->IsConnected()) || p_controller->Controller_LeftStickIsRight())
	{
		//m_Position += Vector3(1.0f, 0.0f, 0.0f);
		m_Position += p_camera->GetRight() * 0.1f;
	}
	
	if ((m_pInput->GetKeyPress(KK_W) && !p_controller->IsConnected()) || p_controller->Controller_LeftStickIsUp())
	{
		//m_Position += Vector3(0.0f, 0.0f, 1.0f);
		m_Position += p_camera->GetFoward() * 0.1f;
	}
	
	if ((m_pInput->GetKeyPress(KK_S) && !p_controller->IsConnected()) || p_controller->Controller_LeftStickIsDown())
	{
		//m_Position += Vector3(0.0f, 0.0f, -1.0f);
		m_Position += -p_camera->GetFoward() * 0.1f;
	}

	Vector3 rotation = p_camera->GetRotation();
	m_Rotation.m_y = rotation.m_y;

	//if (m_pInput->GetKeyTrigger(KK_SPACE))
	//{
	//	Manager::GetScene()->AddGameObject<Bullet>();

	//	//エルミーと用
	//	/*Bullet* bullet = Manager::AddGameObject<Bullet>();
	//	bullet->SetPosition(m_Position);
	//	
	//	Enemy* enemy = Manager::GetGameObject<Enemy>();
	//	bullet->Shot(m_Position, enemy->GetPosition());*/
	//}

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


	{
		ModelManager::SetShaders(m_ModelTag, SHADER_TOON);


		//平行移動行列の作成（表示座標を決める）
		XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.m_x, m_Position.m_y, m_Position.m_z);

		//回転行列（Z回転）行列の作成
		XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.m_x, m_Rotation.m_y * XM_PI, m_Rotation.m_z);

		//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
		XMMATRIX	ScalingMatrix = XMMatrixScaling(m_Scale.m_x, m_Scale.m_y, m_Scale.m_z);

		//ワールド行列の作成（ポリゴンの表示の仕方を指定する最終的な行列
		XMMATRIX	WorldMatrix = ScalingMatrix * RotationMatrix * TranslationMatrix;

		//マテリアル設定
		MATERIAL material{};
		material.Diffuse = { 1.0f , 1.0f , 1.0f , 1.0f };
		material.TextureEnable = true;


		Renderer::SetMaterial(material);


		Renderer::SetWorldMatrix(WorldMatrix);

		//m_pModelRenderer->Draw();
		ModelManager::ModelDraw(m_ModelTag);
	}


}

void Player::GivePlayerExp(int gainingexp)
{
	

	m_TotalExpOfPlayer += gainingexp;

	if (m_PlayerCurrentLevel == LEVEL_MAX) return;

	if (m_TotalExpOfPlayer > m_NecessaryExpForNextLevel)
	{
		m_PrevousExpCount = m_NecessaryExpForNextLevel;
		m_NecessaryExpForNextLevel += 100 * (m_PlayerCurrentLevel + 1);


		Game::SetGameState(PLAYER_LEVELUP);
		switch (m_PlayerCurrentLevel)
		{
		case LEVEL_ONE:
			m_PlayerCurrentLevel = LEVEL_TWO;
			//ここのタイミングレベルアップのアイテム選択をさせる
			
			break;
		case LEVEL_TWO:
			m_PlayerCurrentLevel = LEVEL_THREE;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_THREE:
			m_PlayerCurrentLevel = LEVEL_FOUR;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_FOUR:
			m_PlayerCurrentLevel = LEVEL_FIVE;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_FIVE:
			m_PlayerCurrentLevel = LEVEL_SIX;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_SIX:
			m_PlayerCurrentLevel = LEVEL_SEVEN;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_SEVEN:
			m_PlayerCurrentLevel = LEVEL_EIGHT;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_EIGHT:
			m_PlayerCurrentLevel = LEVEL_NINE;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_NINE:
			m_PlayerCurrentLevel = LEVEL_TEN;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_TEN:
			m_PlayerCurrentLevel = LEVEL_ELEVEN;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_ELEVEN:
			m_PlayerCurrentLevel = LEVEL_TWELVE;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_TWELVE:
			m_PlayerCurrentLevel = LEVEL_THIRTEEN;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_THIRTEEN:
			m_PlayerCurrentLevel = LEVEL_FOURTEEN;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_FOURTEEN:
			m_PlayerCurrentLevel = LEVEL_FIFTEEN;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_FIFTEEN:
			m_PlayerCurrentLevel = LEVEL_SIXTEEN;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_SIXTEEN:
			m_PlayerCurrentLevel = LEVEL_SEVENTEEN;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_SEVENTEEN:
			m_PlayerCurrentLevel = LEVEL_EIGHTTEEN;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_EIGHTTEEN:
			m_PlayerCurrentLevel = LEVEL_NINETEEN;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_NINETEEN:
			m_PlayerCurrentLevel = LEVEL_MAX;
			//ここのタイミングレベルアップのアイテム選択をさせる
			Game::SetGameState(PLAYER_LEVELUP);
			break;
		case LEVEL_MAX:
			
			break;
		}

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
