#pragma once

#include <functional>

#include "Core.h"

namespace tdrl {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "TDRL",
					unsigned int width = 1280,
					unsigned int height = 720)
			: Title(title), Height(height), Width(width)
		{
		}
	};

	class TDRL_API Window
	{
	public:
		using EventCallbackFn = std::function<void()>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

} // namespace TDRL