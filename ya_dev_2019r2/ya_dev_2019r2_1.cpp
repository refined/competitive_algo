#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <iomanip> 
#include <map>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <cstdlib> // atoi
#include <cmath>
#include <limits>
#include <queue>
#include <stack>
#include <tuple> 
#include <iterator>

#ifdef _DEBUG
#include "tests.h"
#endif

using namespace std;

void run_ya_dev_2019r2_1(std::istream& in, std::ostream& out) {
	string test; in >> test;
	out << test;
}

#ifdef _DEBUG
int task_ya_dev_2019r2_1() {
	run_test_from_text(run_ya_dev_2019r2_1, "ya_dev_2019r2_1_test.txt", true);
#else
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	run_ya_dev_2019r2_1(cin, cout);
#endif
	return 0;
}