#include <iostream>
#include <thread>

#include "report.hpp"
using namespace std;

int main() {
	std::cout << std::boolalpha;
	std::cout << "Threads available: " << std::thread::hardware_concurrency() << std::endl;
	
	std::string f = "D:/report9.json";

	report2(0.03, f);

	//auto x = random_graph(10, 0.2, 5);
	//auto y = random_graph(3, 1, 5);
	//full_test(x, y);

	//short_test("test-20-3-true.json");

	//test1();
	//test2();
}