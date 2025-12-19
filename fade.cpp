//********************************************************************************
//
// Fade.h[攻撃管理クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/15
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "scene.h"

#include "fade.h"


//********************************************************************************
//グローバル変数
//********************************************************************************
//FadeState Fade::m_State;
//float Fade::m_trans;
//********************************************************************************
//関数
//********************************************************************************
Fade::Fade()
{
	m_color = { 1.0f , 1.0f , 1.0f };
	m_trans = 0.0f;
	m_State = FADE_NONE;
	m_Scale = { 1.0f , 1.0f , 1.0f };
	m_Position = { 0.0f , 0.0f , 0.0f };

	{//ポーズ画面の背景描画


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
		vertex[0].Diffuse = XMFLOAT4(m_color.x, m_color.y, m_color.z, m_trans);;
		vertex[0].TexCoord = XMFLOAT2(tx, ty);
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
		vertex[1].Diffuse = XMFLOAT4(m_color.x, m_color.y, m_color.z, m_trans);
		vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
		vertex[2].Diffuse = XMFLOAT4(m_color.x, m_color.y, m_color.z, m_trans);;
		vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
		vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
		vertex[3].Diffuse = XMFLOAT4(m_color.x, m_color.y, m_color.z, m_trans);;
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
	}
	m_TextureFade = Texture::Load("asset\\texture\\black.png");//頭にLを入れる必要がない

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	
}

Fade::~Fade()
{
	m_TextureFade->Release();

	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Fade::Update()
{
	if (m_State == FADE_IN)
	{
		fadein();
	}
	else if (m_State == FADE_OUT)
	{
		fadeout();
	}
}

void Fade::Draw()
{

	{
		//入力レイアウト設定
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		////シェーダ設定
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


		//マトリクス設定
		Renderer::SetWorldViewProjection2D();

		//マテリアル設定
		MATERIAL material{};
		material.Diffuse = { m_color.x, m_color.y, m_color.z, m_trans };
		material.TextureEnable = true;
		Renderer::SetMaterial(material);

		//頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);


		//テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureFade);

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = 0.0f;//描画開始位置・・・X座標
		float y = 0.0f;//描画開始位置・・・Y座標
		float w = SCREEN_WIDTH;//描画物の幅
		float h = SCREEN_HEIGHT;//描画物の高さ

		float tw = 1;
		float th = 1;
		float tx = 0;
		float ty = 0;



		vertex[0].Position = XMFLOAT3(x, y, 0.0f);
		vertex[0].Diffuse = XMFLOAT4(m_color.x, m_color.y, m_color.z, m_trans);
		vertex[0].TexCoord = XMFLOAT2(tx, ty);
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
		vertex[1].Diffuse = XMFLOAT4(m_color.x, m_color.y, m_color.z, m_trans);
		vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
		vertex[2].Diffuse = XMFLOAT4(m_color.x, m_color.y, m_color.z, m_trans);
		vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
		vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
		vertex[3].Diffuse = XMFLOAT4(m_color.x, m_color.y, m_color.z, m_trans);
		vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);


		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}
}

void Fade::fadein()
{
	m_trans -= 0.025f;


	if (m_trans <= 0.0f)
	{
		m_trans = 0.0f;
		m_State = FADE_FIN;
	}
}

void Fade::fadeout()
{
	m_trans += 0.025f;

	if (m_trans >= 1.0f)
	{
		m_trans = 1.0f;
		m_State = FADE_FIN;
	}
}
