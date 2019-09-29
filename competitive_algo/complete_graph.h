#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>

#ifdef _DEBUG
#include "tests.h"
#endif

namespace algo::dynamic {
	using namespace std;

	void add_rib(map<int, set<int>>& ribs_to_vertices, int a, int b)
	{
		auto it = ribs_to_vertices.find(a);
		if(it != ribs_to_vertices.end())
		{
			it->second.emplace(b);
		} else
		{
			set<int> vert;
			vert.emplace(b);
			ribs_to_vertices.emplace(a, vert);
		}
	}

	set<int> set_minus_set(set<int>& all_vertices, set<int>& verts)
	{
		set<int> diff;
		std::set_difference(all_vertices.begin(), all_vertices.end(), verts.begin(), verts.end(),
			inserter(diff, diff.begin()));
		return diff;
	}

	/// Прямо сейчас ведущему нужно разбить всех коллег на две команды так, 
	/// чтобы каждые два человека в одной команде хорошо знали друг друга — и это непростая задача.
	/// Вам дан граф, в котором каждому человеку сопоставлена ровно одна вершина.
	/// Ребро(u, v) означает, что коллега u хорошо знает коллегу v(и в то же время коллега v хорошо знает коллегу u).
	/// Проверьте, можно ли разбить вершины графа на два множества требуемым образом, и, 
	/// если это возможно, выведите любое подходящее разбиение.
	///  n и m (2 ≤ n ≤ 5000, 0 ≤ m ≤ 200000) — число вершин и число рёбер в графе. 
	///  В следующих m строках даны описания рёбер — пары целых чисел a b (1 ≤ a, b ≤ n, a ≠ b), означающих наличие ребра между вершинами a и b. 
	inline void complete_graph_io(std::istream& in, std::ostream& out)
	{
		size_t n, m;
		in >> n >> m;
		map<tuple<int, int>, bool> ribs_exist;
		map<int, set<int>> ribs_to_vertices;
		set<int> all_vertices;
		for (size_t i = 0; i < n; i++) all_vertices.emplace(i+1);

		for (size_t i = 0; i < m; i++)
		{
			int a, b;
			in >> a >> b;

			ribs_exist.emplace(make_tuple(a, b), true);
			ribs_exist.emplace(make_tuple(b, a), true);
			add_rib(ribs_to_vertices, a, b);
			add_rib(ribs_to_vertices, b, a);
		}

		set<int> arr1_likely;
		set<int> arr1_not;

		arr1_likely.emplace(1);
		const auto it_ribs = ribs_to_vertices.find(1);
		if (it_ribs == ribs_to_vertices.end())
		{
			set<int> empty_set;
			arr1_not = set_minus_set(all_vertices, empty_set);
		} else
		{
			arr1_likely = it_ribs->second;
			arr1_not = set_minus_set(all_vertices, arr1_likely);
		}
		auto it = arr1_likely.begin();

		while (it != arr1_likely.end())
		{
			auto set_not_vert = set_minus_set(all_vertices, ribs_to_vertices.find(*it)->second);
			for (int i : set_not_vert) {
				arr1_not.emplace(i);
			}
			++it;
		}
		arr1_likely = set_minus_set(all_vertices, arr1_not);


	}

#ifdef _DEBUG
	inline int complete_graph_test() {
		tests::run_test_from_text(complete_graph_io, "complete_graph_test.txt");
#else
	int main() {
		ios_base::sync_with_stdio(false);
		cin.tie(0);
		complete_graph_io(cin, cout);
#endif
		return 0;
	}
}

