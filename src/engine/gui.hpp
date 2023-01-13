#pragma once
#include <string>
#include <fstream>
#include <json.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "window.hpp"
#include "assets_manager.hpp"
namespace core {

class Label {
 public:
  Label(const sf::Font &font, const sf::Vector2f &pos, int size) {
    mText = sf::Text(L"", font, size);
    mText.setPosition(pos);
    mText.setFillColor(sf::Color::Black);
  }

  void SetText(const std::wstring &text) {
    std::vector<size_t> repl, tmp;
    std::wstring res(text);
    size_t d = 0;
    size_t l = 0;
    for (size_t i(0); i < text.size(); ++i)
      if (res[i] == L' ')
        tmp.push_back(i);
    for (auto &k: tmp) {
      if ((k - d >= 60 && k - d <= 65)) {
        repl.push_back(k);
        d = k;
        l = k;
      } else if (k - d > 65) {
        repl.push_back(l);
        d = l;
        l = k;
      } else {
        l = k;
      }
    }
    for (size_t i: repl)
      res[i] = L'\n';
    mText.setString(res);
  }

  void Draw() {
    graphic::Window::getWindow()->getRenderWindow().draw(mText);
  }

 private:
  sf::Text mText;
};

class Button {
  enum class Type {
    Normal,
    Selected,
    Triggered,
    Pressed
  };

 public:

  Button(const sf::Vector2f &pos_u,
         const sf::Vector2f &size) {
    state = Type::Normal;
    isActive = false;
    isSelected = false;
    pos = pos_u;
    size_ = size;
    flag = false;
  }

  bool IsClicked() {
    if (state == Type::Pressed) {
      Deactivate();
      return true;
    }
    return false;
  }

  void Draw() {
    switch (state) {
      case Type::Normal: sprite_.setTexture(common);
        break;
      case Type::Selected: sprite_.setTexture(triggered);
        break;
      case Type::Triggered:
      case Type::Pressed: sprite_.setTexture(clicked);
        break;
    }
    graphic::Window::getWindow()->getRenderWindow().draw(sprite_);
  }

  void Update(const sf::Event &event) {
    if (event.type == sf::Event::EventType::MouseMoved) {
      auto m_pos = event.mouseMove;

      const auto x_collide = (pos.x <= m_pos.x && m_pos.x <= (pos.x + size_.x));
      const auto y_collide = (pos.y <= m_pos.y && m_pos.y <= (pos.y + size_.y));

      if (x_collide && y_collide)
        Select();
      else
        Deselect();
    } else if (event.type == sf::Event::MouseButtonPressed && isSelected && !flag) {
      flag = true;
      state = Type::Triggered;
    } else if (event.type == sf::Event::MouseButtonReleased && isSelected) {
      flag = false;
      Activate();
    }
  }
 private:
  void Select() {
    isSelected = true;
    if (state != Type::Pressed)
      state = Type::Selected;
  }

  void Deselect() {
    isSelected = false;
    if (state != Type::Pressed)
      state = Type::Normal;
  }

  void Activate() {
    isActive = true;
    state = Type::Pressed;
  }

  void Deactivate() {
    isActive = false;
    state = Type::Selected;
  }

  sf::Vector2f pos;
  sf::Vector2f size_;
  sf::Sprite sprite_{};
  bool isSelected;
  bool isActive;
  bool flag;
  Type state;

};

}