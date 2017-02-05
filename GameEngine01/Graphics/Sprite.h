#ifndef _SPRITE_
#define _SPRITE_

// GLEW
#include <GL/glew.h>

#include "Renderable2d.h"

namespace GameEngine {
	namespace Graphics {
		/////////////////////////////////////////////////////////////

		class Sprite: public Renderable2D {
		public:
			Sprite(float x, float y, float width, float height, Math::vec4 &color);
			~Sprite();

			void init() override;
			void terminate() override;
		private:

		};

		/////////////////////////////////////////////////////////////
	}
}

#endif