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

	inline vector<int> get_length_subsequence(vector<int>& arr)
	{
		size_t n = arr.size();
		vector<int> lengths(n, 1);

		for (size_t i = 1; i < n; i++)
		{
			int max_length = 0;
			for (size_t j = 0; j < i; j++)
			{
				if (arr[i] <= arr[j] && lengths[j] + 1 > max_length)
				{
					max_length = lengths[j]+1;
				}
			}
			lengths[i] = max_length;
		}
		return lengths;
	}

	inline vector<int> restore_answer(vector<int>& lengths, vector<int>& arr, int max_i)
	{
		vector<int> res;
		res.push_back(max_i+1);

		for(int i = max_i-1; i >= 0; --i)
		{
			if (lengths[i] == lengths[max_i]-1 && arr[i] >= arr[max_i])
			{
				max_i = i;
				res.push_back(max_i+1);
			}
		}
		reverse(res.begin(), res.end());
		return res;
	}

	/// Дано целое число 1≤n≤105и массив A[1…n], содержащий неотрицательные целые числа, не превосходящие 109. 
	/// Найдите наибольшую невозрастающую подпоследовательность в A. 
	/// В первой строке выведите её длину k, во второй — её индексы 1≤i1<i2<…<ik≤n (таким образом, A[i1]≥A[i2]≥…≥A[in]).
	inline void longest_nonincreasing_subsequence(std::istream& in, std::ostream& out)
	{
		size_t n; in >> n;
		vector<int> arr(n, 0);
		for (int& a : arr) in >> a;

		vector<int> lengths = get_length_subsequence(arr);
		int max = 0;
		int max_i = 0;

		for (size_t i = 0; i < lengths.size(); i++)
		{
			if (lengths[i] > max) {
				max = lengths[i];
				max_i = i;
			}
		}
		vector<int> answer = restore_answer(lengths, arr, max_i);

		out << max << endl;
		for (int a : answer) out << a << " ";
	}

#ifdef _DEBUG
	inline int longest_nonincreasing_subsequence_test() {
		run_test_from_text(longest_nonincreasing_subsequence, "longest_nonincreasing_subsequence_test.txt");
#else
	int main() {
		ios_base::sync_with_stdio(false);
		cin.tie(0);
		longest_nonincreasing_subsequence(cin, cout);
#endif
		return 0;
	}
}

