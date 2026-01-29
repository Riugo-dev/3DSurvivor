//********************************************************************************
//
// explosion_gpuparticle.h[爆発GPUパーティクルクラス]
//
//															Author :Riugo Honda
//															Date   :2026/01/29
//********************************************************************************
#ifndef _EXPLOSION_GPUPARTICLE_H_
#define _EXPLOSION_GPUPARTICLE_H_

class GPUExplosionParticle
{
public:
	struct TimeConstantBuffer
	{
		float DeltaTime;
		float padding[3];
	};

	struct ExplosionConstantBuffer
	{
		XMFLOAT3 Position;
		float Life;
		float speed;
		int BaseIndex;
		float padding[2];
	};

private:
	ID3D11Buffer* m_pParticleBuffer = nullptr;
	ID3D11UnorderedAccessView* m_pUnorderdAccessView = nullptr;
	ID3D11ShaderResourceView* m_pShaderResourceView = nullptr;

	ID3D11ComputeShader* m_pInitComputeShader = nullptr;
	ID3D11ComputeShader* m_pUpdateComputeShader = nullptr;

	ID3D11Buffer* m_pTimeConstantBuffer = nullptr;
	ID3D11Buffer* m_pExplosionConstantBuffer = nullptr;

	int m_NextExlposionIndex = 0;

public:
	static GPUExplosionParticle* GetInstance();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SpawnExplosion(Vector3);

private:
	GPUExplosionParticle() = default;

	void createparticlebuffer();
	void createviews();
	void createconstantbuffers();
	void loadshaders();

	void updatetime();
	void updatecs();
	void initcs(int);
};

#endif // !_EXPLOSION_GPUPARTICLE_H_
