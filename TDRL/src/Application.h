#pragma once

#include <iostream>

#include "Core.h"
#include "Window.h"

namespace tdrl {

class TDRL_API Application {
public:
	Application();
	virtual ~Application();

	void Run();

private:
	std::unique_ptr<Window> m_Window;
	bool m_Running = true;
};

// To be defined in the client.
Application *CreateApplication();

} // namespace tdrl
