//********************************************************************************
//
// texture.h[テクスチャ]
//
//															Author :Riugo Honda
//															Date   :2025/06/11
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/14
//********************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "texture.h"
//********************************************************************************
//関数宣言
//********************************************************************************
std::unordered_map<std::string, ID3D11ShaderResourceView*>Texture::m_TexturePool;//配列のように見える仕組みがunorderd_map番号ではなく名前で管理するときに使う
//********************************************************************************
//関数
//********************************************************************************
ID3D11ShaderResourceView* Texture::Load(const char* FileName)
{
	if (m_TexturePool.count(FileName) > 0)
	{
		return  m_TexturePool[FileName];
	}

	wchar_t wFileName[512];
	mbstowcs(wFileName, FileName, strlen(FileName) + 1);

	// テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;
	ID3D11ShaderResourceView* texture;
	LoadFromWICFile(wFileName, WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &texture);
	assert(texture);

	m_TexturePool[FileName] = texture;


	return texture;
	
	
}

void Texture::ReleaseAll()
{
	for (auto& itr : m_TexturePool)
	{
		if (itr.second)
		{
			itr.second->Release();
			itr.second = nullptr;
		}
	}

	m_TexturePool.clear();
}
