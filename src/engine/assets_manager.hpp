#pragma once

#include <string>
#include <fstream>
#include <json.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace core {
// need add AM request class

class AssetsManager {
 public:
  static AssetsManager *init(const std::string &filename) {
    if (!instance)
      instance = new AssetsManager(filename);
    return instance;
  }

  static AssetsManager &getAssetsManager() {
    return (*instance); // if some problem - check this
  }

  sf::Texture &operator[](const std::string &texture_name) {
    return m_texture_data[texture_name];
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
      if (obj["type"] == "texture") {
        sf::Image img;
        m_texture_data[obj["name"]].loadFromFile(
            filename + static_cast<std::string>(obj["filename"]));
      }
    }
  }

  static AssetsManager *instance;
  std::unordered_map<std::string, sf::Texture> m_texture_data;
};

AssetsManager *AssetsManager::instance = nullptr;
}