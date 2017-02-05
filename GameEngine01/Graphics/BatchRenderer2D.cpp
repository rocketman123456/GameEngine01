#include "BatchRenderer2D.h"

namespace GameEngine {
	namespace Graphics {
		/////////////////////////////////////////////////////////////////////////////////////

		void BatchRenderer2D::init() {
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_COLOUR_INDEX);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *) 0);
			glVertexAttribPointer(SHADER_COLOUR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *) (3 * sizeof(GLfloat)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			

			GLuint indices[RENDERER_INDICES_SIZE];

			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
				indices[i + 0] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}

			m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

			glBindVertexArray(0);
		}

		void BatchRenderer2D::terminate() {
			m_IBO->terminate();
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}

		void BatchRenderer2D::submitBegin() {

		}

		void BatchRenderer2D::SubmitEnd() {

		}

		void BatchRenderer2D::submit(const Renderable2D * renderable) {
			VertexData *buffer = (VertexData *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			buffer->vertex = renderable->getPosition();
			buffer->color = renderable->getColor();


		}

		void BatchRenderer2D::flush() {

		}

		/////////////////////////////////////////////////////////////////////////////////
	}
}