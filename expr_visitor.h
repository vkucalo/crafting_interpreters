#pragma once
#include "expr.h"

template <typename T>
struct expr_visitor {
	virtual T visit(binary& ex);
	virtual T visit(grouping& ex);
	virtual T visit(literal& ex);
	virtual T visit(binary& ex);
};
