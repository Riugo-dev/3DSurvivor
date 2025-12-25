//********************************************************************************
//
// fire_particle.h[パーティクル]
//
//															Author :Riugo Honda
//															Date   :2025/10/22
//********************************************************************************
#pragma once

#ifndef _FIRE_PARTICLE_H_
#define _FIRE_PARTICLE_H_

#include "particle.h"

#define FIRE_PARTICLE_MAX (1000)
#define FIRE_PARTICLE_LIFESPAN_MAX (200)

class FireParticle :public Particle
{
private:
	int m_SpawnerLife;
	Vector3 m_ParticleSize[FIRE_PARTICLE_MAX];
	Vector3 m_SpawnerCenterPoint;
	float m_Radius;
	ID3D11ShaderResourceView* m_FloorTexture;
	ID3D11Buffer* m_FloorVertexBuffer;
	ID3D11Buffer* m_IndexBuffer;

	Vector3 m_FloorTopLeft;
	//VERTEX_3D	m_Vertex[4] = {};
public:
	FireParticle(Vector3 size = { 0.3f , 0.3f , 0.3f }, Vector3 position = { 0.0f , 0.0f , 0.0f }, int movementx = 0, int movementy = 0, Vector3 rotation = { 0.0f , 0.0f , 0.0f });
	~FireParticle() override;

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	void SetParticle(int , Vector3 , float);

private:

};

#endif // !_EXPLOSION_PARTICLE_H_




