#include "divide_with_precision.h"
#include "test_framework.h"

using std::string;

int main()
{
	string file_name = "sci_to_d_test.cpp";
	ASSERT(sci_to_d("1e10"), "10000000000", "Test 1");

	ASSERT(sci_to_d("1.23e5"), "123000", "Test 2");

	ASSERT_ERROR(test_3, sci_to_d(".234e.5"), "Test 3");
	
	ASSERT(sci_to_d(".234e4"), "2340", "Test 4");

	ASSERT(sci_to_d("-2e6"), "-2000000", "Test 5");

	ASSERT(sci_to_d("-2.34e4"), "-23400", "Test 6");

	ASSERT(sci_to_d("-.402e9"), "-402000000", "Test 7");

	ASSERT(sci_to_d("1e-1"), ".1", "Test 8");

	ASSERT(sci_to_d("-2e-3"),  "-.002", "Test 9");

	ASSERT(sci_to_d("2.432e-6"), ".000002432", "Test 10");	

	ASSERT(sci_to_d(".632156e-9"), ".00000000632156", "Test 11");

	ASSERT_ERROR(test_4, sci_to_d(".24e-.4"), "Test 12");
	
	ASSERT(sci_to_d("1e-100"), ".0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", "Test 13");

	ASSERT_ERROR(no_significand, sci_to_d("e10"), "Test 14");

	ASSERT_ERROR(no_e_1, sci_to_d("1.23"), "Test 15");

	ASSERT_ERROR(no_e_2, sci_to_d("1.2-34"), "Test 16");

	ASSERT_ERROR(no_exponential_1, sci_to_d("1e"), "Test 17");

	ASSERT_ERROR(no_exponential_2, sci_to_d("2.34e-"), "Test 18");
	
	ASSERT(sci_to_d("1e100"), "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "Test 19");

	TEST_SUMMARY(file_name);
}
