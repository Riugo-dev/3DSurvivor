//********************************************************************************
//
// Vector3 クラス[vector.h]
//
//															Author :Riugo Honda
//															Date   :2025/05/13
// -------------------------------------------------------------------------------
//															Last Edited:2025/05/13
//********************************************************************************


#ifndef _VECTOR3_
#define _VECTOR3_

#include <math.h>

class Vector3
{
public:
	//パブリックな表現：ここに書かれるものは、多くない
	float m_x;
	float m_y;
	float m_z;

//コンストラクタ
	//デフォルトのコンストラクタはベクトルは未決定な状態になる
	Vector3() {}

	//コピーコンストラクタ
 	Vector3(const Vector3& a) : m_x(a.m_x), m_y(a.m_y), m_z(a.m_z) {}

	//三つの値で作成する
	Vector3(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {}

//標準的なオブジェクトの保守

	//代入（Cの習慣に従い値への参照を返す）

	Vector3& operator = (const Vector3& a)
	{
		m_x = a.m_x;
		m_y = a.m_y;
		m_z = a.m_z;
		return *this;
	}

	//等しさのチェック

	bool operator == (const Vector3& a) const
	{
		return m_x == a.m_x && m_y == a.m_y && m_z == a.m_z;
	}

	bool operator != (const Vector3& a) const
	{
		return m_x != a.m_x || m_y != a.m_y || m_z != a.m_z;
	}

//ベクトルの操作
	//ベクトルを０に設定する

	void Zero() { m_x = m_y = m_z = 0.0f; }

	//単項式のマイナスは、反転したベクトルを返す

	Vector3 operator -() const { return Vector3(-m_x, -m_y, -m_z); }

	//二項式の＋と－はベクトルを加算し、減算する

	Vector3 operator + (const Vector3& a) const
	{
		return Vector3(m_x + a.m_x, m_y + a.m_y, m_z + a.m_z);
	}

	Vector3 operator - (const Vector3& a) const
	{
		return Vector3(m_x - a.m_x, m_y - a.m_y, m_z - a.m_z);
	}

	//スカラーによる乗算と除算

	Vector3 operator * (float a) const
	{
		return Vector3(m_x * a, m_y * a, m_z * a);
	}

	Vector3 operator / (float a) const
	{
		float oneOverA = 1.0f / a;//ここではゼロ除算をチェックしてはならない
		
		return Vector3(m_x * oneOverA, m_y * oneOverA, m_z * oneOverA);
				
	}

	//Cの表記法に準拠するための組み合わせ代入演算

	Vector3& operator += (const Vector3& a)
	{
		m_x += a.m_x;
		m_y += a.m_y;
		m_z += a.m_z;
		return *this;
	}


	Vector3& operator -= (const Vector3& a)
	{
		m_x -= a.m_x;
		m_y -= a.m_y;
		m_z -= a.m_z;
		return *this;
	}


	Vector3& operator *= (float a)
	{
		m_x *= a;
		m_y *= a;
		m_z *= a;
		return *this;
	}

	Vector3 &operator /= (float a) 
	{
		float oneOverA = 1.0f / a;//ここではゼロ除算をチェックしてはならない

		m_x *= oneOverA;
		m_y *= oneOverA;
		m_z *= oneOverA;

		return *this;

	}

	//ベクトルを正規化する
	void normalize()
	{
		float magSq = m_x * m_x + m_y * m_y + m_z * m_z;
		if (magSq > 0.0f)
		{
			//０除算をチェックする
			float oneOverMag = 1.0f / sqrt(magSq);
			m_x *= oneOverMag;
			m_y *= oneOverMag;
			m_z *= oneOverMag;
		}
	}

	Vector3 normalized()
	{
		float magSq = m_x * m_x + m_y * m_y + m_z * m_z;
		if (magSq > 0.0f)
		{
			//０除算をチェックする
			float oneOverMag = 1.0f / sqrt(magSq);
			m_x *= oneOverMag;
			m_y *= oneOverMag;
			m_z *= oneOverMag;
		}
		return{ m_x , m_y , m_z };
	}

	float length() const
	{
		return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
	}
	
	////ベクトルの内積・・・標準の乗算記号をこれにオーバーロードする

	//float operator  (const Vector3& a) const
	//{
	//	return m_x * a.m_x + m_y * a.m_y + m_z * a.m_z;
	//}

};

#endif // !_VECTOR3_
