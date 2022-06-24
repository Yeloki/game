#define DEBUG

#include "engine/window.hpp"
#include "engine/assets_manager.hpp"
#include "engine/camera.hpp"
#include "engine/logger.hpp"
using namespace graphic;
using namespace core;

int main() {
  logger::init();
  Window::init("Test", {1920, 1080});
  AssetsManager::init("gamedata/assets/");
  Map map(Map::gen_type::debug);
  Camera camera;
  camera.applyToMap(&map);
  while (!graphic::Window::getWindow()->isDone()) {
    Window::getWindow()->beginDraw();
    sf::Event event{};
    while (Window::getWindow()->pollEvent(event)) {
      Window::getWindow()->update(event);
      camera.update(event);
    }
    map.draw();
    Window::getWindow()->endDraw();
  }
  Window::destroyWindow();
  return 0;
}