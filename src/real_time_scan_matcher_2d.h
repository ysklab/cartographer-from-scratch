#pragma once

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include "submap_2d.h"

namespace cart {

struct SearchWindow {
    double linear, angular;
};

class RealTimeScanMatcher2D {
 public:
  static double Match(const Eigen::Matrix2Xd& scan, const Submap2D& map,
               const Eigen::Affine2d& init_pose, const SearchWindow& search_range,
               Eigen::Affine2d* out_pose);

 private:
  static int Score(const Eigen::Matrix2Xd& scan, const Submap2D& map,
            const Eigen::Affine2d& pose);
};

}  // namespace cart
