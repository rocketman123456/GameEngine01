#include "vec4.h"

namespace GameEngine {
	namespace Math {
		/////////////////////////////////////////////////////////////////////////////////////////////

		vec4::vec4(const float vx, const float vy, const float vz, const float vw) {
			x = vx;
			y = vy;
			z = vz;
			w = vw;
		}

		///
		vec4 & vec4::add(const vec4 & other) {
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		vec4 & vec4::subtract(const vec4 & other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		vec4 & vec4::multiply(const vec4 & other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
			return *this;
		}

		vec4 & vec4::divide(const vec4 & other) {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
			return *this;
		}
		///

		///
		vec4 operator+(vec4 left, const vec4& right) {
			return left.add(right);
		}

		vec4 operator-(vec4 left, const vec4& right) {
			return left.subtract(right);
		}

		vec4 operator*(vec4 left, const vec4& right) {
			return left.multiply(right);
		}

		vec4 operator/(vec4 left, const vec4& right) {
			return left.divide(right);
		}
		///

		///
		vec4& vec4::operator+=(const vec4& right) {
			return add(right);
		}

		vec4& vec4::operator-=(const vec4& right) {
			return subtract(right);
		}

		vec4& vec4::operator*=(const vec4& right) {
			return multiply(right);
		}

		vec4& vec4::operator/=(const vec4& right) {
			return divide(right);
		}
		///

		bool vec4::operator==(const vec4& right) {
			return x == right.x && y == right.y && z == right.z && w == right.w;
		}

		bool vec4::operator!=(const vec4& right) {
			return !(*this == right);
		}

		std::ostream& operator<< (std::ostream& stream, const vec4 &vector) {
			stream << "vec4: ( " << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << " )";
			return stream;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}