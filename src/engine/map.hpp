#pragma once

#include <iostream>
#include <set>

namespace core {
  enum class block_type {
    STONE,
    WATER,
  };

  struct v2 {
    int x{0}, y{0};
  };

  class Block {
    v2 m_pos;
    block_type m_type;
  };

  class Chunk {
  public:

  private:
    v2 m_pos;
    static constexpr size_t m_chunk_size{32};
    Block m_data[32][32];
  };

  class Map {
  public:
    Map() = default;

  private:
    size_t m_size{128};
    std::set<Chunk> m_data{};
  };
} // end namespace core