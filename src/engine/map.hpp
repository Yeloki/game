#pragma once

#include <iostream>
#include <set>
#include <json.hpp>
#include <utility>
#include "core.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
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
      if (map_size % 2 == 1)
        fix = {px_block_size / 2, px_block_size / 2};
      m_sprite.setPosition({static_cast<float>(world_pos.x * m_size - fix.x),
                            static_cast<float>(world_pos.y * m_size - fix.y)});
//      m_sprite.setOrigin(m_size, m_size);
      m_sprite.setTexture(AssetsManager::getAssetsManager()[m_type]);
      std::cout << "Sprite with WP: " << world_pos << " has px cords: " << m_sprite.getPosition() << std::endl;

      rect.setSize({static_cast<float>(m_size), static_cast<float>(m_size)});
      rect.setPosition(m_sprite.getPosition());
      rect.setFillColor({0, 0, 0, 0});
      rect.setOutlineThickness(2);
      rect.setOutlineColor(sf::Color::Red);
    }

    void draw() {

      graphic::Window::getWindow()->getRenderWindow().draw(m_sprite);
      graphic::Window::getWindow()->getRenderWindow().draw(rect);
    }

  private:
    int m_size;
    sf::Sprite m_sprite{};
    std::string m_type;
    sf::RectangleShape rect;
  }; // end class Block

  class Map {
  public:
    enum class gen_type {
      debug,
    };

    explicit Map(gen_type type) {
      m_px_block_size = 64;
      switch (type) {
        case gen_type::debug:
          m_size = 32;
          m_data = new Block[m_size * m_size];
          for (int y(0); y < m_size; ++y)
            for (int x(0); x < m_size; ++x)
              m_data[y * m_size + x].setSprite({x - m_size / 2, y - m_size / 2}, m_size, m_px_block_size);
          break;
      }
      m_map_px_size = static_cast<sf::Vector2f>(sf::Vector2i{m_size * m_px_block_size, m_size * m_px_block_size});
      std::cout << "Map px size: " << m_map_px_size << std::endl;
    }

    void draw() {
      for (int y(0); y < m_size; ++y)
        for (int x(0); x < m_size; ++x)
          m_data[y * m_size + x].draw();
    }

    ~Map() {
      delete m_data;
    }

    const sf::Vector2f &getMapPXSize() const {
      return m_map_px_size;
    }

  private:
    sf::Vector2f m_map_px_size;
    int m_px_block_size;
    int m_size;
    Block *m_data;
  };

} // end namespace core
