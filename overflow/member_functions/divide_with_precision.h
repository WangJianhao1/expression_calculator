#ifndef DIVIDE_WITH_PRECISION_H
#define DIVIDE_WITH_PRECISION_H

#include <string>
#include <vector>

using std::string;	using std::vector;

string build_int();
void putback_str(string);
vector<bool> remove_dec_significand(string&);
void sci_to_d_exp_grtr_zero(int& , int&, string&);
void sci_t_d_exp_less_zero(int&, int&, string&);
void get_significand_exponential(string&, int&);
string to_str_with_precision(double);
string remove_trailing_zero(string);
string sci_to_d(string);
bool is_scientific(string);
vector<int> remove_decimals(double);
vector<int> divide(int, int);
double add_decimals(int, int);
double divide_with_precision(double, double);

#endif
