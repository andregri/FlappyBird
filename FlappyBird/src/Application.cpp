#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <chrono>
#include <thread>

#include <glm/glm.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/TestMenu.h"
#include "tests/TestHelloWorld.h"
#include "tests/TestTexture2D.h"
#include "tests/TestMVP.h"

#include "Error.h"
#include "Game.h"

#define global_variable static

// TODO: deal input without global variables
global_variable bool keys[65536];
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	keys[key] = (action != GLFW_RELEASE);
}

int main(void)
{
	int window_width = 1280;
	int window_height = 720;

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // I want core profile instead of compatibility profile.

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(window_width, window_height, "Flappy Bird", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	glfwSetWindowPos(window, ((*mode).width - window_width) / 2, ((*mode).height - window_height) / 2);
	glfwSetKeyCallback(window, key_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Initializr glew */
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, "Status: Using GL %s\n", glGetString(GL_VERSION));

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	const char* glsl_version = "#version 150";
	ImGui_ImplOpenGL3_Init(glsl_version);

	test::TestMenu test_menu;
	test_menu.RegisterTest<test::TestHelloWorld>("Hello test!");
	test_menu.RegisterTest<test::TestTexture2D>("Texture2D");
	test_menu.RegisterTest<test::TestMVP>("Matrices");

	Game game(window, keys);

	using namespace std::chrono;
	using Framerate = duration<steady_clock::rep, std::ratio<1, 60>>;
	auto next = steady_clock::now() + Framerate{ 1 };

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		game.OnUpdate();

		std::this_thread::sleep_until(next);
		next += Framerate{ 1 };

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/* Render here */
		GLCall(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		game.OnRender();

		test_menu.OnImGuiRender();
		game.OnImGuiRender();

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		
		/* Poll for and process events */
		glfwPollEvents();
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}