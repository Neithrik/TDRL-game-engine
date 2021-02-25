#include "WindowsWindow.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace tdrl {

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Size = props.Size;
		m_Data.Gran = props.Gran;

		TDRL_CORE_INFO("Initializing window {0} ({1} {2})", props.Title, props.Size, props.Gran);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			TDRL_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(
			(int)props.Size, (int)props.Size, props.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		glewInit();

		// Set GLFW callbacks.
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowResizeEvent event(width, height);

			data.EventCallback(event);
			data.Size = width;
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
				break;
			case GLFW_REPEAT:
				break;
			}
		});

	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		for (int x = 0; x < m_Data.Gran; x++) {
			for (int y = 0; y < m_Data.Gran; y++) {

				float vertex_x = x * 0.02 - 1.0;
				float vertex_y = y * 0.02 - 1.0;

				glColor4f(x * 0.01, y * 0.01, 1, 1);
				glBegin(GL_QUADS);
				glVertex2d(vertex_x, vertex_y);
				glVertex2d(vertex_x + 0.02, vertex_y);
				glVertex2d(vertex_x + 0.02, vertex_y + 0.02);
				glVertex2d(vertex_x, vertex_y + 0.02);
				glEnd();
			}
		}

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

} // namespace tdrl