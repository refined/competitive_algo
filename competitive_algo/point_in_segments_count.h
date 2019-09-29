#pragma once
#include <istream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <iostream>

#ifdef _DEBUG
#include "tests.h"
#endif

namespace algo::segments {
	using namespace std;
	using Segment = pair<int, int>;

	/// Даны отрезки. Определить в какое количество отрезков попала точка
	inline vector<int> point_in_segments_count(vector<Segment>&& segments, vector<int>&& points) {
		sort(segments.begin(), segments.end(), 
			[](const Segment & a, const Segment & b) { return a.first < b.first; });
		vector<Segment> segments_sorted_second(segments.begin(), segments.end());
		sort(segments_sorted_second.begin(), segments_sorted_second.end(),
			[](const Segment & a, const Segment & b) { return a.second < b.second; });
		
		vector<int> result;

		for(int point : points)
		{
			const auto found_it_start_before_point = lower_bound(segments.begin(), segments.end(), point,
				[](const Segment& segment, int p) { return segment.first <= p;	});
			const int start_before_point_count = distance(segments.begin(), found_it_start_before_point);

			const auto found_it_end_before_point = lower_bound(segments_sorted_second.begin(), segments_sorted_second.end(), point,
				[](const Segment& segment, int p) { return segment.second < p;	});
			const int end_before_point_count = distance(segments_sorted_second.begin(), found_it_end_before_point);

			// вычитаем из тех, что начинаются до точки, те что закончились до точки
			// не может отрезок закончится до точки и начаться после него
			result.push_back(start_before_point_count - end_before_point_count); 
		}
		
		return result;
	}

	inline void run_point_in_segments_count(std::istream& in, std::ostream& out)
	{
		int segments_count, points_count;
		in >> segments_count >> points_count;

		vector <Segment> segments(segments_count);
		for (auto &s : segments) {
			in >> s.first >> s.second;
		}
		vector<int> points(points_count);
		for (auto &p : points) {
			in >> p;
		}
		auto counts = point_in_segments_count(move(segments), move(points));
		for (auto point : counts) {
			out << point << " ";
		}
	}


#ifdef _DEBUG
	inline int point_in_segments_count_test() {
		tests::run_test_from_text(run_point_in_segments_count, "point_in_segments_count_test.txt");
#else
	int main() {
		ios_base::sync_with_stdio(false);
		cin.tie(0);
		run_point_in_segments_count(cin, cout);
#endif
		return 0;
	}
	}
