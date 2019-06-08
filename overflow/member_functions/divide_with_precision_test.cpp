#include "divide_with_precision.h"
#include "test_framework.h"
#include <string>
#include <iostream>
#include <stdexcept>

using std::cout;	using std::endl;
using std::string;	using std::cin;
using std::exception;

int main()
{
	string file_name = "divide_with_precision_test.cpp";

	// Test 1
	ASSERT_DOUBLE(divide_with_precision(10, 4), 2.5, "Test 1");

	// Test 2
	ASSERT_DOUBLE(divide_with_precision(1, 6), .16666666, "Test 2");
	
	// Test 3
	ASSERT_DOUBLE(divide_with_precision(7, 8), .875, "Test 3");

	// Test 4
	ASSERT_DOUBLE(divide_with_precision(1, .1), 10, "Test 4");

	// Test 5
	ASSERT_DOUBLE(divide_with_precision(10, .1), 100, "Test 5");

	// Test 6
	ASSERT_DOUBLE(divide_with_precision(-4, 3), -1.333333, "Test 6");

	// Test 7
	ASSERT_DOUBLE(divide_with_precision(-4, .02), -200, "Test 7");

	// Test 8
	ASSERT_DOUBLE(divide_with_precision(-7, -12), .583333, "Test 8");

	// Test 9
	ASSERT_DOUBLE(divide_with_precision(-6, -5), 1.2, "Test 9");

	// Test 10
	ASSERT_DOUBLE(divide_with_precision(-90, .3), -300, "Test 10");

	ASSERT_ERROR(divide_by_zero, divide_with_precision(10,0), "Test 11");

	ASSERT_DOUBLE(divide_with_precision(0,10000), 0, "Test 12");

	TEST_SUMMARY(file_name);

}
