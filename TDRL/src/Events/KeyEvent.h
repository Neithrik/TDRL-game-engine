#pragma once

#include "Event.h"

namespace tdrl {

	class KeyPressedEvent : public Event {
	public:
		KeyPressedEvent(int key, int repeat_count) : key_(key), repeat_count_(repeat_count) {}

		EventType GetEventType() const override {
			return EventType::KeyPressed;
		};

		const char* GetName() const override {
			return "KeyPressedEvent";
		};

		int GetCategoryFlags() const override {
			return int(EventCategory::EventCategoryKeyboard);
		};

	private:
		int key_;
		int repeat_count_;
	};

	class KeyReleasedEvent : public Event {
	public:
		KeyReleasedEvent(int key, int repeat_count) : key_(key), repeat_count_(repeat_count) {}

		EventType GetEventType() const override {
			return EventType::KeyReleased;
		};

		const char* GetName() const override {
			return "KeyReleasedEvent";
		};

		int GetCategoryFlags() const override {
			return int(EventCategory::EventCategoryKeyboard);
		};

	private:
		int key_;
		int repeat_count_;
	};
}
