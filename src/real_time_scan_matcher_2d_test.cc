#include "real_time_scan_matcher_2d.h"

#include <cmath>
#include <fstream>
#include <iostream>

#include <gtest/gtest.h>
#include <Eigen/Dense>

#include "io.h"
#include "submap_2d.h"

namespace cart {

TEST(RealTimeScanMatcher2D, Match) {
  Submap2D map(Eigen::Array2i(10, 10), Eigen::Array2d(0.0, 0.0), 0.1);
  Eigen::Matrix2Xd scan(2, 9);
  // clang-format off
  scan << 0.1, 0.2, 0.3, 0.4, 0.5, 0.5, 0.5, 0.5, 0.5,
          0.5, 0.5, 0.5, 0.5, 0.5, 0.4, 0.3, 0.2, 0.1;
  // clang-format on
  Eigen::Affine2d real_pose = Eigen::Affine2d::Identity();
  real_pose.pretranslate(Eigen::Vector2d(0.05, 0.05));

  for (int c = 0; c < scan.cols(); ++c) {
    map.SetValue(map.CellIndex(real_pose * scan.col(c)), 100);
  }

  Eigen::Affine2d init_pose = Eigen::Affine2d::Identity();
  init_pose.pretranslate(Eigen::Vector2d{0.3, 0.3});
  init_pose.rotate(M_PI / 6.0);

  SearchWindow search_window{5.0, M_PI / 2};
  Eigen::Affine2d out_pose;
  RealTimeScanMatcher2D matcher;
  double s = matcher.Match(scan, map, init_pose, search_window, &out_pose);
  EXPECT_NEAR(s, 100, 0.1);
  Eigen::Matrix2Xd aligned = out_pose * scan;

  std::ofstream ofs("/tmp/cart.json");
  EXPECT_TRUE(ofs.is_open());

  ofs << Scan2DToJson(init_pose * scan) << std::endl;
  ofs << Submap2DToJson(map) << std::endl;
  ofs << Scan2DToJson(out_pose * scan) << std::endl;
}

}  // namespace cart

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
