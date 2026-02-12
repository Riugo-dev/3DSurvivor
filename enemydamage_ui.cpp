//********************************************************************************
//
// enemydamage_ui.h[敵ダメージUIクラス]
//
//															Author :Riugo Honda
//															Date   :2026/02/07
//********************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "texture.h"
#include "camera.h"
#include <vector>
#include <unordered_map>

#include "enemydamage_ui.h"

//********************************************************************************
//グローバル変数
//********************************************************************************
EnemyDamageUI* EnemyDamageUI::m_pMySelf;

#define DAMAGE_ONE_MAX (1000)
#define DAMAGE_OTHER_MAX (300)

struct CameraforDamageUI
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

EnemyDamageUI* EnemyDamageUI::GetInstance()
{
	if (!m_pMySelf)
	{
		m_pMySelf = new EnemyDamageUI;

		m_pMySelf->Init();
	}

	return m_pMySelf;
}

void EnemyDamageUI::DestroyInstance()
{
	if (!m_pMySelf)return;
	m_pMySelf->Uninit();
	delete m_pMySelf;
	m_pMySelf = nullptr;
}

void EnemyDamageUI::Init()
{
	createbuffers();
	createshaders();
}

void EnemyDamageUI::Uninit()
{
	for (auto& itr : map_DamageUIs)
	{
		DamageUIInfo& inst = itr.second;

		inst.InstanceBuffer->Release();
		inst.m_pVertexBuffer->Release();
		inst.m_DamageData.clear();
		inst.m_Sendingdata.clear();
	}

	m_pVertexShader->Release();
	m_pPixelShader->Release();
	m_pInputLayout->Release();
	m_pCameraBuffer->Release();
}

void EnemyDamageUI::Update()
{
	updateuis();
	updateinstancebuffer();
	destroyuis();
}

void EnemyDamageUI::Draw()
{
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

	CameraforDamageUI cb{};
	cb.CameraRight = camright;
	cb.CameraUp = camup;
	cb.ViewProj = XMMatrixTranspose(view * camera->GetProjectionMatrix());
	Renderer::GetDeviceContext()->UpdateSubresource(m_pCameraBuffer, 0, nullptr, &cb, 0, 0);

	for (auto& itr : map_DamageUIs)
	{
		DamageUI tag = itr.first;
		DamageUIInfo& inst = itr.second;

		if (inst.m_Sendingdata.empty())	continue;

		Renderer::GetDeviceContext()->IASetInputLayout(m_pInputLayout);
		Renderer::GetDeviceContext()->VSSetShader(m_pVertexShader , NULL , 0);
		Renderer::GetDeviceContext()->PSSetShader(m_pPixelShader , NULL , 0);
		Renderer::GetDeviceContext()->VSSetConstantBuffers(8, 1, &m_pCameraBuffer);

		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &inst.Texture);

		//頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &inst.m_pVertexBuffer, &stride, &offset);

		Renderer::SetDepthEnable(false);

		Renderer::GetDeviceContext()->DrawInstanced(4, inst.m_Sendingdata.size(), 0, 0);

		Renderer::SetDepthEnable(true);
	}
}

void EnemyDamageUI::SpawnDamageUI(DamageUI damage, Vector3 pos)
{
	for (auto& itr : map_DamageUIs)
	{
		auto tag = itr.first;
		DamageUIInfo& inst = itr.second;

		if (tag == damage)
		{
			DamageData data;
			data.Position = pos;
			data.Position.y += 1.0f;
			data.Scale = Vector3{ 0.5f ,0.5f , 0.5f };
			data.Rotation = Vector3{ 0.0f, 0.0f , 0.0f };
			data.IsDestory = false;
			data.LifeCount = 0;

			inst.m_DamageData.push_back(data);
		}

	}
}



//********************************************************************************
//プライベート関数
//********************************************************************************

