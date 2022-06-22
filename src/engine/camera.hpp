#pragma once

#include <algorithm>
#include "core.hpp"
#include "map.hpp"
#include <cmath>
#include "window.hpp"
#include "assets_manager.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>

using namespace graphic;

namespace core {


  class Camera {
  public:
    Camera() {
      m_size = {60 + 1, 40 + 1};
      m_sprite_size = 128;
      m_scale = -2;
      m_sprite_map.resize(m_size.y, std::vector<sf::Sprite>{static_cast<size_t>(m_size.x)});
      m_sprite_map.shrink_to_fit();
      for (auto &c: m_sprite_map)
        c.shrink_to_fit();
//      for (int y(0); y < m_size.y; ++y) {
//        for (int x(0); x < m_size.x; ++x) {
//          m_sprite_map[y][x].setRect({})
//        }
//      }
    }


    void update(const sf::Event &event) {

    }

    void render(const Map &map) {
      for (int y(-m_size.y / 2); y < m_size.y / 2; ++y) {
        for (int x(-m_size.x / 2); x < m_size.x / 2; ++x) {
          const std::string &block_type = map[{x, y}][{x, y}].getType();
          m_sprite_map[y + m_size.y / 2][x + m_size.x / 2].setTexture(AssetsManager::getAssetsManager()[block_type]);
          m_sprite_map[y + m_size.y / 2][x + m_size.x / 2].setScale({powf(2, m_scale), powf(2, m_scale)});
        }
      }
    }

//    void draw() {
//      for (int y(0); y < m_size.y; ++y) {
//        for (int x(0); x < m_size.x; ++x) {
//          // wrong
//          Window::getWindow()->getRenderWindow().draw();
//        }
//      }
//    }

    void upscale() {
      m_scale = std::min(max_scale, m_scale + 1);
    }

    void downscale() {
      m_scale = std::max(min_scale, m_scale - 1);
    }

  private:
    // min val = -5, max val = 5
    static constexpr int min_scale{-2};
    static constexpr int max_scale{2};
    int m_scale = 0;
    v2 m_center{0, 0}; // from map
    std::vector<std::vector<sf::Sprite>> m_sprite_map;
    int m_sprite_size;
    v2 m_size;
  };
}