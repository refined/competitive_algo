#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>

#ifdef _DEBUG
#include "tests.h"
#endif

namespace algo::graph {
	using namespace std;
	using empty_result = std::tuple<set<int>, set<int>>;

	struct Vert
	{
		explicit Vert(int num) : num(num) {  }
		int num;
		set<int> verts;
		bool visited = false;
	};

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

	set<int> set_minus_set(const set<int>& arr1, const set<int>& arr2)
	{
		set<int> diff;
		std::set_difference(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(),
			inserter(diff, diff.begin()));
		return diff;
	}

	set<int> operator-(const set<int>& arr1, const set<int>& arr2)
	{
		return set_minus_set(arr1, arr2);
	}


	set<int> get_full_connected_verts(const map<int, set<int>>& map)
	{
		size_t verts_count = map.size();
		set<int> res;
		for (auto [v, ribs] : map)
		{
			if (ribs.size() == verts_count - 1)
			{
				res.emplace(v);
			}
		}
		return res;
	}

	bool check_full_connection(set<int> X, const map<int, set<int>>& vert_ribs)
	{
		for (int x : X)
		{
			auto it = vert_ribs.find(x);
			if (it == vert_ribs.end()) return false;

			if(!includes(X.begin(), X.end(), 
				it->second.begin(), it->second.end()))
			{
				return false;	
			}
		}
		return true;
	}

	tuple<set<int>, set<int>> solve(const map<int, set<int>>& vert_ribs, const set<int>& All)
	{
		set<int> A;
		set<int> B;

		int no_ribs = -1;
		for (int a : All)
		{
			auto it = vert_ribs.find(a);
			if (it == vert_ribs.end())
			{
				if (no_ribs != -1)
				{
					return empty_result();
				}
				no_ribs = a;
			}
		}
		if(no_ribs != -1) 
		{
			B = set<int>({ no_ribs });
			A = All - B;
			if (check_full_connection(A, vert_ribs)) return make_tuple(A, B);
			return empty_result();
		} 

		// solve
		set<int> Full = get_full_connected_verts(vert_ribs);
		A.insert(Full.begin(), Full.end());

		if (Full.size() == All.size()) // totally connected graph
		{
			B = set<int>({ 1 });
			A = All - B;
			return make_tuple(A, B);
		}

		while (A.size() + B.size() != All.size())
		{
			set<int> Left = All - A - B - Full;
			int a1 = *Left.begin();
			A.emplace(a1);
			
			set<int> notA = All - vert_ribs.find(a1)->second;
			B.insert(notA.begin(), notA.end());

			for (int b : B)
			{
				set<int> b_verts = vert_ribs.find(b)->second;
				set<int> notB = All - b_verts;
				A.insert(notB.begin(), notB.end());
			}
			// в этом месте остаются только вершины которые полностью связаны и с А и с B
			// но мы не знаем как они между собой связаны, попробуем положить одну из них в А
		}
		
		if (check_full_connection(A, vert_ribs)) return make_tuple(A, B);
		return empty_result();
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
		// arrange
		size_t n, m;
		in >> n >> m;
		map<int, set<int>> ribs_to_vertices;
		set<int> all_vertices;
		for (size_t i = 0; i < n; i++) all_vertices.emplace(i+1);

		for (size_t i = 0; i < m; i++)
		{
			int a, b;
			in >> a >> b;
			add_rib(ribs_to_vertices, a, b);
			add_rib(ribs_to_vertices, b, a);
		}
		
		auto [A, B] = solve(ribs_to_vertices, all_vertices);

		if (A.empty())
		{
			out << -1 << endl;
		}
		else
		{
			out << A.size() << endl;
			for (int a : A) out << a << " ";
			out << endl;
			for (int b : B) out << b << " ";
			out << endl;
		}
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

