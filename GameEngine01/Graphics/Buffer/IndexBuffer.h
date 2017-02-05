#ifndef _INDEXBUFFER_
#define _INDEXBUFFER_

// GLEW
#include <GL/glew.h>

namespace GameEngine {
	namespace Graphics {

		class IndexBuffer {
		public:
			IndexBuffer(GLuint *data, GLsizei count);
			~IndexBuffer() {}

			void init()			{}
			void terminate()	{ glDeleteBuffers(1, &m_bufferID); }

			void bind() const;
			void unbind() const;

			inline GLuint getCount() const { return m_count; }
		private:
			GLuint m_bufferID;
			GLuint m_count;
		};

	}
}

#endif