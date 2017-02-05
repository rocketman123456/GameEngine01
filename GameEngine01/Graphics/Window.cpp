#include "Window.h"

namespace GameEngine {
	namespace Graphics {
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//bool Window::m_keys[MAX_KEYS] = {};
		//bool Window::m_mouseButtons[MAX_MOUSE_BUTTONS] = {};
		//double Window::mx = 0;
		//double Window::my = 0;

		bool Window::isKeyPressed(unsigned int keycode) const {
			// TODO: Log this
			if (keycode > MAX_KEYS) 
				return false; 
			return m_keys[keycode];
		}

		bool Window::isMousePressed(unsigned int keycode) const {
			// TODO: Log this
			if (keycode > MAX_MOUSE_BUTTONS)
				return false;
			return m_mouseButtons[keycode];
		}

		void Window::getMousePosition(double &x, double &y) const {
			x = mx;
			y = my;
		}

		void Window::window_resize(GLFWwindow *window, int width, int height) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_width = width;
			win->m_height = height;
			glViewport(0, 0, width, height);
		}

		void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
			Window* win = (Window*) glfwGetWindowUserPointer(window);
			win->m_keys[key] = (action != GLFW_RELEASE);
		}

		void Window::mouse_button_callback(GLFWwindow * window, int key, int action, int mods) {
			Window* win = (Window*) glfwGetWindowUserPointer(window);
			win->m_mouseButtons[key] = (action != GLFW_RELEASE);
		}

		void Window::mouse_position_callback(GLFWwindow * window, double x, double y) {
			Window* win = (Window*) glfwGetWindowUserPointer(window);
			win->mx = x;
			win->my = y;
		}
		
		Window::Window(const char * name, int width, int height):
			m_name(name), m_width(width), m_height(height) {
			// initialize the buttons
			for (int i = 0; i < MAX_KEYS; ++i) {
				m_keys[i] = false;
			}
			for (int i = 0; i < MAX_MOUSE_BUTTONS; ++i) {
				m_mouseButtons[i] = false;
			}
		}

		Window::~Window() {

		}

		bool Window::init() {
			// GLFW
			if (!glfwInit()) {
				std::cout << "Failed to initialize GLFW" << std::endl;
				return false;
			}
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			m_window = glfwCreateWindow(m_width, m_height, m_name, nullptr, nullptr);
			if (!m_window) {
				glfwTerminate();
				std::cout << "Failed to create GLDW window!" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_window);
			glfwSetWindowUserPointer(m_window, this);
			glfwSetWindowSizeCallback(m_window, window_resize);
			glfwSetKeyCallback(m_window, key_callback);
			glfwSetMouseButtonCallback(m_window, mouse_button_callback);
			glfwSetCursorPosCallback(m_window, mouse_position_callback);
			// GLFW end

			// GLEW
			if (glewInit() != GLEW_OK) {
				std::cout << "Failed to initialize GLEW" << std::endl;
				return false;
			}
			// GLEW end

			std::cout << "OpenGL Version " << glGetString(GL_VERSION) << std::endl;
			fp = fopen("DebugMatrix.txt", "wt+");
			if (fp == nullptr) {
				std::cout << "Failed to open debug print, program will continue." << std::endl;
			}
			return true;
		}

		bool Window::closed() {
			m_closed = glfwWindowShouldClose(m_window);
			return m_closed;
		}

		void Window::clear() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update() {
			GLenum error = glGetError();
			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error:" << (error) << std::endl;
			}

			glfwPollEvents();

			glfwSwapBuffers(m_window);
		}

		void Window::terminate() {
			glfwTerminate();
			fclose(fp);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}