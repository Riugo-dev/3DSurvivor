//********************************************************************************
//
// fire_instparticle.cpp[炎パーティクルのインスタンタンシング]
//
//															Author :Riugo Honda
//															Date   :2026/02/16
//********************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "texture.h"
#include "camera.h"
#include <random>
#include <vector>
#include <cmath>

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

	return m_pMyself;
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
	m_ResetSpawnPoint = false;
	m_SpawnPointLife = 0;
	m_FrameCount = 0;

	for (auto itr : m_FireParticles)
	{
		itr.ParticleData.reserve(PARTICLE_MAXCOUNT);
	}
}

void FireInstParticle::Uninit()
{

	for (auto& itr : m_FireParticles)
	{
		itr.InstanceBuffer->Release();
		itr.Sendingdata.clear();
		itr.ParticleData.clear();
		itr.RingVertexBuffer->Release();
	}
	m_FireParticles.clear();

	m_pVertexBuffer->Release();
	m_pVertexShader->Release();
	m_pPixelShader->Release();
	m_pInputLayout->Release();
	m_pCameraBuffer->Release();
	
	m_pRingVertexShader->Release();
	m_pRingPixelShader->Release();
	m_pRingInputLayout->Release();
}

void FireInstParticle::Update()
{
	spawnparticles();
	updateparticles();
	updateinstancebuffer();
	destroyparticles();

	
	{

		m_FrameCount++;

		if (m_FrameCount >= m_SpawnPointLife)
		{
			m_ResetSpawnPoint = true;
		}
	}


	if (m_ResetSpawnPoint)
	{
		destroyspawnpoints();
	}
}

void FireInstParticle::Draw()
{
	if (m_FireParticles.empty()) return;

	Camera* camera = Manager::GetScene()->GetGameObject<Camera>();

	if (!camera) return;

	XMMATRIX view = camera->GetViewMatrix();

	XMFLOAT3 camright =
	{
		view.r[0].m128_f32[0],
		view.r[1].m128_f32[0],
		view.r[2].m128_f32[0]
	};

	XMFLOAT3 camup =
	{
		view.r[0].m128_f32[1],
		view.r[1].m128_f32[1],
		view.r[2].m128_f32[1]
	};

	CameraforFireParticle cb{};
	cb.CameraRight = camright;
	cb.CameraUp = camup;
	cb.ViewProj = XMMatrixTranspose(view * camera->GetProjectionMatrix());
	Renderer::GetDeviceContext()->UpdateSubresource(m_pCameraBuffer, 0, nullptr, &cb, 0, 0);



	for (auto& itr : m_FireParticles)
	{
		if (!itr.IsUsed) continue;

		{//範囲円
			//ワールド行列
			XMMATRIX world = XMMatrixTranslation(0.0f, 0.5f + 0.01f, 0.0f); // +0.01fはZ-fighting避け
			Renderer::SetWorldMatrix(world);

			// 頂点バッファ＆インデックス
			UINT stride = sizeof(VERTEX_3D);
			UINT offset = 0;
			Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &itr.RingVertexBuffer, &stride, &offset);
			Renderer::GetDeviceContext()->IASetIndexBuffer(m_pRingIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

			// マテリアル設定
			MATERIAL material;
			ZeroMemory(&material, sizeof(material));
			material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			material.TextureEnable = true;
			Renderer::SetMaterial(material);

			// シェーダー＆テクスチャ
			Renderer::GetDeviceContext()->IASetInputLayout(m_pRingInputLayout);
			Renderer::GetDeviceContext()->VSSetShader(m_pRingVertexShader, nullptr, 0);
			Renderer::GetDeviceContext()->PSSetShader(m_pRingPixelShader, nullptr, 0);
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_RingTexture);
			Renderer::SetDepthEnable(false);
			// 描画
			Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			Renderer::GetDeviceContext()->DrawIndexed(6, 0, 0);
			Renderer::SetDepthEnable(true);
		}

		{//炎パーティクル
			Renderer::GetDeviceContext()->IASetInputLayout(m_pInputLayout);
			Renderer::GetDeviceContext()->VSSetShader(m_pVertexShader, NULL, 0);
			Renderer::GetDeviceContext()->PSSetShader(m_pPixelShader, NULL, 0);
			Renderer::GetDeviceContext()->VSSetConstantBuffers(8, 1, &m_pCameraBuffer);

			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

			//マテリアル設定
			MATERIAL material{};
			material.Diffuse = { 1.0f , 1.0f , 1.0f , 1.0f };
			material.TextureEnable = true;
			Renderer::SetMaterial(material);


			//頂点バッファ設定
			UINT stride[2] = { sizeof(VERTEX_3D), sizeof(InstanceData) };
			UINT offset[2] = { 0 , 0 };

			ID3D11Buffer* buffers[2]{ m_pVertexBuffer , itr.InstanceBuffer };

			Renderer::GetDeviceContext()->IASetVertexBuffers(0, 2, buffers, stride, offset);

			Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

			Renderer::SetDepthEnable(false);

			Renderer::GetDeviceContext()->DrawInstanced(4, itr.Sendingdata.size(), 0, 0);

			Renderer::SetDepthEnable(true);
		}
	}

}

