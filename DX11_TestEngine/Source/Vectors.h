#pragma once

namespace Vector2
{
	struct VecInt2D
	{
		int x = 0;
		int y = 0;

		VecInt2D() {}
		VecInt2D(int _x, int _y) : x(_x), y(_y) {}
		VecInt2D(float _x, float _y) : x((int)(_x + 0.5f)), y((int)(_y + 0.5f)) {}

		struct Vec2D normalized();
		float magnitude();
		float vectorAngle();

		friend VecInt2D operator *(const VecInt2D& _vecInt2, float _a)
		{
			VecInt2D vecInt2 = _vecInt2;
			vecInt2.x *= _a;
			vecInt2.y *= _a;
			return vecInt2;
		}
		friend VecInt2D operator +(const VecInt2D& _vecInt2A, const VecInt2D& _vecInt2B)
		{
			VecInt2D vecInt2 = _vecInt2A;
			vecInt2.x = vecInt2.x + _vecInt2B.x;
			vecInt2.y = vecInt2.y + _vecInt2B.y;
			return vecInt2;
		}
		friend VecInt2D operator -(const VecInt2D& _vec2A, const VecInt2D& _vec2B)
		{
			VecInt2D vecInt2 = _vec2A;
			vecInt2.x = vecInt2.x - _vec2B.x;
			vecInt2.y = vecInt2.y - _vec2B.y;
			return vecInt2;
		}
		friend VecInt2D operator /(const VecInt2D& _vec2, float _a)
		{
			VecInt2D vecInt2 = _vec2;
			vecInt2.x /= _a;
			vecInt2.y /= _a;
			return vecInt2;
		}
	};
	struct Vec2D
	{
		float x = 0.0f;
		float y = 0.0f;

		Vec2D() {}
		Vec2D(float _x, float _y) : x(_x), y(_y) {}
		Vec2D(int _x, int _y) : x((float)_x), y((float)_y) {}
		Vec2D(float _x, int _y) : x(_x), y((float)_y) {}
		Vec2D(int _x, float _y) : x((float)_x), y(_y) {}
		Vec2D(VecInt2D _vecInt2D) : x((float)_vecInt2D.x), y((float)_vecInt2D.y) {}

		operator VecInt2D() const { return VecInt2D(x, y); }

		float magnitude();
		Vec2D normalized();
		float vectorAngle();
		void rotate(float _a);


		Vec2D& operator *=(float _a)
		{
			x *= _a;
			y *= _a;
			return *this;
		}
		Vec2D& operator *=(const Vec2D& _vec2)
		{
			x *= _vec2.x;
			y *= _vec2.y;
			return *this;
		}
		friend Vec2D operator *(const Vec2D& _vec2A, const Vec2D& _vec2B)
		{
			Vec2D vec2 = _vec2A;
			vec2.x *= _vec2B.x;
			vec2.y *= _vec2B.y;
			return vec2;
		}
		friend Vec2D operator *(const Vec2D& _vec2, float _a)
		{
			Vec2D vec2 = _vec2;
			vec2.x *= _a;
			vec2.y *= _a;
			return vec2;
		}
		Vec2D& operator /=(float _a)
		{
			x /= _a;
			y /= _a;
			return *this;
		}
		friend Vec2D operator /(const Vec2D& _vec2, float _a)
		{
			Vec2D vec2 = _vec2;
			vec2.x /= _a;
			vec2.y /= _a;
			return vec2;
		}
		Vec2D& operator +=(const Vec2D& _vec2)
		{
			x += _vec2.x;
			y += _vec2.y;
			return *this;
		}
		friend Vec2D operator +(const Vec2D& _vec2A, const Vec2D& _vec2B)
		{
			Vec2D vec2 = _vec2A;
			vec2.x = vec2.x + _vec2B.x;
			vec2.y = vec2.y + _vec2B.y;
			return vec2;
		}
		friend Vec2D operator +(const Vec2D& _vec2A, const VecInt2D& _vec2B)
		{
			Vec2D vec2 = _vec2A;
			vec2.x = vec2.x + _vec2B.x;
			vec2.y = vec2.y + _vec2B.y;
			return vec2;
		}
		friend Vec2D operator -(const Vec2D& _vec2A, const Vec2D& _vec2B)
		{
			Vec2D vec2 = _vec2A;
			vec2.x = vec2.x - _vec2B.x;
			vec2.y = vec2.y - _vec2B.y;
			return vec2;
		}
	};

	//Consts
	const Vec2D Vec2Zero{ 0.0f,0.0f };
	const Vec2D Vec2One{ 1.0f,1.0f };
	const Vec2D Vec2Up{ 0.0f,1.0f };
	const Vec2D Vec2Down{ 0.0f,-1.0f };
	const Vec2D Vec2Left{ -1.0f,0.0f };
	const Vec2D Vec2Right{ 1.0f,0.0f };
	const VecInt2D VecInt2Zero{ 0,0 };
}
namespace Vector3
{
	struct Vec3D
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		Vec3D() {}
		Vec3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		Vec3D(Vector2::VecInt2D _vecInt2, float _z) : x(_vecInt2.x), y(_vecInt2.y), z(_z) {}
		Vec3D(Vector2::Vec2D _vec2, float _z) : x(_vec2.x), y(_vec2.y), z(_z) {}

