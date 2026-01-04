//********************************************************************************
//
// pause.h[[ポーズ画面表示]
//
//															Author :Riugo Honda
//															Date   :2025/09/12
//********************************************************************************
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "gameobject.h"

class Pause :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_VertexBufferPause;

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	ID3D11ShaderResourceView* m_TexturePause;//文字
	ID3D11ShaderResourceView* m_TextureBG;//背景画

	XMFLOAT3 m_VertexPosition[4] = {};

	int m_HP;
public:
	Pause();
	~Pause() override;

	void Init() override {};
	void Uninit() override {};
	void Update() override;
	void Draw() override;

};

#endif // !_PAUSE_H_

