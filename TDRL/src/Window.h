#pragma once

#include <functional>

#include "Events/Event.h"
#include "Core.h"

namespace tdrl {

	struct WindowProps
	{
		std::string Title;
		unsigned int Size;
		unsigned int Gran;

		WindowProps(const std::string& title = "TDRL",
					unsigned int size = 720,
					unsigned int gran = 100)
			: Title(title), Size(size), Gran(gran)
		{
		}
	};

	class TDRL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetSize() const = 0;
		virtual unsigned int GetGran() const = 0;

		virtual void SetEventCallback(EventCallbackFn event_callback) = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

} // namespace TDRL