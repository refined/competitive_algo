#pragma once
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <tuple> 
#include <functional>

namespace algo
{
	using namespace std;

	// [-   -   -   -] [      4      ]
	// [-   -] [-   -] [  2  ] [  4  ]
	// [-] [-] [-] [-] [1] [2] [3] [4]
	class SegmentTree
	{
		const vector<int>& arr_;
		vector<vector<int>> max_segments_;
		vector<vector<int>> min_segments_;
		int max_pow_;

		void build()
		{
			max_segments_.push_back(arr_); // pow of 2 == 0, base layer
			min_segments_.push_back(arr_);
			max_pow_ = static_cast<int>(ceil(log2(arr_.size())));

			for (int pow_2 = 1; pow_2 < max_pow_; pow_2++)
			{
				const vector<int>& prev_layer_max = max_segments_[pow_2 - 1];

				vector<int> curr_layer_max;
				for (size_t i = 0; i < prev_layer_max.size(); i += 2)
				{
					if (i + 1 < prev_layer_max.size())
						curr_layer_max.push_back(max(prev_layer_max[i], prev_layer_max[i + 1]));
					else
						curr_layer_max.push_back(prev_layer_max[i]);
				}
				max_segments_.push_back(curr_layer_max);

				const vector<int>& prev_layer_min = min_segments_[pow_2 - 1];
				vector<int> curr_layer_min;
				for (size_t i = 0; i < prev_layer_min.size(); i += 2)
				{
					if (i + 1 < prev_layer_min.size())
						curr_layer_min.push_back(min(prev_layer_min[i], prev_layer_min[i + 1]));
					else
						curr_layer_min.push_back(prev_layer_min[i]);
				}
				min_segments_.push_back(curr_layer_min);
			}
		}

	public:
		SegmentTree(const vector<int>& arr) : arr_(arr) { build(); }

		// include r
		tuple<int, int> get_min_max(int l, int r) const
		{
			int min = max_segments_[0][l];
			int max = min_segments_[0][l];
			while (l <= r)
			{
				int segment_max = max_segments_[0][l];;
				int segment_min = min_segments_[0][l];;
				int power = 2;
				for (size_t pow_2 = 1; pow_2 < max_pow_; pow_2++)
				{
					// right side of segment more right than R or left side of segment if more left than L
					if (l + power - 1 <= r && l % power == 0)
					{
						segment_max = max_segments_[pow_2][static_cast<int>(l / power)];
						segment_min = min_segments_[pow_2][static_cast<int>(l / power)];
						power = power * 2;
					}
					else
					{
						break;
					}
				}
				l = l + power / 2;
				if (segment_max > max) max = segment_max;
				if (segment_min < min) min = segment_min;
			}
			return tuple(min, max);
		}
	};
}

int segment_tree_testing();
