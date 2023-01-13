#pragma once

namespace core {

class Config {
 public:
  enum class Type {
    play,
    pause,

  };
  [[nodiscard]] Type GetGameStatus() const {
    return status;
  }

  void SetGameStatus(Type new_status) {
    status = new_status;
  }

  static Config *Get() {
    if (!instance_) {
      instance_ = new Config();
    }
    return instance_;
  }

 private:
  Config() {
    status = Type::pause;
  };
  Type status;
 protected:
  static Config *instance_;
};

Config *Config::instance_ = nullptr;

}