//********************************************************************************
//
// attack_manager.h[攻撃管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/15
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "manager.h"
#include "scene.h"
#include "game.h"
#include "input.h"
#include "bulletattack.h"
#include "swordattack.h"
#include "shurikenattack.h"
#include "bombattack.h"
#include "player.h"
#include "controller.h"


#include "attack_manager.h"
#include "result_ui.h"

AttackManager::AttackManager()
{
	VERTEX_3D vertex[4] = {};

	float x = 0.0f;//描画開始位置・・・X座標
	float y = 0.0f;//描画開始位置・・・Y座標
	float w = SCREEN_WIDTH;//描画物の幅
	float h = SCREEN_HEIGHT;//描画物の高さ

	float tw = 1;
	float th = 1;
	float tx = 0;
	float ty = 0;

	vertex[0].Position = XMFLOAT3(x, y, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	vertex[0].TexCoord = XMFLOAT2(tx, ty);
	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;//ここをダイナミックに変更しなければ途中でテクスチャマッピングを変えれない
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//ここをwriteに変更

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	m_TextureBG = Texture::Load("asset\\texture\\pauseBG.png");
	m_TextureWordBG = Texture::Load("asset\\texture\\tatami.jpg");
	m_TextureShuriken = Texture::Load("asset\\texture\\shuriken.png");
	m_TextureSword = Texture::Load("asset\\texture\\sword.png");
	m_TextureBullet = Texture::Load("asset\\texture\\bullet.png");
	m_TextureBomb = Texture::Load("asset\\texture\\bomb.png");
	m_TexturePowerUp = Texture::Load("asset\\texture\\LevelUp.png");
	m_TextureLVMAX = Texture::Load("asset\\texture\\LVMAX.png");
	m_TextureSelect = Texture::Load("asset\\texture\\select.png");

	m_SelectNumber = 0;

	m_pInput = Manager::GetScene()->GetInput();

	Manager::GetScene()->AddGameObject<BombAttack>(5);
	Manager::GetScene()->AddGameObject<SwordAttack>(5);
	Manager::GetScene()->AddGameObject<BulletAttack>(5);
	Manager::GetScene()->AddGameObject<ShurikenAttack>(5);

	m_SlideAnimation = SCREEN_WIDTH;
}

AttackManager::~AttackManager()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void AttackManager::Update()
{
	if (Game::GetGameState() == PLAYER_LEVELUP)
	{
		if (m_SlideAnimation > 0)
		{
			m_SlideAnimation -= (SCREEN_WIDTH / 10);

			if (m_SlideAnimation <= 0)
			{
				m_SlideAnimation = 0;
			}
		}

		Controller* p_contorller = Manager::GetController();

		if ((m_pInput->GetKeyTrigger(KK_RIGHT) && !p_contorller->IsConnected()) || p_contorller->LeftStickIsRightContinuous())
		{
			m_SelectNumber++;

			if (m_SelectNumber > 3)
			{
				m_SelectNumber = 0;
			}
		}
		else if ((m_pInput->GetKeyTrigger(KK_LEFT) && !p_contorller->IsConnected()) || p_contorller->LeftStickIsLeftContinuous())
		{
			m_SelectNumber--;

			if (m_SelectNumber < 0)
			{
				m_SelectNumber = 3;
			}
		}

		if ((m_pInput->GetKeyTrigger(KK_ENTER) && !p_contorller->IsConnected()) || p_contorller->Controller_IsJustPressed(p_contorller->GetButtonForTrigger(XINPUT_GAMEPAD_B)))
		{
			switch (m_SelectNumber)

			case 0:
			{			{
				if (Manager::GetScene()->GetGameObject<BulletAttack>()->GetLevel() == ATT_LVMAX) return;

				Manager::GetScene()->GetGameObject<BulletAttack>()->SetToNextLevel();
				
				Game::SetGameState(GAME_PLAY);

				//もし過剰に経験値がある場合の確認処理
				Manager::GetScene()->GetGameObject<Player>()->GivePlayerExp(0);
			}
				break;
			case 1:
			{
				if (Manager::GetScene()->GetGameObject<BombAttack>()->GetLevel() == ATT_LVMAX) return;

				Manager::GetScene()->GetGameObject<BombAttack>()->SetToNextLevel();

				Game::SetGameState(GAME_PLAY);

				//もし過剰に経験値がある場合の確認処理
				Manager::GetScene()->GetGameObject<Player>()->GivePlayerExp(0);
			}
				break;
			case 2:
			{
				if (Manager::GetScene()->GetGameObject<SwordAttack>()->GetLevel() == ATT_LVMAX) return;

				Manager::GetScene()->GetGameObject<SwordAttack>()->SetToNextLevel();

				Game::SetGameState(GAME_PLAY);

				//もし過剰に経験値がある場合の確認処理
				Manager::GetScene()->GetGameObject<Player>()->GivePlayerExp(0);
			}
				break;
			case 3:
			{
				if (Manager::GetScene()->GetGameObject<ShurikenAttack>()->GetLevel() == ATT_LVMAX) return;

				Manager::GetScene()->GetGameObject<ShurikenAttack>()->SetToNextLevel();

				Game::SetGameState(GAME_PLAY);

				//もし過剰に経験値がある場合の確認処理
				Manager::GetScene()->GetGameObject<Player>()->GivePlayerExp(0);
			}
				break;
			}

			m_SlideAnimation = SCREEN_WIDTH;
		}

		

	}
}

void AttackManager::Draw()
{
	if (Game::GetGameState() == PLAYER_LEVELUP)
	{
		//入力レイアウト設定
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		//シェーダ設定
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


		//マトリクス設定
		Renderer::SetWorldViewProjection2D();

		//平行移動行列の作成（表示座標を決める）
		XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.x, m_Position.y, 0.0f);

		//回転行列（Z回転）行列の作成
		XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, m_Rotation.z);

		//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
		XMMATRIX	ScalingMatrix = XMMatrixScaling(m_Scale.x, m_Scale.y, 1.0f);

		//ワールド行列の作成（ポリゴンの表示の仕方を指定する最終的な行列
		XMMATRIX	WorldMatrix = ScalingMatrix * RotationMatrix * TranslationMatrix;

		Renderer::SetWorldMatrix(WorldMatrix);

		//マテリアル設定
		MATERIAL material{};
		material.Diffuse = { 1.0f , 1.0f , 1.0f , 1.0f };
		material.TextureEnable = true;
		Renderer::SetMaterial(material);

		//頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

		drawbg();
		drawicon();
		drawselect();
		drawoption();
	}
}


