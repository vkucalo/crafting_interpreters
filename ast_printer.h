#pragma once
#include "expr.h"
#include "expr_visitor.h"

class ast_printer : expr_visitor<std::string> {
	std::string print(expr ex) {
		//return ex.accept(this);
	}
};