#ifndef _RENDERABLE2D_
#define _RENDERABLE2D_

#include "Shader.h"
#include "Buffer/Buffer.h"
#include "Buffer/IndexBuffer.h"
#include "Buffer/VertexArray.h"
#include "../Math/Math.h"

namespace GameEngine {
	namespace Graphics {

		struct VertexData {
			Math::vec3 vertex;
			Math::vec4 color;
		};

		class Renderable2D {
		public:
			Renderable2D(Math::vec3 position, Math::vec2 size, Math::vec4 color):
				m_position(position), m_size(size), m_color(color) {}

			virtual ~Renderable2D() {}

			virtual void init() = 0;
			virtual void terminate() = 0;

			//inline const VertexArray* getVAO() const		{ return m_vertexArray; }
			//inline const IndexBuffer* getIBO() const		{ return m_indexBuffer; }
			//inline		 Shader&	  getShader() const		{ return m_shader; }
			inline const Math::vec3& getPosition() const	{ return m_position; }
			inline const Math::vec2& getSize() const		{ return m_size; }
			inline const Math::vec4& getColor() const		{ return m_color; }

		protected:
			Math::vec3 m_position;
			Math::vec2 m_size;
			Math::vec4 m_color;
		};

	}
}

#endif