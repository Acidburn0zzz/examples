/**
 @file
 @brief C++11
 @defgroup CPP11 C++11 examples

 https://en.wikipedia.org/wiki/C++11

 https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP11.md

 @{
*/
static_assert(__cplusplus == 201103, "");

#include <utility>
#include <iostream>
#include <cassert>
#include <functional>
#include <algorithm>
#include <array>
#include <memory>

#if __has_include (<version>)
#include <version>
#endif


using namespace std;

/**
 @defgroup lang11 Language
 @{
	https://en.cppreference.com/w/cpp/language/move_constructor

	https://en.cppreference.com/w/cpp/language/move_assignment

	https://en.cppreference.com/w/cpp/language/data_members#Member_initialization

	https://en.cppreference.com/w/cpp/language/override

	https://en.cppreference.com/w/cpp/language/final

	https://en.cppreference.com/w/cpp/language/reference &&

	https://en.cppreference.com/w/cpp/language/attributes

	https://en.cppreference.com/w/cpp/language/string_literal

	https://en.cppreference.com/w/cpp/language/character_literal

	https://en.cppreference.com/w/cpp/language/user_literal

	https://en.cppreference.com/w/cpp/language/aggregate_initialization

	https://en.cppreference.com/w/cpp/language/initializer_list

	https://en.cppreference.com/w/cpp/language/range-for

	https://en.cppreference.com/w/cpp/language/decltype

	https://en.cppreference.com/w/cpp/language/parameter_pack

 */

void init_11()
{
	// https://en.cppreference.com/w/cpp/language/direct_initialization
	// https://en.cppreference.com/w/cpp/language/list_initialization

	class C { public: int a, b, c; };
	auto o2 = C{1, 2, 3};
	C o3{1, 2, 3};
	(void) o3;

	// https://en.cppreference.com/w/cpp/language/zero_initialization
	auto z1 = C();
	C z2 = {};
	auto z3 = C{};

	assert(!z1.a);
	assert(!z2.a);
	assert(!z3.a);
}

/**
 Trailing return type

 https://en.cppreference.com/w/cpp/language/function

 https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_73/rzarg/trailing_return.htm

*/


/// https://en.cppreference.com/w/cpp/language/auto
auto auto_int = 1;

// int before(int a) { return a; }
auto trailing_return_type(int a) -> int
{
	return a;
}

void func_11()
{
	class functor {
		int y = 1;
		public:
		int operator()(int a) const {
			return a + y;
		}
	};
	functor ft;
	assert(ft(1) == 2);

	// https://en.cppreference.com/w/cpp/utility/functional/function
	function<int(int)> ft2 = ft;
	assert(ft(2) == 3);
	return;

	// https://en.cppreference.com/w/cpp/utility/functional/bind
	auto binded = bind(ft2, 3);
	assert(binded() == 5);
}

static_assert(__cpp_constexpr);

/// https://en.cppreference.com/w/cpp/language/constexpr

constexpr int constexpr_factorial(int n)
{
    return n <= 1 ? 1 : (n * constexpr_factorial(n - 1));
}


/// @}

/**
 @defgroup lambda11 Lambda
 https://en.cppreference.com/w/cpp/language/lambda
 https://www.geeksforgeeks.org/lambda-expression-in-c/
 @{
 */

static void lambda_basics(void)
{
	auto annotated_named_lambda_expression =  // optional name
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
	auto pass = [] (int a) { return a; };
	assert(pass(5) == 5);

	// lambda captures external value
	int c = 1;
	auto get_i = [=] () { return c; };
	assert(get_i() == 1);

	// lambda captures external variable by reference
	// with omitted arguments and return type
	auto inc_get = [&] { return ++c; };
	assert(inc_get() == 2);
	assert(inc_get() == 3);

	// annotated expanded empty inline lambda call:
	[ ] // capture
	( ) // optional list of arguments
	-> void // optional return value
	{ } // body
	( ); // call with arguments

	// annotated expanded sample inline lambda call:
	c = // result
	[c] // capture
	(int a) // optional list of arguments
	-> int // optional return value
	{ return c + a; } // body
	(1); // call with argument
	assert(c == 4);

	// inline lambda which is called in place
	// https://en.wikipedia.org/wiki/Anonymous_function

	// assert((1 + 1) == 2);
	assert([](int a) { return a + 1; }(1) == 2);

	// Actually calling lambda inline is useless
	// and is provided only for demonstration.
}

