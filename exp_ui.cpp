//********************************************************************************
//
// exp_ui.cpp[経験値バーUIクラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/29
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "texture.h"
#include "player.h"


#include "exp_ui.h"

#define EXP_BAR_YPOS (680.0f)
#define EXP_BAR_WIDTH (1060.0f)

EXPUI::EXPUI()
{
	m_Scale = { 1.0f , 1.0f , 1.0f };
	m_Position = { 0.0f , 0.0f , 0.0f };//これがバーの動く部分の
	VERTEX_3D vertex[4];
	
	vertex[0].Position = XMFLOAT3(-10.0f, 0.0f, 10.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(10.0f, 0.0f, 10.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-10.0f, 0.0f, -10.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(10.0f, 0.0f, -10.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;//ここをダイナミックに変更しなければ途中でテクスチャマッピングを変えれない
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//ここをwriteに変更

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	m_TextureExpBarFrame = Texture::Load("asset\\texture\\expbar_frame2.png");
	m_TextureExpBar = Texture::Load("asset\\texture\\expbar_white.png");
	

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	m_expinterpolation = 0;
	m_expbarpos = 100.0f;
	m_expbarwidth = 0;

	m_color = { 0.0f , 1.0f , 0.0f };
	m_IslvMax = false;
}

EXPUI::~EXPUI()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void EXPUI::Init(Input*)
{
}

void EXPUI::Uninit()
{
	

}

void EXPUI::Update()
{
	Player* p_player = Manager::GetScene()->GetGameObject<Player>();

	if(p_player->GetPlayerLevel() != LEVEL_MAX)
	{

		m_expinterpolation = p_player->GetCurrentExpPercentage();

		m_expbarwidth = EXP_BAR_WIDTH * m_expinterpolation;
	}
	else
	{
		m_IslvMax = true;

		colorchange();
	}

	//m_Position.m_x = (SCREEN_WIDTH - 210.0f) - (EXP_BAR_WIDTH - m_expbarwidth);
}

void EXPUI::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//マテリアル設定
	MATERIAL material{};
	material.Diffuse = { 1.0f , 1.0f , 1.0f , 1.0f };
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	drawframe();

	if(!m_IslvMax)
	{
		drawexpbar();
	}
	else
	{
		drawexpbarmax();
	}
}

//********************************************************************************
//プライベート関数
//********************************************************************************

void EXPUI::drawframe()
{
	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureExpBarFrame);

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;

	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float x = 100.0f;//描画開始位置・・・X座標
	float y = EXP_BAR_YPOS;//描画開始位置・・・Y座標
	float w = SCREEN_WIDTH - 200.0f;//描画物の幅
	float h = 20.0f;//描画物の高さ

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

void EXPUI::drawexpbar()
{
	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureExpBar);

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;

	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float x = 110.0f;//描画開始位置・・・X座標
	float y = EXP_BAR_YPOS + 3;//描画開始位置・・・Y座標
	float w = m_expbarwidth;//描画物の幅
	float h = 14.0f;//描画物の高さ

	float tw = 1;
	float th = 1;
	float tx = 0;
	float ty = 0;


	{
		vertex[0].Position = XMFLOAT3(x, y, 0.0f);
		vertex[0].Diffuse = XMFLOAT4(m_color.m_x, m_color.m_y, m_color.m_z, 1.0f);
		vertex[0].TexCoord = XMFLOAT2(tx, ty);
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
		vertex[1].Diffuse = XMFLOAT4(m_color.m_x, m_color.m_y, m_color.m_z, 1.0f);
		vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
		vertex[2].Diffuse = XMFLOAT4(m_color.m_x, m_color.m_y, m_color.m_z, 1.0f);
		vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
		vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
		vertex[3].Diffuse = XMFLOAT4(m_color.m_x, m_color.m_y, m_color.m_z, 1.0f);
		vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	}

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	//ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);
}

void EXPUI::drawexpbarmax()
{
	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureExpBar);

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;

	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float x = 110.0f;//描画開始位置・・・X座標
	float y = EXP_BAR_YPOS + 3;//描画開始位置・・・Y座標
	float w = EXP_BAR_WIDTH;//描画物の幅
	float h = 14.0f;//描画物の高さ

	float tw = 1;
	float th = 1;
	float tx = 0;
	float ty = 0;


	{
		vertex[0].Position = XMFLOAT3(x, y, 0.0f);
		vertex[0].Diffuse = XMFLOAT4(m_color.m_x, m_color.m_y, m_color.m_z, 1.0f);
		vertex[0].TexCoord = XMFLOAT2(tx, ty);
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
		vertex[1].Diffuse = XMFLOAT4(m_color.m_x, m_color.m_y, m_color.m_z, 1.0f);
		vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
		vertex[2].Diffuse = XMFLOAT4(m_color.m_x, m_color.m_y, m_color.m_z, 1.0f);
		vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
		vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
		vertex[3].Diffuse = XMFLOAT4(m_color.m_x, m_color.m_y, m_color.m_z, 1.0f);
		vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	}

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	//ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);
}

void EXPUI::colorchange()
{
	static bool RedToOrange = false;
	static bool OrangeToYellow = false;
	static bool YellowToGreen = false;
	static bool GreenToLightBlue = true;
	static bool LightBlueToBlue = false;
	static bool BlueToPurple = false;
	static bool PurpleToRed = false;

	for(int i = 0 ; i < 2 ; i++)
	{//とりあえずカラーチェンジ後々一定の強さで打たないと出ないように
		if (RedToOrange)
		{
			m_color.m_y += 0.01f;

			if (m_color.m_y >= 0.5f)
			{
				m_color.m_y = 0.5f;

				RedToOrange = false;
				OrangeToYellow = true;
			}
		}
		else if (OrangeToYellow)
		{
			m_color.m_y += 0.01f;

			if (m_color.m_y >= 1.0f)
			{
				m_color.m_y = 1.0f;

				OrangeToYellow = false;
				YellowToGreen = true;
			}
		}
		else if (YellowToGreen)
		{
			m_color.m_x -= 0.02f;

			if (m_color.m_x <= 0.0f)
			{
				m_color.m_x = 0.0f;

				YellowToGreen = false;
				GreenToLightBlue = true;
			}
		}
		else if (GreenToLightBlue)
		{
			m_color.m_z += 0.02f;

			if (m_color.m_z >= 1.0f)
			{
				m_color.m_z = 1.0f;

				GreenToLightBlue = false;
				LightBlueToBlue = true;
			}
		}
		else if (LightBlueToBlue)
		{
			m_color.m_y -= 0.02f;

			if (m_color.m_y <= 0.0f)
			{
				m_color.m_y = 0.0f;

				LightBlueToBlue = false;
				BlueToPurple = true;
			}
		}
		else if (BlueToPurple)
		{
			m_color.m_x += 0.005f;
			m_color.m_z -= 0.005f;

			if (m_color.m_x >= 0.5f)
			{
				m_color.m_x = 0.5f;
				m_color.m_z = 0.5f;

				BlueToPurple = false;
				PurpleToRed = true;
			}
		}
		else if (PurpleToRed)
		{
			m_color.m_x += 0.005f;
			m_color.m_z -= 0.005f;

			if (m_color.m_x >= 1.0f)
			{
				m_color.m_x = 1.0f;
				m_color.m_z = 0.0f;

				PurpleToRed = false;
				RedToOrange = true;
			}
		}

	}
}
