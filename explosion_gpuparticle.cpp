//********************************************************************************
//
// explosion_gpuparticle.cpp[爆発GPUパーティクルクラス]
//
//															Author :Riugo Honda
//															Date   :2026/01/29
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "manager.h"
#include "scene.h"
#include "camera.h"

#include "explosion_gpuparticle.h"

//********************************************************************************
//グローバル変数
//********************************************************************************
GPUExplosionParticle* GPUExplosionParticle::m_pMyself;

//各種バッファのデータ　※RendererにGPUパーティクルは定義してる
struct SpawnCB
{
	UINT SpawnCount;
	UINT ParticleCount;
	float padding[2];
};

struct UpdateCB
{
	float Gravity;
	float FadeSpeed;
	UINT  AliveCount;
	float padding;
};

struct CameraforParticleCB
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
GPUExplosionParticle* GPUExplosionParticle::GetInstance()
{
	if (!m_pMyself)
	{
		m_pMyself = new GPUExplosionParticle;

		m_pMyself->Init();
	}
	return m_pMyself;
}

void GPUExplosionParticle::DestroyInstance()
{
	if (!m_pMyself)return;
	m_pMyself->Uninit();
	delete m_pMyself;
	m_pMyself = nullptr;
}

void GPUExplosionParticle::Init()
{
	createbuffers();//バッファの作成
	createviews();//UAVの作成&パーティクルのSRVの作成
	loadshaders();//シェーダーの読み込み
	initializedeadlist();//死者リストの初期化
}

void GPUExplosionParticle::Uninit()
{
	m_pParticleBuffer->Release();
	m_pAliveListBuffer->Release();
	m_pDeadListBuffer->Release();
	m_pSpawnPositionBuffer->Release();
	m_pSpawnBuffer->Release();
	m_pUpdateBuffer->Release();
	m_pCameraBuffer->Release();
	m_pIndirectArgsBuffer->Release();
	m_pAliveCountReadBack->Release();

	m_pParticleUAV->Release();
	m_pAliveListUAV->Release();
	m_pDeadListUAV->Release();

	m_pParticleSRV->Release();
	m_pSpawnPositionSRV->Release();
	m_pAliveListSRV->Release();
	
	m_pVertexShader->Release();
	m_pPixelShader->Release();
	m_pDeadListInitCS->Release();
	m_pSpawnCS->Release();
	m_pUpdateCS->Release();
}

