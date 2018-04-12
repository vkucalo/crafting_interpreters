#pragma once
#include "expr.h"
#include "value.h"

struct interpreter : expr_visitor {

    value result;
    expr* expression;

    interpreter(expr* expr) : expression(expr) {}

    value evaluate(expr* expression){
        expression->accept(this);
        return result;
    }

    bool is_truthy(value val){
        if (val.v_type == NILL_VALUE) return false;
        if (val.v_type == BOOLEAN_VALUE) return true;
        return true;
    }

    void visit(binary* expr){
        value left = evaluate(expr->left);
        value right = evaluate(expr->right);
        switch(expr->op.type){
            case PLUS:
                if (left.v_type == STRING_VALUE && right.v_type == STRING_VALUE)
                    result = value(left.string_value + right.string_value);
                if (left.v_type == DOUBLE_VALUE && right.v_type == DOUBLE_VALUE)
                    result = value(left.double_value + right.double_value);
                break;
            case MINUS:
                if (left.v_type == DOUBLE_VALUE && right.v_type == DOUBLE_VALUE)
                    result = value(left.double_value - right.double_value);
                break;    
            case STAR:
                if (left.v_type == DOUBLE_VALUE && right.v_type == DOUBLE_VALUE)
                    result = value(left.double_value * right.double_value);
                break;
            case SLASH:
                if (left.v_type == DOUBLE_VALUE && right.v_type == DOUBLE_VALUE)
                    result = value(left.double_value / right.double_value);
                break;    
            default:
                result = value();
                break;
        }
    }

	void visit(grouping* expr){
		expr->expression->accept(this);
	}	
	
	void visit(unary* expr){
		value right = evaluate(expr->ex);

        switch(expr->op.type){
            case MINUS: 
                if (right.v_type == DOUBLE_VALUE) 
                    result = value(-right.double_value);
                break;
            case BANG:
                if (is_truthy(right))
                    result = value(!is_truthy(right));
                break;
            default:
                result = value();
                break;
        }
	}
	
	void visit(literal* expr){
		result = expr->val; 
	}

    value interpret(){
        expression->accept(this);
        return result;
    }

};