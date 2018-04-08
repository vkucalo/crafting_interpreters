#pragma once
#include "expr.h"
#include "token.h"
#include <string>
#include <iostream>

struct ast_printer : expr_visitor {
	expr* expression;


	ast_printer(expr* ex) : expression(ex) {}


	std::string visit(binary* expr){
		std::string out;
		out += "(";
		out += expr->op.lexeme;
		out += " ";
		out += expr->left->accept(this);
		out += " ";
		out += expr->right->accept(this);
		out += " )";
		return out;
	}

	std::string visit(grouping* expr){
		std::string out;
		out += "grouping (";
		out += " ";
		out += expr->expression->accept(this);
		out +=  " )";
		return out;
	}	
	
	std::string visit(unary* expr){
		std::string out;
		out += "(";
		out += " ";
		out += expr->ex->accept(this);
		out += " )";
		return out;
	}
	
	std::string visit(literal* expr){
		if (expr->value.empty()) return "nil";
		return expr->value;
	}
	
	std::string print(){
		return expression->accept(this);
	}
};
