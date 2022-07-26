#include "io.h"

namespace cart {

nlohmann::json Vec2iToJson(const Eigen::Vector2i& vec2) {
  nlohmann::json j;
  j["x"] = vec2.x();
  j["y"] = vec2.y();
  return j;
}

nlohmann::json Vec2dToJson(const Eigen::Vector2d& vec2) {
  nlohmann::json j;
  j["x"] = vec2.x();
  j["y"] = vec2.y();
  return j;
}

nlohmann::json Scan2DToJson(const Eigen::Matrix2Xd& scan) {
  nlohmann::json j = nlohmann::json::array();
  for (int c = 0; c < scan.cols(); ++c) {
    j.push_back(Vec2dToJson(scan.col(c)));
  }
  return j;
}

nlohmann::json Submap2DToJson(const Submap2D& m) {
  nlohmann::json j;
  j["origin"] = Vec2dToJson(m.origin());
  j["size"] = Vec2iToJson(m.size());
  j["resolution"] = m.resolution();
  j["data"] = nlohmann::json::array();
  for (int x = 0; x < m.size().x(); ++x) {
    for (int y = 0; y < m.size().y(); ++y) {
      j["data"].push_back(m.Value({x, y}));
    }
  }
  return j;
}

}  // namespace cart
