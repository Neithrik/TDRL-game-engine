#pragma once

#include <iostream>

#include "Core.h"

namespace tdrl {

class TDRL_API Application {
public:
  Application();
  virtual ~Application();

  void Run();
};

// To be defined in the client.
Application *CreateApplication();

} // namespace tdrl
