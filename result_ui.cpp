//********************************************************************************
//
// result_ui.h[[リザルト画面表示]
//
//															Author :Riugo Honda
//															Date   :2025/09/15
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "manager.h"
#include "scene.h"
#include "input.h"
#include "controller.h"
#include "ranking.h"
#include "result.h"

#include "result_ui.h"

ResultUI::ResultUI()
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

	m_TextureResultScore = Texture::Load("asset\\texture\\Score.png");//文字
	m_TextureResultEXPBonus = Texture::Load("asset\\texture\\EXPBonus.png");//
	m_TextureResultTotalScore = Texture::Load("asset\\texture\\Total.png");
	m_TextureNumbers = Texture::Load("asset\\texture\\numbers.png");//文字
	m_TextureBG = Texture::Load("asset\\texture\\tatami.jpg");//背景画

	m_RankText[0] = Texture::Load("asset\\texture\\first.png");
	m_RankText[1] = Texture::Load("asset\\texture\\second.png");
	m_RankText[2] = Texture::Load("asset\\texture\\third.png");
	m_RankText[3] = Texture::Load("asset\\texture\\fourth.png");
	m_RankText[4] = Texture::Load("asset\\texture\\fifth.png");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	m_Height = SCREEN_HEIGHT + 200.0f;
	m_IsRising = false;
}

ResultUI::~ResultUI()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void ResultUI::Update()
{
	if (m_IsRising)
	{
		m_Height -= 2.5f;

		if (Input::GetKeyTrigger(KK_SPACE) || Manager::GetController()->Controller_IsJustPressed(Manager::GetController()->GetButtonForTrigger(XINPUT_GAMEPAD_A)))
		{
			m_Height = 25.0f;
		}

		if (m_Height <= 25.0f)
		{
			m_Height = 25.0f;
			m_IsRising = false;
		}
	}
}

void ResultUI::Draw()
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


	drawbg();
	if (m_State == RESULT)
	{
		drawnumbers();
		drawscore();
		drawbonus();
		drawtotal();
	}
	else
	{
		drawranknumbers();
		drawranks();
	}
}
//********************************************************************************
//プライベート関数
//********************************************************************************

void ResultUI::SetState(State state)
{
	m_State = state;
	if (state == RANKING)
	{
		Result* p_result = dynamic_cast<Result*>(Manager::GetScene());

		for (int i = 0; i < 5; i++)
		{
			m_Ranking[i] = p_result->GetRanking()->GetRank(i);
		}
		m_IsRising = true;
	}
}

void ResultUI::drawnumbers()
{
	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureNumbers);


	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	{//スコアの描画
		int value = m_Score;

		for (int i = 0; i < 7; i++)
		{
			//頂点データ書き換え
			D3D11_MAPPED_SUBRESOURCE msr;
			Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			float x = (100.0f * (7 - 1) - 100.0f * i) + 500;
			float y = 150.0f;
			float w = 100.0f;
			float h = 100.0f;

			int num = value % 10;
			value /= 10;

			float tw = (1.0f / 5);
			float th = 1.0f / 2;
			float tx = num % 5 * tw;
			float ty = num / 5 * th;


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

	{//ボーナスの描画
		int value = m_EXPBonus;

		for (int i = 0; i < 7; i++)
		{
			//頂点データ書き換え
			D3D11_MAPPED_SUBRESOURCE msr;
			Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			float x = (100.0f * (7 - 1) - 100.0f * i) + 500;
			float y = 350.0f;
			float w = 100.0f;
			float h = 100.0f;

			int num = value % 10;
			value /= 10;

			float tw = (1.0f / 5);
			float th = 1.0f / 2;
			float tx = num % 5 * tw;
			float ty = num / 5 * th;


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

	{//合計の描画
		int value = m_TotalScore;

		for (int i = 0; i < 7; i++)
		{
			//頂点データ書き換え
			D3D11_MAPPED_SUBRESOURCE msr;
			Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			float x = (100.0f * (7 - 1) - 100.0f * i) + 500;
			float y = 550.0f;
			float w = 100.0f;
			float h = 100.0f;

			int num = value % 10;
			value /= 10;

			float tw = (1.0f / 5);
			float th = 1.0f / 2;
			float tx = num % 5 * tw;
			float ty = num / 5 * th;


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

void ResultUI::drawscore()
{
	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureResultScore);


	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float x =  200.0f;//描画開始位置・・・X座標
	float y = 100.0f;//描画開始位置・・・Y座標
	float w = 200.0f;//描画物の幅
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

void ResultUI::drawbonus()
{
	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureResultEXPBonus);


	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float x = 150.0f;//描画開始位置・・・X座標
	float y = 300.0f;//描画開始位置・・・Y座標
	float w = 250.0f;//描画物の幅
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

void ResultUI::drawtotal()
{
	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureResultTotalScore);


	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float x = 200.0f;//描画開始位置・・・X座標
	float y = 500.0f;//描画開始位置・・・Y座標
	float w = 200.0f;//描画物の幅
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

void ResultUI::drawbg()
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

void ResultUI::drawranks()
{
	for (int i = 0; i < 5; i++)
	{
		//テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_RankText[i]);


		//プリミティブトポロジ設定
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = 200;
		float y = m_Height + 125 * i;
		float w = 200.0f;
		float h = 200.0f;

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

void ResultUI::drawranknumbers()
{
	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureNumbers);


	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	for (int j = 0; j < 5; j++)
	{//スコアの描画
		int value = m_Ranking[j];

		for (int i = 0; i < 7; i++)
		{
			//頂点データ書き換え
			D3D11_MAPPED_SUBRESOURCE msr;
			Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			float x = (100.0f * (7 - 1) - 100.0f * i) + 500;
			float y = m_Height + 125.0f * j + 12.5f;
			float w = 100.0f;
			float h = 150.0f;

			int num = value % 10;
			value /= 10;

			float tw = (1.0f / 5);
			float th = 1.0f / 2;
			float tx = num % 5 * tw;
			float ty = num / 5 * th;


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
