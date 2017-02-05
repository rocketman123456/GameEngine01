#include "Shader.h"

namespace GameEngine {
	namespace Graphics {
		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		Shader::Shader(const GLchar * _vertPath, const GLchar * _fragPath):
			m_vertPath(_vertPath), m_fragPath(_fragPath){
			m_shaderID = load();
		}

		Shader::~Shader() {
			
		}

		void Shader::deleteShader() {
			glDeleteProgram(m_shaderID);
		}

		GLuint Shader::load() {
			GLuint program = glCreateProgram();
			GLuint vert = glCreateShader(GL_VERTEX_SHADER);
			GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);

			std::string _vertSource = read_file(m_vertPath);
			std::string _fragSource = read_file(m_fragPath);
			const char *vertSource = _vertSource.c_str();
			const char *fragSource = _fragSource.c_str();

			glShaderSource(vert, 1, &vertSource, nullptr);
			glCompileShader(vert);
			GLint result;
			glGetShaderiv(vert, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				std::cout << "Vert Shader Compile Error!" << std::endl;
				GLint length;
				glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &length);
				std::vector<GLchar> error(length);
				glGetShaderInfoLog(vert, length, &length, &error[0]);
				std::cout << &error[0] << std::endl;
				glDeleteShader(vert);
				return 0;
			}

			glShaderSource(frag, 1, &fragSource, nullptr);
			glCompileShader(frag);
			glGetShaderiv(frag, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				std::cout << "Frag Shader Compile Error!" << std::endl;
				GLint length;
				glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &length);
				std::vector<GLchar> error(length);
				glGetShaderInfoLog(vert, length, &length, &error[0]);
				std::cout << &error[0] << std::endl;
				glDeleteShader(frag);
				return 0;
			}

			glAttachShader(program, vert);
			glAttachShader(program, frag);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vert);
			glDeleteShader(frag);

			return program;
		}

		GLint Shader::getUniformLocation(const char * name) {
			return glGetUniformLocation(m_shaderID, name);
		}

		void Shader::setUniform1f(const char * name, const float value) {
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniform1i(const char * name, const int value) {
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::setUniform2f(const char * name, const Math::vec2 & value) {
			glUniform2f(getUniformLocation(name), value.x, value.y);
		}

		void Shader::setUniform3f(const char * name, const Math::vec3 & value) {
			glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
		}

		void Shader::setUniform4f(const char * name, const Math::vec4 & value) {
			glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
		}

		void Shader::setUniformMat4(const char * name, const Math::mat4 & matrix) {
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}

		void Shader::enable() const {
			glUseProgram(m_shaderID);
		}

		void Shader::disable() const {
			glUseProgram(0);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}