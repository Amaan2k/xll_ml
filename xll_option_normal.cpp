// xll_option_normal.cpp
#include "fms_option_normal.h"
#include "xll_ml.h"

#undef CATEGORY
#define CATEGORY L"OPTION"

using namespace xll;
using namespace fms::option;

AddIn xai_option_normal(
	Function(XLL_HANDLEX, L"xll_option_normal", L"\\" CATEGORY L".NORMAL")
	.Arguments({
		})
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(L"Return handle to normal option pricing model.")
);
HANDLEX WINAPI xll_option_normal()
{
#pragma XLLEXPORT
	HANDLEX result = INVALID_HANDLEX;
	
	try {
		static handle<base<>> m_(new normal<>{});
		ensure(m_);
		result = m_.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (...) {
		XLL_ERROR(__FUNCTION__ ": unknown exception");
	}
	
	return result;
}
