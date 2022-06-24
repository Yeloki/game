#pragma once

#include <algorithm>
#include "core.hpp"
#include "map.hpp"
#include <cmath>
#include "window.hpp"
#include "assets_manager.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include "logger.hpp"
#include <iostream>


using namespace graphic;

namespace core {


  class Camera {
  public:
    Camera() {
      m_scale = 0;
      m_view = Window::getWindow()->getRenderWindow().getDefaultView();
      m_view.move(-m_view.getSize().x / 2, -m_view.getSize().y / 2);
      Window::getWindow()->getRenderWindow().setView(m_view);
    }

    void update(const sf::Event &event) {
      std::cout << "View center: " << m_view.getCenter() << std::endl;
      if (event.type == sf::Event::MouseButtonPressed) { // camera movement
        m_mouse_pos = {event.mouseButton.x, event.mouseButton.y};
        m_is_mouse_pressed = true;
      } else if (event.type == sf::Event::MouseButtonReleased) {
        m_is_mouse_pressed = false;
      } else if (event.type == sf::Event::MouseMoved && m_is_mouse_pressed) {
        float x_move_on = (m_mouse_pos.x - event.mouseMove.x) * pow(2, -m_scale);
        float y_move_on = (m_mouse_pos.y - event.mouseMove.y) * pow(2, -m_scale);
        m_view.move(x_move_on, y_move_on);
        m_mouse_pos = {event.mouseMove.x, event.mouseMove.y};
        applyToWindow();
      } else if (event.type == sf::Event::MouseWheelMoved) { // camera zoom
        if (event.mouseWheel.delta > 0 && min_scale > m_scale ||
            event.mouseWheel.delta < 0 && max_scale < m_scale) { // if zoom available

          sf::Vector2f w_size = static_cast<sf::Vector2f>(Window::getWindow()->getRenderWindow().getSize());
          double delta_x = event.mouseWheel.x - w_size.x / 2;
          double delta_y = event.mouseWheel.y - w_size.y / 2;
          std::cout << "Delta X: " << delta_x << std::endl;
          double x_move_on = (delta_x * (1 - pow(2, -event.mouseWheel.delta * scale_step))) * pow(2, -m_scale);
          double y_move_on = (delta_y * (1 - pow(2, -event.mouseWheel.delta * scale_step))) * pow(2, -m_scale);

          m_scale += event.mouseWheel.delta * scale_step;
          m_view.zoom(pow(2, -event.mouseWheel.delta * scale_step));
          m_view.move(x_move_on, y_move_on);
          applyToWindow();
        }
      }
    }

    void applyToMap(Map *game_map) {
      m_game_map = game_map;
    }

  private:
    void applyToWindow() {
      correctPosition();
      Window::getWindow()->getRenderWindow().setView(m_view);
    }


    void correctPosition() {
      sf::Vector2f center = m_view.getCenter();
      sf::Vector2f map_px_size = m_game_map->getMapPXSize();
      m_view.setCenter(std::min(std::max(center.x ,-map_px_size.x / 2), map_px_size.x / 2),
                       std::min(std::max(center.y ,-map_px_size.y / 2), map_px_size.y / 2));
    }

    // min val = -5, max val = 5
    static constexpr double min_scale{1};
    static constexpr double max_scale{-1};
    static constexpr double scale_step{0.2};
    double m_scale = 0;
    sf::View m_view;
    sf::Vector2i m_mouse_pos;
    bool m_is_mouse_pressed{false};
    Map* m_game_map= nullptr;
  };
}