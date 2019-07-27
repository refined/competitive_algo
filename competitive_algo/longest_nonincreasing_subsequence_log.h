#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>

#ifdef _DEBUG
#include "tests.h"
#endif

namespace algo::dynamic {
	using namespace std;

	inline tuple<int, vector<vector<size_t>>> get_all_length_subsequence_indexes(vector<int>& arr)
	{
		const size_t n = arr.size();
		vector<int> max_element_in_size; // maximum element available in subsequence with given size
		max_element_in_size.push_back(arr[0]);

		vector<vector<size_t>> length_subsequence_indexes(n, vector<size_t>()); // vector of all element indexes in subsequence with given size 
		length_subsequence_indexes[0].push_back(0);
		int max_size = 1;

		for (size_t i = 1; i < n; i++)
		{
			int item = arr[i];
			auto it = lower_bound(max_element_in_size.rbegin(), max_element_in_size.rend(), item);
			if (it == max_element_in_size.rbegin())
			{
				max_element_in_size.push_back(item);
				length_subsequence_indexes[max_element_in_size.size() - 1].push_back(i);
				max_size++;
			}
			else
			{
				--it;
				*it = item;
				const int it_index = distance(it, max_element_in_size.rend()) - 1;
				length_subsequence_indexes[it_index].push_back(i);
			}
		}

		return make_tuple(max_size, length_subsequence_indexes);
	}

	/// Дано целое число 1≤n≤105и массив A[1…n], содержащий неотрицательные целые числа, не превосходящие 109. 
	/// Найдите наибольшую невозрастающую подпоследовательность в A. 
	/// В первой строке выведите её длину k, во второй — её индексы 1≤i1<i2<…<ik≤n (таким образом, A[i1]≥A[i2]≥…≥A[in]).
	/// Решение: тут решение состоит в том, чтобы хранить все максимальные подпоследовательности которые могут получиться 
	/// и их индексы тоже. то есть массив, массивов, где индекс - размер макс подпоследовательности 
	/// Улучшение - можно не хранить все значения максимальные, достаточно хранить только самое большое числ
	inline void longest_nonincreasing_subsequence_log(std::istream& in, std::ostream& out)
	{
		size_t n; in >> n;
		vector<int> arr(n, 0);
		for (int& a : arr) in >> a;

		auto res = get_all_length_subsequence_indexes(arr);
		int max_length = std::get<0>(res); 
		auto length_subsequence_indexes = std::get<1>(res);
		out << max_length << endl;
		vector<int> answer;
		size_t last_index = *length_subsequence_indexes[max_length-1].rbegin();
		answer.push_back(last_index+1);

		for (int len = max_length-2; len >= 0; len--)
		{
			vector<size_t>& length_indexes = length_subsequence_indexes[len];
			for (auto it = length_indexes.rbegin(); it != length_indexes.rend(); ++it)
			{
				if (*it < last_index)
				{
					answer.push_back(*it + 1);
					last_index = *it;
					break;
				}
			}
		}
		reverse(answer.begin(), answer.end());
		for (int a : answer) out << a << " ";
	}

#ifdef _DEBUG
	inline int longest_nonincreasing_subsequence_log_test() {
		run_test_from_text(longest_nonincreasing_subsequence_log, "longest_nonincreasing_subsequence_test.txt");
#else
	int main() {
		ios_base::sync_with_stdio(false);
		cin.tie(0);
		longest_nonincreasing_subsequence_log(cin, cout);
#endif
		return 0;
	}
	}

