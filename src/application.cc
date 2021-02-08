#include "src/application.h"

#include <iostream>

namespace tdlr {

Application::Application() {}

Application::~Application() {}

void Application::Run() {
  std::cout << "Hello World inside Application::Run()" << std::endl;
}

} // namespace tdlr