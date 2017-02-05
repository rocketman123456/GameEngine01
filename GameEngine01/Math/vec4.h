#ifndef _VEC4_
#define _VEC4_

#include <iostream>

namespace GameEngine {
	namespace Math {
		/////////////////////////////////////////////////////////////////////////////////////////////////

		struct vec4 {
			float x = 0, y = 0, z = 0, w = 0;

			vec4() = default;
			vec4(const float x, const float y, const float z, const float w);

			vec4& add(const vec4& other);
			vec4& subtract(const vec4& other);
			vec4& multiply(const vec4& other);
			vec4& divide(const vec4& other);

			friend vec4 operator+(vec4 left, const vec4& right);
			friend vec4 operator-(vec4 left, const vec4& right);
			friend vec4 operator*(vec4 left, const vec4& right);
			friend vec4 operator/(vec4 left, const vec4& right);

			vec4& operator+=(const vec4& right);
			vec4& operator-=(const vec4& right);
			vec4& operator*=(const vec4& right);
			vec4& operator/=(const vec4& right);

			bool operator==(const vec4& right);
			bool operator!=(const vec4& right);

			friend std::ostream& operator<< (std::ostream& stream, const vec4 &other);
		};

		/////////////////////////////////////////////////////////////////////////////////////////////////
	}
}

#endif