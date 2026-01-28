//	utils_math.h
//
//
//	2025.04.07			大山凌太朗

#ifndef UTILS_MATH_H
#define UTILS_MATH_H

#include <cmath>

namespace math {
    // Int2構造体（x, y）
    struct Int2 {
        int x, y;
        // コンストラクタ
        Int2() : x(0), y(0) {}
        Int2(int x, int y) : x(x), y(y) {}

        // 演算子オーバーロード（加算）
        Int2 operator+(const Int2& other) const {
            return Int2(x + other.x, y + other.y);
        }
        // 演算子オーバーロード（減算）
        Int2 operator-(const Int2& other) const {
            return Int2(x - other.x, y - other.y);
        }
        // 演算子オーバーロード（乗算）
        Int2 operator*(int scalar) const {
            return Int2(x * scalar, y * scalar);
        }
        // 演算子オーバーロード（除算）
        Int2 operator/(int scalar) const {
            return Int2(x / scalar, y / scalar);
        }
    };

    // Int3構造体（x, y, z）
    struct Int3 {
        int x, y, z;

        // コンストラクタ
        Int3() : x(0), y(0), z(0) {}
        Int3(int x, int y, int z) : x(x), y(y), z(z) {}
        // 演算子オーバーロード（加算）
        Int3 operator+(const Int3& other) const {
            return Int3(x + other.x, y + other.y, z + other.z);
        }
        // 演算子オーバーロード（減算）
        Int3 operator-(const Int3& other) const {
            return Int3(x - other.x, y - other.y, z - other.z);
        }
        // 演算子オーバーロード（乗算）
        Int3 operator*(int scalar) const {
            return Int3(x * scalar, y * scalar, z * scalar);
        }
        // 演算子オーバーロード（除算）
        Int3 operator/(int scalar) const {
            return Int3(x / scalar, y / scalar, z / scalar);
        }
    };

    // Float2構造体（x, y）
    struct Float2 {
        //--------------------------------------------------
        float x, y;

        //--------------------------------------------------
        // コンストラクタ
        Float2() : x(0.0f), y(0.0f) {}
        Float2(float x, float y) : x(x), y(y) {}

        //--------------------------------------------------
        // 演算子オーバーロード（加算）
        Float2 operator+(const Float2& other) const {
            return Float2(x + other.x, y + other.y);
        }
        // 演算子オーバーロード（減算）
        Float2 operator-(const Float2& other) const {
            return Float2(x - other.x, y - other.y);
        }
        // 演算子オーバーロード（乗算）
        Float2 operator*(float scalar) const {
            return Float2(x * scalar, y * scalar);
        }
        // 演算子オーバーロード（除算）
        Float2 operator/(float scalar) const {
            return Float2(x / scalar, y / scalar);
        }

    };


    // Float3構造体（x, y, z）
    struct Float3 {
        float x, y, z;

        // コンストラクタ
        Float3() : x(0.0f), y(0.0f), z(0.0f) {}
        Float3(float x, float y, float z) : x(x), y(y), z(z) {}
        // 演算子オーバーロード（加算）
        Float3 operator+(const Float3& other) const {
            return Float3(x + other.x, y + other.y, z + other.z);
        }
        // 演算子オーバーロード（減算）
        Float3 operator-(const Float3& other) const {
            return Float3(x - other.x, y - other.y, z - other.z);
        }
        // 演算子オーバーロード（乗算）
        Float3 operator*(float scalar) const {
            return Float3(x * scalar, y * scalar, z * scalar);
        }
        // 演算子オーバーロード（除算）
        Float3 operator/(float scalar) const {
            return Float3(x / scalar, y / scalar, z / scalar);
        }
    };

    // Float4構造体（x, y, z, w）
    struct Float4 {
        float x, y, z, w;

        // コンストラクタ
        Float4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        Float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        // 演算子オーバーロード（加算）
        Float4 operator+(const Float4& other) const {
            return Float4(x + other.x, y + other.y, z + other.z, w + other.w);
        }
        // 演算子オーバーロード（減算）
        Float4 operator-(const Float4& other) const {
            return Float4(x - other.x, y - other.y, z - other.z, w - other.w);
        }
        // 演算子オーバーロード（乗算）
        Float4 operator*(float scalar) const {
            return Float4(x * scalar, y * scalar, z * scalar, w * scalar);
        }

        // 演算子オーバーロード（除算）
        Float4 operator/(float scalar) const {
            return Float4(x / scalar, y / scalar, z / scalar, w / scalar);
        }

    };

    //class Vector3
    //{
    //public:
    //    float x = 0.0f;
    //    float y = 0.0f;
    //    float z = 0.0f;

    //    Vector3() {}

    //    Vector3(const Vector3& vector) :x(vector.x), y(vector.y), z(vector.z) {}
    //    Vector3(float nx, float ny, float nz) :x(nx), y(ny), z(nz) {}

