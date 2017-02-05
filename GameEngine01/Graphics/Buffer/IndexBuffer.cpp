#include "IndexBuffer.h"

namespace GameEngine {
	namespace Graphics {

		IndexBuffer::IndexBuffer(GLuint * data, GLsizei count):
			m_count(count) {

			glGenBuffers(1, &m_bufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * count, data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void IndexBuffer::bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
		}

		void IndexBuffer::unbind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

	}
}