//********************************************************************************
//
// score.h[スコア表示]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************
#ifndef _SCORE_H_
#define _SCORE_H_

#include "gameobject.h"

class Score :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_WorldBuffer;

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ID3D11ShaderResourceView* m_Texture;//数字
	ID3D11ShaderResourceView* m_TextureScore;//文字

	int m_movement_x;
	int m_movement_y;

	XMFLOAT3 m_VertexPosition[4] = {};

	int m_Points;

public:
	Score(Vector3 size = { 1.0f , 1.0f , 1.0f }, Vector3 position = { 0.0f , 0.0f , 0.0f }, int movementx = 0, int movementy = 0, Vector3 rotation = { 0.0f , 0.0f , 0.0f });
	~Score();

	void Init(Input*) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetScore(float x, float y, float width, float height, const char* filename);
	void AddPoints(int points) { m_Points += points; }
private:

};

#endif // !_SCORE_H_


