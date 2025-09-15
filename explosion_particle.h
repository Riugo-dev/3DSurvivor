//********************************************************************************
//
// particle.h[パーティクル]
//
//															Author :Riugo Honda
//															Date   :2025/07/08
// -------------------------------------------------------------------------------
//															Last Edited:2025/07/08
//********************************************************************************
#pragma once

#ifndef _EXPLOSION_PARTICLE_H_
#define _EXPLOSION_PARTICLE_H_

#include "particle.h"

#define EXPLOSION_PARTICLE_MAX (1000)
#define EXPLOSION_PARTICLE_LIFESPAN_MAX (200)

class ExplosionParticle :public Particle
{
public:
	ExplosionParticle(Vector3 size = { 0.3f , 0.3f , 0.3f }, Vector3 position = { 0.0f , 0.0f , 0.0f }, int movementx = 0, int movementy = 0, Vector3 rotation = { 0.0f , 0.0f , 0.0f });
	~ExplosionParticle();

	virtual void Init(Input*) override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
private:

};

#endif // !_EXPLOSION_PARTICLE_H_



