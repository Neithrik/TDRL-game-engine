#include "application.h"

#include <iostream>

namespace tdrl {

Application::Application() {}

Application::~Application() {}

void Application::Run() {
  std::cout << "Hello World inside Application::Run()" << std::endl;
}

} // namespace tdrl