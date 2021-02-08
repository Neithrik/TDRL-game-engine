#pragma once

namespace tdlr {

class Application {
public:
  Application();
  ~Application();

  void Run();
};

// To be defined in the client.
Application *CreateApplication();

} // namespace tdlr