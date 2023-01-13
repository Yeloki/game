#pragma once

#include <iostream>
#include <set>
#include <json.hpp>
#include <utility>
#include "core.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include "runtime_config.hpp"
#include <array>
//#include <BS_thread_pool.hpp>

namespace core {

std::ostream &operator<<(std::ostream &os, const sf::Vector2f &v) {
  os << "{x: " << v.x << ", y: " << v.y << "}";
  return os;
}

class Block {
 public:

  Block() {
    m_type = "stone";
  }

  explicit Block(const std::string &b_t) {
    m_type = b_t;
  }

  const std::string &getType() const {
    return m_type;
  }

  const sf::Sprite &getSprite() const {
    return m_sprite;
  }

  void setSprite(const v2 &world_pos, int map_size, int px_block_size) {
    m_size = px_block_size;

    v2 fix;
    if (map_size % 2 == 1) {
      fix = {px_block_size / 2, px_block_size / 2};
    }
    m_sprite.setPosition({static_cast<float>(world_pos.x * m_size - fix.x),
                          static_cast<float>(world_pos.y * m_size - fix.y)});

    m_sprite.setTexture(AssetsManager::getAssetsManager()[m_type]);
    const int thickness = 5;
    rect.setSize({static_cast<float>(m_size - thickness * 2), static_cast<float>(m_size - thickness * 2)});
    rect.setPosition(m_sprite.getPosition() + sf::Vector2f{thickness, thickness});
    rect.setFillColor({0, 0, 0, 0});
    rect.setOutlineThickness(5);
  }

  void draw() {
    graphic::Window::getWindow()->getRenderWindow().draw(m_sprite);
    if (is_alive) {
      rect.setOutlineColor(sf::Color::Green);
    } else {
      rect.setOutlineColor(sf::Color::Red);
    }
    graphic::Window::getWindow()->getRenderWindow().draw(rect);

  }

  void SetStatus(bool new_status) {
    is_alive = new_status;
  }

  bool IsAlive() const {
    return is_alive;
  }

 private:
  int m_size{0};
  sf::Sprite m_sprite{};
  std::string m_type;
  sf::RectangleShape rect;
  bool is_alive{false};
}; // end class Block

class Map {
 public:
  enum class gen_type {
    debug,
  };

  explicit Map(gen_type type) {
    m_px_block_size = 64;
    switch (type) {
      case gen_type::debug: {
        m_size = 32;
        m_data = new Block[m_size * m_size * 2];

        for (int y(0); y < m_size; ++y) {
          for (int x(0); x < m_size; ++x) {

            const v2 world_pos = {x - m_size / 2, y - m_size / 2};
            m_data[0 * m_size * m_size + y * m_size + x]
                .setSprite(world_pos, m_size, m_px_block_size);
          }
        }
        for (int y(0); y < m_size; ++y) {
          for (int x(0); x < m_size; ++x) {
            const v2 world_pos = {x - m_size / 2, y - m_size / 2};
            m_data[1 * m_size * m_size + y * m_size + x]
                .setSprite(world_pos, m_size, m_px_block_size);
          }
        }
        m_data[map_general_index * m_size * m_size + 3 * m_size + 1].SetStatus(true);
        m_data[map_general_index * m_size * m_size + 3 * m_size + 2].SetStatus(true);
        m_data[map_general_index * m_size * m_size + 3 * m_size + 3].SetStatus(true);

        m_data[map_general_index * m_size * m_size + 1 * m_size + 2].SetStatus(true);
        m_data[map_general_index * m_size * m_size + 2 * m_size + 3].SetStatus(true);

        m_data[map_general_index * m_size * m_size + (m_size - 1) * m_size + (m_size - 1)].SetStatus(true);
        m_data[map_general_index * m_size * m_size + (m_size - 1) * m_size + (m_size - 2)].SetStatus(true);
        m_data[map_general_index * m_size * m_size + (m_size - 2) * m_size + (m_size - 1)].SetStatus(true);
        m_data[map_general_index * m_size * m_size + (m_size - 2) * m_size + (m_size - 2)].SetStatus(true);
        break;
      }
    }

    m_map_px_size =
        sf::Vector2f{static_cast<float>(m_size * m_px_block_size),
                     static_cast<float>(m_size * m_px_block_size)};
    std::cout << "Map px size: " << m_map_px_size << std::endl;
  }

