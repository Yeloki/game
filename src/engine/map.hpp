#pragma once

#include <iostream>
#include <set>
#include <json.hpp>
#include "core.hpp"
//#include <BS_thread_pool.hpp>

namespace core {


  class Block {
  public:
    enum class BlockType {
      STONE,
      WATER,
    };

    Block() {
      m_type = BlockType::STONE;
    }

    explicit Block(BlockType type) {
      m_type = type;
    }

  private:
    BlockType m_type;
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

  private:
    int m_size;
    int m_chunk_size;

    std::vector<std::vector<Chunk>> m_data;
  }; // end class Map

} // end namespace core