void GPUExplosionParticle::Update()
{
	////新規爆発データのリクエスト整理
	//uploadspawnrequests();

	//int read = m_CurrentParticleIndex;
	//int write = 1 - read;

	////出力先UAVのAppendカウンタをクリア
	//UINT clear[4] = { 0,0,0,0 };
	//Renderer::GetDeviceContext()->ClearUnorderedAccessViewUint(m_pParticleUAV[write], clear);

	//UINT alivecount = getalivecount(m_pParticleUAV[read]);

	////新規爆発がある場合それをもとにCSに送信
	//if (m_CurrentSpawnCount > 0 && alivecount < MAX_PARTICLE)
	//{

	//	SpawnCB cb{};
	//	cb.SpawnCount = m_CurrentSpawnCount;
	//	cb.ParticleCount = PARTICLE_PER_EXPLOSION;

	//	Renderer::GetDeviceContext()->UpdateSubresource(m_pSpawnBuffer, 0, nullptr, &cb, 0, 0);

	//	//CSのセット
	//	Renderer::GetDeviceContext()->CSSetShader(m_pSpawnCS, NULL, 0);

	//	//UAVのセット
	//	Renderer::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, &m_pParticleUAV[write], nullptr);

	//	//SRVのセット
	//	Renderer::GetDeviceContext()->CSSetShaderResources(0, 1, &m_pSpawnPositionSRV);

	//	//定数バッファのセット
	//	Renderer::GetDeviceContext()->CSSetConstantBuffers(8, 1, &m_pSpawnBuffer);

	//	uint32_t totalspawn = m_CurrentSpawnCount * PARTICLE_PER_EXPLOSION;

	//	Renderer::GetDeviceContext()->Dispatch((totalspawn + 255) / 256, 1, 1);
	//}

	//if(alivecount > 0)
	//{//パーティクルの更新
	//	UpdateCB ucb{};
	//	ucb.Gravity = -0.01f;
	//	ucb.FadeSpeed = 1.0f;
	//	ucb.AliveCount = alivecount;

	//	Renderer::GetDeviceContext()->UpdateSubresource(m_pUpdateBuffer, 0, nullptr, &ucb, 0, 0);

	//	Renderer::GetDeviceContext()->CSSetConstantBuffers(8, 1, &m_pUpdateBuffer);

	//	Renderer::GetDeviceContext()->CSSetShader(m_pUpdateCS, NULL, 0);

	//	Renderer::GetDeviceContext()->CSSetShaderResources(0, 1, &m_pParticleSRV[read]);

	//	Renderer::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, &m_pParticleUAV[write], nullptr);

	//	Renderer::GetDeviceContext()->Dispatch((alivecount + 255) / 256, 1, 1);
	//}

	{
		ID3D11UnorderedAccessView* uavs[3] = { m_pParticleUAV, m_pAliveListUAV , m_pDeadListUAV };

		UINT initCounts[3] = { (UINT)-1, 0, (UINT)-1 };

		Renderer::GetDeviceContext()->CSSetUnorderedAccessViews(0, 3, uavs, initCounts);
	}

	updatespawn();

	updateparticle();

	updateindirectargs();

	////後処理
	//ID3D11UnorderedAccessView* nullUAV = nullptr;
	//ID3D11ShaderResourceView* nullSRV = nullptr;

	//Renderer::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, &nullUAV, nullptr);
	//Renderer::GetDeviceContext()->CSSetShaderResources(0, 1, &nullSRV);
	//Renderer::GetDeviceContext()->CSSetShader(nullptr, nullptr, 0);
}

void GPUExplosionParticle::Draw()
{
	Camera* camera = Manager::GetScene()->GetGameObject<Camera>();

	if (!camera) return;
	if (!m_pAliveListSRV)return;

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

	CameraforParticleCB cb{};
	cb.CameraRight = camright;
	cb.CameraUp = camup;
	cb.ViewProj = XMMatrixTranspose(view * camera->GetProjectionMatrix());
	Renderer::GetDeviceContext()->UpdateSubresource(m_pCameraBuffer, 0, nullptr, &cb, 0, 0);

	Renderer::GetDeviceContext()->VSSetConstantBuffers(8, 1, &m_pCameraBuffer);

	Renderer::GetDeviceContext()->IASetInputLayout(nullptr);
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	Renderer::GetDeviceContext()->VSSetShader(m_pVertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_pPixelShader, NULL, 0);

	Renderer::GetDeviceContext()->VSSetShaderResources(0, 1, &m_pParticleSRV);
	Renderer::GetDeviceContext()->VSSetShaderResources(1, 1, &m_pAliveListSRV);
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	Renderer::SetDepthEnable(false);

	Renderer::GetDeviceContext()->DrawInstancedIndirect(m_pIndirectArgsBuffer, 0);

	Renderer::SetDepthEnable(true);
}

void GPUExplosionParticle::SpawnExplosion(Vector3 pos)
{
	XMFLOAT3 data = { pos.x , pos.y , pos.z };
	m_SpawnRequests.push_back(data);
}


void GPUExplosionParticle::initializedeadlist()
{
	UINT clear4[4] = { 0,0,0,0 };
	UINT initcount = 0;
	ID3D11ShaderResourceView* nullSRV[8] = {};
	Renderer::GetDeviceContext()->VSSetShaderResources(0, 8, nullSRV);
	Renderer::GetDeviceContext()->CSSetShaderResources(0, 8, nullSRV);

	Renderer::GetDeviceContext()->CSSetShader(m_pDeadListInitCS, nullptr, 0);
	Renderer::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, &m_pDeadListUAV, &initcount);
	Renderer::GetDeviceContext()->Dispatch((MAX_PARTICLE + 255) / 256, 1, 1);

	//後片付け
	ID3D11UnorderedAccessView* nullUAV[3]{};
	Renderer::GetDeviceContext()->CSSetUnorderedAccessViews(0, 3, nullUAV, nullptr);
	Renderer::GetDeviceContext()->CSSetShader(nullptr, nullptr, 0);
}

