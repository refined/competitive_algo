#pragma once
//#include <fstream>
#include <algorithm>
//#include <cmath>
//#include <numeric>

#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <limits>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <random>

namespace algo::search {
	using namespace std;

	int count_same_hash(const vector<int>& arr1, const vector<int>& arr2) {
		const vector<int>& small = arr1.size() < arr2.size() ? arr1 : arr2;
		const vector<int>& big = arr1.size() < arr2.size() ? arr2 : arr1;
		unordered_set<int> hash(small.begin(), small.end());
		std::cout << "current max_load_factor: " << hash.max_load_factor() << std::endl;
		std::cout << "current size: " << hash.size() << std::endl;
		std::cout << "current bucket_count: " << hash.bucket_count() << std::endl;
		std::cout << "current load_factor: " << hash.load_factor() << std::endl;

		int counter = 0;
		for (int el : big)
		{
			if (hash.find(el) != hash.end())
			{
				counter++;
			}
		}
		return counter;
	}

	template <typename SortT>
	int count_same_using_sort(const vector<int>& arr1c, const vector<int>& arr2c, SortT sort) {
		vector<int> arr1(arr1c.begin(), arr1c.end());
		vector<int> arr2(arr2c.begin(), arr2c.end());
		sort(arr1, arr2);
		auto it1 = arr1.begin();
		auto it2 = arr2.begin();
		int counter = 0;

		while (it1 != arr1.end() && it2 != arr2.end())
		{
			if (*it1 == *it2)
			{
				counter++;
				++it1;
				++it2;
			}
			else if (*it1 < *it2) ++it1;
			else ++it2;
		}

		return counter;
	}



	int count_same_quick_sort(const vector<int>& arr1c, const vector<int>& arr2c) {
		return count_same_using_sort(arr1c, arr2c, [](vector<int>& arr1, vector<int>& arr2) {
			int(*comp)(const void* a, const void* b) = [](const void* a, const void* b)
			{
				return *static_cast<const int*>(a) > *static_cast<const int*>(b) ? 1 : -1;
			};

			std::qsort(&arr1[0], arr1.size(), sizeof(int), comp);
			std::qsort(&arr2[0], arr2.size(), sizeof(int), comp);
		});
	}

	int count_same_std_sort(const vector<int>& arr1c, const vector<int>& arr2c) {
		return count_same_using_sort(arr1c, arr2c, [](vector<int>& arr1, vector<int>& arr2) {
			sort(arr1.begin(), arr1.end());
			sort(arr2.begin(), arr2.end());
		});
	}



	static void countSort(vector<int>& arr, int exp)
	{
		vector<int> output(arr.size(), 0);
		vector<int> count(10, 0);
		int n = arr.size();

		for (int i = 0; i < n; i++)
			count[(arr[i] / exp) % 10]++;

		for (int i = 1; i < 10; i++)
			count[i] += count[i - 1];

		for (int i = n - 1; i >= 0; i--)
		{
			output[count[(arr[i] / exp) % 10] - 1] = arr[i];
			count[(arr[i] / exp) % 10]--;
		}

		for (int i = 0; i < n; i++)
			arr[i] = output[i];
	}

	void radixSort(vector<int>& arr) {
		int max = 0;
		for (int item : arr)
			if (item > max) max = item;
		//int maxExp = (max == 0 ? 1 : int(log10(max) + 1));

		for (int exp = 1; max / exp > 0; exp *= 10)
			countSort(arr, exp);
	}

	int count_same_radix(const vector<int>& arr1c, const vector<int>& arr2c) {
		return count_same_using_sort(arr1c, arr2c, [](vector<int>& arr1, vector<int>& arr2) {
			radixSort(arr1);
			radixSort(arr2);
		});
	}

	int count_same_set(const vector<int>& arr1c, const vector<int>& arr2c) {
		set<int> arr1(arr1c.begin(), arr1c.end());
		set<int> arr2(arr2c.begin(), arr2c.end());

		auto it1 = arr1.begin();
		auto it2 = arr2.begin();
		int counter = 0;

		while (it1 != arr1.end() && it2 != arr2.end())
		{
			if (*it1 == *it2)
			{
				counter++;
				++it1;
				++it2;
			}
			else if (*it1 < *it2) ++it1;
			else ++it2;
		}

		return counter;
	}


	int count_same_elements(const vector<int>& arr1, const vector<int>& arr2) {
		return count_same_hash(arr1, arr2);
	}

	void run_program_io(std::istream& in, std::ostream& out) {
		size_t size1, size2;
		in >> size1 >> size2;

		vector<int> arr1(size1);
		vector<int> arr2(size2);

		for (size_t i = 0; i < size1; i++) in >> arr1[i];
		for (size_t i = 0; i < size2; i++) in >> arr2[i];

		out << count_same_elements(arr1, arr2);
	}

