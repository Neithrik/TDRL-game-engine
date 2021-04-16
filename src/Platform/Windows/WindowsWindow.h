#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "src/Log.h"
#include "src/Window.h"

namespace tdrl {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate(ColorMap color_map) override;

		void Exit() {
			Shutdown();
		}

		inline unsigned int GetSize() const override { return m_Data.Size; }
		inline unsigned int GetGran() const override { return m_Data.Gran; }

		void SetEventCallback(EventCallbackFn event_callback) override {
			m_Data.EventCallback = event_callback;
		};

	private:
		virtual void Init(const WindowProps& props);
		void Shutdown()
		{
			glfwDestroyWindow(m_Window);
		}

		struct WindowData {
			std::string Title;
			unsigned int Size, Gran;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		GLFWwindow* m_Window;
		WindowData m_Data;
	};

} // namespace tdrl

