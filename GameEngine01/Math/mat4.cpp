#include "mat4.h"

namespace GameEngine {
	namespace Math {
		////////////////////////////////////////////////////////////////////////////////////

		mat4::mat4() {
			for (int i = 0; i < 16; ++i) {
				elements[i] = 0.0f;
			}
		}

		mat4::mat4(float diagonal) {
			elements[0 + 0 * 4] = diagonal;
			elements[1 + 0 * 4] = 0.0f;
			elements[2 + 0 * 4] = 0.0f;
			elements[3 + 0 * 4] = 0.0f;

			elements[0 + 1 * 4] = 0.0f;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 1 * 4] = 0.0f;
			elements[3 + 1 * 4] = 0.0f;

			elements[0 + 2 * 4] = 0.0f;
			elements[1 + 2 * 4] = 0.0f;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 2 * 4] = 0.0f;

			elements[0 + 3 * 4] = 0.0f;
			elements[1 + 3 * 4] = 0.0f;
			elements[2 + 3 * 4] = 0.0f;
			elements[3 + 3 * 4] = diagonal;
		}

		mat4 mat4::identity() {
			return mat4(1.0f);
		}

		mat4 mat4::orthographic(float l, float r, float b, float t, float n, float f) {
			mat4 result(1.0f);
			result.elements[0 + 0 * 4] = 2.0f / (r - l);
			result.elements[1 + 1 * 4] = 2.0f / (t - b);
			result.elements[2 + 2 * 4] = 2.0f / (n - f);
			
			result.elements[0 + 3 * 4] = (r + l) / (l - r);
			result.elements[1 + 3 * 4] = (t + b) / (b - t);
			result.elements[2 + 3 * 4] = (f + n) / (f - n);
			return result;
		}

		mat4 mat4::perspective(float fov, float aspectRatio, float n, float f) {
			mat4 result(1.0f);
			float q = 1.0f / tan(DegToRad(fov * 0.5f));
			float a = q / aspectRatio;
			float b = (n + f) / (n - f);
			float c = (2.0f * n * f) / (n - f);
			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = b;
			result.elements[3 + 2 * 4] = c;
			result.elements[2 + 3 * 4] = -1.0f;
			return result;
		}

		mat4 mat4::rotation(float angle, const vec3 &axis) {
			mat4 result(1.0f);
			float r = DegToRad(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;
			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[0 + 0 * 4] = x * x * omc + c;
			result.elements[0 + 1 * 4] = y * x * omc - z * s;
			result.elements[0 + 2 * 4] = x * z * omc + y * s;

			result.elements[1 + 0 * 4] = x * y * omc + z * s;
			result.elements[1 + 1 * 4] = y * y * omc + c;
			result.elements[1 + 2 * 4] = y * z * omc - x * s;

			result.elements[2 + 0 * 4] = x * z * omc - y * s;
			result.elements[2 + 1 * 4] = y * z * omc + x * s;
			result.elements[2 + 2 * 4] = z * z * omc + c;

			return result;
		}

		mat4 mat4::translation(const vec3 &t) {
			mat4 result(1.0f);
			result.elements[0 + 3 * 4] = t.x;
			result.elements[1 + 3 * 4] = t.y;
			result.elements[2 + 3 * 4] = t.z;
			return result;
		}

		mat4 mat4::scale(const vec3 &scale) {
			mat4 result(1.0f);
			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.y;
			result.elements[2 + 2 * 4] = scale.z;
			return result;
		}

		mat4& mat4::multiply(const mat4 &other) {
			for (int y = 0; y < 4; ++y) {
				for (int x = 0; x < 4; ++x) {
					float sum = 0;
					for (int e = 0; e < 4; ++e) {
						sum += elements[x + e * 4] * other.elements[e + y * 4];
					}
					elements[x + y * 4] = sum;
				}
			}
			return *this;
		}
		/*
		mat4 operator+(mat4 left, const mat4 &right) {
			return mat4();
		}

		mat4 operator-(mat4 left, const mat4 &right) {
			return mat4();
		}
		*/
		mat4 operator*(mat4 left, const mat4 &right) {
			mat4 result = left.multiply(right);
			return result;
		}
		/*
		mat4 operator/(mat4 left, const mat4 & right) {
			return mat4();
		}
		*/
		std::ostream& operator<<(std::ostream &stream, const mat4 &other) {
			stream << "mat4(";
			for (int i = 0; i < 16; ++i) {
				stream << other.elements[i] << ", ";
			}
			stream << ")" << std::endl;
			return stream;
		}
		/*/
		mat4& mat4::operator+=(const mat4 &right) {
			// TODO: insert return statement here
		}

		mat4& mat4::operator-=(const mat4 &right) {
			// TODO: insert return statement here
		}
		*/
		mat4& mat4::operator*=(const mat4 &right) {
			return multiply(right);
		}
		/*
		mat4& mat4::operator/=(const mat4 &right) {
			// TODO: insert return statement here
		}

		bool mat4::operator==(const mat4 &right) {
			return false;
		}

		bool mat4::operator!=(const mat4 &right) {
			return false;
		}
		*/

		///////////////////////////////////////////////////////////////////////////////////
	}
}