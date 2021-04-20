#pragma once

#include <iostream>

#include "Application.h"
#include "Log.h"

extern tdrl::Application *tdrl::CreateApplication();

int main(int argc, char **argv) {
	tdrl::Log::Init();
	TDRL_CORE_WARN("Initialized log");
	int a = 5;
	TDRL_CORE_INFO("Hello Var={0}", a);

    auto game = tdrl::CreateApplication();
    game->Run();

    delete game;
}
