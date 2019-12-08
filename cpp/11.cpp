#include <utility>
#include <iostream>
#include <cassert>
#include <functional>

using namespace std;

/**
 @file
 @brief C++11
 @defgroup CPP11 C++11 examples
 @{
 @defgroup lang11 Language
 @{
	https://en.cppreference.com/w/cpp/language/move_constructor

	https://en.cppreference.com/w/cpp/language/move_assignment

	https://en.cppreference.com/w/cpp/language/data_members#Member_initialization

	https://en.cppreference.com/w/cpp/language/override

	https://en.cppreference.com/w/cpp/language/final

	https://en.cppreference.com/w/cpp/language/reference &&

	https://en.cppreference.com/w/cpp/language/attributes

	https://en.cppreference.com/w/cpp/language/nullptr

	https://en.cppreference.com/w/cpp/language/string_literal

	https://en.cppreference.com/w/cpp/language/character_literal

	https://en.cppreference.com/w/cpp/language/user_literal

	https://en.cppreference.com/w/cpp/language/aggregate_initialization

	https://en.cppreference.com/w/cpp/language/range-for

	https://en.cppreference.com/w/cpp/language/decltype

	https://en.cppreference.com/w/cpp/language/auto

	https://en.cppreference.com/w/cpp/language/constexpr

	https://en.cppreference.com/w/cpp/language/parameter_pack

 */

/**
 Trailing return type

 https://en.cppreference.com/w/cpp/language/function

 https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_73/rzarg/trailing_return.htm

*/

// int before(int a) { return a; }
auto trailing_return_type(int a) -> int
{
	return a;
}

/**
 @}
 @defgroup lambda11 Lambda
 https://en.cppreference.com/w/cpp/language/lambda
 https://www.geeksforgeeks.org/lambda-expression-in-c/
 @{
 */

static void lambda_basics(void)
{
	int i = 1;

	auto annotated_named_lambda_declaraion =  // optional name
		[ ] // capture
		( ) // optional list of arguments
		{ }; // body

	// Primitive named lambdas are just like closure functions:
	// https://en.wikipedia.org/wiki/Closure_(computer_programming)

	// declaration like a function:
	// void closure() { };
	auto closure = [] { };

	closure();

	// with arguments
	auto pass = [] (int a) -> int { return a; };
	assert(pass(5) == 5);

	// lambda captures external value
	auto get_i = [=] () -> int { return i; };
	assert(get_i() == 1);

	// lambda captures external variable by reference
	auto inc_get = [&] () -> int { return ++i; };
	assert(inc_get() == 2);
	assert(inc_get() == 3);

	// annotated expanded empty inline lambda call:
	[ ] // capture
	( ) // optional list of arguments
	-> void // optional return value
	{ } // body
	( ); // call with arguments

	// annotated expanded sample inline lambda call:
	[i] // capture
	(int a) // optional list of arguments
	-> int // optional return value
	{ return i + a; } // body
	(1); // call with argument

	// inline lambda which is called in place
	// https://en.wikipedia.org/wiki/Anonymous_function

	// assert((1 + 1) == 2);
	assert([](int a) { return a + 1; }(1) == 2);

	// Actually calling lambda inline is useless
	// and is provided only for demonstration.
}

static int glob;

static void lambda_capture(void)
{
	// read only
	int i = 2;
	assert([=]{return i; }() == 2);

	// read and write access
	[&](int a){i = a;}(3);
	assert(i == 3);

	// explicit r/o and r/w
	int j;
	[i, &j](){ j = i; }();
	assert(j == i);

	// r/o by default
	i++;
	[=, &j](){ j = i; }();
	assert(j == i);

	// r/w by default
	i++;
	[&, i](){ j = i; }();
	assert(j == i);

	// can access globals anyway
	auto inc_global = [] () -> int { return ++glob; };
	assert(inc_global() == 1);
	assert(inc_global() == 2);
}

/// More complex useful examples

// int use_lambda(int a; int (func*)(int))
static int use_lambda(int a, function<int(int)> f)
{
	return f(a);
}

static function<int(int)> g_f;

static void set_lambda(function<int(int)> f)
{
	g_f = f;
}

static int call_lambda(int a)
{
	return g_f(a);
}

static void lambda_complex(void)
{
	auto increment = [] (int a) -> int { return a + 1; };
	assert(increment(5) == 6);

	// named lambda as argument
	assert(use_lambda(2, increment) == 3);
	set_lambda(increment);
	assert(call_lambda(3) == 4);

	// inline lambda as argument
	assert(use_lambda(1, [](int a) {return a + 1;}) == 2);
}

/// @}

int main(void)
{
	cout << __cplusplus << endl;
	auto r = trailing_return_type(1);
	lambda_basics();
	lambda_capture();
	lambda_complex();
	return 0;
}
/// @}