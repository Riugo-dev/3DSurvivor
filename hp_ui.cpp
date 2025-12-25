//********************************************************************************
//
// score.cpp[スコア表示]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "manager.h"
#include "manager_soundeffect.h"

#include "hp_ui.h"
//********************************************************************************
//マクロ定義
//********************************************************************************
#define PLAYER_HP_MAX (3)
//********************************************************************************
//関数
//********************************************************************************
HPUI::HPUI()
{
	m_Scale = { 1.0f , 1.0f , 1.0f };
	m_Position = { 0.0f , 0.0f , 0.0f };
	VERTEX_3D vertex[4];
	//上面
	m_VertexPosition[0] = XMFLOAT3(m_Position.m_x - m_Scale.m_x, m_Position.m_y + m_Scale.m_y, m_Position.m_z);
	m_VertexPosition[1] = XMFLOAT3(m_Position.m_x + m_Scale.m_x, m_Position.m_y + m_Scale.m_y, m_Position.m_z);
	m_VertexPosition[2] = XMFLOAT3(m_Position.m_x - m_Scale.m_x, m_Position.m_y - m_Scale.m_y, m_Position.m_z);
	m_VertexPosition[3] = XMFLOAT3(m_Position.m_x + m_Scale.m_x, m_Position.m_y - m_Scale.m_y, m_Position.m_z);

	//vertex[0].Position = XMFLOAT3(-10.0f, 0.0f, 10.0f);
	vertex[0].Position = m_VertexPosition[0];
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	//vertex[1].Position = XMFLOAT3(10.0f, 0.0f, 10.0f);
	vertex[1].Position = m_VertexPosition[1];
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	//vertex[2].Position = XMFLOAT3(-10.0f, 0.0f, -10.0f);
	vertex[2].Position = m_VertexPosition[2];
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	//vertex[3].Position = XMFLOAT3(10.0f, 0.0f, -10.0f);
	vertex[3].Position = m_VertexPosition[3];
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

	m_TextureHP = Texture::Load("asset\\texture\\HP.png");//頭にLを入れる必要がない
	m_TextureHeart = Texture::Load("asset\\texture\\heart.png");//頭にLを入れる必要がない
	m_TextureCase = Texture::Load("asset\\texture\\disheart.png");//頭にLを入れる必要がない

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");


	m_HP = PLAYER_HP_MAX;
}

HPUI::~HPUI()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void HPUI::Init()
{
}

void HPUI::Uninit()
{
}

void HPUI::Update()
{
}

void HPUI::Draw()
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

	drawhpword();

	switch (m_HP)
	{
	case 0:
		drawzerohp();
		break;
	case 1:
		drawonehp();
		break;
	case 2:
		drawtwohp();
		break;
	case 3:
		drawthreehp();
		break;
	}
}

void HPUI::SubtractHP(int hp)
{
	if (m_HP <= 0) { m_HP = 0; return; }
	Manager::GetSoundEffect()->PlaySE(SE_PLAYERDAMAGE);
	m_HP -= hp;
}

//********************************************************************************
//プライベート関数
//********************************************************************************

void HPUI::drawzerohp()
{
	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureCase);


	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	for (int i = 0; i < 3; i++)
	{
		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = (60.0f * (3 - 1) - 60.0f * i) + 120;
		float y = 40.0f;
		float w = 60.0f;
		float h = 60.0f;

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


void HPUI::drawonehp()
{
	{//ハートの出力
		//テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureHeart);


		//プリミティブトポロジ設定
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = 120;
		float y = 40.0f;
		float w = 60.0f;
		float h = 60.0f;

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

	{//枠の出力
		//テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureCase);


		//プリミティブトポロジ設定
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		for (int i = 0; i < 2; i++)
		{
			//頂点データ書き換え
			D3D11_MAPPED_SUBRESOURCE msr;
			Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			float x = (60.0f * (2 - 1) - 60.0f * i) + 180;
			float y = 40.0f;
			float w = 60.0f;
			float h = 60.0f;

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
}

void HPUI::drawtwohp()
{
	{//ハートの出力
		//テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureHeart);


		//プリミティブトポロジ設定
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		for (int i = 0; i < 2; i++)
		{
			//頂点データ書き換え
			D3D11_MAPPED_SUBRESOURCE msr;
			Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			float x = (60.0f * (2 - 1) - 60.0f * i) + 120;
			float y = 40.0f;
			float w = 60.0f;
			float h = 60.0f;

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

	{//枠の出力
		//テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureCase);


		//プリミティブトポロジ設定
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = 240;
		float y = 40.0f;
		float w = 60.0f;
		float h = 60.0f;

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

void HPUI::drawthreehp()
{
	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureHeart);


	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	for (int i = 0; i < 3; i++)
	{
		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = (60.0f * (3 - 1) - 60.0f * i) + 120;
		float y = 40.0f;
		float w = 60.0f;
		float h = 60.0f;

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

void HPUI::drawhpword()
{
	

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureHP);

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float x = 0.0f;//描画開始位置・・・X座標
	float y = 50.0f;//描画開始位置・・・Y座標
	float w = 120.0f;//描画物の幅
	float h = 40.0f;//描画物の高さ

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
