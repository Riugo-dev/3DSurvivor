//********************************************************************************
//
// explosion.cpp[爆発エフェクト]
//
//															Author :Riugo Honda
//															Date   :2025/06/11
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/14
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"
#include "texture.h"
#include "scene.h"

#include "explosion.h"


//********************************************************************************
//関数
//********************************************************************************
Explosion::Explosion(Vector3 size, Vector3 position, int movementx, int movementy, Vector3 rotation)
{
	m_Scale = size;
	m_Position = position;
	VERTEX_3D vertex[24];
	//上面
	m_VertexPosition[0] = XMFLOAT3(position.m_x - m_Scale.m_x, position.m_y + m_Scale.m_y, position.m_z);
	m_VertexPosition[1] = XMFLOAT3(position.m_x + m_Scale.m_x, position.m_y + m_Scale.m_y, position.m_z);
	m_VertexPosition[2] = XMFLOAT3(position.m_x - m_Scale.m_x, position.m_y - m_Scale.m_y, position.m_z);
	m_VertexPosition[3] = XMFLOAT3(position.m_x + m_Scale.m_x, position.m_y - m_Scale.m_y, position.m_z);

	/*m_Position[0] = XMFLOAT3(position.x - m_Size.x, position.y , position.z - m_Size.z);
	m_Position[1] = XMFLOAT3(position.x + m_Size.x, position.y , position.z - m_Size.z);
	m_Position[2] = XMFLOAT3(position.x - m_Size.x, position.y , position.z + m_Size.z);
	m_Position[3] = XMFLOAT3(position.x + m_Size.x, position.y , position.z + m_Size.z);*/
	////下面面
	//m_Position[4] = XMFLOAT3(position.x + m_Size.x, position.y + m_Size.y, position.z);
	//m_Position[5] = XMFLOAT3(position.x , position.y + m_Size.y, position.z);
	//m_Position[6] = XMFLOAT3(position.x + m_Size.x, position.y + m_Size.y, position.z + m_Size.z);
	//m_Position[7] = XMFLOAT3(position.x , position.y + m_Size.y, position.z + m_Size.z);
	////正面
	//m_Position[8] = XMFLOAT3(position.x, position.y, position.z + m_Size.z);
	//m_Position[9] = XMFLOAT3(position.x + m_Size.x, position.y, position.z + m_Size.z);
	//m_Position[10] = XMFLOAT3(position.x, position.y + m_Size.y, position.z + m_Size.z);
	//m_Position[11] = XMFLOAT3(position.x + m_Size.x, position.y + m_Size.y, position.z + m_Size.z);
	////右面
	//m_Position[12] = XMFLOAT3(position.x + m_Size.x, position.y, position.z + m_Size.z);
	//m_Position[13] = XMFLOAT3(position.x + m_Size.x, position.y, position.z);
	//m_Position[14] = XMFLOAT3(position.x + m_Size.x, position.y + m_Size.y, position.z + m_Size.z);
	//m_Position[15] = XMFLOAT3(position.x + m_Size.x, position.y + m_Size.y, position.z);
	////裏面
	//m_Position[16] = XMFLOAT3(position.x + m_Size.x, position.y, position.z);
	//m_Position[17] = XMFLOAT3(position.x, position.y, position.z);
	//m_Position[18] = XMFLOAT3(position.x + m_Size.x, position.y + m_Size.y, position.z);
	//m_Position[19] = XMFLOAT3(position.x + m_Size.x, position.y + m_Size.y, position.z);
	////左面
	//m_Position[20] = XMFLOAT3(position.x, position.y, position.z);
	//m_Position[21] = XMFLOAT3(position.x, position.y, position.z + m_Size.z);
	//m_Position[22] = XMFLOAT3(position.x, position.y + m_Size.y, position.z);
	//m_Position[23] = XMFLOAT3(position.x, position.y + m_Size.y, position.z + m_Size.z);

	//vertex[0].Position = XMFLOAT3(-10.0f, 0.0f, 10.0f);
	vertex[0].Position = m_VertexPosition[0];
	vertex[0].Normal   = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
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

	////テクスチャの読み込み
	//TexMetadata metadata;
	//ScratchImage image;
	////LoadFromWICFile(L"asset\\texture\\bakuhatu_30f.png", WIC_FLAGS_NONE, &metadata, image);
	//LoadFromWICFile(L"asset\\texture\\explosion.png", WIC_FLAGS_NONE, &metadata, image);
	//CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	//assert(m_Texture);//読み込めなかったらここで止めようにassertを使う

	m_Texture = Texture::Load("asset\\texture\\explosion.png");//頭にLを入れる必要がない

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");


	m_Frame_x = 6;
	m_Frame_y = 5;
	m_Frame_max = m_Frame_x * m_Frame_y -3;
	m_Frame_count = 0;

	m_movement_x = movementx;
	m_movement_y = movementy;
}

Explosion::~Explosion()
{
	//m_Texture->Release();

	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Explosion::Init(Input*)
{
}

void Explosion::Uninit()
{

}

void Explosion::Update()
{
	


	m_Frame_count++;

	if (m_Frame_count >= m_Frame_max)
	{
		m_IsDestroy = true;
	}

	//updateposition();
}

void Explosion::Draw()
{

	float w = (1.0f / m_Frame_x);
	float h = 1.0f / m_Frame_y;
	float x = m_Frame_count % m_Frame_x * w;
	float y = m_Frame_count / m_Frame_y * h;

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	 Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
	{
		vertex[0].Position  = XMFLOAT3(-1.0f, 1.0f, 0.0f);
		vertex[0].Diffuse   = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord  = XMFLOAT2(x, y);
		vertex[0].Normal    = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[1].Position  = XMFLOAT3(1.0f, 1.0f, 0.0f);
		vertex[1].Diffuse   = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord  = XMFLOAT2(x + w, y);
		vertex[1].Normal    = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[2].Position  = XMFLOAT3(-1.0f, -1.0f, 0.0f);
		vertex[2].Diffuse   = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord  = XMFLOAT2(x, y + h);
		vertex[2].Normal    = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[3].Position  = XMFLOAT3(1.0f, -1.0f, 0.0f);
		vertex[3].Diffuse   = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord  = XMFLOAT2(x + w, y + h);
		vertex[3].Normal    = XMFLOAT3(0.0f, 0.0f, -1.0f);
	}

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリックスの設定
	//ビューの逆行列
	Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();

	XMMATRIX view = p_camera->GetViewMatrix();

	XMMATRIX inView;
	inView = XMMatrixInverse(nullptr, view); //逆行列
	inView.r[3].m128_f32[0] = 0.0f;
	inView.r[3].m128_f32[1] = 0.0f;
	inView.r[3].m128_f32[2] = 0.0f;

	//平行移動行列の作成（表示座標を決める）
	XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.m_x, m_Position.m_y, m_Position.m_z);

	//回転行列（Z回転）行列の作成
	//XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.m_x, m_Rotation.m_y, m_Rotation.m_z);

	//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
	XMMATRIX	ScalingMatrix = XMMatrixScaling(m_Scale.m_x, m_Scale.m_y, m_Scale.m_z);

	//ワールド行列の作成（ポリゴンの表示の仕方を指定する最終的な行列
	XMMATRIX	WorldMatrix = ScalingMatrix * inView * TranslationMatrix;

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
	//Zバッファを切るコード
	//Renderer::SetDepthEnable(false);

	//ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);

	//Renderer::SetDepthEnable(true);
}

