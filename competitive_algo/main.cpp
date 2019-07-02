#include <iostream>
#include <sstream>
#include "segment_tree.h"
#include "min_points_cover_for_segments.h"
#include "point_in_segments_count.h"

#ifdef _DEBUG
#endif

using namespace std;

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	algo::segments::point_in_segments_count_test();

	std::cin.get();
	return 0;
}