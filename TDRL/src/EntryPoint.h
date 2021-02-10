#pragma once

#include <iostream>

extern tdrl::Application *tdrl::CreateApplication();

int main(int argc, char **argv) {
  std::cout << "Hello World inside main()" << std::endl;
  auto pong = tdrl::CreateApplication();
  pong->Run();
  delete pong;
}