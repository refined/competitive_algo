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

	/// Прямо сейчас ведущему нужно разбить всех коллег на две команды так, 
	/// чтобы каждые два человека в одной команде хорошо знали друг друга — и это непростая задача.
	/// Вам дан граф, в котором каждому человеку сопоставлена ровно одна вершина.
	/// Ребро(u, v) означает, что коллега u хорошо знает коллегу v(и в то же время коллега v хорошо знает коллегу u).
	/// Проверьте, можно ли разбить вершины графа на два множества требуемым образом, и, 
	/// если это возможно, выведите любое подходящее разбиение.
	///  n и m (2 ≤ n ≤ 5000, 0 ≤ m ≤ 200000) — число вершин и число рёбер в графе. 
	inline void complete_graph(std::istream& in, std::ostream& out)
	{

	}

#ifdef _DEBUG
	inline int complete_graph_test() {
		run_test_from_text(complete_graph, "complete_graph_test.txt");
#else
	int main() {
		ios_base::sync_with_stdio(false);
		cin.tie(0);
		complete_graph(cin, cout);
#endif
		return 0;
	}
	}

