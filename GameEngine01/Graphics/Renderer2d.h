#ifndef _RENDERER2D_
#define _RENDERER2D_

#include "Renderable2d.h"

namespace GameEngine {
	namespace Graphics {
		/////////////////////////////////////////////////////////////////////////

		class Renderer2D {
		protected:
			virtual void submit(const Renderable2D *renderable) = 0;
			virtual void flush() = 0;
		};

		//////////////////////////////////////////////////////////////////////////
	}
}

#endif