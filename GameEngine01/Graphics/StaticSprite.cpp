#include "StaticSprite.h"

namespace GameEngine {
	namespace Graphics {
		/////////////////////////////////////////////////////////////

		StaticSprite::StaticSprite(float x, float y, float width, float height, Math::vec4 &color, Shader &shader) :
			Renderable2D(Math::vec3(x, y, 0.0f), Math::vec2(width, height), color), m_shader(shader) {
			
		}

		StaticSprite::~StaticSprite() {

		}

		void StaticSprite::init() {
			m_vertexArray = new VertexArray();
			GLfloat vertices[] = {
				0,		   0, 0,
				0,	m_size.y, 0,
		 m_size.x,	m_size.y, 0,
		 m_size.x,		   0, 0
			};
			GLfloat colors[] = {
				m_color.x, m_color.y, m_color.z, m_color.w,
				m_color.x, m_color.y, m_color.z, m_color.w,
				m_color.x, m_color.y, m_color.z, m_color.w,
				m_color.x, m_color.y, m_color.z, m_color.w
			};
			GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

			m_vertexArray->init();
			m_vertexArray->addBuffers(new Buffer(vertices, 12, 3), 0);
			m_vertexArray->addBuffers(new Buffer(colors, 16, 4), 1);
			m_indexBuffer = new IndexBuffer(indices, 6);
			m_indexBuffer->init();
		}

		void StaticSprite::terminate() {
			m_vertexArray->terminate();
			m_indexBuffer->terminate();
			delete m_vertexArray;
			delete m_indexBuffer;
		}

		/////////////////////////////////////////////////////////////
	}
}