	void run_simple_tests() {
		tuple<int, int, string, string, string> tests[5]{
			{3, 2, "10 11 12", "1 23", "0"},
			{3, 1, "10 11 12", "10", "1"},
			{1, 3, "10", "11 12 10", "1"},
			{0, 0, "", "", "0"},
			{7, 3, "900000 1000003 1 2 3 4 1000002", "1000003 1000001 1000002", "2"},
		};

		for (auto&[size1, size2, arr1, arr2, expected] : tests)
		{
			std::ostringstream out_stream;
			std::istringstream in_stream(to_string(size1) + " " + to_string(size2) + "\n" + arr1 + "\n" + arr2);

			clock_t start = clock();
			run_program_io(in_stream, out_stream);
			string result = out_stream.str();

			double duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			if (result == expected) cout << "OK" << endl;
			else cout << "FAIL" << endl;
			cout << in_stream.str() << endl << "result: " << result << " expected: " << expected << endl;
			cout << "duration " << duration << " sec" << endl << endl;
		}
	}

	template <typename MethodT>
	void log_generated_test(string sort_name, const vector<int>& arr1, const vector<int>& arr2, MethodT countMethod, int expected) {
		clock_t start = clock();
		cout << endl << sort_name << endl;
		int res = countMethod(arr1, arr2);
		if (res == expected) cout << "OK" << endl;
		else cout << "FAIL" << endl;
		cout << "result: " << res << " expected: " << expected << endl;
		cout << "duration " << (clock() - start) / (double)CLOCKS_PER_SEC << " sec" << endl;

	}

	void run_rand_generated_test() {
		size_t size1 = 9;
		size_t size2 = 900000;
		vector<int> arr1(size1);
		unordered_set<int> hash1(size1);
		vector<int> arr2(size2);
		random_device rd;
		mt19937 rng(rd());
		uniform_int_distribution uni(0, INT32_MAX);

		clock_t start = clock();

		// first size1 are equal, so answer size1
		for (size_t i = 0; i < size1; i++)
		{
			int next = uni(rng);
			while (hash1.find(next) != hash1.end())
			{
				next = uni(rng);
			}
			arr1[i] = next;
			arr2[i] = next;
			hash1.emplace(next);
		}
		for (size_t i = size1; i < size2; i++)
		{
			int next = uni(rng);
			while (hash1.find(next) != hash1.end())
			{
				next = uni(rng);
			}
			arr2[i] = next;
			hash1.emplace(next);
		}
		cout << "generating data duration " << (clock() - start) / (double)CLOCKS_PER_SEC << " sec" << endl;

		log_generated_test("hash", arr1, arr2, count_same_hash, size1);
		log_generated_test("quick sort", arr1, arr2, count_same_quick_sort, size1);
		log_generated_test("std sort", arr1, arr2, count_same_std_sort, size1);
		log_generated_test("set", arr1, arr2, count_same_set, size1);
		log_generated_test("radix", arr1, arr2, count_same_radix, size1);


		// size_t size1 = 100000;
		// size_t size2 = 900000;
		//generating data duration 15.87 sec
		//hash
		//	current max_load_factor : 1
		//	current size : 100000
		//	current bucket_count : 131072
		//	current load_factor : 0.762939
		//	OK
		//	result : 100000 expected : 100000
		//	duration 4.724 sec

		//	quick sort
		//	OK
		//	result : 100000 expected : 100000
		//	duration 2.21 sec

		//	std sort
		//	OK
		//	result : 100000 expected : 100000
		//	duration 3.459 sec

		//	set
		//	OK
		//	result : 100000 expected : 100000
		//	duration 12.171 sec

		//	radix
		//	OK
		//	result : 100000 expected : 100000
		//	duration 31.048 sec

		//////////////////////////////////////
		// size_t size1 = 9;
		// size_t size2 = 900000;
		// generating data duration 16.81 sec
		// hash
		// current max_load_factor : 1
		// current size : 9
		// current bucket_count : 64
		// current load_factor : 0.140625
		// OK
		// result : 9 expected : 9
		// duration 2.553 sec

		// quick sort
		// OK
		// result : 9 expected : 9
		// duration 2.112 sec

		// std sort
		// OK
		// result : 9 expected : 9
		// duration 3.192 sec

		// set
		// OK
		// result : 9 expected : 9
		// duration 10.619 sec

		// radix
		// OK
		// result : 9 expected : 9
		// duration 27.948 sec
	}


	/// Counting of the same elements in two arrays 
	/// task from vk.com trainee 2019
	int main() {
		//run_simple_tests();
		run_rand_generated_test();
		//run_program_io(cin, cout);
		return 0;
	}
}