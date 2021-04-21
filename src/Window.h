#pragma once

#include <map>
#include <functional>

#include "Events/Event.h"
#include "Core.h"
#include "GameObject.h"

namespace tdrl {

	using ColorMap = std::map<Coordinate, GameObject::Color>;

	struct WindowProps
	{
		std::string Title;
		unsigned int Size;
		unsigned int Gran;

		WindowProps(const std::string& title = "TDRL",
					unsigned int size = 300,
					unsigned int gran = 20)
			: Title(title), Size(size), Gran(gran)
		{
		}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void Exit() = 0;

		virtual void OnUpdate(ColorMap color_map) = 0;

		virtual unsigned int GetSize() const = 0;
		virtual unsigned int GetGran() const = 0;

		virtual void SetEventCallback(EventCallbackFn event_callback) = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

} // namespace TDRL