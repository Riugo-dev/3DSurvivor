//********************************************************************************
//
// fire_instparticle.cpp[炎パーティクルのインスタンタンシング]
//
//															Author :Riugo Honda
//															Date   :2026/02/16
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "texture.h"

#include "fire_instparticle.h"

//********************************************************************************
//グローバル変数 & マクロ定義
//********************************************************************************
FireInstParticle* FireInstParticle::m_pMyself;

#define PARITCLE_MAXLIFE (200)
#define PARTICLE_MAXCOUNT (1000)
#define MAX_SPAWNPOINT (6)
#define MAXSPAWN_PERSPAWN (5)

struct CameraforFireParticle
{
	XMFLOAT3 CameraRight;
	float Padding1;

	XMFLOAT3 CameraUp;
	float Padding2;

	XMMATRIX ViewProj;
};

//********************************************************************************
//関数
//********************************************************************************


FireInstParticle* FireInstParticle::GetInstance()
{
	if (!m_pMyself)
	{
		m_pMyself = new FireInstParticle;

		m_pMyself->Init();
	}

	return nullptr;
}

void FireInstParticle::DestroyInstance()
{
	if (!m_pMyself) return;
	m_pMyself->Uninit();
	delete m_pMyself;
	m_pMyself = nullptr;
}

void FireInstParticle::Init()
{
	createbuffers();
	createshaders();
}

void FireInstParticle::Uninit()
{
}

void FireInstParticle::Update()
{
}

void FireInstParticle::Draw()
{
}

void FireInstParticle::SetParticleSpawnPoint(int life ,Vector3 pos , float radius)
{
	for (auto& itr : m_FireParticles)
	{
		if (!itr.IsUsed)
		{
			itr.SpawnPoint = pos;
			itr.IsUsed = true;
			itr.Radius = radius;
			itr.SpawnPointLife = life;
			return;
		}
	}
}

//********************************************************************************
//プライベート関数
//********************************************************************************

void FireInstParticle::createbuffers()
{
	m_FireParticles.reserve(MAX_SPAWNPOINT);

	for (auto& itr : m_FireParticles)
	{
		//インスタンスバッファの作成
		D3D11_BUFFER_DESC desc{};
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.ByteWidth = sizeof(InstanceData) * PARTICLE_MAXCOUNT;
		itr.ParticleData.reserve(PARTICLE_MAXCOUNT);
		itr.Sendingdata.reserve(PARTICLE_MAXCOUNT);

		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &itr.InstanceBuffer);

		itr.IsUsed = false;
		itr.SpawnPoint = { 0.0f , -10.0f , 0.0f };
		itr.Radius = 0.0f;
		itr.SpawnPointLife = 0;
	}

	m_Texture = Texture::Load(("asset\\texture\\fire.png"));
	m_RingTexture = Texture::Load("asset\\texture\\range_ring.png");

	//パーティクル部分用
	{
		//VertexBufferの作成
		VERTEX_3D vertex[4];
		vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = XMFLOAT4(0.7f, 0.0f, 0.0f, 1.0f);
		vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = XMFLOAT4(0.7f, 0.0f, 0.0f, 1.0f);
		vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
		vertex[2].Diffuse = XMFLOAT4(0.7f, 0.0f, 0.0f, 1.0f);
		vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[3].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
		vertex[3].Diffuse = XMFLOAT4(0.7f, 0.0f, 0.0f, 1.0f);
		vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		D3D11_BUFFER_DESC desc{};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(VERTEX_3D) * 4;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA srd{};
		srd.pSysMem = vertex;

		Renderer::GetDevice()->CreateBuffer(&desc, &srd, &m_pVertexBuffer);
	}

	{
		//Cameraのバッファー作成
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = sizeof(CameraforFireParticle);
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &m_pCameraBuffer);
	}

	//範囲を視覚的にわかりやすくするための枠用
	{
		//VertexBufferの作成
		VERTEX_3D vertex[4];
		vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		vertex[3].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		D3D11_BUFFER_DESC desc{};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(VERTEX_3D) * 4;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA srd{};
		srd.pSysMem = vertex;

		Renderer::GetDevice()->CreateBuffer(&desc, &srd, &m_pRingVertexBuffer);
	}
}

void FireInstParticle::createshaders()
{
	Renderer::CreateInstanceVertexShader(&m_pVertexShader, &m_pInputLayout, "shader\\unlitTexInstancedVS.cso");
	Renderer::CreatePixelShader(&m_pPixelShader, "shader\\unlitTexturePS.cso");

	Renderer::CreateInstanceVertexShader(&m_pRingVertexShader, &m_pRingInputLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_pRingPixelShader, "shader\\unlitTexturePS.cso");
}

void FireInstParticle::spawnparticles()
{
}

void FireInstParticle::updateparticles()
{
}

void FireInstParticle::updateinstancebuffer()
{
}

void FireInstParticle::destroyparticles()
{
}
