#include "segment_tree.h"
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <tuple> 
#include "tests.h"

void run_segment_tree_test(std::istream& in, std::ostream& out)
{
	size_t n; in >> n;
	vector<int> arr(n,0);
	for (size_t i = 0; i < n; i++) in >> arr[i];
	algo::SegmentTree tree(arr);

	int l, r; in >> l >> r;

	auto[min, max] = tree.get_min_max(l, r);
	out << min << " " << max;
}

int segment_tree_testing() {
	tests::run_test_from_text(run_segment_tree_test, "segment_tree_testing.txt");
	return 0;
}