//UINT GPUExplosionParticle::getalivecount(ID3D11UnorderedAccessView* uav)
//{
//	UINT count = 0;
//
//	Renderer::GetDeviceContext()->CopyStructureCount(m_pCountBuffer, 0, uav);
//
//	D3D11_MAPPED_SUBRESOURCE mapped{};
//	Renderer::GetDeviceContext()->Map(m_pCountBuffer, 0, D3D11_MAP_READ, 0, &mapped);
//
//	count = *(UINT*)mapped.pData;
//
//	Renderer::GetDeviceContext()->Unmap(m_pCountBuffer, 0);
//
//	return count;
//}

void GPUExplosionParticle::createbuffers()
{
	{
		//ParticleBufferの作成
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = sizeof(GPUParticle) * MAX_PARTICLE;//GPU状に確保するメモリ量
		desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;//更新と描画両方を行うために必要
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;//バッファの指定
		desc.StructureByteStride = sizeof(GPUParticle);//一個当たりのサイズ

		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &m_pParticleBuffer);
	}

	{//DeadListのバッファ作成
		
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = sizeof(UINT) * MAX_PARTICLE;
		desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = sizeof(UINT);

		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &m_pDeadListBuffer);

	}

	{//AliveListのバッファ作成
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = sizeof(UINT) * MAX_PARTICLE;
		desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = sizeof(UINT);

		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &m_pAliveListBuffer);
	}

	{
		//SpawnPositionBufferの作成
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = sizeof(XMFLOAT3) * MAX_PARTICLE;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;//初期値情報を送信するだけなので書き込みが必要ない
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = sizeof(XMFLOAT3);

		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &m_pSpawnPositionBuffer);
	}

	{
		//Spawnのバッファー作成
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = sizeof(SpawnCB);
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &m_pSpawnBuffer);
	}

	{
		//Updateのバッファー作成
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = sizeof(UpdateCB);
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &m_pUpdateBuffer);
	}


	{
		//Cameraのバッファー作成
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = sizeof(CameraforParticleCB);
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &m_pCameraBuffer);
	}

	{
		//IndirectDrawのバッファー作成
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = sizeof(D3D11_DRAW_INSTANCED_INDIRECT_ARGS);
		desc.BindFlags =0;
		desc.MiscFlags = D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS;
		desc.Usage = D3D11_USAGE_DEFAULT;

		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &m_pIndirectArgsBuffer);
	}

	{
		//ReadBackバッファの作成
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = sizeof(UINT);
		desc.Usage = D3D11_USAGE_STAGING;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &m_pAliveCountReadBack);
	}
}

void GPUExplosionParticle::createviews()
{
	{//ParticleUAVとSRV作成
		D3D11_UNORDERED_ACCESS_VIEW_DESC uav{};
		uav.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		uav.Format = DXGI_FORMAT_UNKNOWN;
		uav.Buffer.NumElements = MAX_PARTICLE;

		Renderer::GetDevice()->CreateUnorderedAccessView(m_pParticleBuffer, &uav, &m_pParticleUAV);

		D3D11_SHADER_RESOURCE_VIEW_DESC srv{};
		srv.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		srv.Buffer.NumElements = MAX_PARTICLE;

		Renderer::GetDevice()->CreateShaderResourceView(m_pParticleBuffer, &srv, &m_pParticleSRV);
	}

	{//AliveのlistUAV作成
		D3D11_UNORDERED_ACCESS_VIEW_DESC desc{};
		desc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		desc.Format = DXGI_FORMAT_UNKNOWN;
		desc.Buffer.NumElements = MAX_PARTICLE;
		desc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_APPEND;

		Renderer::GetDevice()->CreateUnorderedAccessView(m_pAliveListBuffer, &desc, &m_pAliveListUAV);
	}

	{//DeadのlistUAV作成
		D3D11_UNORDERED_ACCESS_VIEW_DESC desc{};
		desc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		desc.Format = DXGI_FORMAT_UNKNOWN;
		desc.Buffer.NumElements = MAX_PARTICLE;
		desc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_APPEND;

		Renderer::GetDevice()->CreateUnorderedAccessView(m_pDeadListBuffer, &desc, &m_pDeadListUAV);
	}

	{//SpawnPosSRVの作成
		D3D11_SHADER_RESOURCE_VIEW_DESC srv{};
		srv.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		srv.Format = DXGI_FORMAT_UNKNOWN;
		srv.Buffer.NumElements = PARTICLE_PER_EXPLOSION;

		Renderer::GetDevice()->CreateShaderResourceView(m_pSpawnPositionBuffer, &srv, &m_pSpawnPositionSRV);
	}

	{//AliveListのSRVの作成
		D3D11_SHADER_RESOURCE_VIEW_DESC srv{};
		srv.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		srv.Format = DXGI_FORMAT_UNKNOWN;
		srv.Buffer.NumElements = MAX_PARTICLE;

		Renderer::GetDevice()->CreateShaderResourceView(m_pAliveListBuffer, &srv, &m_pAliveListSRV);
	}

	m_Texture = Texture::Load("asset\\texture\\particle.png");
}

