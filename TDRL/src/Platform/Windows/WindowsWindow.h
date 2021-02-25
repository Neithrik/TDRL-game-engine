#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Core.h"
#include "Log.h"
#include "Window.h"

namespace tdrl {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetSize() const override { return m_Data.Size; }
		inline unsigned int GetGran() const override { return m_Data.Gran; }

		void SetEventCallback(EventCallbackFn event_callback) override {
			m_Data.EventCallback = event_callback;
		};

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

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

