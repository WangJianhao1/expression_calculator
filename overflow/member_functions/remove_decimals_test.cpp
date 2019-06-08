#include "divide_with_precision.h"
#include "test_framework.h"

using std::string;

int main()
{
	string file_name = "remove_decimal_test.cpp";
	vector<int> res;

	res = remove_decimals(1.2345567);
	ASSERT(res[0], 12345567, "Test case 1");
	ASSERT(res[1], 7, "Test case 2");
	res.clear();

	res = remove_decimals(-.2345);
	ASSERT(res[0], -2345, "Test case 3");
	ASSERT(res[1], 4, "Test case 4");
	res.clear();

	res = remove_decimals(.2300000000000000000);
	ASSERT(res[0], 23, "Test case 5");
	ASSERT(res[1], 2, "Test case 6");
	res.clear();

	
	res = remove_decimals(.230000000000000001);
	ASSERT(res[0], 230000000000000001, "Test case 7");
	ASSERT(res[1], 18, "Test case 8");
	res.clear();

	res = remove_decimals(10000000000000000.1);
	ASSERT(res[0], 100000000000000001, "Test case 9");
	ASSERT(res[1], 1, "Test case 10");
	res.clear();

	res = remove_decimals(-.00000000023456);
	ASSERT(res[0], -23456, "Test case 11");
	ASSERT(res[1], 14, "Test case 12");
	res.clear();
	
	TEST_SUMMARY(file_name);
	
}
