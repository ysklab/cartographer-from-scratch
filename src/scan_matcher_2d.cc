#include "scan_matcher_2d.h"

namespace cart {

int RealTimeScanMatcher2D::Score(const Eigen::Matrix2Xd& scan, const Submap2D& map,
                         const Eigen::Affine2d& pose) {
  Eigen::Matrix2Xd aligned_scan = pose * scan;
  int s = 0;
  for (int c = 0; c < aligned_scan.cols(); ++c) {
    Eigen::Vector2i cell_index = map.CellIndex(aligned_scan.col(c));
    if (map.Contains(cell_index)) {
      s += map.Value(cell_index);
    }
  }
  return s;
}

double RealTimeScanMatcher2D::Match(const Eigen::Matrix2Xd& scan, const Submap2D& map,
                            const Eigen::Affine2d& init_pose,
                            const SearchWindow& search_range,
                            Eigen::Affine2d* out_pose) {
  double r = map.resolution();
  double dmax = scan.colwise().norm().maxCoeff();
  dmax = std::max(dmax, 3 * r);  // in case of dmax is very small
  double delta_th = std::acos(1 - r * r / 2 / dmax / dmax);
  int linear_steps = std::ceil(search_range.linear / r);
  int angular_steps = std::ceil(search_range.angular / delta_th);

  double best_score = 0.0;
  Eigen::Affine2d best_pose = init_pose;
  for (int offset_x = -linear_steps; offset_x <= linear_steps; ++offset_x) {
    for (int offset_y = -linear_steps; offset_y <= linear_steps; ++offset_y) {
      for (int offset_th = -angular_steps; offset_th <= angular_steps;
           ++offset_th) {
        Eigen::Affine2d pose = init_pose;
        pose.rotate(offset_th * delta_th);
        pose.pretranslate(Eigen::Vector2d(offset_x, offset_y) * r);
        int score = Score(scan, map, pose);
        if (score > best_score) {
          best_score = score;
          best_pose = pose;
        }
      }
    }
  }
  *out_pose = best_pose;
  return best_score / scan.cols();
}

}  // namespace cart
