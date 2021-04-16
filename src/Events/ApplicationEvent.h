#pragma once

#include "Event.h"

namespace tdrl {

	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(int width, int height) : width_(width), height_(height) {}

		EventType GetEventType() const override {
			return EventType::WindowResize;
		};

		const char* GetName() const override {
			return "WindowResizeEvent";
		};

		int GetCategoryFlags() const override {
			return int(EventCategory::EventCategoryApplication);
		};

	private:
		int width_;
		int height_;
	};

	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}

		EventType GetEventType() const override {
			return EventType::WindowClose;
		};

		const char* GetName() const override {
			return "WindowCloseEvent";
		};

		int GetCategoryFlags() const override {
			return int(EventCategory::EventCategoryApplication);
		};
	};
}