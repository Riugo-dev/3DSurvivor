//	manager_effekseer.h
//	
//	2025.11.13			大山凌太朗

#ifndef MANAGER_EFFEKSEER_H
#define MANAGER_EFFEKSEER_H

#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <unordered_map>
#include <string>

namespace graphics {

	class EffekseerManager {
	private:
		EffekseerManager() = default;

		Effekseer::ManagerRef m_Manager;
		EffekseerRendererDX11::RendererRef m_Renderer;
		std::unordered_map<std::string, Effekseer::EffectRef> m_EffectCache;

		ID3D11Device* m_Device = nullptr;
		ID3D11DeviceContext* m_Context = nullptr;

	public:
		static EffekseerManager* GetInstance();

		bool Init(ID3D11Device* device, ID3D11DeviceContext* context, int maxInstances = 8000);
		void Update();
		void Terminate();

		// 描画処理（SceneのEFFECTレイヤーから呼ぶ）
		void DrawAll();

		// エフェクトロード（キャッシュ利用）
		Effekseer::EffectRef LoadEffect(const std::string& fileName);

		// エフェクト再生・制御
		Effekseer::Handle PlayEffect(const std::string& name, const Effekseer::Vector3D& pos);
		void StopEffect(Effekseer::Handle handle);
		void StopAllEffects();

		// 各種設定
		void SetSpeed(Effekseer::Handle handle, float speed);
		void SetColor(Effekseer::Handle handle, const Effekseer::Color& color);
		void SetRotation(Effekseer::Handle handle, const Effekseer::Vector3D& rot);
		void SetScale(Effekseer::Handle handle, const Effekseer::Vector3D& scale);

		// カメラ設定
		void SetCamera(const Effekseer::Matrix44& view, const Effekseer::Matrix44& proj);

		Effekseer::ManagerRef GetManager() const { return m_Manager; }
		EffekseerRendererDX11::RendererRef GetRenderer() const { return m_Renderer; }
	};

}

#endif // MANAGER_EFFEKSEER_H
