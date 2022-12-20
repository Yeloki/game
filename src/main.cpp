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

  bool f = false;
  bool play = false;
  sf::Clock clock;
  float last_render = 0;
  while (!graphic::Window::getWindow()->isDone()) {

    Window::getWindow()->beginDraw();
    sf::Event event{};

    while (Window::getWindow()->pollEvent(event)) {
      Window::getWindow()->update(event);
      camera.update(event);

      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        f = true;
      }
      if (event.type == sf::Event::KeyReleased && f && event.key.code == sf::Keyboard::Space) {
        std::cout << "upd" << std::endl;
        map.update();
        f = false;
        play = !play;
        last_render = clock.getElapsedTime().asSeconds();
      }

    }

    camera.draw();
    Window::getWindow()->endDraw();

    if (play && clock.getElapsedTime().asSeconds() - last_render > 1.0 / 4) {
      last_render = clock.getElapsedTime().asSeconds();
      std::cout << "updated" << std::endl;
      map.update();
    }

  }
  Window::destroyWindow();
  return 0;
}