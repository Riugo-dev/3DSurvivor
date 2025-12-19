//********************************************************************************
//
// meshfield.cpp[地形]
//
//															Author :Riugo Honda
//															Date   :2025/09/10
//********************************************************************************
#include "main.h"
#include "renderer.h"
#include "meshField.h"
//#include "shader.h"

//********************************************************************************
//グローバル変数
//********************************************************************************
float g_FieldHeight[21][21] =
{
	{0.0f , 1.0f , -2.0f , -2.0f , -2.0f , -2.0f ,  0.0f , 0.0f , 1.0f , 2.0f , 3.0f , 4.0f , 5.0f, 6.0f , 7.0f , 8.0f , 9.0f , 10.0f ,11.0f , 12.0f , 13.0f},
	{0.0f , 2.0f , -2.0f , -2.0f , -2.0f , -2.0f ,  0.0f , 0.0f , 0.0f , 1.0f , 2.0f , 3.0f , 4.0f, 5.0f , 6.0f , 7.0f , 8.0f , 9.0f ,10.0f , 11.0f , 12.0f},
	{1.0f , 1.0f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 1.0f , 2.0f , 3.0f, 4.0f , 5.0f , 6.0f , 7.0f , 8.0f ,9.0f , 10.0f , 11.0f},
	{1.0f , 1.0f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 1.0f , 2.0f, 3.0f , 4.0f , 5.0f , 6.0f , 7.0f ,8.0f , 9.0f , 10.0f},
	{1.0f , 1.0f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 1.0f, 2.0f , 3.0f , 4.0f , 5.0f , 6.0f ,7.0f , 8.0f , 9.0f},
	{1.0f , 1.0f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f, 1.0f , 2.0f , 3.0f , 4.0f , 5.0f ,6.0f , 7.0f , 8.0f},
	{1.0f , 1.0f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f, 0.0f , 1.0f , 2.0f , 3.0f , 4.0f ,5.0f , 6.0f , 7.0f},
	{1.0f , 1.0f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f, 0.0f , 0.0f , 1.0f , 2.0f , 3.0f ,4.0f , 5.0f , 6.0f},
	{1.0f , 1.0f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f, 0.0f , 0.0f , 0.0f , 1.0f , 2.0f ,3.0f , 4.0f , 5.0f},
	{1.0f , 1.0f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f, 0.0f , 0.0f , 0.0f , 0.0f , 1.0f ,2.0f , 3.0f , 4.0f},
	{1.0f , 1.0f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f, 0.0f , 0.0f , 0.0f , 0.0f , 0.0f ,1.0f , 2.0f , 3.0f},
	{1.0f , 1.0f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f, 0.0f , 0.0f , 0.0f , 0.0f , 0.0f ,0.0f , 1.0f , 2.0f},
	{1.0f , 1.0f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f, 0.0f , 0.0f , 0.0f , 0.0f , 0.0f ,0.0f , 0.0f , 1.0f},
	{1.0f , 1.0f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f, 0.0f , 0.0f , 0.0f , 0.0f , 0.0f ,0.0f , 0.0f , 0.0f},
	{1.0f , 1.0f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f, 0.0f , 0.0f , 0.0f , 0.0f , 0.0f ,0.0f , 0.0f , 0.0f},
	{1.0f , 1.0f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f, 0.0f , 0.0f , 0.0f , 0.0f , 0.0f ,0.0f , 0.0f , 0.0f},
	{1.0f , 1.5f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f, 0.0f , 0.0f , 0.0f , 0.0f , 0.0f ,0.0f , 0.0f , 0.0f},
	{1.0f , 1.5f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f, 0.0f , 0.0f , 0.0f , 0.0f , 0.0f ,0.0f , 0.0f , 0.0f},
	{1.0f , 1.5f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f, 0.0f , 0.0f , 0.0f , 0.0f , 0.0f ,0.0f , 0.0f , 0.0f},
	{1.0f , 1.5f , -2.0f , -2.0f , -2.0f , -2.0f , -2.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f, 0.0f , 0.0f , 0.0f , 0.0f , 0.0f ,0.0f , 0.0f , 0.0f},
	{0.0f , 1.0f , 3.0f , 2.0f , 1.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f, 1.0f , 2.0f , 0.0f , 0.0f , 1.0f ,1.0f , 0.0f , 0.0f},
};