//各種シェーダーの作成
void GPUExplosionParticle::loadshaders()
{
	Renderer::CreateVertexShaderForParticle(&m_pVertexShader, nullptr, "shader\\particleVS.cso");

	Renderer::CreatePixelShader(&m_pPixelShader, "shader\\particlePS.cso");

	Renderer::CreateComputeShader(&m_pDeadListInitCS, "shader\\deadlistinitCS.cso");

	Renderer::CreateComputeShader(&m_pSpawnCS, "shader\\particlespawnCS.cso");

	Renderer::CreateComputeShader(&m_pUpdateCS, "shader\\particleupdateCS.cso");

}

//void GPUExplosionParticle::buildindirectargs()
//{
//	Renderer::GetDeviceContext()->CSSetShader(m_pIndirectArgsCS, nullptr, 0);
//	Renderer::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, &m_pAliveListUAV, nullptr);
//	Renderer::GetDeviceContext()->CSSetUnorderedAccessViews(1, 1, &m_pIndirectArgsUAV, nullptr);
//	Renderer::GetDeviceContext()->Dispatch(1, 1, 1);
//
//	//後処理
//	ID3D11UnorderedAccessView* nullUAV = nullptr;
//	Renderer::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, &nullUAV, nullptr);
//	Renderer::GetDeviceContext()->CSSetShader(nullptr, nullptr, 0);
//}

void GPUExplosionParticle::updateindirectargs()
{
	Renderer::GetDeviceContext()->CopyStructureCount(m_pAliveCountReadBack, 0, m_pAliveListUAV);

	D3D11_MAPPED_SUBRESOURCE map{};
	Renderer::GetDeviceContext()->Map(m_pAliveCountReadBack, 0, D3D11_MAP_READ, 0, &map);

	UINT alivecount = *(UINT*)map.pData;


	Renderer::GetDeviceContext()->Unmap(m_pAliveCountReadBack, 0);

	D3D11_DRAW_INSTANCED_INDIRECT_ARGS args{};
	args.VertexCountPerInstance = 4;
	args.InstanceCount = alivecount;
	args.StartVertexLocation = 0;
	args.StartInstanceLocation = 0;


	Renderer::GetDeviceContext()->UpdateSubresource(m_pIndirectArgsBuffer, 0, nullptr, &args, 0, 0);

}

