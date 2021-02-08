#include <iostream>

#include "tdlr.h"

class Pong : public tdlr::Application {
public:
  Pong() {}

  ~Pong() {}
};

tdlr::Application *tdlr::CreateApplication() { return new Pong(); }
