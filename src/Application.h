#pragma once

#include <iostream>

#include "Core.h"
#include "Events/Event.h"
#include "GameObject.h"
#include "Window.h"

namespace tdrl {

class Application {
public:	
	enum class Key {
		DEFAULT,
		LEFT,
		RIGHT,
	};

	Application();
	virtual ~Application();

	void Run(bool train);

	void Train();

	void OnEvent(Event& e);

	void Exit() {
		m_Window->Exit();
	}

	Key last_key_;
private:
	virtual std::vector<GameObject*>* GetGameObjects(bool train) = 0;
	virtual void Reset() = 0;
	virtual void TrainStep() = 0;

	std::unique_ptr<Window> m_Window;
	bool m_Running = true;
};

// To be defined in the client.
Application *CreateApplication();

} // namespace tdrl
