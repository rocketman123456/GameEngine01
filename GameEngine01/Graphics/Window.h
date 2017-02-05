#ifndef _WINDOW_
#define _WINDOW_

// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <iostream>

#include "../Profile/profile.h"

namespace GameEngine {
	namespace Graphics {
		/////////////////////////////////////////////////////////////////////////////////////////

	#define MAX_KEYS			1024
	#define MAX_MOUSE_BUTTONS	32

		struct MousePosition {
			double x, y;
		};

		class Window {
		public:
			Window(const char *name, int width, int height);
			~Window();

			bool init();
			bool closed();
			void clear() const;
			void update();
			void terminate();

			inline int getWidth() const { return m_width; }
			inline int getHeight() const { return m_height; }
			void getMousePosition(double &x, double &y) const;
			bool isKeyPressed(unsigned int keycode) const;
			bool isMousePressed(unsigned int keycode) const;

		private:
			static void window_resize(GLFWwindow *window, int width, int height);
			static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
			static void mouse_button_callback(GLFWwindow *window, int key, int action, int mods);
			static void mouse_position_callback(GLFWwindow *window, double x, double y);

			GLFWwindow *m_window;
			const char			*m_name;
			int					m_width;
			int					m_height;
			bool				m_closed;

			bool m_keys[MAX_KEYS];
			bool m_mouseButtons[MAX_MOUSE_BUTTONS];
			double mx;
			double my;

			// frame rate
			int					count = 0;
			float				fps;
			long				currTime;
			long				lastTime = 0;

			// Debug
			FILE *fp;
		};

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}

#endif
