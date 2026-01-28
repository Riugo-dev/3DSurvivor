//	
//	utils_color.h
//
//	2025.09.19			大山凌太朗

#ifndef UTILS_COLOR_H
#define UTILS_COLOR_H

#include "utils_math.h"
#include <algorithm>
#include "vector3.h"


namespace math {

	// RGB カラー
	class Color3 {
	public:
		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;

		Color3() : r(0), g(0), b(0) {}
		Color3(float rr, float gg, float bb) : r(rr), g(gg), b(bb) {}
		Color3(Vector3 color):r(color.x),g(color.y),b(color.z){}

		// ---- 基本演算 ----
		Color3 operator+(const Color3& o) const { return { r + o.r, g + o.g, b + o.b }; }
		Color3 operator-(const Color3& o) const { return { r - o.r, g - o.g, b - o.b }; }
		Color3 operator*(float s) const { return { r * s, g * s, b * s }; }
		Color3 operator/(float s) const { return { r / s, g / s, b / s }; }

		Color3& operator+=(const Color3& o) { r += o.r; g += o.g; b += o.b; return *this; }
		Color3& operator-=(const Color3& o) { r -= o.r; g -= o.g; b -= o.b; return *this; }
		Color3& operator*=(float s) { r *= s; g *= s; b *= s; return *this; }
		Color3& operator/=(float s) { r /= s; g /= s; b /= s; return *this; }

		// ---- ユーティリティ ----
		/*void Clamp() {
			r = std::clamp(r, 0.0f, 1.0f);
			g = std::clamp(g, 0.0f, 1.0f);
			b = std::clamp(b, 0.0f, 1.0f);
		}*/

		//グレースケール
		float Luminance() const {
			return 0.299f * r + 0.587f * g + 0.114f * b;
		}

		//ラープ
		static Color3 Lerp(const Color3& a, const Color3& b, float t) {
			return { a.r + (b.r - a.r) * t,
					 a.g + (b.g - a.g) * t,
					 a.b + (b.b - a.b) * t };
		}

		// ---- 定数色 ----
		static const Color3 Black() { return { 0.0f, 0.0f, 0.0f }; }
		static const Color3 White() { return { 1.0f, 1.0f, 1.0f }; }
		static const Color3 Red() { return { 1.0f, 0.0f, 0.0f }; }
		static const Color3 Green() { return { 0.0f, 1.0f, 0.0f }; }
		static const Color3 Blue() { return { 0.0f, 0.0f, 1.0f }; }
		static const Color3 Yellow() { return { 1.0f, 1.0f, 0.0f }; }
		static const Color3 Cyan() { return { 0.0f, 1.0f, 1.0f }; }
		static const Color3 Magenta() { return { 1.0f, 0.0f, 1.0f }; }
		static const Color3 Gray() { return { 0.5f, 0.5f, 0.5f }; }
		static const Color3 LightGray() { return { 0.75f, 0.75f, 0.75f }; }
		static const Color3 DarkGray() { return { 0.25f, 0.25f, 0.25f }; }
		static const Color3 Orange() { return { 1.0f, 0.5f, 0.0f }; }
		static const Color3 Pink() { return { 1.0f, 0.75f, 0.8f }; }
		static const Color3 Purple() { return { 0.5f, 0.0f, 0.5f }; }
		static const Color3 Brown() { return { 0.6f, 0.3f, 0.0f }; }
	};

	//RGBAカラー
	class Color4 {
	public:
		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;
		float a = 1.0f;

		Color4() : r(0), g(0), b(0), a(1) {}
		Color4(float rr, float gg, float bb, float aa = 1.0f) : r(rr), g(gg), b(bb), a(aa) {}
		Color4(const Color3& c, float aa = 1.0f) : r(c.r), g(c.g), b(c.b), a(aa) {}
		Color4(Vector3 color,float aa=1.0f) :r(color.x), g(color.y), b(color.z),a (aa){}

		// ---- 基本演算 ----
		Color4 operator+(const Color4& o) const { return { r + o.r, g + o.g, b + o.b, a + o.a }; }
		Color4 operator-(const Color4& o) const { return { r - o.r, g - o.g, b - o.b, a - o.a }; }
		Color4 operator*(float s) const { return { r * s, g * s, b * s, a * s }; }
		Color4 operator/(float s) const { return { r / s, g / s, b / s, a / s }; }

		Color4& operator+=(const Color4& o) { r += o.r; g += o.g; b += o.b; a += o.a; return *this; }
		Color4& operator-=(const Color4& o) { r -= o.r; g -= o.g; b -= o.b; a -= o.a; return *this; }
		Color4& operator*=(float s) { r *= s; g *= s; b *= s; a *= s; return *this; }
		Color4& operator/=(float s) { r /= s; g /= s; b /= s; a /= s; return *this; }

		// ---- ユーティリティ ----
		/*void Clamp() {
			r = std::clamp(r, 0.0f, 1.0f);
			g = std::clamp(g, 0.0f, 1.0f);
			b = std::clamp(b, 0.0f, 1.0f);
			a = std::clamp(a, 0.0f, 1.0f);
		}*/

		float Luminance() const {
			return 0.299f * r + 0.587f * g + 0.114f * b;
		}

		static Color4 Lerp(const Color4& a, const Color4& b, float t) {
			return { a.r + (b.r - a.r) * t,
					 a.g + (b.g - a.g) * t,
					 a.b + (b.b - a.b) * t,
					 a.a + (b.a - a.a) * t };
		}

		// ---- 定数色 ----
		static const Color4 Transparent() { return { 0.0f, 0.0f, 0.0f, 0.0f }; }
		static const Color4 Black() { return { 0.0f, 0.0f, 0.0f, 1.0f }; }
		static const Color4 White() { return { 1.0f, 1.0f, 1.0f, 1.0f }; }
		static const Color4 Red() { return { 1.0f, 0.0f, 0.0f, 1.0f }; }
		static const Color4 Green() { return { 0.0f, 1.0f, 0.0f, 1.0f }; }
		static const Color4 Blue() { return { 0.0f, 0.0f, 1.0f, 1.0f }; }
		static const Color4 Yellow() { return { 1.0f, 1.0f, 0.0f, 1.0f }; }
		static const Color4 Cyan() { return { 0.0f, 1.0f, 1.0f, 1.0f }; }
		static const Color4 Magenta() { return { 1.0f, 0.0f, 1.0f, 1.0f }; }
		static const Color4 Gray() { return { 0.5f, 0.5f, 0.5f, 1.0f }; }
		static const Color4 LightGray() { return { 0.75f, 0.75f, 0.75f, 1.0f }; }
		static const Color4 DarkGray() { return { 0.25f, 0.25f, 0.25f, 1.0f }; }
		static const Color4 Orange() { return { 1.0f, 0.5f, 0.0f, 1.0f }; }
		static const Color4 Pink() { return { 1.0f, 0.75f, 0.8f, 1.0f }; }
		static const Color4 Purple() { return { 0.5f, 0.0f, 0.5f, 1.0f }; }
		static const Color4 Brown() { return { 0.6f, 0.3f, 0.0f, 1.0f }; }
	};
	

}

#endif // UTILS_COLOR_H
