//********************************************************************************
//
// title_ui.cpp[[タイトル画面表示]
//
//															Author :Riugo Honda
//															Date   :2025/10/30
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "manager.h"
#include "controller.h"

#include "title_ui.h"

TitleUI::TitleUI()
{
	m_Scale = { 1.0f , 1.0f , 1.0f };
	m_Position = { 0.0f , 0.0f , 0.0f };
	VERTEX_3D vertex[4];
	//上面
	m_VertexPosition[0] = XMFLOAT3(m_Position.x - m_Scale.x, m_Position.y + m_Scale.y, m_Position.z);
	m_VertexPosition[1] = XMFLOAT3(m_Position.x + m_Scale.x, m_Position.y + m_Scale.y, m_Position.z);
	m_VertexPosition[2] = XMFLOAT3(m_Position.x - m_Scale.x, m_Position.y - m_Scale.y, m_Position.z);
	m_VertexPosition[3] = XMFLOAT3(m_Position.x + m_Scale.x, m_Position.y - m_Scale.y, m_Position.z);

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

	m_TextureTitleButtonCon = Texture::Load("asset\\texture\\controller_button.png");//
	m_TextureTitleButtonKey = Texture::Load("asset\\texture\\keyboard_button.png");
	m_TextureTitleBar = Texture::Load("asset\\texture\\title_bar.png");//文字
	m_TextureBG = Texture::Load("asset\\texture\\Title.png");//背景画

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");
}

TitleUI::~TitleUI()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void TitleUI::Update()
{

}

void TitleUI::Draw()
{
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

	//drawbg();
	drawbutton();
	drawtitlebar();

}

void TitleUI::drawtitlebar()
{
	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureTitleBar);


	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float x = (SCREEN_WIDTH / 2) - 400.0f;//描画開始位置・・・X座標
	float y = (SCREEN_HEIGHT / 8);//描画開始位置・・・Y座標
	float w = 800.0f;//描画物の幅
	float h = 200.0f;//描画物の高さ

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

void TitleUI::drawbutton()
{
	if (Manager::GetController()->IsConnected())
	{
		//テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureTitleButtonCon);


		//プリミティブトポロジ設定
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = (SCREEN_WIDTH / 2) - 125.0f;//描画開始位置・・・X座標
		float y = (SCREEN_HEIGHT * 3 / 4);//描画開始位置・・・Y座標
		float w = 250.0f;//描画物の幅
		float h = 150.0f;//描画物の高さ

		float tw = 1;
		float th = 1;
		float tx = 0;
		float ty = 0;

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


		{
			vertex[0].Position = XMFLOAT3(x, y, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, trans);
			vertex[0].TexCoord = XMFLOAT2(tx, ty);
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, trans);
			vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, trans);
			vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, trans);
			vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		}

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}
	else
	{
		//テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureTitleButtonKey);


		//プリミティブトポロジ設定
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = (SCREEN_WIDTH / 2) - 125.0f;//描画開始位置・・・X座標
		float y = (SCREEN_HEIGHT * 3 / 4);//描画開始位置・・・Y座標
		float w = 250.0f;//描画物の幅
		float h = 150.0f;//描画物の高さ

		float tw = 1;
		float th = 1;
		float tx = 0;
		float ty = 0;

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


		{
			vertex[0].Position = XMFLOAT3(x, y, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, trans);
			vertex[0].TexCoord = XMFLOAT2(tx, ty);
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[1].Position = XMFLOAT3(x + w, y, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, trans);
			vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[2].Position = XMFLOAT3(x, y + h, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, trans);
			vertex[2].TexCoord = XMFLOAT2(tx, ty + th);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[3].Position = XMFLOAT3(x + w, y + h, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, trans);
			vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		}

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}
}

void TitleUI::drawbg()
{
	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureBG);


	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

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