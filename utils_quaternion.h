//	utils_quaternion.h
//
//	2025.09.18			大山凌太朗
//
#ifndef UTILS_QUATERNION_H
#define UTILS_QUATERNION_H

#include "main.h"
#include "utils_math.h"
#include "vector3.h"

namespace math {

	class Quaternion {
	public:
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

		//--------------------------------------------------
		// コンストラクタ
		//--------------------------------------------------
		
		//xyzw指定での生成なので基本使わない
		//下記の作成系static関数を用いての作成を推奨
		
		// 単位クォータニオン（回転なし）を生成
		Quaternion() : x(0), y(0), z(0), w(1) {}

		// 値を直接指定して生成
		Quaternion(float _x, float _y, float _z, float _w)
			: x(_x), y(_y), z(_z), w(_w) {									
		}

		// Float4 から生成
		Quaternion(const Float4& f) : x(f.x), y(f.y), z(f.z), w(f.w) {}

		virtual ~Quaternion(){}

		//--------------------------------------------------
		// 単位クォータニオン
		//--------------------------------------------------
		static Quaternion Identity() { return Quaternion(0, 0, 0, 1); }		// 回転なしのクォータニオンを返す

		//--------------------------------------------------
		// 自信を変換
		//--------------------------------------------------

		//　XMVECTOR に変換
		XMVECTOR ToXMVECTOR() const {
			XMFLOAT4 f(x, y, z, w);
			return XMLoadFloat4(&f);
		}

		// XMFLOAT4 へ変換
		XMFLOAT4 ToXMFLOAT4() const {
			return XMFLOAT4(x, y, z, w);
		}

		// Float4 へ変換
		Float4 ToFloat4() const {
			return Float4(x, y, z, w);
		}

		//--------------------------------------------------
		// 作成系
		//--------------------------------------------------

		// XMVECTOR から Quaternion を生成
		static Quaternion FromXMVECTOR(FXMVECTOR q) {
			XMFLOAT4 f;
			XMStoreFloat4(&f, q);
			return Quaternion(f.x, f.y, f.z, f.w);
		}

		// XMFLOAT4 から Quaternion を生成
		static Quaternion FromXMFLOAT4(XMFLOAT4 f) {
			return Quaternion(f.x, f.y, f.z, f.w);
		}


		// オイラー角(ラジアン)から生成
		static Quaternion FromEulerRad(const Vector3& euler) {
			XMVECTOR q = XMQuaternionRotationRollPitchYaw(euler.x, euler.y, euler.z);
			return FromXMVECTOR(q);
		}

		// オイラー角(度数法)から生成
		static Quaternion FromEulerDeg(const Vector3& eulerDeg) {
			Vector3 rad(
				XMConvertToRadians(eulerDeg.x),
				XMConvertToRadians(eulerDeg.y),
				XMConvertToRadians(eulerDeg.z));
			return FromEulerRad(rad);
		}

		// 任意軸と角度(ラジアン)から生成
		static Quaternion FromAxisAngle(const Vector3& axis, float angleRad) {
			XMVECTOR q = XMQuaternionRotationAxis(XMLoadFloat3((XMFLOAT3*)&axis), angleRad);
			return FromXMVECTOR(q);
		}

		// 回転行列から生成
		static Quaternion FromMatrix(const DirectX::XMMATRIX& m) {
			XMVECTOR q = XMQuaternionRotationMatrix(m);
			return FromXMVECTOR(q);
		}

		//--------------------------------------------------
		// Euler変換
		//--------------------------------------------------

		// クォータニオンをオイラー角(ラジアン)に変換
		Vector3 ToEulerRad() const {
			XMMATRIX m = XMMatrixRotationQuaternion(ToXMVECTOR());
			Vector3 euler;
			euler.x = asinf(-m.r[2].m128_f32[1]); // Pitch
			if (cosf(euler.x) > 1e-6f) {
				euler.y = atan2f(m.r[2].m128_f32[0], m.r[2].m128_f32[2]); // Yaw
				euler.z = atan2f(m.r[0].m128_f32[1], m.r[1].m128_f32[1]); // Roll
			}
			else {
				euler.y = atan2f(-m.r[0].m128_f32[2], m.r[0].m128_f32[0]);
				euler.z = 0.0f;
			}
			return euler;
		}