/// @cond
static int glob;
/// @endcond

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
	auto inc_global = [] () { return ++glob; };
	assert(inc_global() == 1);
	assert(inc_global() == 2);
}

/// Compare with @ref sort_03

void sort_11()
{
	array<int, 10> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
	sort(s.begin(), s.end(),
		  // sort using a lambda expression
		  [](int a, int b)
		  { return a > b; }
		 );
}

/// @}

/**
 @defgroup lambda11_comples More complex Lambdas
 @{
 */

/// @cond
// int use_lambda(int a; int (func*)(int))
static int use_lambda(int a, function<int(int)> f)
{
	return f(a);
}

/// https://en.cppreference.com/w/cpp/utility/functional/function
static function<int(int)> g_f;

/// @endcond

static void set_lambda(function<int(int)> &&f)
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

void dynamic_memory_11()
{
	int d = 0;
	unique_ptr<int> u1;
	assert(!u1);
	u1.reset(&d);
	assert(u1);
	*u1 = 1;
	assert(d == 1);
	unique_ptr<int> u2;
        // u2 = u1; - prohibited
	int * p1 = u1.get();
        u2 = move(u1); // https://en.cppreference.com/w/cpp/utility/move
	assert(p1 == u2.get());
	assert(!u1);
	assert(u2);
	// must release because d is local
	u2.release();
	u2.reset(new int(10));
	assert(*u2 == 10);
	u2.reset(); // deletes int(10)
	assert(u2 == nullptr); // https://en.cppreference.com/w/cpp/language/nullptr

	assert(!u2);

	shared_ptr<int> s1;
	assert(!s1);
	assert(!s1.use_count());
	auto s2 = make_shared<int>(1);
	assert(s2.use_count() == 1);
	s1 = s2;
	assert(s1.use_count() == 2);
	*s1 = 2;
	assert(*s1 == *s1.get());
	assert(*s2 == 2);
	s2.reset();
	assert(s1.use_count() == 1);
	assert(!s2.use_count());
}

/// @cond
#if ! gcc_extension
#define static_assert(a) static_assert(a, "")
#endif
/// @endcond

void types_11()
{
	static_assert(__cpp_decltype);

	int a;
	decltype(a) b;

	static_assert(is_same<decltype(a), decltype(b)>::value);
	static_assert(!is_same<decltype(a), unsigned>::value);
	static_assert(is_same<int, int32_t>::value);
	static_assert(is_same<signed, int32_t>::value);

	static_assert(is_integral<int>::value);
	static_assert(is_integral<bool>::value);
	static_assert(!is_integral<float>::value);
	static_assert(is_pointer<int*>::value);

}
/// @}

int main(void)
{
	init_11();
	auto r = trailing_return_type(1);
	(void) r;
	lambda_basics();
	lambda_capture();
	lambda_complex();
	func_11();
	sort_11();
	dynamic_memory_11();
	static_assert(constexpr_factorial(4));

	types_11();
	return 0;
}
/// @}

extern "C" {
void main3()
{
	struct ab {
		int a;
		int b;
	};


	// Point2D point2D = {.x = 1, .y = 2};
	// Point2D point2D = {.x , };
	ab ab {1, 2};
	(void) ab;
	(void) ab.a;
	(void) ab.b;

	// Point3D point3D {.x = 1, .y = 2, .z = 2};
}
}
