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
	
	/// ƒаны отрезки на пр€мой. Ќайти такие точки, которые лежат на всех заданных отрезках. 
	/// Ќайденное множество должно быть минимальным по размеру.
	inline vector<int> get_covering_set(vector <Segment> segments) {
		vector <int> result;
		sort(segments.begin(), segments.end(), [](const Segment & a, const Segment & b)
		{
			return a.second < b.second;
		});

		while (!segments.empty())
		{
			int point = segments.begin()->second;
			auto it = segments.begin();
			while (it != segments.end())
			{
				if (it->first <= point)
				{
					it = segments.erase(it);
				} else
				{
					it = next(it);
				}
			}
			result.push_back(point);
		}		

		return result;
	}

	inline void min_points_cover_for_segments(std::istream& in, std::ostream& out)
	{
		int segments_count;
		in >> segments_count;
		vector <Segment> segments(segments_count);
		for (auto &s : segments) {
			in >> s.first >> s.second;
		}

		auto points = get_covering_set(std::move(segments));
		out << points.size() << std::endl;
		for (auto point : points) {
			out << point << " ";
		}
		out << std::endl;		
	}


#ifdef _DEBUG
	inline int min_points_cover_for_segments_test() {
		run_test_from_text(min_points_cover_for_segments, "min_points_cover_for_segments_test.txt");
#else
	int main() {
		ios_base::sync_with_stdio(false);
		cin.tie(0);
		min_points_cover_for_segments(cin, cout);
#endif
		return 0;
	}
}
