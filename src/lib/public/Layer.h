#pragma once

#include <string>

class Layer {
 public:
  Layer(const std::string &name = "Layer") : _name(name) {};
  virtual ~Layer() {};

  virtual void onAttach() {}
  virtual void onDetach() {}
  virtual void onUpdate() {}

  inline const std::string &getName() {
    return _name;
  }

 protected:
  std::string _name;
};