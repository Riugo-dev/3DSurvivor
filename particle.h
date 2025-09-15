//********************************************************************************
//
// particle.h[パーティクル]
//
//															Author :Riugo Honda
//															Date   :2025/07/01
// -------------------------------------------------------------------------------
//															Last Edited:2025/07/01
//********************************************************************************
#pragma once

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#define PARTICLE_MAX (10000)
#define PARTICLE_LIFESPAN_MAX (200)

class Particle :public GameObject
{
protected:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_WorldBuffer;

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ID3D11ShaderResourceView* m_Texture;

	Vector3 m_RGB;//色

	XMFLOAT3 m_VertexPosition[24] = {};

	int m_Frame_count;
	int m_Frame_max;

	struct PARTICLE
	{
		bool Enable;//生きてるかチェック
		int LifeFrame;//生存フレーム数
		Vector3 Position;//現在位置
		Vector3 Velocity;//速度
	};

	PARTICLE m_Particle[PARTICLE_MAX];

public:
	Particle(Vector3 size = { 0.7f , 0.7f , 0.7f }, Vector3 position = { 0.0f , 0.0f , 0.0f }, int movementx = 0, int movementy = 0, Vector3 rotation = { 0.0f , 0.0f , 0.0f });
	~Particle();

	virtual void Init(Input*) override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
private:

};

#endif // !_PARTICLE_H_

