#include "application.h"

#include <iostream>

#include "Log.h"

namespace tdrl {

#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));
	}

	Application::~Application() {}

	void Application::OnEvent(Event& e)
	{
		TDRL_CORE_INFO("{0}", e.ToString());
	}

	void Application::Run() {
		while (m_Running) {
			m_Window->OnUpdate();
		}
	}

} // namespace tdrl
