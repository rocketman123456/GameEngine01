#ifndef _BUFFER_
#define _BUFFER_

// GLEW
#include <GL/glew.h>

namespace GameEngine {
	namespace Graphics {

		class Buffer {
		public:
			Buffer(GLfloat *data, GLsizei count, GLuint componentCount);
			~Buffer() {}

			void init()			{}
			void terminate()	{ glDeleteBuffers(1, &m_bufferID); }

			void bind() const;
			void unbind() const;

			inline GLuint getCompnentCount() { return m_componentCount; }
		private:
			GLuint m_bufferID;
			GLuint m_componentCount;
		};

	}
}

#endif