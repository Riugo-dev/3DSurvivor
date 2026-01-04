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

#include "score.h"


//********************************************************************************
//関数
//********************************************************************************
Score::Score(Vector3 size, Vector3 position, int movementx, int movementy, Vector3 rotation)
{

	m_Scale = size;
	m_Position = position;
	VERTEX_3D vertex[24];
	//上面
	m_VertexPosition[0] = XMFLOAT3(position.m_x - m_Scale.m_x, position.m_y + m_Scale.m_y, position.m_z);
	m_VertexPosition[1] = XMFLOAT3(position.m_x + m_Scale.m_x, position.m_y + m_Scale.m_y, position.m_z);
	m_VertexPosition[2] = XMFLOAT3(position.m_x - m_Scale.m_x, position.m_y - m_Scale.m_y, position.m_z);
	m_VertexPosition[3] = XMFLOAT3(position.m_x + m_Scale.m_x, position.m_y - m_Scale.m_y, position.m_z);

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

	m_Texture = Texture::Load("asset\\texture\\numbers.png");//頭にLを入れる必要がない
	m_TextureScore = Texture::Load("asset\\texture\\SCORE.png");//頭にLを入れる必要がない

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");


	/*m_Frame_x = 6;
	m_Frame_y = 5;
	m_Frame_max = m_Frame_x * m_Frame_y - 3;
	m_Frame_count = 0;*/

	m_movement_x = movementx;
	m_movement_y = movementy;

	m_Points = 0;
}

Score::~Score()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Score::Init()
{
}

void Score::Uninit()
{

}

void Score::Update()
{

	//m_Position.m_x += m_movement_x;
	//m_Position.m_y += m_movement_y;

	//if (m_Rotation.m_x > 0.0f)
	//{
	//	m_Rotation.m_x += 1.0f / 360.0f;
	//}

	//updateposition();
}

void Score::Draw()
{


	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//平行移動行列の作成（表示座標を決める）
	XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.m_x, m_Position.m_y, 0.0f);

	//回転行列（Z回転）行列の作成
	XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, m_Rotation.m_z);

	//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
	XMMATRIX	ScalingMatrix = XMMatrixScaling(m_Scale.m_x, m_Scale.m_y, 1.0f);

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

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);


	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//updateposition();
	int value = m_Points;

	for (int i = 0; i < 6; i++)
	{
		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = (50.0f * (6 - 1) - 50.0f * i) + 300;
		float y = 0.0f;
		float w = 50.0f;
		float h = 50.0f;

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

	{

		//テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureScore);

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float x = 0.0f;
		float y = 0.0f;
		float w = 300.0f;
		float h = 50.0f;

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

void Score::SetScore(float x, float y, float width, float height, const char* filename)
{
	///*m_Scale.m_x = width;
	//m_Scale.m_y = height;
	//m_Scale.m_z = 1.0f;

	//m_Position.m_x = x;
	//m_Position.m_y = y;
	//m_Position.m_z = 1.0f;

	//テクスチャ読み込み
	//m_Texture = Texture::Load(filename);

	//Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	//Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");*/


}

int Score::GetPoints()
{
	return m_Points;
}

