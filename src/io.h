#pragma once

#include <Eigen/Dense>
#include <nlohmann/json.hpp>

#include "submap_2d.h"

namespace cart {

nlohmann::json Vec2iToJson(const Eigen::Vector2i& vec2);
nlohmann::json Vec2dToJson(const Eigen::Vector2d& vec2);
nlohmann::json Scan2DToJson(const Eigen::Matrix2Xd& scan);
nlohmann::json Submap2DToJson(const Submap2D& m);

}  // namespace cart