void EnemyDamageUI::createbuffers()
{
	for (int tag = DAMAGE_1; tag < DAMAGE_MAX; tag++)
	{
		map_DamageUIs[(DamageUI)tag] = DamageUIInfo();

		auto& inst = map_DamageUIs[(DamageUI)tag];

		switch(tag)
		{
		case DAMAGE_1:
			inst.m_Sendingdata.reserve(DAMAGE_ONE_MAX);
			inst.m_DamageData.reserve(DAMAGE_ONE_MAX);
			inst.Texture = Texture::Load("asset\\texture\\EnemyDamage1.png");
			break;
		case DAMAGE_60:
			inst.m_Sendingdata.reserve(DAMAGE_OTHER_MAX);
			inst.m_DamageData.reserve(DAMAGE_OTHER_MAX);
			inst.Texture = Texture::Load("asset\\texture\\EnemyDamage60.png");
			break;
		case DAMAGE_300:
			inst.m_Sendingdata.reserve(DAMAGE_OTHER_MAX);
			inst.m_DamageData.reserve(DAMAGE_OTHER_MAX);
			inst.Texture = Texture::Load("asset\\texture\\EnemyDamage300.png");
		case DAMAGE_360:
			inst.m_Sendingdata.reserve(DAMAGE_OTHER_MAX);
			inst.m_DamageData.reserve(DAMAGE_OTHER_MAX);
			inst.Texture = Texture::Load("asset\\texture\\EnemyDamage360.png");
			break;
		case DAMAGE_420:
			inst.m_Sendingdata.reserve(DAMAGE_OTHER_MAX);
			inst.m_DamageData.reserve(DAMAGE_OTHER_MAX);
			inst.Texture = Texture::Load("asset\\texture\\EnemyDamage420.png");
			break;
		case DAMAGE_480:
			inst.m_Sendingdata.reserve(DAMAGE_OTHER_MAX);
			inst.m_DamageData.reserve(DAMAGE_OTHER_MAX);
			inst.Texture = Texture::Load("asset\\texture\\EnemyDamage480.png");
			break;
		case DAMAGE_540:
			inst.m_Sendingdata.reserve(DAMAGE_OTHER_MAX);
			inst.m_DamageData.reserve(DAMAGE_OTHER_MAX);
			inst.Texture = Texture::Load("asset\\texture\\EnemyDamage540.png");
			break;
		case DAMAGE_600:
			inst.m_Sendingdata.reserve(DAMAGE_OTHER_MAX);
			inst.m_DamageData.reserve(DAMAGE_OTHER_MAX);
			inst.Texture = Texture::Load("asset\\texture\\EnemyDamage600.png");
			break;
		}

		//インスタンスバッファの作成
		D3D11_BUFFER_DESC desc{};
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &inst.InstanceBuffer);

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

			Renderer::GetDevice()->CreateBuffer(&desc, &srd, &inst.m_pVertexBuffer);
		}

	} 
}

void EnemyDamageUI::createshaders()
{
	Renderer::CreateInstanceVertexShader(&m_pVertexShader, &m_pInputLayout, "shader\\unlitTexInstancedVS.cso");
	Renderer::CreatePixelShader(&m_pPixelShader ,"shader\\unlitTexturePS.cso");
}

void EnemyDamageUI::updateuis()
{

	for (auto& itr : map_DamageUIs)
	{
		auto tag = itr.first;
		DamageUIInfo& inst = itr.second;

		if (inst.m_DamageData.empty()) continue;

		for (auto data : inst.m_DamageData)
		{
			data.LifeCount++;
			data.Position.y += 0.01;
			if (data.LifeCount >= 60)
			{
				data.IsDestory = true;
			}
		}
	}
}

void EnemyDamageUI::updateinstancebuffer()
{
	for (auto& itr : map_DamageUIs)
	{
		DamageUIInfo& inst = itr.second;

		inst.m_Sendingdata.clear();

		for (auto itr : inst.m_DamageData)
		{
			InstanceData data{};
			data.Position = { itr.Position.x , itr.Position.y , itr.Position.z , 1.0f };
			data.Rotation = { itr.Rotation.x , itr.Rotation.y , itr.Rotation.z , 0.0f };
			data.Scale = { itr.Scale.x , itr.Scale.y , itr.Scale.z , 1.0f };

			inst.m_Sendingdata.push_back(data);
		}

		if (inst.m_Sendingdata.empty()) continue;

		D3D11_MAPPED_SUBRESOURCE mapped{};
		Renderer::GetDeviceContext()->Map(inst.InstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);

		memcpy(mapped.pData, inst.m_Sendingdata.data(), sizeof(InstanceData) * inst.m_Sendingdata.size());

		Renderer::GetDeviceContext()->Unmap(inst.InstanceBuffer, 0);

	}
}

void EnemyDamageUI::destroyuis()
{
	for (auto& itr : map_DamageUIs)
	{
		auto tag = itr.first;
		DamageUIInfo& inst = itr.second;

		if (inst.m_DamageData.empty()) continue;

		for (auto itr = inst.m_DamageData.begin(); itr != inst.m_DamageData.end();)
		{
			if (itr->IsDestory) {
				itr = inst.m_DamageData.erase(itr);

			}
			else
			{
				++itr;
			}
		}
	}
}