    //    //代入
    //    Vector3& operator = (const Vector3& vector) {
    //        x = vector.x;
    //        y = vector.y;
    //        z = vector.z;
    //        return *this;
    //    }

    //    //等号・不等号チェック
    //    bool operator == (const Vector3& vector) const {
    //        return x == vector.x && y == vector.y && z == vector.z;
    //    }

    //    bool operator != (const Vector3& vector) const {
    //        return x != vector.x || y != vector.y || z != vector.z;
    //    }

    //    //ベクトル操作

    //    //0ベクトル設定
    //    void zero() { x = y = z = 0.0f; }

    //    //逆ベクトル
    //    Vector3 operator -() const { return Vector3(-x, -y, -z); }

    //    //加算
    //    Vector3 operator +(const Vector3& vector) const {
    //        return Vector3(x + vector.x, y + vector.y, z + vector.z);
    //    }

    //    //減算
    //    Vector3 operator -(const Vector3& vector) const {
    //        return Vector3(x - vector.x, y - vector.y, z - vector.z);
    //    }

    //    //乗算
    //    Vector3 operator *(float scalar) const {
    //        return Vector3(x * scalar, y * scalar, z * scalar);
    //    }

    //    //除算
    //    Vector3 operator /(float scalar) const {
    //        float oneOver = 1.0f / scalar;
    //        return Vector3(x * oneOver, y * oneOver, z * oneOver);
    //    }

    //    //代入演算
    //    Vector3& operator += (const Vector3& vector) {
    //        x += vector.x;
    //        y += vector.y;
    //        z += vector.z;
    //        return *this;
    //    }

    //    Vector3& operator -= (const Vector3& vector) {
    //        x -= vector.x;
    //        y -= vector.y;
    //        z -= vector.z;
    //        return *this;
    //    }

    //    Vector3& operator *= (const float scalar) {
    //        x *= scalar;
    //        y *= scalar;
    //        z *= scalar;
    //        return *this;
    //    }

    //    Vector3& operator /= (const float scalar) {
    //        float oneOver = 1.0f / scalar;
    //        x *= oneOver;
    //        y *= oneOver;
    //        z *= oneOver;
    //        return *this;
    //    }

    //    //正規化
    //    void normalize() {
    //        float magSq = x * x + y * y + z * z;
    //        if (magSq > 0.0f) {
    //            float oneOverMag = 1.0f / sqrt(magSq);
    //            x *= oneOverMag;
    //            y *= oneOverMag;
    //            z *= oneOverMag;
    //        }
    //    }

    //    Vector3 normalized() const {
    //        float magSq = x * x + y * y + z * z;
    //        if (magSq > 0.0f) {
    //            float oneOverMag = 1.0f / sqrt(magSq);
    //            return Vector3(x * oneOverMag, y * oneOverMag, z * oneOverMag);
    //        }
    //        return Vector3(0.0f, 0.0f, 0.0f); // 長さ0ならゼロベクトル返す
    //    }

    //    //長さ
    //    float length() const {
    //        return sqrtf(x * x + y * y + z * z);
    //    }

    //    //内積
    //    static float dot(const Vector3& a, const Vector3& b) {
    //        return a.x * b.x + a.y * b.y + a.z * b.z;
    //    }

    //    //外積
    //    static Vector3 cross(const Vector3& a, Vector3& b) {
    //        Vector3 ret;
    //        ret.x = a.y * b.z - a.z * b.y;
    //        ret.y = a.z * b.x - a.x * b.z;
    //        ret.z = a.x * b.y - a.y * b.x;
    //        return ret;
    //    }

    //    //方向ベクトル

    //    //上
    //    static Vector3 UP() {
    //        Vector3 up;
    //        up = { 0.0f,1.0f,0.0f };
    //        return up;
    //    }

    //    //下
    //    static Vector3 DOWN() {
    //        Vector3 down;
    //        down = -Vector3::UP();
    //        return down;
    //    }

    //    //右
    //    static Vector3 RIGHT() {
    //        Vector3 right;
    //        right = { 1.0f,0.0f,0.0f };
    //        return right;  
    //    }
    //    //左
    //    static Vector3 LEFT() {
    //        Vector3 left;
    //        left = -Vector3::RIGHT();
    //        return left;
    //    }
    //    //前
    //    static Vector3 FRONT() {
    //        Vector3 front;
    //        front = { 0.0f,0.0f,1.0f };
    //        return front;
    //    }
    //    //後
    //    static Vector3 BACK() {
    //        Vector3 back;
    //        back = -Vector3::FRONT();
    //        return back;
    //    }

    //    static Vector3 ZERO() {
    //        Vector3 zero;
    //        zero = { 0.0f,0.0f,0.0f };
    //        return zero;
    //    }

    //    // 線形補間 Lerp
    //    static Vector3 Lerp(const Vector3& a, const Vector3& b, float t) {
    //        return a + (b - a) * t;
    //    }
    //};
}

#endif // UTILS_MATH_H