void AttackManager::drawbg()
{
	

	{//背景
		//テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureBG);

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = 0.0f - m_SlideAnimation;//描画開始位置・・・X座標
		float y = 0.0f;//描画開始位置・・・Y座標
		float w = SCREEN_WIDTH - m_SlideAnimation;//描画物の幅
		float h = SCREEN_HEIGHT;//描画物の高さ

		float tw = 1;
		float th = 1;
		float tx = 0;
		float ty = 0;


		{
			vertex[0].Position = XMFLOAT3(x, y, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = XMFLOAT2(tx, ty);
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		}

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}

	{
		//背景
		//テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureWordBG);

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = (SCREEN_WIDTH / 4) - m_SlideAnimation;//描画開始位置・・・X座標
		float y = SCREEN_HEIGHT / 4;//描画開始位置・・・Y座標
		float w = (SCREEN_WIDTH / 2) - m_SlideAnimation;//描画物の幅
		float h = SCREEN_HEIGHT / 2;//描画物の高さ

		float tw = 1;
		float th = 1;
		float tx = 0;
		float ty = 0;


		{
			vertex[0].Position = XMFLOAT3(x, y, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = XMFLOAT2(tx, ty);
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		}

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}
}

void AttackManager::drawicon()
{
	{//bullet
		//テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureBullet);

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = (SCREEN_WIDTH / 4) - m_SlideAnimation;//描画開始位置・・・X座標
		float y = (SCREEN_WIDTH / 4) - 75.0f;//描画開始位置・・・Y座標
		float w = 100.0f - m_SlideAnimation;//描画物の幅
		float h = 100.0f;//描画物の高さ

		float tw = 1;
		float th = 1;
		float tx = 0;
		float ty = 0;


		{
			vertex[0].Position = XMFLOAT3(x, y, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = XMFLOAT2(tx, ty);
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		}

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}

	{//剣
		//テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureBomb);

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = (SCREEN_WIDTH / 4) + 175.0f - m_SlideAnimation;//描画開始位置・・・X座標
		float y = (SCREEN_WIDTH / 4) - 75.0f;//描画開始位置・・・Y座標
		float w = 75.0f - m_SlideAnimation;//描画物の幅
		float h = 75.0f;//描画物の高さ

		float tw = 1;
		float th = 1;
		float tx = 0;
		float ty = 0;


		{
			vertex[0].Position = XMFLOAT3(x, y, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = XMFLOAT2(tx, ty);
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		}

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}

	{//剣
		//テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureSword);

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = (SCREEN_WIDTH / 4) + 350.0f - m_SlideAnimation;//描画開始位置・・・X座標
		float y = (SCREEN_WIDTH / 4) - 75.0f;//描画開始位置・・・Y座標
		float w = 75.0f - m_SlideAnimation;//描画物の幅
		float h = 75.0f;//描画物の高さ

		float tw = 1;
		float th = 1;
		float tx = 0;
		float ty = 0;


		{
			vertex[0].Position = XMFLOAT3(x, y, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = XMFLOAT2(tx, ty);
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		}

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}


	{//手裏剣
		//テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureShuriken);

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = (SCREEN_WIDTH / 4) + 525.0f - m_SlideAnimation;//描画開始位置・・・X座標
		float y = (SCREEN_WIDTH / 4) - 75.0f;//描画開始位置・・・Y座標
		float w = 75.0f - m_SlideAnimation;//描画物の幅
		float h = 75.0f;//描画物の高さ

		float tw = 1;
		float th = 1;
		float tx = 0;
		float ty = 0;


		{
			vertex[0].Position = XMFLOAT3(x, y, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = XMFLOAT2(tx, ty);
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		}

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}
}

void AttackManager::drawselect()
{
	{
		//テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureSelect);

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = 0;

		if (m_SelectNumber == 0 || m_SelectNumber == 3)
		{
			x = ((SCREEN_WIDTH / 4) + (515 / 3) * m_SelectNumber) - m_SlideAnimation;//描画開始位置・・・X座標
		}
		else //if (m_SelectNumber == 2)
		{
			x = ((SCREEN_WIDTH / 4) - 12.5f + (515 / 3) * m_SelectNumber) - m_SlideAnimation;//描画開始位置・・・X座標
		}

		
		float y = (SCREEN_WIDTH / 4) + 50.0f;//描画開始位置・・・Y座標
		float w = 100.0f - m_SlideAnimation;//描画物の幅
		float h = 100.0f;//描画物の高さ

		float tw = 1;
		float th = 1;
		float tx = 0;
		float ty = 0;


		{
			vertex[0].Position = XMFLOAT3(x, y, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
			vertex[0].TexCoord = XMFLOAT2(tx, ty);
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
			vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
			vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
			vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		}

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}

}

void AttackManager::drawoption()
{
	
	{//bullet
		if (Manager::GetScene()->GetGameObject<BulletAttack>()->GetLevel() != ATT_LVMAX)
		{
			//テクスチャ設定
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TexturePowerUp);
		}
		else
		{
			//テクスチャ設定
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureLVMAX);
		}

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = (SCREEN_WIDTH / 4) - m_SlideAnimation;//描画開始位置・・・X座標
		float y = (SCREEN_WIDTH / 4)  + 50.0f;//描画開始位置・・・Y座標
		float w = 100.0f - m_SlideAnimation;//描画物の幅
		float h = 100.0f;//描画物の高さ

		float tw = 1;
		float th = 1;
		float tx = 0;
		float ty = 0;


		{
			vertex[0].Position = XMFLOAT3(x, y, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = XMFLOAT2(tx, ty);
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		}

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}

	{//sword
		if (Manager::GetScene()->GetGameObject<BombAttack>()->GetLevel() != ATT_LVMAX)
		{
			//テクスチャ設定
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TexturePowerUp);
		}
		else
		{
			//テクスチャ設定
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureLVMAX);
		}

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = (SCREEN_WIDTH / 4) + 160.0f - m_SlideAnimation;//描画開始位置・・・X座標
		float y = (SCREEN_WIDTH / 4) + 50.0f;//描画開始位置・・・Y座標
		float w = 100.0f - m_SlideAnimation;//描画物の幅
		float h = 100.0f;//描画物の高さ

		float tw = 1;
		float th = 1;
		float tx = 0;
		float ty = 0;


		{
			vertex[0].Position = XMFLOAT3(x, y, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = XMFLOAT2(tx, ty);
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		}

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}

	{//sword
		if (Manager::GetScene()->GetGameObject<SwordAttack>()->GetLevel() != ATT_LVMAX)
		{
			//テクスチャ設定
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TexturePowerUp);
		}
		else
		{
			//テクスチャ設定
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureLVMAX);
		}

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = (SCREEN_WIDTH / 4) + 335.0f - m_SlideAnimation;//描画開始位置・・・X座標
		float y = (SCREEN_WIDTH / 4) + 50.0f;//描画開始位置・・・Y座標
		float w = 100.0f - m_SlideAnimation;//描画物の幅
		float h = 100.0f;//描画物の高さ

		float tw = 1;
		float th = 1;
		float tx = 0;
		float ty = 0;


		{
			vertex[0].Position = XMFLOAT3(x, y, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = XMFLOAT2(tx, ty);
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		}

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}


	{//sword
		if (Manager::GetScene()->GetGameObject<ShurikenAttack>()->GetLevel() != ATT_LVMAX)
		{
			//テクスチャ設定
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TexturePowerUp);
		}
		else
		{
			//テクスチャ設定
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureLVMAX);
		}

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = (SCREEN_WIDTH / 4) + 515.0f - m_SlideAnimation;//描画開始位置・・・X座標
		float y = (SCREEN_WIDTH / 4) + 50.0f;//描画開始位置・・・Y座標
		float w = 100.0f - m_SlideAnimation;//描画物の幅
		float h = 100.0f;//描画物の高さ

		float tw = 1;
		float th = 1;
		float tx = 0;
		float ty = 0;


		{
			vertex[0].Position = XMFLOAT3(x, y, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = XMFLOAT2(tx, ty);
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		}

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}
}
