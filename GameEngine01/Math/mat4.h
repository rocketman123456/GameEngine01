#ifndef _MAT4_
#define _MAT4_

#define _USE_MATH_DEFINES
#include <cmath>
#include "Math.h"

namespace GameEngine {
	namespace Math {
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		struct mat4 {

			union {
				float	elements[4 * 4];
				vec4	columns[4];
			};

			mat4();
			mat4(float diagonal);

			static mat4 identity();
			static mat4 orthographic(float _left, float _right, float _bottom, float _top, float _near, float _far);
			static mat4 perspective(float _fov, float _aspectRatio, float _near, float _far);
			static mat4 rotation(float angle, const vec3 &axis);
			static mat4 translation(const vec3& t);
			static mat4 scale(const vec3& scale);

			mat4& multiply(const mat4& other);
			// TODO: complete all this functions
			//friend mat4 operator+(mat4 left, const mat4& right);
			//friend mat4 operator-(mat4 left, const mat4& right);
			friend mat4 operator*(mat4 left, const mat4& right);
			//friend mat4 operator/(mat4 left, const mat4& right);

			//mat4& operator+=(const mat4& right);
			//mat4& operator-=(const mat4& right);
			mat4& operator*=(const mat4& right);
			//mat4& operator/=(const mat4& right);

			//bool operator==(const mat4& right);
			//bool operator!=(const mat4& right);

			friend std::ostream& operator<< (std::ostream& stream, const mat4 &other);
		};

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}

#endif