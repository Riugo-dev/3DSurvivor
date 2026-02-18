//********************************************************************************
//
// stage_field.h[ステージの基底クラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/13
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "camera.h"


#include "stage_field.h"

//********************************************************************************
//マクロ定義
//********************************************************************************

//********************************************************************************
//関数
//********************************************************************************
StageField::StageField()
{


	//1chunk用の頂点データ
	m_Vertex[0].Position = XMFLOAT3(-m_FloorSize / 2, 0.0f, -m_FloorSize / 2);
	m_Vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_Vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	m_Vertex[1].Position = XMFLOAT3(m_FloorSize / 2, 0.0f, -m_FloorSize / 2);
	m_Vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_Vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertex[1].TexCoord = XMFLOAT2(m_TileRepeat, 0.0f);

	m_Vertex[2].Position = XMFLOAT3(-m_FloorSize / 2, 0.0f, m_FloorSize / 2);
	m_Vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_Vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertex[2].TexCoord = XMFLOAT2(0.0f, m_TileRepeat);

	m_Vertex[3].Position = XMFLOAT3(m_FloorSize / 2, 0.0f, m_FloorSize / 2);
	m_Vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_Vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertex[3].TexCoord = XMFLOAT2(m_TileRepeat, m_TileRepeat);

	{
		//頂点バッファ作成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(m_Vertex);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_Vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}

	//インデックス作成
	WORD index[6] = { 0 , 2 , 1 , 1, 2, 3 };


	{
		//インデックスバッファ作成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(index);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}

	// テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\texture\\floor.png", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);

	//Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\vertexDirectionalLightingVS.cso");

	//Renderer::CreatePixelShader(&m_PixelShader, "shader\\vertexDirectionalLightingPS.cso");
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\toon1VS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\toon1PS.cso");

}

StageField::~StageField()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->Release();


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}





void StageField::Update()
{

}


void StageField::Draw()
{
	//床をカメラに追従させる
	Camera* p_camera = Manager::GetScene()->GetGameObject<Camera>();
	Vector3 campos = p_camera->GetPosition();

	XMMATRIX view = p_camera->GetViewMatrix();
	XMMATRIX proj = p_camera->GetProjectionMatrix();
	Vector3 foward = p_camera->GetFoward();

	//カメラ周囲のチャンクのワールド行列を作成して描画
	int half = m_ChunkCount / 2;
	for (int i = -half; i <= half; i++)
	{
		for (int j = -half; j <= half; j++)
		{
		
			//チャンクの中心座標
			float offsetX = floorf(campos.x / m_FloorSize) * m_FloorSize + i * m_FloorSize;
			float offsetZ = floorf(campos.z / m_FloorSize) * m_FloorSize + j * m_FloorSize;
			Vector3 chunkCenter{ offsetX , 0.0f , offsetZ };
			
			//カメラ→チャンク方向ベクトル
			Vector3 toChunk = chunkCenter - campos;

			//前方だけ描画(dot > 0 なら前方（dot < 0は後方）//今回は省いた
			float dot = Vector3::dot(toChunk.normalized(), foward);

			//ワールド行列
			XMMATRIX world = XMMatrixTranslation(offsetX, 0.0f, offsetZ);
			Renderer::SetWorldMatrix(world);

			//ビュープロジェクション
			Renderer::SetViewMatrix(view);
			Renderer::SetProjectionMatrix(proj);

			// 頂点バッファ＆インデックス
			UINT stride = sizeof(VERTEX_3D);
			UINT offset = 0;
			Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
			Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

			// マテリアル設定
			MATERIAL material;
			ZeroMemory(&material, sizeof(material));
			material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			material.TextureEnable = true;
			Renderer::SetMaterial(material);

			// シェーダー＆テクスチャ
			Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
			Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, nullptr, 0);
			Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, nullptr, 0);
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

			// 描画
			Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			Renderer::GetDeviceContext()->DrawIndexed(m_IndexCount, 0, 0);
		}
	}
}



