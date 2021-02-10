#include <iostream>

#include "Tdrl.h"

class Pong : public tdrl::Application {
public:
  Pong() {}

  ~Pong() {}
};

tdrl::Application *tdrl::CreateApplication() { return new Pong(); }
