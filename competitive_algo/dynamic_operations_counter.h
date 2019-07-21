#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#ifdef _DEBUG
#include "tests.h"
#endif

namespace algo::dynamic {
	using namespace std;

	inline vector<int> get_best_counts(int k)
	{
		vector<int> counts(k + 1, 0);

		for (size_t x = 2; x <= k; x++)
		{
			int count = counts[x - 1];
			if (x % 3 == 0) {
				count = min(count, counts[x / 3]);
			}
			if (x % 2 == 0) {
				count = min(count, counts[x / 2]);
			}
			counts[x] = count + 1;
		}
		return counts;
	}

	/// У вас есть примитивный калькулятор, который умеет выполнять всего три операции с текущим числом x: 
	/// заменить x на 2x, 3x или x+1. По данному целому числу 1≤n≤105 
	/// определите минимальное число операций k, необходимое, чтобы получить n из 1. 
	/// Выведите k и последовательность промежуточных чисел.
	inline int dynamic_operations_counter(std::istream& in, std::ostream& out) {
		int k; in >> k;
		vector<int> counts = get_best_counts(k);

		out << counts[k] << "\n";
		vector<int> res;

		while (k > 1)
		{
			res.push_back(k);
			int next_k = k - 1;
			int count = counts[k - 1];
			if (k % 3 == 0 && count > counts[k / 3]) {
				count = counts[k / 3];
				next_k = k / 3;
			}
			if (k % 2 == 0 && count > counts[k / 2]) {
				next_k = k / 2;
			}
			k = next_k;
		}
		res.push_back(1);

		for (auto it = res.rbegin(); it != res.rend(); ++it)
			out << *it << " ";

		return 0;
	}


#ifdef _DEBUG
	inline int dynamic_operations_counter_test() {
		run_test_from_text(dynamic_operations_counter, "dynamic_operations_counter_test.txt");
#else
	int main() {
		ios_base::sync_with_stdio(false);
		cin.tie(0);
		knapsack_get_max_value(cin, cout);
#endif
		return 0;
	}
}