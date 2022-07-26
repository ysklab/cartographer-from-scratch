#pragma once

#include <Eigen/Dense>
#include <cstdint>

namespace cart {

using ValueType = std::uint16_t;

class Submap2D {
 public:
  Submap2D(const Eigen::Vector2i& size, const Eigen::Vector2d& origin,
           double resolution, ValueType init_value = 0)
      : size_(size),
        origin_(origin),
        data_(MatType::Constant(size.x(), size.y(), init_value)),
        resolution_(resolution) {}
  ValueType Value(const Eigen::Vector2i& cell_index) const {
    return data_(cell_index.x(), cell_index.y());
  }
  void SetValue(const Eigen::Vector2i& cell_index, ValueType value) {
    data_(cell_index.x(), cell_index.y()) = value;
  }
  Eigen::Vector2i CellIndex(const Eigen::Vector2d& point) const {
    return ((point - origin_) / resolution_).array().floor().cast<int>();
  }
  double resolution() const { return resolution_; }
  Eigen::Vector2d origin() const { return origin_; }
  Eigen::Vector2i size() const { return size_; }
  bool Contains(const Eigen::Vector2i& cell_index) const {
    return (cell_index.array() >= Eigen::Array2i(0, 0)).all() &&
           (cell_index.array() < size_.array()).all();
  }

 private:
  using MatType = Eigen::Matrix<ValueType, Eigen::Dynamic, Eigen::Dynamic>;
  Eigen::Vector2i size_;
  Eigen::Vector2d origin_;
  MatType data_;
  double resolution_;
};

}  // namespace cart
