//********************************************************************************
//
// pause.cpp[[ポーズ画面表示]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "scene.h"
#include "game.h"

#include "pause.h"

Pause::Pause()
{
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
	}


	{//ポーズ画面の文字描画


		VERTEX_3D vertex[4] = {};

		float x = SCREEN_WIDTH/4;//描画開始位置・・・X座標
		float y = SCREEN_HEIGHT/4;//描画開始位置・・・Y座標
		float w = SCREEN_WIDTH/2;//描画物の幅
		float h = SCREEN_HEIGHT/2;//描画物の高さ

		float tw = 1;
		float th = 1;
		float tx = 0;
		float ty = 0;

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

		//頂点バッファ生成
		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DYNAMIC;//ここをダイナミックに変更しなければ途中でテクスチャマッピングを変えれない
		bd.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//ここをwriteに変更

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBufferPause);
	}

	m_TexturePause = Texture::Load("asset\\texture\\pause.png");//頭にLを入れる必要がない
	m_TextureBG = Texture::Load("asset\\texture\\black.png");//頭にLを入れる必要がない

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");
}

Pause::~Pause()
{
	m_VertexBuffer->Release();
	m_VertexBufferPause->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}


void Pause::Update()
{

}

void Pause::Draw()
{
	if(Game::GetGameState() == GAME_PAUSE)
	{	//入力レイアウト設定
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		////シェーダ設定
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


		//マトリクス設定
		Renderer::SetWorldViewProjection2D();

	

		

		{

			//マテリアル設定
			MATERIAL material{};
			material.Diffuse = { 1.0f , 1.0f , 1.0f , 0.7f};
			material.TextureEnable = true;
			Renderer::SetMaterial(material);

			//頂点バッファ設定
			UINT stride = sizeof(VERTEX_3D);
			UINT offset = 0;
			Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

			//プリミティブトポロジ設定
			Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureBG);

			Renderer::GetDeviceContext()->Draw(4, 0);
		}


		{
			static float trans = 1.0f;
			static bool updown = true;
			if (updown)
			{
				trans -= 0.01;
				if (trans <= 0.5f)
				{
					updown = false;
				}
			}
			else
			{
				trans += 0.01;
				if (trans >= 1.0f)
				{
					updown = true;
				}
			}


			//マテリアル設定
			MATERIAL material{};
			material.Diffuse = { 1.0f , 1.0f , 1.0f , trans };
			material.TextureEnable = true;
			Renderer::SetMaterial(material);

			//頂点バッファ設定
			UINT stride = sizeof(VERTEX_3D);
			UINT offset = 0;
			Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBufferPause, &stride, &offset);

			//プリミティブトポロジ設定
			Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TexturePause);
			Renderer::GetDeviceContext()->Draw(4, 0);
		}
	}

	
}
