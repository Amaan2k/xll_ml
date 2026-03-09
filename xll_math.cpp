// xll_math.cpp - Math functions
#include "fms_math.h"
#include "xll_ml.h"

#undef CATEGORY
#define CATEGORY L"MATH"

using namespace xll;
using namespace fms::math;

AddIn xai_erf_as(
	Function(XLL_DOUBLE, L"xll_erf_as", CATEGORY L".ERF")
	.Arguments({
		Arg(XLL_DOUBLE, L"x", L"is the value to compute the error function for."),
	})
	.Category(CATEGORY)
	.FunctionHelp(L"Return the error function of x using Abramowitz& Stegun approximation.")
);
double WINAPI xll_erf_as(double x)
{
#pragma XLLEXPORT
	return erf_as(x);
}

AddIn xai_clamp(
    Function(XLL_DOUBLE, L"xll_clamp", L"ML.CLAMP")
    .Arguments({
        Arg(XLL_DOUBLE, L"x",   L"is the value to clamp."),
        Arg(XLL_DOUBLE, L"lo",  L"is the minimum value."),
        Arg(XLL_DOUBLE, L"hi",  L"is the maximum value."),
        })
        .Category(CATEGORY)
    .FunctionHelp(L"Clamp x to the range [lo, hi].")
);
double WINAPI xll_clamp(double x, double lo, double hi)
{
#pragma XLLEXPORT
    if (x < lo) return lo;
    if (x > hi) return hi;
    return x;
}
