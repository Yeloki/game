#include "engine/window.hpp"
#include "engine/assets_manager.hpp"

using namespace graphic;
using namespace core;

int main() {
  Window::init("Test", {1920, 1080});
  AssetsManager::init("gamedata/assets/");

  while (!graphic::Window::getWindow()->isDone()) {
    Window::getWindow()->beginDraw();
    sf::Event event{};
    while (Window::getWindow()->pollEvent(event)) {
      Window::getWindow()->update(event);
    }
    Window::getWindow()->endDraw();
  }
  Window::destroyWindow();
  return 0;
}