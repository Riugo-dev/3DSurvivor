//********************************************************************************
//
// polygon.cpp[ポリゴン描画]
//
//															Author :Riugo Honda
//															Date   :2025/04/23
// -------------------------------------------------------------------------------
//															Last Edited:2025/04/23
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "manager.h"
#include "scene.h"

#include "polygon.h"


//********************************************************************************
//関数
//********************************************************************************
Polygon2D::Polygon2D(Vector3 size, Vector3 position, int movementx , int movementy , Vector3 rotation)
{
	//m_Scale = size;
	//m_Position = position;

	//m_Rotation = rotation;
	//VERTEX_3D vertex[4];
	//m_VertexPosition[0] = XMFLOAT3(position.x, position.y, 0.0f);
	//m_VertexPosition[1] = XMFLOAT3(position.x + m_Scale.x, position.y, 0.0f);
	//m_VertexPosition[2] = XMFLOAT3(position.x, position.y + m_Scale.y, 0.0f);
	//m_VertexPosition[3] = XMFLOAT3(position.x + m_Scale.x, position.y + m_Scale.y, 0.0f);

	//vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	//vertex[1].Position = XMFLOAT3(SCREEN_WIDTH, 0.0f, 0.0f);
	//vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
	//
	//vertex[2].Position = XMFLOAT3(0.0f, SCREEN_HEIGHT, 0.0f);
	//vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
	//
	//vertex[3].Position = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	//vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
	//
	////頂点バッファ生成
	//D3D11_BUFFER_DESC bd{};
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;

	//D3D11_SUBRESOURCE_DATA sd{};
	//sd.pSysMem = vertex;

	//Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	////テクスチャの読み込み
	//TexMetadata metadata;
	//ScratchImage image;
	//LoadFromWICFile(L"asset\\texture\\Title.png", WIC_FLAGS_NONE, &metadata, image);
	//CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	//assert(m_Texture);//読み込めなかったらここで止めようにassertを使う

	//Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	//Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");


	//m_movement_x = movementx;
	//m_movement_y = movementy;
}

void Polygon2D::Initialize(float x, float y, float width, float height, const char* filename)
{
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(x, y, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(x + width, y, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(x, y + height, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(x + width, y + height, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャ読み込み
	m_Texture = Texture::Load(filename);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");
}

Polygon2D::~Polygon2D()
{
	m_Texture->Release();

	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Polygon2D::Init()
{
}

void Polygon2D::Uninit()
{
	
}

void Polygon2D::Update()
{
	
	m_Position.x += m_movement_x;
	m_Position.y += m_movement_y;

	if (m_Rotation.x > 0.0f)
	{
		m_Rotation.x += 1.0f/ 360.0f;
	}

	//updateposition();
}

void Polygon2D::Draw()
{
	

	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL , 0);
	
	
	//マトリクス設定
	Renderer::SetWorldViewProjection2D();
	//
	////平行移動行列の作成（表示座標を決める）
	//XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.x, m_Position.y, 0.0f);

	////回転行列（Z回転）行列の作成
	//XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(0.0f , 0.0f, m_Rotation.z);

	////スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
	//XMMATRIX	ScalingMatrix = XMMatrixScaling(m_Scale.x, m_Scale.y, 1.0f);

	////ワールド行列の作成（ポリゴンの表示の仕方を指定する最終的な行列
	//XMMATRIX	WorldMatrix = ScalingMatrix * RotationMatrix * TranslationMatrix;

	//Renderer::SetWorldMatrix(WorldMatrix);

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

	//ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);


}

