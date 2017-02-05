#include "Sprite.h"

namespace GameEngine {
	namespace Graphics {
		/////////////////////////////////////////////////////////////

		Sprite::Sprite(float x, float y, float width, float height, Math::vec4 &color):
			Renderable2D(Math::vec3(x, y, 0.0f), Math::vec2(width, height), color) {

		}

		Sprite::~Sprite() {

		}

		void Sprite::init() {

		}

		void Sprite::terminate() {

		}

		/////////////////////////////////////////////////////////////
	}
}