#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

template<typename T>
std::ostream &operator<<(std::ostream &fs, const std::vector<T> &v) {
  fs << '{';
  for (size_t i(0); i < v.size(); ++i)
    fs << std::setw(4) << v[i] << (i == v.size() - 1 ? "" : ", ");
  fs << '}';
  return fs;
}

class logger {
 private:
  static logger *instance;
  std::ofstream fout;
  int i = 0; // info
  int e = 0; // error
  int w = 0; // warning

  logger() {
    fout = std::ofstream("../core.log", std::ios_base::out);
  };

 public:
  static logger *init() {
    if (!instance)
      instance = new logger;
    return instance;
  }

  template<typename T>
  static void logInfo(const T &s) {
    (instance->fout) << "info #" << instance->i << ": " << s << std::endl;
    ++(instance->i);
  }

  template<typename T>
  static void logError(const T &s) {
    (instance->fout) << "error #" << instance->e << ": " << s << std::endl;
    ++(instance->e);
  }

  template<typename T>
  static void logWarning(const T &s) {
    (instance->fout) << "warning #" << instance->w << ": " << s << std::endl;
    ++(instance->w);
  }
};

logger *logger::instance = nullptr;