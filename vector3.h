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
	float x;
	float y;
	float z;

//コンストラクタ
	//デフォルトのコンストラクタはベクトルは未決定な状態になる
	Vector3() {}

	//コピーコンストラクタ
 	Vector3(const Vector3& a) : x(a.x), y(a.y), z(a.z) {}

	//三つの値で作成する
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

//標準的なオブジェクトの保守

	//代入（Cの習慣に従い値への参照を返す）

	Vector3& operator = (const Vector3& a)
	{
		x = a.x;
		y = a.y;
		z = a.z;
		return *this;
	}

	//等しさのチェック

	bool operator == (const Vector3& a) const
	{
		return x == a.x && y == a.y && z == a.z;
	}

	bool operator != (const Vector3& a) const
	{
		return x != a.x || y != a.y || z != a.z;
	}

//ベクトルの操作
	//ベクトルを０に設定する

	void Zero() { x = y = z = 0.0f; }

	//単項式のマイナスは、反転したベクトルを返す

	Vector3 operator -() const { return Vector3(-x, -y, -z); }

	//二項式の＋と－はベクトルを加算し、減算する

	Vector3 operator + (const Vector3& a) const
	{
		return Vector3(x + a.x, y + a.y, z + a.z);
	}

	Vector3 operator - (const Vector3& a) const
	{
		return Vector3(x - a.x, y - a.y, z - a.z);
	}

	//スカラーによる乗算と除算

	Vector3 operator * (float a) const
	{
		return Vector3(x * a, y * a, z * a);
	}

	Vector3 operator / (float a) const
	{
		float oneOverA = 1.0f / a;//ここではゼロ除算をチェックしてはならない
		
		return Vector3(x * oneOverA, y * oneOverA, z * oneOverA);
				
	}

	//Cの表記法に準拠するための組み合わせ代入演算

	Vector3& operator += (const Vector3& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		return *this;
	}


	Vector3& operator -= (const Vector3& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return *this;
	}


	Vector3& operator *= (float a)
	{
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	Vector3 &operator /= (float a) 
	{
		float oneOverA = 1.0f / a;//ここではゼロ除算をチェックしてはならない

		x *= oneOverA;
		y *= oneOverA;
		z *= oneOverA;

		return *this;

	}

	//ベクトルを正規化する
	void normalize()
	{
		float magSq = x * x + y * y + z * z;
		if (magSq > 0.0f)
		{
			//０除算をチェックする
			float oneOverMag = 1.0f / sqrt(magSq);
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
		}
	}

	Vector3 normalized()
	{
		float magSq = x * x + y * y + z * z;
		if (magSq > 0.0f)
		{
			//０除算をチェックする
			float oneOverMag = 1.0f / sqrt(magSq);
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
		}
		return{ x , y , z };
	}

	float length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}
	
	////ベクトルの内積・・・標準の乗算記号をこれにオーバーロードする

	//ベクトルの内積計算
	static float dot(const Vector3& a, const Vector3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}



	//外積
	static Vector3 cross(const Vector3& a, const Vector3& b)
	{
		Vector3 ret;
		ret.x = a.y * b.z - a.z * b.y;
		ret.y = a.z * b.x - a.x * b.z;
		ret.z = a.x * b.y - a.y * b.x;
		return ret;
	}
};

#endif // !_VECTOR3_
