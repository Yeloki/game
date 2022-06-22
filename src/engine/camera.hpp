#pragma once

#include "core.hpp"
#include <SFML/Window/Event.hpp>

namespace core {


  class Camera { // ?? maybe It will be main (character) class ??
    // on this step I don't know how to do that)
  public:
    Camera() = default;

    void update(const sf::Event &event) {

    }

  private:
    int scale = 0; // ?? if < 0 then zoom out, else zoom in ??
    v2 center{0, 0};
  };
}