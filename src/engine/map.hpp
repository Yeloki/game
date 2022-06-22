#pragma once

#include <iostream>
#include <set>
#include <json.hpp>
#include <utility>
#include "core.hpp"
//#include <BS_thread_pool.hpp>

namespace core {


  class Block {
  public:

    Block() {
      m_type = "stone";
    }

    explicit Block(std::string b_t) {
      m_type = std::move(b_t);
    }

    const std::string &getType() const {
      return m_type;
    }

  private:
    std::string m_type;
  }; // end class Block

  class Chunk {
  public:

    explicit Chunk(int chunk_size) {
      m_chunk_size = chunk_size;
      m_data.resize(chunk_size, std::vector<Block>{static_cast<size_t>(chunk_size)});
    }

    v2 getChunkPosition() const {
      return m_pos;
    }

    Block &operator[](v2 pos) {
      int y = pos.y % static_cast<int>(m_chunk_size);
      y = (y + static_cast<int>(m_chunk_size)) % static_cast<int>(m_chunk_size);

      int x = pos.x % static_cast<int>(m_chunk_size);
      x = (x + static_cast<int>(m_chunk_size)) % static_cast<int>(m_chunk_size);

      return m_data[y][x];
    }

    const Block &operator[](v2 pos) const {
      int y = pos.y % static_cast<int>(m_chunk_size);
      y = (y + static_cast<int>(m_chunk_size)) % static_cast<int>(m_chunk_size);

      int x = pos.x % static_cast<int>(m_chunk_size);
      x = (x + static_cast<int>(m_chunk_size)) % static_cast<int>(m_chunk_size);

      return m_data[y][x];
    }

  private:
    v2 m_pos;
    int m_chunk_size;
    std::vector<std::vector<Block>> m_data;
  }; // end class Chunk


  class Map {
  public:
    explicit Map(int size, int chunk_size) {
      m_size = size;
      m_chunk_size = chunk_size;
      m_data.resize(size * 2 + 1, std::vector<Chunk>{static_cast<size_t>(size * 2 + 1), Chunk{chunk_size}});
    };

    void loadMap(const std::string &filename) {}

    void saveMap(const std::string &filename) {}

    void generateMap(int map_size, int chunk_size) {}

    Chunk &operator[](v2 pos) {
      int y = pos.y / static_cast<int>(m_size);
      y = (y + static_cast<int>(m_size)) / static_cast<int>(m_size);

      int x = pos.x / static_cast<int>(m_size);
      x = (x + static_cast<int>(m_size)) / static_cast<int>(m_size);

      return m_data[y][x];
    }

    const Chunk &operator[](v2 pos) const {
      int y = pos.y / static_cast<int>(m_size);
      y = (y + static_cast<int>(m_size)) / static_cast<int>(m_size);

      int x = pos.x / static_cast<int>(m_size);
      x = (x + static_cast<int>(m_size)) / static_cast<int>(m_size);

      return m_data[y][x];
    }

  private:
    int m_size;
    int m_chunk_size;

    std::vector<std::vector<Chunk>> m_data;
  }; // end class Map

} // end namespace core