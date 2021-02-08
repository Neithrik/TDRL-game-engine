#pragma once

#include <iostream>

extern tdlr::Application *tdlr::CreateApplication();

int main(int argc, char **argv) {
  std::cout << "Hello World inside main()" << std::endl;
  auto pong = tdlr::CreateApplication();
  pong->Run();
  delete pong;
}