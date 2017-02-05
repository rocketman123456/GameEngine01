/*
	rocketman 2017-1-24
*/

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>

#include "Graphics\Graphics.h"
#include "Graphics\Shader.h"
#include "Graphics\Window.h"
#include "Graphics\Renderer2d.h"
#include "Graphics\Renderable2d.h"
#include "Graphics\Simple2DRenderer.h"
#include "Graphics\Buffer\Buffer.h"
#include "Graphics\Buffer\IndexBuffer.h"
#include "Graphics\Buffer\VertexArray.h"
#include "Graphics\StaticSprite.h"

#include "TextBox\TextBox.h"
#include "Profile\profile.h"
#include "Profile\custom_time.h"
#include "Math\Math.h"
#include "utils\FileUtils.h"

int main(int argc, char* argv[]) {
	
	using namespace std;
	using namespace GameEngine;
	using namespace Graphics;
	using namespace Math;

#if 1
	Window window("GameEngine", 1280, 720);
	if (!window.init()) {
		return -1;
	}
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	Shader shader("ShaderOpenGL/shader.vert", "ShaderOpenGL/shader.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	shader.setUniform4f("color", vec4(0.8f, 0.1f, 0.5f, 1.0f));
	shader.setUniform2f("light_pos", vec2(4.0f, 1.0f));

	StaticSprite sprite00(5, 5, 4, 4, vec4(1, 0, 1, 1), shader);
	StaticSprite sprite01(3, 4, 4, 2, vec4(0, 1, 1, 1), shader);
	StaticSprite sprite02(2, 1, 2, 4, vec4(0, 0, 1, 1), shader);
	Simple2DRenderer renderer;
	
	sprite00.init();
	sprite01.init();
	sprite02.init();

	// initialize time and profile
	InitTime();
	ProfileInit(0, 500, 0, 300);

	while (!window.closed()) {
		window.clear();

		ProfileBegin("Main Loop");
		ProfileBegin("Draw Shape");

		shader.enable();
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2(x * 16.0f / 1280.0f, 9.0f - y * 9.0f / 720.0f));
		renderer.submit(&sprite00);
		renderer.submit(&sprite01);
		renderer.submit(&sprite02);
		renderer.flush();
		shader.disable();

		ProfileEnd("Draw Shape");
		ProfileBegin("Profile Draw");
		ProfileDraw();
		ProfileEnd("Profile Draw");
		ProfileEnd("Main Loop");

		ProfileDumpOutputToBuffer();

		window.update();
	}

	sprite00.terminate();
	sprite01.terminate();
	sprite02.terminate();
	
	window.terminate();
#endif

#if 0
	Graphics::RenderWindow renderer;
	renderer.Initialize();

	// initialize time and profiler
	InitTime();
	ProfileInit(0, 500, 0, 400);
	try {
		renderer.RenderLoop();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	renderer.Terminate();
#endif

	system("pause");
	return EXIT_SUCCESS;
}