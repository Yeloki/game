#pragma once

#include <string>
#include <fstream>
#include <json.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace core {

struct ButtonStyle {
  std::string type;
  std::string common;
  std::string hover;
  std::string pressed;
};

// need add AM request class

class AssetsManager {
 public:
  static AssetsManager *init(const std::string &filename) {
    if (!instance_)
      instance_ = new AssetsManager(filename);
    return instance_;
  }

  static AssetsManager &getAssetsManager() {
    return (*instance_); // if some problem - check this
  }

  sf::Texture &operator[](const std::string &texture_name) {
    return texture_data_[texture_name];
  }

 private:
  explicit AssetsManager(const std::string &filename) {
    loadFromFile(filename);
  }

  void loadFromFile(const std::string &filename) {
    nlohmann::json file;
    std::ifstream fin(filename + "assets.json");
    fin >> file;

    for (const auto &obj: file) {
      sf::Image img;
      texture_data_[obj["name"]].loadFromFile(
          filename + static_cast<std::string>(obj["filename"]));
    }
  }

  static AssetsManager *instance_;
  std::unordered_map<std::string, sf::Texture> texture_data_;
  std::unordered_map<std::string, sf::Texture> button_styles_;
};

AssetsManager *AssetsManager::instance_ = nullptr;
}