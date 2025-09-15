//********************************************************************************
//
// stage_field.h[ステージの基底クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/13
//********************************************************************************
#ifndef _STAGE_FIELD_H_
#define _STAGE_FIELD_H_

#include "gameObject.h"

class StageField : public GameObject
{

private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11Buffer* m_IndexBuffer{};

	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout; //頂点レイアウトオブジェクト

	//無限床作成用
	const float m_FloorSize = 200.0f;//チャンクサイズ
	const float m_TileRepeat =  20.0f;//１チャンク内でのテクスチャの繰り返し
	const int m_ChunkCount = 3;	//周囲に描画するチャンク数
	VERTEX_3D	m_Vertex[4];
	const int m_IndexCount = 6;
public:
	StageField();

	void Init(Input*) override {};
	void Uninit() override;
	void Update() override;
	void Draw() override;
};

#endif // !_STAGE_FIELD_H_