void GPUExplosionParticle::uploadspawnrequests()
{
	if (m_SpawnRequests.empty()) return;

	//既存のSRVを解放
	if (m_pSpawnPositionSRV)
	{
		m_pSpawnPositionSRV->Release();
		m_pSpawnPositionSRV = nullptr;
	}

	m_CurrentSpawnCount = (int)m_SpawnRequests.size();

	//GPUが読み取るようにStructuredBufferの作成
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = sizeof(XMFLOAT3) * m_CurrentSpawnCount;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.StructureByteStride = sizeof(XMFLOAT3);

	D3D11_SUBRESOURCE_DATA sub{};
	sub.pSysMem = m_SpawnRequests.data();

	ID3D11Buffer* buffer = nullptr;
	Renderer::GetDevice()->CreateBuffer(&desc, &sub, &buffer);

	//SRVの作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srv{};
	srv.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	srv.Buffer.FirstElement = 0;
	srv.Buffer.NumElements = m_CurrentSpawnCount;
	srv.Format = DXGI_FORMAT_UNKNOWN;

	Renderer::GetDevice()->CreateShaderResourceView(buffer, &srv, &m_pSpawnPositionSRV);

	//生成したバッファの解放
	buffer->Release();

	//リクエストの解放
	m_SpawnRequests.clear();
}

void GPUExplosionParticle::updatespawn()
{
	if (m_SpawnRequests.empty()) return;

	m_pSpawnPositionBuffer->Release();
	m_pSpawnPositionSRV->Release();

	//現在のリクエストに応じたスポーンバッファの作
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = UINT(sizeof(XMFLOAT3) * m_SpawnRequests.size());
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.StructureByteStride = sizeof(XMFLOAT3);

	D3D11_SUBRESOURCE_DATA sub{};
	sub.pSysMem = m_SpawnRequests.data();

	Renderer::GetDevice()->CreateBuffer(&desc, &sub, &m_pSpawnPositionBuffer);

	D3D11_SHADER_RESOURCE_VIEW_DESC srv{};
	srv.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	srv.Buffer.FirstElement = 0;
	srv.Buffer.NumElements = m_SpawnRequests.size();
	srv.Format = DXGI_FORMAT_UNKNOWN;

	Renderer::GetDevice()->CreateShaderResourceView(m_pSpawnPositionBuffer, &srv, &m_pSpawnPositionSRV);



	//ここからGPUにこの新規データを送信
	SpawnCB cb{};
	cb.SpawnCount = (UINT)m_SpawnRequests.size();
	cb.ParticleCount = PARTICLE_PER_EXPLOSION;

	Renderer::GetDeviceContext()->UpdateSubresource(m_pSpawnBuffer, 0, nullptr, &cb, 0, 0);
	Renderer::GetDeviceContext()->CSSetConstantBuffers(8, 1, &m_pSpawnBuffer);

	Renderer::GetDeviceContext()->CSSetShader(m_pSpawnCS, nullptr, 0);
	Renderer::GetDeviceContext()->CSSetShaderResources(0, 1, &m_pSpawnPositionSRV);

	ID3D11UnorderedAccessView* uavs[] =
	{
		m_pParticleUAV,
		m_pAliveListUAV,
		m_pDeadListUAV
	};

	// Spawnでは AliveList をリセットしない（-1）
	UINT initCounts[3] = { (UINT)-1, (UINT)-1, (UINT)-1 };

	Renderer::GetDeviceContext()->CSSetUnorderedAccessViews(0, 3, uavs, initCounts);
	UINT total = cb.SpawnCount * cb.ParticleCount;
	Renderer::GetDeviceContext()->Dispatch((total + 255) / 256, 1, 1);

	m_SpawnRequests.clear();
}

void GPUExplosionParticle::updateparticle()
{
	UpdateCB ucb{};
	ucb.Gravity = -0.01f;
	ucb.FadeSpeed = 1.0f;
	ucb.AliveCount = 0; // Append方式では不要

	Renderer::GetDeviceContext()->UpdateSubresource(m_pUpdateBuffer, 0, nullptr, &ucb, 0, 0);


	Renderer::GetDeviceContext()->CSSetShader(m_pUpdateCS, nullptr, 0);
	Renderer::GetDeviceContext()->CSSetConstantBuffers(8, 1, &m_pUpdateBuffer);

	ID3D11UnorderedAccessView* uavs[] =
	{
		m_pParticleUAV,
		m_pAliveListUAV,
		m_pDeadListUAV
	};

	Renderer::GetDeviceContext()->CSSetUnorderedAccessViews(0, 3, uavs, nullptr);
	Renderer::GetDeviceContext()->Dispatch((MAX_PARTICLE + 255) / 256, 1, 1);
}

