#pragma once

namespace core {

  struct v2 {
    int x{0}, y{0};
  };

  v2 operator+(const v2 &first, const v2 &second) {
    return {first.x + second.x, first.y + second.y};
  }

}