		float magnitude();
		Vec3D normalized();

		operator Vector2::Vec2D() const { return Vector2::Vec2D(x, y); }
		operator Vector2::VecInt2D() const { return Vector2::VecInt2D(x, y); }

		friend Vec3D operator *(const Vec3D& _vec3, float _a)
		{
			Vec3D vec3 = _vec3;
			vec3.x *= _a;
			vec3.y *= _a;
			vec3.z *= _a;
			return vec3;
		}
		friend Vec3D operator +(const Vec3D& _vec3A, const Vec3D& _vec3B)
		{
			Vec3D vec3 = _vec3A;
			vec3.x = vec3.x + _vec3B.x;
			vec3.y = vec3.y + _vec3B.y;
			vec3.z = vec3.z + _vec3B.z;
			return vec3;
		}
		friend Vec3D operator -(const Vec3D& _vec3A, const Vec3D& _vec3B)
		{
			Vec3D vec3 = _vec3A;
			vec3.x = vec3.x - _vec3B.x;
			vec3.y = vec3.y - _vec3B.y;
			vec3.z = vec3.z - _vec3B.z;
			return vec3;
		}
		friend Vec3D operator /(const Vec3D& _vec3, float _a)
		{
			Vec3D vec3 = _vec3;
			vec3.x /= _a;
			vec3.y /= _a;
			vec3.z /= _a;
			return vec3;
		}
	};
	struct VecInt3D
	{
		int x = 0;
		int y = 0;
		int z = 0;
	};
	//Consts
	const Vec3D Vec3Zero{0.0f,0.0f,0.0f };
	const Vec3D Vec3One{ 1.0f,1.0f,1.0f };
	const Vec3D Vec3Forward{ 0.0f,0.0f,1.0f };
	const VecInt3D VecInt3Zero{ 0,0,0 };

}


namespace Vector4
{
	struct Vec4D
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

		Vec4D() {}
		Vec4D(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
		Vec4D(Vector3::Vec3D _vec3, float _w) : x(_vec3.x), y(_vec3.y), z(_vec3.z), w(_w) {}

		operator unsigned int() const 
		{
			unsigned int AaBbGgRr;

			AaBbGgRr = ((int)(255 * w)) << 24;
			AaBbGgRr += ((int)(255 * z)) << 16;
			AaBbGgRr += ((int)(255 * y)) << 8;
			AaBbGgRr += ((int)(255 * x)) << 0;

			return AaBbGgRr;
		}
	};
	struct VecByte4D
	{
		unsigned char x = 0;
		unsigned char y = 0;
		unsigned char z = 0;
		unsigned char w = 0;

		VecByte4D() {}
		VecByte4D(unsigned char _x, unsigned char _y, unsigned char _z, unsigned char _w) : x(_x), y(_y), z(_z), w(_w) {}
		VecByte4D(Vec4D _floatColor) : x((unsigned char)(_floatColor.x * 255)),
									   y((unsigned char)(_floatColor.y * 255)), 
									   z((unsigned char)(_floatColor.z * 255)), 
									   w((unsigned char)(_floatColor.w * 255)) {}

		operator unsigned int() const
		{
			unsigned int AaBbGgRr;

			AaBbGgRr = ((int)(w)) << 24;
			AaBbGgRr += ((int)(z)) << 16;
			AaBbGgRr += ((int)(y)) << 8;
			AaBbGgRr += ((int)(x)) << 0;

			return AaBbGgRr;
		}

	};
	struct VecInt4D
	{
		int x = 0;
		int y = 0;
		int z = 0;
		int w = 0;

	};

	//Consts
	const Vec4D Vec4Zero{ 0.0f,0.0f,0.0f,0.0f };
	const Vec4D Vec4One{ 1.0f,1.0f,1.0f,1.0f };
	const Vec4D Vec4Half{ 0.5f,0.5f,0.5f,0.5f };
	const Vec4D Vec4Blue{ 0.0f,0.0f,1.0f,1.0f };
	const Vec4D Vec4Red{ 1.0f,0.0f,0.0f,1.0f };
	const Vec4D Vec4Green{ 0.0f,1.0f,0.0f,1.0f };
	const VecInt4D VecInt4Zero{ 0,0,0,0 };
}



typedef Vector3::Vec3D Vertex;
typedef Vector4::VecByte4D Color;

struct VertexColor
{
	Vertex pos;
	Vector3::Vec3D normal;
	Vector4::VecByte4D color;

	VertexColor(Vertex _vertex, Vector4::Vec4D _color) : pos(_vertex), color(_color) {}
	VertexColor(Vertex _vertex) : pos(_vertex), color(Vector4::VecByte4D(255, 255, 255, 255)) {}
};