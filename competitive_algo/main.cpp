#include <iostream>
#include <sstream>
#include "segment_tree.h"
#include "min_points_cover_for_segments.h"

#ifdef _DEBUG
#endif

using namespace std;

int main() {

	int n; std::cin >> n;
	int k = 0;
	int sum = 0;
	std::vector<int> res;

	for (int i = 1; i <= n; i++) {
		sum += i;
		if (sum > n) {
			sum = sum - i;
			res[k - 1] = res[k - 1] + n - sum;
			break;
		}
		
		k++;
		res.push_back(i);
	}
	std::cout << k << "\n";
	for (int i : res) std::cout << i << " ";
	return 0;

	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	//algo::segments::min_points_cover_for_segments_test();

	//std::cin.get();
	//return 0;
}