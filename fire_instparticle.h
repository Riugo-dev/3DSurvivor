//********************************************************************************
//
// fire_instparticle.h[炎パーティクルのインスタンタンシング]
//
//															Author :Riugo Honda
//															Date   :2026/02/16
//********************************************************************************

#ifndef _FIRE_INSTPARTICLE_H_
#define _FIRE_INSTPARTICLE_H_

#include "renderer.h"

class FireInstParticle
{
private:
	static FireInstParticle* m_pMyself;

	struct Particle
	{
		Vector3 Position;
		Vector3 Scale;
		Vector3 Rotation;
		bool Enable = false;
		int LifeCount = 0;
		Vector3 Velocity;
	};

	struct ParticleInfo
	{
		ID3D11Buffer* InstanceBuffer;
		bool IsUsed = false;
		Vector3 SpawnPoint;
		float Radius;
		ID3D11Buffer* RingVertexBuffer = nullptr;
		std::vector<InstanceData> Sendingdata;
		std::vector<Particle> ParticleData;
	};

	ID3D11ShaderResourceView* m_Texture = nullptr;
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3D11InputLayout* m_pInputLayout = nullptr;
	ID3D11Buffer* m_pCameraBuffer = nullptr;

	ID3D11ShaderResourceView* m_RingTexture = nullptr;
	ID3D11Buffer* m_pRingIndexBuffer = nullptr;
	ID3D11VertexShader* m_pRingVertexShader = nullptr;
	ID3D11PixelShader* m_pRingPixelShader = nullptr;
	ID3D11InputLayout* m_pRingInputLayout = nullptr;

	std::vector<ParticleInfo> m_FireParticles;

	int m_FrameCount;
	int m_SpawnPointLife = 0;
	bool m_ResetSpawnPoint = false;
public:
	static FireInstParticle* GetInstance();

	void DestroyInstance();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetParticleSpawnPoint(int ,Vector3, float);

private:
	FireInstParticle() {}
	~FireInstParticle() {}

	void createbuffers();
	void createshaders();
	void spawnparticles();
	void updateparticles();
	void updateinstancebuffer();
	void destroyparticles();
	void destroyspawnpoints();

};

#endif // !_FIRE_INSTPARTICLE_H_

