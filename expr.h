#pragma once
#include "token.h" 

template <typename R>
struct expr {
	virtual R accept();
};
template <typename R>
 struct binary : expr<R> { 
	expr<R> left;
	token oper;
	expr<R> right;

	binary(expr<R> left,token oper,expr<R> right) {
		this-> left =  left;
		this-> oper =  oper;
		this-> right =  right;
	} 

	virtual R accept(expr_visitor& visitor) {
		return visitor.visit(this);
	}
};

template <typename R>
 struct grouping : expr<R> { 
	expr<R> expression;

	grouping(expr<R> expression) {
		this-> expression =  expression;
	} 

	virtual R accept(expr_visitor& visitor) {
		return visitor.visit(this);
	}
};

template <typename R>
 struct literal : expr<R> { 
	std::string value;

	literal(std::string value) {
		this-> value =  value;
	} 

	virtual R accept(expr_visitor& visitor) {
		return visitor.visit(this);
	}
};

template <typename R>
 struct unary : expr<R> { 
	token oper;
	expr<R> right;

	unary(token oper,expr<R> right) {
		this-> oper =  oper;
		this-> right =  right;
	} 

	virtual R accept(expr_visitor& visitor) {
		return visitor.visit(this);
	}
};

