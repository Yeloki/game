#pragma once

#include <ios>

namespace core {

  struct v2 {
    int x{0}, y{0};
  };

  v2 operator+(const v2 &first, const v2 &second) {
    return {first.x + second.x, first.y + second.y};
  }

  v2 &operator+=(v2 &first, const v2 &second) {
    first = first + second;
    return first;
  }

  std::ostream &operator<<(std::ostream &os, v2 v) {
    os << "{x: " << v.x << ", y: " << v.y << "}";
    return os;
  }


  template<typename T>
  T sign(T val) {
    if (val < 0)
      return -1;
    else if (val > 0)
      return 1;
    return 0;
  }

}