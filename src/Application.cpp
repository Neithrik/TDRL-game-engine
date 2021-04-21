#include "application.h"

#include <chrono>
#include <iostream>
#include <thread> 

#include "GameObject.h"
#include "Log.h"
#include "Window.h"
#include "Events/KeyEvent.h"

namespace tdrl {

	constexpr int FPS = 30;

#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));
	}

	Application::~Application() {}


	void Application::OnEvent(Event& e)
	{
		if (e.GetEventType() == EventType::KeyPressed) {
			KeyPressedEvent& kpe = dynamic_cast<KeyPressedEvent&>(e);
			switch (kpe.GetKey()) {
			case 263:
				last_key_ = Key::LEFT;
				break;
			case 262:
				last_key_ = Key::RIGHT;
				break;
			default:
				break;
			}
		}
	}

	ColorMap BuildColorMap(std::vector<GameObject*>* gameObjects) {
		ColorMap color_map;
		for (GameObject* gameObject : *gameObjects) {
			for (Coordinate coordinate : gameObject->GetCoordinates()) {
				color_map.insert({ coordinate, gameObject->GetColor() });
			}
		}
		return color_map;
	}

	void Application::Run(bool train) {
		int i = 0;
		while (m_Running) {
			i++;
			if (train && i > 10000) {
				return;
			}
			auto begin = std::chrono::high_resolution_clock::now();

			std::vector<GameObject*>* gameObjects = GetGameObjects(train);

			if (train) {
				TrainStep();
			}

			if (gameObjects == nullptr) {
				return;
			}

			if (!train) {
				last_key_ = Key::DEFAULT;
				ColorMap colorMap = BuildColorMap(gameObjects);
				m_Window->OnUpdate(colorMap);

				auto end = std::chrono::high_resolution_clock::now();
				auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
				auto frame_length = std::chrono::duration<float>(1.0f / FPS);
				auto remaining = std::chrono::duration_cast<std::chrono::nanoseconds>(frame_length - elapsed);
				std::this_thread::sleep_for(remaining);
			}
			// std::this_thread::sleep_for(std::chrono::duration<float>(5.0));
		}
	}

	void Application::Train() {

		for (int i = 0; i < 100000; i++) {
			if (i < 10 || (i < 100 && i % 10 == 0) || i % 50 == 0) {
				std::cout << "Training step: " << i << std::endl;
				Run(false);
			}
			else {
				Run(true);
			}
			Reset();
		}
		m_Window->Exit();
	}

} // namespace tdrl
