//********************************************************************************
//
// texture.h[テクスチャ]
//
//															Author :Riugo Honda
//															Date   :2025/06/11
// -------------------------------------------------------------------------------
//															Last Edited:2025/06/14
//********************************************************************************
#pragma once

#include <unordered_map>
#include <string>


class Texture
{
private:
	//メンバ変数でstaticにした場合はcpp側にもちゃんと宣言しないと作られない
	static std::unordered_map<std::string, ID3D11ShaderResourceView*>m_TexturePool;

	
public:
	static ID3D11ShaderResourceView* Load(const char* FileName);

	static void ReleaseAll();
};
