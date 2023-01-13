#define DEBUG

#include "engine/window.hpp"
#include "engine/assets_manager.hpp"
#include "engine/camera.hpp"
#include "engine/logger.hpp"
#include "engine/runtime_config.hpp"

using namespace graphic;
using namespace core;

int main() {

  logger::init();
  Window::init("Test", {1920, 1080});
  AssetsManager::init("gamedata/assets/");
  Config::Get();
  Map map(Map::gen_type::debug);
  Camera camera;
  camera.applyToMap(&map);

  bool f = false;
  sf::Clock clock;
  float last_render = 0;
  while (!graphic::Window::getWindow()->isDone()) {

    Window::getWindow()->beginDraw();
    sf::Event event{};

    while (Window::getWindow()->pollEvent(event)) {
      Window::getWindow()->update(event);
      camera.update(event);
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Space) {
        f = true;
      }
      if (event.type == sf::Event::KeyReleased && f &&
          event.key.code == sf::Keyboard::Space) {
        std::cout << "upd" << std::endl;
        map.simulate();
        f = false;
        switch (Config::Get()->GetGameStatus()) {
          case Config::Type::play: {
            Config::Get()->SetGameStatus(Config::Type::pause);
            break;
          }
          case Config::Type::pause: {
            Config::Get()->SetGameStatus(Config::Type::play);
            break;
          }
        }
        last_render = clock.getElapsedTime().asSeconds();
      }

    }

    camera.draw();
    Window::getWindow()->endDraw();

    if (Config::Get()->GetGameStatus() == Config::Type::play
        && clock.getElapsedTime().asSeconds() - last_render > 1.0 / 10) {
      last_render = clock.getElapsedTime().asSeconds();

      map.simulate();
    }

  }
  Window::destroyWindow();
  return 0;
}