void FireInstParticle::SetParticleSpawnPoint(int life ,Vector3 pos , float radius)
{
	m_SpawnPointLife = life;
	m_FrameCount = 0;
	for (auto& itr : m_FireParticles)
	{
		if (!itr.IsUsed)
		{
			itr.SpawnPoint = pos;
			itr.IsUsed = true;
			itr.Radius = radius;

			{
				//範囲円の更新
				VERTEX_3D vertex[4];
				vertex[0].Position = XMFLOAT3(pos.x - radius, 0.0f/* + (itr.ParticleData.size() * 0.0001)*/, pos.z - radius);
				vertex[0].Diffuse = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
				vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
				vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

				vertex[1].Position = XMFLOAT3(pos.x + radius, 0.0f/* + (itr.ParticleData.size() * 0.0001)*/, pos.z - radius);
				vertex[1].Diffuse = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
				vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
				vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

				vertex[2].Position = XMFLOAT3(pos.x - radius, 0.0f/* + (itr.ParticleData.size() * 0.0001)*/, pos.z + radius);
				vertex[2].Diffuse = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
				vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
				vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

				vertex[3].Position = XMFLOAT3(pos.x + radius, 0.0f /*+ (itr.ParticleData.size() * 0.0001)*/, pos.z + radius);
				vertex[3].Diffuse = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
				vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
				vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

				Renderer::GetDeviceContext()->UpdateSubresource(itr.RingVertexBuffer, 0, nullptr, vertex, 0, 0);

			}
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

	for (int i = 0; i < MAX_SPAWNPOINT; i++)
	{
		ParticleInfo itr;

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
			desc.CPUAccessFlags = 0;;

			D3D11_SUBRESOURCE_DATA srd{};
			srd.pSysMem = vertex;

			Renderer::GetDevice()->CreateBuffer(&desc, &srd, &itr.RingVertexBuffer);
		}

		m_FireParticles.push_back(itr);
		
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

	{
		//インデックス作成
		WORD index[6] = { 0 , 2 , 1 , 1, 2, 3 };

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

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_pRingIndexBuffer);
	}
}

void FireInstParticle::createshaders()
{
	Renderer::CreateInstanceVertexShader(&m_pVertexShader, &m_pInputLayout, "shader\\unlitTexInstancedVS.cso");
	Renderer::CreatePixelShader(&m_pPixelShader, "shader\\unlitTexturePS.cso");

	Renderer::CreateVertexShader(&m_pRingVertexShader, &m_pRingInputLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_pRingPixelShader, "shader\\unlitTexturePS.cso");
}

void FireInstParticle::spawnparticles()
{
	for (auto& itr : m_FireParticles)
	{
		if (!itr.IsUsed) return;


		std::random_device rd;
		std::mt19937 mt(rd());

		if (itr.ParticleData.size() >= 990) continue;

		for (int i = 0; i < MAXSPAWN_PERSPAWN; i++)
		{
			std::uniform_real_distribution<float> randangle(0.0f, XM_2PI);
			float angle = randangle(mt);

			Vector3 spawnpoint;

			std::uniform_real_distribution<float> randdist(-itr.Radius, itr.Radius);
			float distance = randdist(mt);

			Particle particle;

			particle.Enable = true;
			particle.Position.x = itr.SpawnPoint.x + cosf(angle) * distance;
			particle.Position.y = 0.1f;
			particle.Position.z = itr.SpawnPoint.z + sinf(angle) * distance;


			std::uniform_real_distribution<float> randsize(0.05f, itr.Radius / 8);

			float size = randsize(mt);

			particle.Scale.x = size;
			particle.Scale.y = size;
			particle.Scale.z = size;

			particle.Velocity = Vector3(0.0f, 0.1f, 0.0f);
			particle.Rotation = Vector3(0.0f, 0.0f, 0.0f);
			particle.LifeCount = PARITCLE_MAXLIFE;

			itr.ParticleData.push_back(particle);
		}
	}
}

void FireInstParticle::updateparticles()
{
	for (auto& itr : m_FireParticles)
	{
		if (!itr.IsUsed) return;

		for (auto& par : itr.ParticleData)
		{
			par.Position += par.Velocity;
			par.LifeCount--;

			if (par.LifeCount <= 0 || par.Position.y >= 5.0f)
			{
				par.Enable = false;
			}

		}
	}
}

void FireInstParticle::updateinstancebuffer()
{
	for (auto& itr : m_FireParticles)
	{
		itr.Sendingdata.clear();

		if (itr.ParticleData.empty()) continue;

		for (auto& inst : itr.ParticleData)
		{
			InstanceData data{};
			data.Position = { inst.Position.x , inst.Position.y , inst.Position.z , 1.0f };
			data.Rotation = { inst.Rotation.x , inst.Rotation.y , inst.Rotation.z , 0.0f };
			data.Scale = { inst.Scale.x , inst.Scale.y , inst.Scale.z , 1.0f };

			itr.Sendingdata.push_back(data);
		}

		if (itr.Sendingdata.empty()) continue;


		D3D11_MAPPED_SUBRESOURCE mapped{};
		Renderer::GetDeviceContext()->Map(itr.InstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);

		memcpy(mapped.pData, itr.Sendingdata.data(), sizeof(InstanceData) * itr.Sendingdata.size());

		Renderer::GetDeviceContext()->Unmap(itr.InstanceBuffer, 0);

	}
}

void FireInstParticle::destroyparticles()
{
	for (auto& itr : m_FireParticles)
	{
		if (itr.ParticleData.empty())continue;

		for (auto par = itr.ParticleData.begin(); par != itr.ParticleData.end();)
		{
			if (!par->Enable)
			{
				par = itr.ParticleData.erase(par);
			}
			else
			{
				++par;
			}
		}
	}
}

void FireInstParticle::destroyspawnpoints()
{
	for (auto& itr : m_FireParticles)
	{
		itr.IsUsed = false;
		itr.ParticleData.clear();
		itr.Radius = 0;
		//itr.Sendingdata.clear();
		itr.SpawnPoint = { 0.0f , 0.0f, 0.0f };
	}

	m_ResetSpawnPoint = false;
}
