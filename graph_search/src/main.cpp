#include <iostream>
#include <thread>
#include <limits>

#include "graph_manip.hpp"
#include "tests.hpp"
#include "report.hpp"
#include "utility.hpp"

using std::cin;
using std::cout;
using std::endl;

int main() {
	cout << std::boolalpha;
	cout << "Threads available: " << std::thread::hardware_concurrency() << endl;
	
	/*
	graph<int> x;
	graph<int> y;

	mutate(x, 30, 0.2, test_gen());
	mutate(y, 3, 1, test_gen());

	short_test("last_test.json");

	puff<int> pf(x, 3);
	cout << "puff " << pf << endl;
	*/

	report("report.json",
		range(3, 25 + 1, 2), 
		range(3, 9 + 1, 2), 
		{0.2},
		5);

	cout << "Done." << endl;
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}