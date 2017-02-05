#include "VertexArray.h"

namespace GameEngine {
	namespace Graphics {

		void VertexArray::init() {
			glGenVertexArrays(1, &m_arrayID);
		}

		void VertexArray::terminate() {
			for (int i = 0; i < m_buffers.size(); ++i) {
				if (m_buffers[i] == nullptr)
					continue;
				delete m_buffers[i];
			}
			glDeleteVertexArrays(1, &m_arrayID);
		}

		void VertexArray::addBuffers(Buffer * buffer, GLuint index) {
			bind();
			buffer->bind();

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->getCompnentCount(), GL_FLOAT, GL_FALSE, 0, 0);

			buffer->unbind();
			unbind();

			m_buffers.push_back(buffer);
		}

		void VertexArray::bind() const {
			glBindVertexArray(m_arrayID);
		}

		void VertexArray::unbind() const {
			glBindVertexArray(0);
		}

	}
}
