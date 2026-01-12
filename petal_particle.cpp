//********************************************************************************
//
// fire_particle.h[パーティクル]
//
//															Author :Riugo Honda
//															Date   :2025/10/22
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "camera.h"
#include "texture.h"
#include "player.h"

#include <random>
#include <cmath>

#include "petal_particle.h"


//********************************************************************************
//関数
//********************************************************************************
PetalParticle::PetalParticle(Vector3 size, Vector3 position, int movementx, int movementy, Vector3 rotation)
{
	m_Scale = size;
	m_Position = position;
	VERTEX_3D vertex[4];
	//上面
	m_VertexPosition[0] = XMFLOAT3(position.x - m_Scale.x, position.y + m_Scale.y, position.z);
	m_VertexPosition[1] = XMFLOAT3(position.x + m_Scale.x, position.y + m_Scale.y, position.z);
	m_VertexPosition[2] = XMFLOAT3(position.x - m_Scale.x, position.y - m_Scale.y, position.z);
	m_VertexPosition[3] = XMFLOAT3(position.x + m_Scale.x, position.y - m_Scale.y, position.z);

	//vertex[0].Position = XMFLOAT3(-10.0f, 0.0f, 10.0f);
	vertex[0].Position = m_VertexPosition[0];
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	//vertex[1].Position = XMFLOAT3(10.0f, 0.0f, 10.0f);
	vertex[1].Position = m_VertexPosition[1];
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(0.5f, 0.0f);

	//vertex[2].Position = XMFLOAT3(-10.0f, 0.0f, -10.0f);
	vertex[2].Position = m_VertexPosition[2];
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	//vertex[3].Position = XMFLOAT3(10.0f, 0.0f, -10.0f);
	vertex[3].Position = m_VertexPosition[3];
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(0.5f, 1.0f);

	////頂点バッファ生成
	//D3D11_BUFFER_DESC bd{};
	//bd.Usage = D3D11_USAGE_DEFAULT;//ここをダイナミックに変更しなければ途中でテクスチャマッピングを変えれない
	//bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;//ここをwriteに変更

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
	m_Texture = Texture::Load("asset\\texture\\petal.png");//頭にLを入れる必要がない

	//m_Texture = Texture::Load("asset\\texture\\fire.png");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	m_IsDestroy = false;
	m_Frame_count = 0;
	m_Frame_max = PETAL_PARTICLE_LIFESPAN_MAX;

	m_RGB = { 1.0f, 0.75f, 0.85f };
	m_SpawnerCenterPoint = { 0.0f , 0.0f ,0.0f };
	m_Radius = 7.5f;

	for (int i = 0; i < PETAL_PARTICLE_MAX; i++)
	{
		m_Petal[i].Enable = false;
	}
}

PetalParticle::~PetalParticle()
{
	//m_Texture->Release();

	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void PetalParticle::Init()
{
}

void PetalParticle::Uninit()
{

}

void PetalParticle::Update()
{

	int count = 5;

	std::random_device rd;
	std::mt19937 mt(rd());

	for (int i = 0; i < PETAL_PARTICLE_MAX; i++)
	{
		if (m_Petal[i].Enable == false)
		{

			std::uniform_real_distribution<float> randVel(-0.01f, 0.01f);

			std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);
			float angle = randangle(mt);

			std::uniform_real_distribution<float> randdist(-m_Radius, m_Radius);
			float distance = randdist(mt);

			{//花びらの位置決定
				m_Petal[i].Position.x = m_SpawnerCenterPoint.x + cosf(angle) * distance;
				m_Petal[i].Position.y = 5.0f;
				m_Petal[i].Position.z = m_SpawnerCenterPoint.z + sinf(angle) * distance;
			}

			m_Petal[i].Enable = true;
			m_Petal[i].LifeFrame = PETAL_PARTICLE_LIFESPAN_MAX;

			/*float x = (rand() % 100 - 50) / 500.0f;
			float y = (rand() % 100 + 50) / 500.0f;
			float z = (rand() % 100 - 50) / 500.0f;*/



			{//花びらの大きさ決定
				std::uniform_real_distribution<float> randsize(0.01f, m_Radius / 60.0f );

				float size = randsize(mt);

				m_PetalSize[i].x = size;
				m_PetalSize[i].y = size;
				m_PetalSize[i].z = size;
			}

			//花びらの速度決定
			m_Petal[i].Velocity = Vector3(randVel(mt), -0.02f, randVel(mt));

			m_Petal[i].RotationSpeed = randVel(mt) * 5.0f;

			//m_Petal[i].Velocity = Vector3(0.3f, 0.3f, 0.3f);
			//評価課題用メモパーティクルを衝突時に生成する
			//バレットは追跡型にする

			count--;

			if (count == 0)
			{
				break;
			}
		}
	}

	for (int i = 0; i < PETAL_PARTICLE_MAX; i++)
	{
		if (m_Petal[i].Enable == true)
		{
			// ふわふわ横揺れ
			m_Petal[i].Velocity.x += sinf(m_Petal[i].LifeFrame * 0.1f) * 0.0005f;
			m_Petal[i].Velocity.z += cosf(m_Petal[i].LifeFrame * 0.1f) * 0.0005f;

			m_Petal[i].Position += m_Petal[i].Velocity;
			m_Petal[i].Rotation += m_Petal[i].RotationSpeed;

			m_Petal[i].LifeFrame--;

			if (m_Petal[i].LifeFrame == 0 || m_Petal[i].Position.y <= -1.0f)
			{
				m_Petal[i].Enable = false;
			}
		}
	}

	/*if (m_Frame_count >= 0 && m_Frame_count < 5)
	{
		m_RGB = { 1.0f , 1.0f , 0.0f };
	}
	else if (m_Frame_count < 20)
	{
		m_RGB = { 0.7f , 0.2f , 0.0f };
	}
	else if (m_Frame_count < 60)
	{
		m_RGB = { 0.5f , 0.0f , 0.0f };
	}
	else
	{
		m_RGB = { 0.3f , 0.3f , 0.3f };
	}*/

	//updateposition();
}

