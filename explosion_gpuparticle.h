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
private:
	static GPUExplosionParticle* m_pMyself;

	//バッファ関係
	ID3D11Buffer* m_pParticleBuffer = nullptr;
	ID3D11Buffer* m_pAliveListBuffer = nullptr;
	ID3D11Buffer* m_pDeadListBuffer = nullptr;
	ID3D11Buffer* m_pSpawnPositionBuffer = nullptr;
	ID3D11Buffer* m_pSpawnBuffer = nullptr;
	ID3D11Buffer* m_pUpdateBuffer = nullptr;
	ID3D11Buffer* m_pCameraBuffer = nullptr;
	ID3D11Buffer* m_pIndirectArgsBuffer = nullptr;
	ID3D11Buffer* m_pAliveCountReadBack = nullptr;

	//UAV関係
	ID3D11UnorderedAccessView* m_pParticleUAV = nullptr;
	ID3D11UnorderedAccessView* m_pAliveListUAV;
	ID3D11UnorderedAccessView* m_pDeadListUAV = nullptr;

	//SRV関係
	ID3D11ShaderResourceView* m_pParticleSRV = nullptr;
	ID3D11ShaderResourceView* m_pSpawnPositionSRV = nullptr;
	ID3D11ShaderResourceView* m_pAliveListSRV = nullptr;
	ID3D11ShaderResourceView* m_Texture;

	//シェーダー関係
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3D11ComputeShader* m_pDeadListInitCS = nullptr;
	ID3D11ComputeShader* m_pSpawnCS = nullptr;
	ID3D11ComputeShader* m_pUpdateCS = nullptr;

	std::vector<XMFLOAT3> m_SpawnRequests;

	static constexpr UINT MAX_PARTICLE = 65536;
	static constexpr UINT PARTICLE_PER_EXPLOSION = 1000;
	int m_CurrentSpawnCount = 0;
	int m_CurrentParticleIndex = 0;
	int m_AlivePingPong = 0;
public:
	static GPUExplosionParticle* GetInstance();

	void DestroyInstance();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SpawnExplosion(Vector3);

private:
	GPUExplosionParticle() {}
	~GPUExplosionParticle() {}

	void initializedeadlist();
	/*UINT getalivecount(ID3D11UnorderedAccessView*);*/
	void createbuffers();
	void createviews();
	void loadshaders();
	//void buildindirectargs();
	void updateindirectargs();
	void uploadspawnrequests();
	void updatespawn();
	void updateparticle();
};

#endif // !_EXPLOSION_GPUPARTICLE_H_
