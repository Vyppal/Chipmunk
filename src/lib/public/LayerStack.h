#pragma once

// main libs
#include "Layer.h"

// std
#include <vector>
#include <functional>

class LayerStack {
 public:
  LayerStack() {}

  ~LayerStack() {
    for (Layer *layer : _layers) {
      layer->onDetach();
      delete layer;
    }
  };

  /**
   * Push layer onto stack (places it after the last layer pushed)
   */
  void pushLayer(Layer *layer) {
    _layers.emplace(_layers.begin() + _layerInsertIndex, layer);
		_layerInsertIndex++;
  }

  /**
   * Push overlay onto stack (places overlay at the end of the stack after all layers)
   * Overlays are always after layers. And are placed acordingly
   */
  void pushOverlay(Layer *overlay) {
    _layers.emplace_back(overlay);
  }

  /**
   * Delete a layer (shuffles stack afterwards)
   */
  void popLayer(Layer *layer) {
    auto it = std::find(_layers.begin(), _layers.begin() + _layerInsertIndex, layer);
    if (it != _layers.begin() + _layerInsertIndex) {
      layer->onDetach();
      _layers.erase(it);
      _layerInsertIndex--;
    }
  }

  /**
   * Delete overlay (shuffles stack afterwards)
   */
  void popOverlay(Layer *overlay) {
    auto it = std::find(_layers.begin() + _layerInsertIndex, _layers.end(), overlay);
		if (it != _layers.end()) {
			overlay->onDetach();
			_layers.erase(it);
		}
  }

  /**
   * Return the beginning layer of the layer stack
   */
  std::vector<Layer*>::iterator begin() {
    return _layers.begin();
  }

  /**
   * Returns the end layer of the layer stack
   */
  std::vector<Layer *>::iterator end() {
    return _layers.end();
  }

  std::vector<Layer *>::reverse_iterator rbegin() {
    return _layers.rbegin();
  }

  std::vector<Layer *>::reverse_iterator rend() {
    return _layers.rend();
  }

  std::vector<Layer *>::const_iterator begin() const {
    return _layers.begin();
  }

  std::vector<Layer *>::const_iterator end()	const {
    return _layers.end();
  }

  std::vector<Layer *>::const_reverse_iterator rbegin() const {
    return _layers.rbegin();
  }
  
  std::vector<Layer *>::const_reverse_iterator rend() const {
    return _layers.rend();
  }

 private:
  std::vector<Layer *> _layers;
  unsigned int _layerInsertIndex = 0;
};