void PetalParticle::Draw()
{

	{//パーティクル部分
		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
		{
			vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(m_RGB.x, m_RGB.y, m_RGB.z, 1.0f);
			vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(m_RGB.x, m_RGB.y, m_RGB.z, 1.0f);
			vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(m_RGB.x, m_RGB.y, m_RGB.z, 1.0f);
			vertex[2].TexCoord = XMFLOAT2(0.0f, 0.0f);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertex[3].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(m_RGB.x, m_RGB.y, m_RGB.z, 1.0f);
			vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
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
		Renderer::SetDepthEnable(false);

		for (int i = 0; i < PETAL_PARTICLE_MAX; i++)
		{
			if (m_Petal[i].Enable == true)
			{
				//平行移動行列の作成（表示座標を決める）
				XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Petal[i].Position.x, m_Petal[i].Position.y, m_Petal[i].Position.z);

				////ローテーション設定
				XMMATRIX	RotationMatrix = XMMatrixRotationZ(m_Petal[i].Rotation);

				//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
				XMMATRIX	ScalingMatrix = XMMatrixScaling(m_PetalSize[i].x, m_PetalSize[i].y, m_PetalSize[i].z);

				//ワールド行列の作成（ポリゴンの表示の仕方を指定する最終的な行列
				XMMATRIX	WorldMatrix = ScalingMatrix * RotationMatrix * inView * TranslationMatrix;

				Renderer::SetWorldMatrix(WorldMatrix);

				//ポリゴン描画
				Renderer::GetDeviceContext()->Draw(4, 0);
			}
		}


		Renderer::SetDepthEnable(true);
	}


}

void PetalParticle::SetParticle(int life, Vector3 centerpos, float radius)
{
	m_SpawnerLife = life;
	m_SpawnerCenterPoint = centerpos;
	m_Radius = radius;

	VERTEX_3D vertex[4];

	//1chunk用の頂点データ
	vertex[0].Position = XMFLOAT3(m_SpawnerCenterPoint.x - m_Radius, 0.0f, m_SpawnerCenterPoint.z - m_Radius);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(m_SpawnerCenterPoint.x + m_Radius, 0.0f, m_SpawnerCenterPoint.z - m_Radius);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(m_SpawnerCenterPoint.x - m_Radius, 0.0f, m_SpawnerCenterPoint.z + m_Radius);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(m_SpawnerCenterPoint.x + m_Radius, 0.0f, m_SpawnerCenterPoint.z + m_Radius);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


	m_FloorTopLeft = { 0.0f , 0.5f, 0.0f };


	{
		//頂点バッファ作成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(vertex);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_FloorVertexBuffer);
	}


	//インデックス作成
	WORD index[6] = { 0 , 2 , 1 , 1, 2, 3 };

	{
		//インデックスバッファ作成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(index);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}
}


