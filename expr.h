#pragma once
#include "token.h"


struct expr {
	
};

struct binary : public expr {
	expr left;
	token oper;
	expr right;
	binary(expr left, token oper, expr right) {
		this->left = left;
		this->oper = oper;
		this->right = right;
	}
};

struct grouping : public expr {
	expr expression;
	grouping(expr expression) {
		this->expression = expression;
	}
};

struct literal : public expr {
	std::string value;
	literal(const std::string& value) {
		this->value = value;
	}
};

struct unary : public expr {
	token oper;
	expr right;
	unary(token oper, expr right) {
		this->oper = oper;
		this->right = right;
	}
}