#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace graphic {

class Window {
 public:
  static Window *init(const std::string &title, const sf::Vector2u &size) {
    if (!instance) {
      instance = new Window(title, size);
    }
    return instance;
  }

  static Window *getWindow() {
    return instance;
  }

  sf::RenderWindow &getRenderWindow() {
    return m_window;
  }

  static void destroyWindow() {
    delete instance;
    instance = nullptr;
  }

  void beginDraw() {
    m_window.clear(sf::Color::Black);
  }

  void endDraw() {
    m_window.display();
  }

  sf::Vector2u getWindowSize() {
    return m_window_size;
  }

  bool isDone() const {
    return m_is_done;
  }

  void doDone() {
    m_is_done = true;
  }

  bool isFullscreen() const {
    return m_is_fullscreen;
  }

  void update(const sf::Event &event) {
    if (event.type == sf::Event::Closed) {
      m_is_done = true;
    } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
      switchFullscreen();
    }
  }

  bool pollEvent(sf::Event &event) {
    return m_window.pollEvent(event);
  }

  void switchFullscreen() {
    m_is_fullscreen = !m_is_fullscreen;
    destroy();
    create();
  }

  Window() = delete;

 private:
  static Window *instance;
  sf::RenderWindow m_window;

  sf::Vector2u m_window_size;
  std::string m_window_title;
  bool m_is_done;
  bool m_is_fullscreen;

  Window(const std::string &l_title, const sf::Vector2u &l_size) {
    m_window_title = l_title;
    m_window_size = l_size;
    m_is_fullscreen = false;
    m_is_done = false;
    const auto style = (m_is_fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create({m_window_size.x, m_window_size.y, 32},
                    m_window_title, style);
  }

  void destroy() {
    m_window.close();
  }

  ~Window() {
    destroy();
  }

  void create() {
    const auto style = (m_is_fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create({m_window_size.x, m_window_size.y, 32},
                    m_window_title, style);
  }

};

Window *Window::instance = nullptr;
}