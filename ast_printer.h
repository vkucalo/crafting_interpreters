#pragma once
#include "expr.h"
#include "token.h"
#include <string>
#include <iostream>

struct ast_printer : expr_visitor {
	expr* expression;
	std::string out;

	ast_printer(expr* ex) : expression(ex) {}


	void visit(binary* expr){
		out += "(";
		out += expr->op.lexeme;
		out += " ";
		expr->left->accept(this);
		out += " ";
		expr->right->accept(this);
		out += " )";
	}

	void visit(grouping* expr){
		out += "grouping (";
		out += " ";
		expr->expression->accept(this);
		out +=  " )";
	}	
	
	void visit(unary* expr){
		out += "(";
		out += " ";
		expr->ex->accept(this);
		out += " )";
	}
	
	void visit(literal* expr){
		if (expr->val.v_type == NILL_VALUE){
			out+= "nil";
			return;
		} 
		out += expr->val.stringify();
	}
	
	std::string print(){
		expression->accept(this);
		return this->out;
	}
};
