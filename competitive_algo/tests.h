#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib> // atoi
#include <type_traits>
#include <fstream>
#include <windows.h> 

using namespace std;

template <typename T>
void packed_args_to_string(T& arg) {
	try
	{
		cout << arg << endl;
	}
	catch (const std::exception& e)
	{
		cout << "non string arg: " << e.what() << endl;
	}
}

template <typename T, typename ...MoreT>
void packed_args_to_string(T& arg, MoreT& ...args) {
	cout << arg << endl;
	packed_args_to_string(args...);
}


template <typename T>
bool out_assert_test(T expected, T result) {
	if (result == expected) {
		cout << "\nsuccess: ";
		return true;
	}
	cout << "\nfail: " << "result\n";
	cout << result << "\nexpected \n" << expected << "\n";
	return false;
}

template <typename T>
bool out_assert_test_colored(T expected, T result) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (result == expected) {
		SetConsoleTextAttribute(hConsole, 2);
		cout << "\nsuccess: ";
		SetConsoleTextAttribute(hConsole, 15);
		return true;
	}
	SetConsoleTextAttribute(hConsole, 4);
	cout << "\nfail: ";
	SetConsoleTextAttribute(hConsole, 2);
	cout << "result\n";
	SetConsoleTextAttribute(hConsole, 15);
	cout << result;
	SetConsoleTextAttribute(hConsole, 2);
	cout << "\nexpected \n";
	SetConsoleTextAttribute(hConsole, 15);
	cout << expected << "\n";
	return false;
}

template <typename ExpectedT, typename MethodT, typename ...InT>
void run_test(ExpectedT& expected, MethodT& method, InT& ...in_args) {
	clock_t start = clock();
	if (!out_assert_test(expected, method(in_args...)))
	{
		packed_args_to_string(in_args...);
	}
	cout << "duration " << (clock() - start) / (double)CLOCKS_PER_SEC << " sec" << endl;
}

template <typename ExpectedT, typename MethodT, typename ...InT>
void run_test(ExpectedT&& expected, MethodT& method, InT&& ...in_args) {
	clock_t start = clock();
	if (!out_assert_test(expected, method(in_args...)))
	{
		packed_args_to_string(in_args...);
	}
	cout << "duration " << (clock() - start) / (double)CLOCKS_PER_SEC << " sec" << endl;
}

inline void trim_end(string& str)
{
	int end = str.find(" \n");
	while (end != string::npos)
	{
		str.erase(end, 1);
		end = str.find(" \n");
	}
	if (*str.rbegin() == '\n') str.erase(str.size() - 1, 1);
	if (*str.rbegin() == ' ') str.erase(str.size() - 1, 1);
}


inline void clearify(string& expected, string& result)
{
	trim_end(expected);
	trim_end(result);
}

template <typename MethodT>
void run_test_from_text(MethodT& method, string&& filename, bool colored = false) {
	ifstream file_stream(filename.c_str());
	int test_num = 1;
	if (!file_stream.good())
	{
		cout << "cant find file: " + filename;
		return;
	}

	try
	{
		while (!file_stream.eof())
		{
			cout << "test case " << test_num++;
			std::ostringstream out_stream;

			clock_t start = clock();

			method(file_stream, out_stream);
			string result = out_stream.str();
			string expected;
			string line;
			do
			{
				getline(file_stream, line);
			} while (line.empty() && !file_stream.eof());

			do
			{
				expected += line + " \n";
				if (file_stream.eof())
					break;
				getline(file_stream, line);
			} while (!line.empty());

			clearify(expected, result);
			if (colored)
				out_assert_test_colored(expected, result);
			else
				out_assert_test(expected, result);

			cout << "duration " << (clock() - start) / static_cast<double>(CLOCKS_PER_SEC) << " sec" << endl << endl;
		}

		file_stream.close();
	}
	catch (...)
	{
		file_stream.close();
		throw;
	}
}
