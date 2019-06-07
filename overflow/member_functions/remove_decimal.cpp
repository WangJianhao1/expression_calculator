#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <limits>
#include <iomanip>
#include "test_framework.h"
using namespace std;

void putback_str(string s)
{
	for (int i = s.size(); i >=0; --i) cin.putback(s[i]);
}

// builds a number fron standard input.
// returns the number in string format.
string build_int()
{
	char ch;
	string number;
	while (cin.get(ch) && (ch == '-' || isdigit(ch) || ch == '.')) number += ch;
	cin.putback(ch);
	return number;
}

// Prepocess the significand by removing the decimal and negative signs if any.
// Returns flags for if the significand was negative or had no integer value.
vector<bool> remove_dec_significand(string& significand)
{
	vector<bool> ret;
	bool neg = false;
	bool no_int = false;
	if (significand[0] == '-')
	{
		significand.erase(0,1);
		neg = true;
	}
	if (significand[0] == '.') 
	{
		no_int = true;
		significand.erase(0,1);
	}
	if (significand[1] == '.') significand.erase(1,1);

	ret.push_back(neg);
	ret.push_back(no_int);

	return ret;
}

// sci_to_d() subroutine for cases when exponential > 0.
void sci_to_d_exp_grtr_zero(int& decimal_index, int& exponential, string& significand)
{
	while (exponential > 0)
	{
		if (decimal_index == significand.size()-1 && exponential > 0)		
		{
			significand += '0';
			++decimal_index;
			--exponential;
		}
		else if (exponential == 1 && decimal_index < significand.size()-2)
		{
			significand.insert(decimal_index, ".");
			--exponential;
		}
		else
		{
			++decimal_index;
			--exponential;
		}
	}
}

// sci_to_d() subroutine for cases when exponential < 0.
void sci_to_d_exp_less_zero(int& decimal_index, int& exponential, string& significand)
{
	while (exponential < 0)
	{
		significand = '0' + significand;
		++exponential;
	}
	
	if (exponential == 0) significand = '.' + significand;
}

void get_significand_exponential(string& significand, int& exponential)
{
	char ch;
	significand = build_int();
	cin.get(ch);
	if (ch != 'e') throw runtime_error("sci_to_d(): Expected 'e' for exponential.");
	cin >> exponential;
	if (!cin) throw runtime_error("sci_to_d(): Invalid input for variable `exponential`.");
	if (exponential == 0) throw runtime_error("sci_to_d(): Illegal: Exponential value is in (-1,1) range.");
	cin.ignore();			// this line is necessary to stop invalid input on next loop.
}

// translate double to string with precision
string to_str_with_precision(double d)
{
	ostringstream out;
	out.precision(15);
	out << d;
	string ret = out.str();
	return ret;
}

// Removes trailing zeros from a double that is represented as a string.
string remove_trailing_zero(string temp)
{
	char c_del = '0';
	int index = temp.size();
	bool decimal_found = false;
	for (int i = 0; i < temp.size(); ++i)
		if (temp[i] == '.') decimal_found = true;

	if (!decimal_found) return temp; 	
	while (c_del == '0')
	{
		c_del = temp[index-1];
		if (c_del == '0') temp.erase(index-1);
		--index;
	}

	return temp;
}

bool is_scientific(string s)
{
	for (int i = 0; i < s.size(); ++i)
		if (s[i] == 'e') return true;

	return false;
}

// Converts string representation of double from scientific notation to
// standard notation.
string sci_to_d(string s)
{
	putback_str(s);

	string significand;
	int exponential;		// for ticket_1 does this have to be long long int?
	get_significand_exponential(significand, exponential);

	int decimal_index = 0;
	
	vector<bool> preprocessed_significand = remove_dec_significand(significand); 
	
	bool neg = preprocessed_significand[0];
	bool no_int = preprocessed_significand[1];
	if (no_int) decimal_index--;				// necessary adjustment for case of no_int		

	sci_to_d_exp_grtr_zero(decimal_index, exponential, significand);
	++exponential; 		// removing decimal is equivalent to applying factor of 10 in below case.

	sci_to_d_exp_less_zero(decimal_index, exponential, significand);
	string ret = significand;
	if (neg) ret = '-' + ret;

	return ret;
}

// Capability to up to 15 digits of precision
// Returns:
// 	[0]: Number without decimal
// 	[1]: Decimal position
vector<int> remove_decimal(double x)
{
	string temp;
	char ch;
	bool dec_flag = false;
	int dec_places = 0;
	vector<int> ret;
	
	temp = to_str_with_precision(x);
	if (is_scientific(temp)) temp = sci_to_d(temp);	
	temp = remove_trailing_zero(temp);
	putback_str(temp);

	temp = "";

	while (cin.get(ch) && (isdigit(ch) || ch == '.' || ch == '-'))
	{
		if (ch == '.') dec_flag = true; 
		else 
		{
			temp += ch;
			if (dec_flag) dec_places += 1;
		}
	}

	putback_str(temp);
	int res;
	cin >> res;
	ret.push_back(res);
	ret.push_back(dec_places);
	cin.ignore(); // this removes the pause
	return ret;
}

int main()
{
	string file_name = "remove_decimal.cpp";
	int x = 1;
	vector<int> res;

	res = remove_decimal(1.2345567);
	ASSERT(res[0], 12345567, "Test case 1");
	ASSERT(res[1], 7, "Test case 2");
	res.clear();

	res = remove_decimal(-.2345);
	ASSERT(res[0], -2345, "Test case 3");
	ASSERT(res[1], 4, "Test case 4");
	res.clear();

	res = remove_decimal(.2300000000000000000);
	ASSERT(res[0], 23, "Test case 5");
	ASSERT(res[1], 2, "Test case 6");
	res.clear();

	
	res = remove_decimal(.230000000000000001);
	ASSERT(res[0], 230000000000000001, "Test case 7");
	ASSERT(res[1], 18, "Test case 8");
	res.clear();

	res = remove_decimal(10000000000000000.1);
	ASSERT(res[0], 100000000000000001, "Test case 9");
	ASSERT(res[1], 1, "Test case 10");
	res.clear();

	res = remove_decimal(-.00000000023456);
	ASSERT(res[0], -23456, "Test case 11");
	ASSERT(res[1], 14, "Test case 12");
	res.clear();
	
	TEST_SUMMARY(file_name);
	
}
