#ifndef _STATICSPRITE_
#define _STATICSPRITE_

#include "Renderable2d.h"
#include "Buffer\IndexBuffer.h"
#include "Buffer\VertexArray.h"
#include "Shader.h"

namespace GameEngine {
	namespace Graphics {
		/////////////////////////////////////////////////////////////
		class StaticSprite : public Renderable2D {
		public:
			StaticSprite(float x, float y, float width, float height, Math::vec4 &color, Shader &shader);
			~StaticSprite();

			void init() override;
			void terminate() override;

			inline const VertexArray* getVAO() const		{ return m_vertexArray; }
			inline const IndexBuffer* getIBO() const		{ return m_indexBuffer; }
			inline		 Shader&	  getShader() const		{ return m_shader; }
		private:
			VertexArray		*m_vertexArray;
			IndexBuffer		*m_indexBuffer;
			Shader			&m_shader;
		};
		/////////////////////////////////////////////////////////////
	}
}

#endif