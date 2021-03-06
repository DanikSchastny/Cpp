// Лямбды.cpp : Defines the entry point for the console application.
//
//h(x,y) = f( g1(x), g2(y), g(g11(x),y) ).  -1
// h(x,y) = f( g1(x), g2(y),  g( g11(x), y ),  g( g12(x), y ) ,…, g( g1n(x), y ) ). 
#include "stdafx.h"

template<typename _F, typename _G, typename _G1, typename _G2, typename _G11>
class ComposeFuncClass
{
public:
	ComposeFuncClass(_F _f, _G _g, _G1 _g1, _G2 _g2, _G11 _g11) : f(_f), g(_g), g1(_g1), g2(_g2), g11(_g11) {}

	template<typename T, typename U>
	auto operator () (T x, U y) { return f(g1(x), g2(y), g(g11(x), y)); }

	_F f;
	_G g;
	_G1 g1;
	_G2 g2;
	_G11 g11;
};

class Hx
{
public :
	template<typename _F, typename _G, typename _G1, typename _G2, typename _G11>
	auto operator () (_F _f, _G _g, _G1 _g1, _G2 _g2, _G11 _g11) 
	{ 
		return ComposeFuncClass<_F, _G, _G1, _G2, _G11>(_f, _g, _g1, _g2, _g11); 
	}
};




double sum(double b) { return b; }

template< typename ...Args>
double sum(double a, Args...args)
{
	return a + sum(args...);
}

double sum(double(*_g)(double), double a)
{ return _g(a); }

template<typename ...Args>
double sum(double (*_g)(double), double a, Args...args)
{
	return _g(a) + sum(_g,args...);
}

double sum(double(*_g)(double, double),double y, double a)
{
	return _g(a, y); 
}

template<typename...Args>
double sum(double(*_g)(double, double),double y, double a, Args...args)
{
	return _g(a, y) + sum(_g, y ,args...);
}

template<typename...Args>
double sum(double a, double b, double(*_g)(double, double), double y, double c, Args...args)
{
	return  a + b + _g(c, y) + sum(_g, y, args...);
}










int main()
{

	auto f = [](auto x, auto y, auto z) {return x + y + z; };
	auto g = [](auto x, auto y) { return x * y; };
	auto g1 = [](auto x) {return pow(2, x); };
	auto g2 = [](auto x) {return -1 * x; };
	auto g11 = [](auto x) {return sin(x); };
	auto g12 = [](auto x) {return cos(x); };
	auto g13 = [](auto x) {return sin(x) / cos(x); };



	//Построение композиции функций с использованием лямбда - выражений:

	auto composeFunct = [](auto _f, auto _g, auto _g1, auto _g2, auto _g11)-> auto
	{ return [_f, _g, _g1, _g2, _g11](auto x, auto y) {return _f(_g1(x), _g2(y), _g(_g11(x), y)); };
	};

	auto res = composeFunct(f, g, g1, g2, g11);

	std::cout <<"1: "<< res(1, 20.2) << std::endl;


	//построение композиции с использованием функтора:

	Hx lyambda;
	auto composeFunct2 = lyambda(f, g, g1, g2, g11);
	std::cout <<"2: "<< composeFunct2(1, 20.2) << std::endl;

	//Построение композиции с переменным кол-вом аргументов:
	// h(x,y) = f( g1(x), g2(y),  g( g11(x), y ),  g( g12(x), y ) ,…, g( g1n(x), y ) ).

	auto dg = [](auto x, auto y) { return x * y; };
	auto dg11 = [](auto x){return (double)sin(x); };
	auto dg12 = [](auto x ) {return cos(x); };
	auto dg13 = [](auto x) {return sin(x) / cos(x); };
	auto dg14 = [](auto x) {return x; };
	auto dg15 = [](auto x) {return 2 * x; };

	

	auto bsum = [](auto...args)->double {return sum(args...); };

	auto bs2 = [](auto _f, auto _g, auto _g1, auto _g2,  auto...args)
	{return[ _f, _g, _g1, _g2, args...](auto x, double y){return _f(_g1(x), _g2(y), _g, y, args(x)...); }; };

    auto fff = bs2(bsum, dg, dg11, dg12, dg13, dg14, dg15);
	std::cout<<"3: "<< fff(1, 1)  <<std::endl;

	/*
	
	auto funct = [](auto _f, auto _g, auto...args)->auto
	{return[_f, args...](auto x) {return _f(args(x)...); }; };

	auto Fn = funct(bsum, dg11, dg12, dg13, ...) = dg11 + dg12 + dg13 +...
	*/
	system("pause");
    return 0;
}