//********************************************************************************
//関数
//********************************************************************************
MeshField::MeshField()
{
	//AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");


	// 頂点バッファ生成
	{
		for (int x = 0; x <= 20; x++)
		{
			for (int z = 0; z <= 20; z++)
			{
				//float y = 0.0f;
				float y = g_FieldHeight[x][z];
				m_Vertex[x][z].Position = XMFLOAT3((x - 10) * 5.0f, y, (z - 10) * -5.0f);
				m_Vertex[x][z].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);//法線ベクトル
				m_Vertex[x][z].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
				m_Vertex[x][z].TexCoord = XMFLOAT2(x * 0.5f, z * 0.5f);
			}
		}

		for (int x = 1; x < 20; x++)
		{
			for (int z = 1; z < 20; z++)
			{
				Vector3 vx, vz, vn;
				vx.x = m_Vertex[x + 1][z].Position.x - m_Vertex[x - 1][z].Position.x;
				vx.y = m_Vertex[x + 1][z].Position.y - m_Vertex[x - 1][z].Position.y;
				vx.z = m_Vertex[x + 1][z].Position.z - m_Vertex[x - 1][z].Position.z;

				vz.x = m_Vertex[x][z -1].Position.x - m_Vertex[x][z + 1].Position.x;
				vz.y = m_Vertex[x][z -1].Position.y - m_Vertex[x][z + 1].Position.y;
				vz.z = m_Vertex[x][z -1].Position.z - m_Vertex[x][z + 1].Position.z;

				vn = Vector3::cross(vz, vx);//外積
				vn.normalize();//正規化（長さを１にする）

				m_Vertex[x][z].Normal.x = vn.x;
				m_Vertex[x][z].Normal.y = vn.y;
				m_Vertex[x][z].Normal.z = vn.z;
				

			}
		}


		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * 21 * 21;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_Vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}




	// インデックスバッファ生成
	{
		unsigned int index[(22 * 2) * 20 - 2];

		int i = 0;
		for (int x = 0; x < 20; x++)
		{
			for (int z = 0; z < 21; z++)
			{
				index[i] = x * 21 + z;
				i++;

				index[i] = (x + 1) * 21 + z;
				i++;
			}

			if (x == 19)
				break;

			index[i] = (x + 1) * 21 + 20;
			i++;

			index[i] = (x + 1) * 21;
			i++;
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * ((22 * 2) * 20 - 2);
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

	/*Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");*/
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\vertexDirectionalLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\vertexDirectionalLightingPS.cso");

}


void MeshField::Uninit()
{

	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->Release();


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}


void MeshField::Update()
{

}


void MeshField::Draw()
{

	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// 頂点バッファ設定
	UINT stride = sizeof( VERTEX_3D );
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers( 0, 1, &m_VertexBuffer, &stride, &offset );

	//平行移動行列の作成（表示座標を決める）
	XMMATRIX	TranslationMatrix = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	//回転行列（Z回転）行列の作成
	XMMATRIX	RotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);

	//スケーリング行列作成（倍率1.0が等倍、0倍はダメ！）
	XMMATRIX	ScalingMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f);

	//ワールド行列の作成（ポリゴンの表示の仕方を指定する最終的な行列
	XMMATRIX	WorldMatrix = ScalingMatrix * RotationMatrix * TranslationMatrix;

	Renderer::SetWorldMatrix(WorldMatrix);

	// インデックスバッファ設定
	Renderer::GetDeviceContext()->IASetIndexBuffer( 
		m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0 );

	// マテリアル設定
	MATERIAL material;
	ZeroMemory( &material, sizeof(material) );
	material.Diffuse = XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f );
	material.TextureEnable = true;
	Renderer::SetMaterial( material );

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	// ポリゴン描画
	Renderer::GetDeviceContext()->DrawIndexed(
		(22 * 2) * 20 - 2, 0, 0);

}

float MeshField::GetHeight(Vector3 Position)
{
	int x, z;

	//ブロック番号算出
	x = Position.x / 5.0f + 10.0f;
	z = Position.z / -5.0f + 10.0f;

	XMFLOAT3 pos0, pos1, pos2, pos3;

	pos0 = m_Vertex[x][z].Position;
	pos1 = m_Vertex[x + 1][z].Position;
	pos2 = m_Vertex[x][z + 1].Position;
	pos3 = m_Vertex[x + 1][z + 1].Position;

	Vector3 v12, v1p;
	v12.x = pos2.x - pos1.x;
	v12.y = pos2.y - pos1.y;
	v12.z = pos2.z - pos1.z;

	v1p.x = Position.x - pos1.x;
	v1p.y = Position.y - pos1.y;
	v1p.z = Position.z - pos1.z;

	//外積
	float cy = v12.z * v1p.x - v12.x * v1p.z;

	float py;
	Vector3 n;
	if (cy > 0.0f)
	{
		//左上ポリゴン
		Vector3 v10;
		v10.x = pos0.x - pos1.x;
		v10.y = pos0.y - pos1.y;
		v10.z = pos0.z - pos1.z;
		
		//外積
		n = Vector3::cross(v10, v12);
	}
	else
	{
		//右下ポリゴン
		Vector3 v13;
		v13.x = pos3.x - pos1.x;
		v13.y = pos3.y - pos1.y;
		v13.z = pos3.z - pos1.z;

		//外積
		n = Vector3::cross(v12, v13);
	}

	//高さ取得
	py = -((Position.x - pos1.x) * n.x + (Position.z - pos1.z) * n.z) / n.y + pos1.y;

	return py;
}


