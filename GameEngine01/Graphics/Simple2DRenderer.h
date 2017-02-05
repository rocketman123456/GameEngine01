#ifndef _SIMPLE2DRENDERER_
#define _SIMPLE2DRENDERER_

#include <GL/glew.h>
#include "../Math/Math.h"
#include "Renderer2d.h"
#include "StaticSprite.h"

#include <deque>

namespace GameEngine {
	namespace Graphics {

		class Simple2DRenderer : public Renderer2D {
		public:
			void submit(const Renderable2D *renderable) override;
			void flush() override;
		private:
			std::deque<const StaticSprite*> m_renderQueue;
		};

	}
}

#endif