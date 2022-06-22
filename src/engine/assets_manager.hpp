#pragma once

#include <string>
#include <fstream>
#include <json.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace core {
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
      return m_data[texture_name];
    }

  private:
    AssetsManager(const std::string &filename) {
      loadFromFile(filename);
    }

    void loadFromFile(const std::string &filename) {
      nlohmann::json file;
      std::ifstream fin(filename + "assets.json");
      fin >> file;
      for (const auto &obj: file) {
        sf::Image img;
        m_data[obj["name"]].loadFromFile(filename + static_cast<std::string>(obj["filename"]));
      }
    }

    static AssetsManager *instance;
    std::map<std::string, sf::Texture> m_data;

  };

  AssetsManager *AssetsManager::instance = nullptr;
}