		// クォータニオンをオイラー角(度数法)に変換
		Vector3 ToEulerDeg() const {
			Vector3 rad = ToEulerRad();
			return Vector3(
				XMConvertToDegrees(rad.x),
				XMConvertToDegrees(rad.y),
				XMConvertToDegrees(rad.z));
		}

		//--------------------------------------------------
		// 基本操作
		//--------------------------------------------------

		// 正規化（長さを1にする）
		Quaternion Normalized() const {
			XMVECTOR q = XMQuaternionNormalize(ToXMVECTOR());
			return FromXMVECTOR(q);
		}

		// 逆クォータニオン（逆回転を表す）
		Quaternion Inverse() const {
			XMVECTOR q = XMQuaternionInverse(ToXMVECTOR());
			return FromXMVECTOR(q);
		}

		// 共役クォータニオン（z,y,x の符号を反転）
		Quaternion Conjugate() const {
			return Quaternion(-x, -y, -z, w);
		}

		// クォータニオンの長さを取得
		float Length() const {
			return sqrtf(x * x + y * y + z * z + w * w);
		}

		//--------------------------------------------------
		// 演算子
		//--------------------------------------------------

		// 掛け算（回転の合成）
		Quaternion operator*(const Quaternion& rhs) const {
			XMVECTOR q = XMQuaternionMultiply(ToXMVECTOR(), rhs.ToXMVECTOR());
			return FromXMVECTOR(q);
		}

		// スカラー倍
		Quaternion operator*(float s) const {
			return Quaternion(x * s, y * s, z * s, w * s);
		}

		// 加算（主に補間用）
		Quaternion operator+(const Quaternion& rhs) const {
			return Quaternion(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
		}

		Quaternion& operator = (const Quaternion& q) {
			x = q.x;
			y = q.y;
			z = q.z;
			w = q.w;
			return *this;
		}

		//--------------------------------------------------
		// ベクトル・行列操作
		//--------------------------------------------------

		// ベクトルをクォータニオンで回転させる
		Vector3 Rotate(const Vector3& v) const {
			XMVECTOR vec = XMLoadFloat3((XMFLOAT3*)&v);
			XMVECTOR rotated = XMVector3Rotate(vec, ToXMVECTOR());
			Vector3 out; XMStoreFloat3((XMFLOAT3*)&out, rotated);
			return out;
		}

		// 回転行列に変換
		XMMATRIX ToMatrix() const {
			return XMMatrixRotationQuaternion(ToXMVECTOR());
		}

		//--------------------------------------------------
		// 補間系
		//--------------------------------------------------

		// 線形補間（Lerp）
		static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float t) {
			// clamp t (任意)
			if (t <= 0.0f) return a;
			if (t >= 1.0f) return b;

			XMVECTOR qA = a.ToXMVECTOR();
			XMVECTOR qB = b.ToXMVECTOR();

			// 最短経路補正（内積が負なら b を反転）
			float dot = XMVectorGetX(XMVector4Dot(qA, qB));
			if (dot < 0.0f) qB = XMVectorNegate(qB);

			// 線形補間してから正規化
			XMVECTOR q = XMVectorLerp(qA, qB, t);
			q = XMQuaternionNormalize(q);

			return FromXMVECTOR(q);
		}

		// 球面線形補間（Slerp）
		static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t) {
			XMVECTOR qA = a.ToXMVECTOR();
			XMVECTOR qB = b.ToXMVECTOR();
			XMVECTOR q = XMQuaternionSlerp(qA, qB, t);
			return FromXMVECTOR(q);
		}
	};

}

#endif // UTILS_QUATERNION_H
