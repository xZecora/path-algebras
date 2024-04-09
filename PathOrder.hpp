#pragma once

#include "Path.hpp"
#include "util.hpp"

enum relations { EQ, LT, GT };

class PathOrder {
  private:
    WeightVector pathWeight(Path path);
    int comparePaths(Path path1, Path path2);
};