  void draw(const sf::View &view) {
    const auto size = view.getSize();
    const auto center = view.getCenter();

    const int lower_bound_y =
        std::max(static_cast<int>(((center.y - size.y) /
            static_cast<float>(m_px_block_size))) + m_size / 2, 0);
    const int upper_bound_y =
        std::min(static_cast<int>(((center.y + size.y) /
            static_cast<float>(m_px_block_size))) + m_size / 2, m_size);

    const int lower_bound_x =
        std::max(static_cast<int>(((center.x - size.x) /
            static_cast<float>(m_px_block_size))) + m_size / 2, 0);
    const int upper_bound_x =
        std::min(static_cast<int>(((center.x + size.x) /
            static_cast<float>(m_px_block_size))) + m_size / 2, m_size);

    for (int y(lower_bound_y); y < upper_bound_y; ++y) {
      for (int x(lower_bound_x); x < upper_bound_x; ++x) {
        m_data[map_general_index * m_size * m_size + y * m_size + x].draw();
      }
    }

  }

  [[nodiscard]] int NearAliveBlockCount(int x, int y) const {

    int ix = map_general_index, ms = m_size;
    const Block *map = m_data;
    const auto get_status = [ix, ms, map](int x, int y) {
      if (x >= 0 && x < ms && y >= 0 && y < ms)
        return map[ix * ms * ms + y * ms + x].IsAlive();
      return false;
    };

    int total_alive = 0;
    total_alive += get_status(x + 1, y);
    total_alive += get_status(x + 1, y + 1);
    total_alive += get_status(x, y + 1);
    total_alive += get_status(x - 1, y + 1);
    total_alive += get_status(x - 1, y);
    total_alive += get_status(x - 1, y - 1);
    total_alive += get_status(x, y - 1);
    total_alive += get_status(x + 1, y - 1);

    return total_alive;
  }

  void simulate() {

    const bool new_general_index = !map_general_index;
    for (int y(0); y < m_size; ++y) {
      for (int x(0); x < m_size; ++x) {
        const auto cnt = NearAliveBlockCount(x, y);

        if (m_data[map_general_index * m_size * m_size + y * m_size + x].IsAlive()) {
          m_data[new_general_index * m_size * m_size + y * m_size + x]
              .SetStatus(cnt == 2 || cnt == 3);

        } else {
          m_data[new_general_index * m_size * m_size + y * m_size + x]
              .SetStatus(cnt == 3);
        }
      }
    }
    map_general_index = new_general_index;
  }

  void update(const sf::Event &event, const sf::View view) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Right &&
        Config::Get()->GetGameStatus() == Config::Type::pause) {

      const auto point = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
      const auto cast_throw_view =
          graphic::Window::getWindow()->getRenderWindow().mapPixelToCoords(point, view);
      const auto map = m_map_px_size;
      auto res = map / 2 + cast_throw_view;
      const auto x = static_cast<int>(res.x) / 64;
      const auto y = static_cast<int>(res.y) / 64;

      if (x >= 0 && x < m_size && y >= 0 && y < m_size)
        mode = !m_data[map_general_index * m_size * m_size + y * m_size + x].IsAlive();

      flag = true;

    }
    if (event.type == sf::Event::MouseMoved && flag &&
        Config::Get()->GetGameStatus() == Config::Type::pause) {

      const auto point = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
      const auto cast_throw_view =
          graphic::Window::getWindow()->getRenderWindow().mapPixelToCoords(point, view);
      const auto map = m_map_px_size;
      auto res = map / 2 + cast_throw_view;
      const auto x = static_cast<int>(res.x) / 64;
      const auto y = static_cast<int>(res.y) / 64;
      if (x >= 0 && x < m_size && y >= 0 && y < m_size)
        m_data[map_general_index * m_size * m_size + y * m_size + x].SetStatus(mode);
    }
    if (event.type == sf::Event::MouseButtonReleased &&
        event.mouseButton.button == sf::Mouse::Right && flag) {
      flag = false;
    }
  }

  ~Map() {
    delete m_data;
  }

  [[nodiscard]] const sf::Vector2f &getMapPXSize() const {
    return m_map_px_size;
  }

 private:
  sf::Vector2f m_map_px_size;
  int m_px_block_size;
  int m_size;
  bool map_general_index{false};
  Block *m_data;
  bool flag{false};
  bool mode{false};
};

} // end namespace core
