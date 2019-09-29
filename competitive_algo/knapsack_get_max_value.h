#pragma once
#include <istream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iterator>
#include <iostream>

#ifdef _DEBUG
#include "tests.h"
#endif

namespace algo::dynamic {
	using namespace std;

	/// Первая строка входа содержит целые числа 1≤W≤104 и 1≤n≤300 — вместимость рюкзака и число золотых слитков. 
	/// Следующая строка содержит n целых чисел 0≤w1,…,wn≤105, задающих веса слитков. 
	/// Найдите максимальный вес золота, который можно унести в рюкзаке.
	inline int calculate_max_gold_weight(vector<int>&& gold_weights, int max_weight) {
		vector<vector<int>> D(max_weight + 1, vector<int>(gold_weights.size() + 1, 0));

		for (size_t i = 1; i <= gold_weights.size(); i++)
		{
			for (int w = 1; w <= max_weight; w++)
			{
				int wi = gold_weights[i - 1];
				if (w >= wi)
				{
					int max_without_wi = D[w - wi][i - 1] + wi;
					D[w][i] = max(D[w][i - 1], max_without_wi);
				} else
				{
					D[w][i] = D[w][i - 1];
				}				
			}
		}		

		return D[max_weight][gold_weights.size()];
	}

	inline void knapsack_get_max_value(std::istream& in, std::ostream& out)
	{
		int max_weight; in >> max_weight;
		int n; in >> n;

		vector<int> gold_weights(n, 0);
		for (size_t i = 0; i < n; i++) in >> gold_weights[i];

		int max_gold_weight = calculate_max_gold_weight(std::move(gold_weights), max_weight);
		out << max_gold_weight << std::endl;
	}


#ifdef _DEBUG
	inline int knapsack_get_max_value_test() {
		tests::run_test_from_text(knapsack_get_max_value, "knapsack_get_max_value_test.txt");
#else
	int main() {
		ios_base::sync_with_stdio(false);
		cin.tie(0);
		knapsack_get_max_value(cin, cout);
#endif
		return 0;
	}
}
