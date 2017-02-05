#ifndef _VERTEXARRAY_
#define _VERTEXARRAY_

// GLEW
#include <GL/glew.h>
#include <vector>

#include "Buffer.h"

namespace GameEngine {
	namespace Graphics {

		class VertexArray {
		public:
			VertexArray() {}
			~VertexArray() {}

			void init();		// init
			void terminate();	// shutdown

			void addBuffers(Buffer *buffer, GLuint index);
			void bind() const;
			void unbind() const;	

		private:
			GLuint m_arrayID;
			std::vector<Buffer*> m_buffers;
		};

	}
}

#endif