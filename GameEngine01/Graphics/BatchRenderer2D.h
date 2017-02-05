#ifndef _BATCHRENDERER2D_
#define _BATCHRENDERER2D_

#include "Renderer2d.h"
#include "Renderable2d.h"
#include "Buffer\VertexArray.h"
#include "Buffer\IndexBuffer.h"

namespace GameEngine {
	namespace Graphics {
		/////////////////////////////////////////

	#define RENDERER_MAX_SPRITES	10000
	#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
	#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
	#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
	#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

	#define SHADER_VERTEX_INDEX		0
	#define SHADER_COLOUR_INDEX		1

		class BatchRenderer2D :public Renderer2D {
		public:
			BatchRenderer2D() {}
			~BatchRenderer2D() {}

			void init();
			void terminate();

			void submitBegin();
			void SubmitEnd();
			void submit(const Renderable2D *renderable) override;
			void flush() override;
			
		private:
			GLuint			m_VAO;
			GLuint			m_VBO;
			IndexBuffer	   *m_IBO; 
			GLsizei			m_indexCount;
			VertexData	   *m_buffer;
		};

		/////////////////////////////////////////
	}
}

#endif