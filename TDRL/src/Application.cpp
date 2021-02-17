#include "application.h"

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace tdrl {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {}

	void Application::Run() {
		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

} // namespace tdrl
