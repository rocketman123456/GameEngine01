#ifndef _SHADER_
#define _SHADER_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// Vulkan
#include <vulkan\vulkan.hpp>

#include "../utils/FileUtils.h"
#include "../Math/Math.h"

namespace GameEngine {
	namespace Graphics {
		//////////////////////////////////////////////////////////////////////////////////////
	
		class Shader {
		public:
			Shader(const GLchar* _vertPath, const GLchar* _fragPath);
			~Shader();

			GLuint load();
			void deleteShader();

			void setUniform1f(const char *name, const float value);
			void setUniform1i(const char *name, const int value);
			void setUniform2f(const char *name, const Math::vec2 &value);
			void setUniform3f(const char *name, const Math::vec3 &value);
			void setUniform4f(const char *name, const Math::vec4 &value);
			void setUniformMat4(const char *name, const Math::mat4 &matrix);

			void enable() const;
			void disable() const;
			
			GLuint m_shaderID;

		private:
			inline GLint getUniformLocation(const char *name);

			const GLchar* m_vertPath;
			const GLchar* m_fragPath;
		};
		
		/////////////////////////////////////////////////////////////////////////////////////
	}
}

#endif