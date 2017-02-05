#include "Simple2DRenderer.h"

namespace GameEngine {
	namespace Graphics {

		void Simple2DRenderer::submit(const Renderable2D *renderable) {
			m_renderQueue.push_back((StaticSprite *)renderable);
		}

		void Simple2DRenderer::flush() {
			while (!m_renderQueue.empty()) {
				const StaticSprite *renderable = m_renderQueue.front();

				renderable->getVAO()->bind();
				renderable->getIBO()->bind();

				renderable->getIBO()->getCount();
				renderable->getShader().setUniformMat4("ml_matrix", Math::mat4::translation(renderable->getPosition()));
				glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_INT, nullptr);

				renderable->getIBO()->unbind();
				renderable->getVAO()->unbind();

				m_renderQueue.pop_front();
			}
		}

	}
}