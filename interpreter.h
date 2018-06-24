#pragma once
#include "expr.h"
#include "value.h"
#include "lox_runtime_error.h"
#include "stmt.h"
#include "environment.h"
#include "lox_callable.h"

struct interpreter : expr_visitor, stmt_visitor {
    static environment env;
    value result;
    
    interpreter() {};

    value evaluate_var_expr(var_expr* v){
        return env.get(v->tok);
    }

    value evaluate(expr* expression){
        expression->accept(this);
        return result;
    }

    void check_number_operand(token oper, value operand){
        if (operand.v_type == DOUBLE_VALUE) 
            return;
        throw lox_runtime_error(oper, "Operand must be a number.");
    }

    void check_number_operands(token oper, value left, value right){
        if (left.v_type == DOUBLE_VALUE && right.v_type == DOUBLE_VALUE){ 
            if (right.double_value == 0 && oper.type == SLASH)
                throw lox_runtime_error(oper, "Division by 0 not allowed!");
            return;
            }
        throw lox_runtime_error(oper, "Operand must be a number.");
    }

    bool is_truthy(value val){
        if (val.v_type == NILL_VALUE) return false;
        if (val.v_type == BOOLEAN_VALUE) return val.boolean_value;
        if (val.v_type == DOUBLE_VALUE) return val.double_value != 0;
        return true;
    }

    bool is_equal(value left, value right){
        if (left.v_type == BOOLEAN_VALUE && right.v_type == BOOLEAN_VALUE) return left.boolean_value == right.boolean_value;
        if (left.v_type == DOUBLE_VALUE && right.v_type == DOUBLE_VALUE) return left.double_value == right.double_value;
        if (left.v_type == STRING_VALUE && right.v_type == STRING_VALUE) return left.string_value == right.string_value;
        if (left.v_type == NILL_VALUE && right.v_type == NILL_VALUE) return true;
        return false;
    }

    void visit(binary* expr){
        value left = evaluate(expr->left);
        value right = evaluate(expr->right);
        switch(expr->op.type){
            case PLUS:
                if (left.v_type == STRING_VALUE && right.v_type == STRING_VALUE)
                    result = value(left.string_value + right.string_value);
                else if (left.v_type == DOUBLE_VALUE && right.v_type == DOUBLE_VALUE)
                    result = value(left.double_value + right.double_value);
                else
                    throw lox_runtime_error(expr->op, "Unsupported operation.");
                break;
            case MINUS:
                check_number_operands(expr->op, left, right);
                result = value(left.double_value - right.double_value);
                break;    
            case STAR:
                check_number_operands(expr->op, left, right);
                result = value(left.double_value * right.double_value);
                break;
            case SLASH:
                check_number_operands(expr->op, left, right);
                result = value(left.double_value / right.double_value);
                break;    
            case LESS:
                check_number_operands(expr->op, left, right);
                result = value(left.double_value < right.double_value);
                break;   
            case LESS_EQUAL:
                check_number_operands(expr->op, left, right);
                result = value(left.double_value <= right.double_value);
                break; 
            case GREATER:
                check_number_operands(expr->op, left, right);
                result = value(left.double_value > right.double_value);
                break;
            case GREATER_EQUAL:
                check_number_operands(expr->op, left, right);
                result = value(left.double_value >= right.double_value);
                break;
            case BANG_EQUAL:
                result = value(!is_equal(left,right));
                break;
            case EQUAL_EQUAL:
                result = value(is_equal(left,right));
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
                check_number_operand(expr->op, right);
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

    void visit(call_expr* expr){
        value callee = evaluate(expr->callee);

        std::vector<value> arguments;
        for (auto& a : expr->arguments){
            arguments.emplace_back(evaluate(a));
        }
        if (callee.v_type != CALLABLE_VALUE)
            throw lox_runtime_error(expr.paren, "Can only call functions and classes.");

        if (arguments.size() > callee.arity)
            throw lox_runtime_error(expr.paren, std::string("Expected ", callee.arity(), " arguments, got ", arguments.size(), " .");
        
        lox_callable function = callee.callable_value;
        result = function.call(this, function);
    }

    void visit(var_expr* ex) {
        result = evaluate_var_expr(ex);
    }
    
    void visit(assignment_expr* ex){
        value val = evaluate(ex->ex);

        env.assign(ex->left, val);
        result = val;
    }

    void visit(logical_expr* ex){
        value left = evaluate(ex->left);
        if (ex->oper.type == OR){
            if (is_truthy(left)){
                result = left;
                return;
            } 
        }
        else{
            if (!is_truthy(left)){
                result = left;
                return;
            }
        }
        result = evaluate(ex->right);
    }

    void execute(stmt* statement){
        statement->accept(this);
    }

    void execute_block(block_stmt* b, environment inner_env){
        environment *outer = &env;
        try{
            env = inner_env;
            for (auto& st : b->statements)
                execute(st);
        }
        catch(std::exception e){
            std::cout << "error!";
        }
        env = *outer;

    }

    void visit(expr_stmt* ex_stmt){
        evaluate(ex_stmt->expression);
    }

    void visit(print_stmt* pr_stmt){
        std::cout << evaluate(pr_stmt->expression).stringify() << std::endl;
        return;
    }

    void visit(var_stmt* v) {
        value val;
        if (v->expression != nullptr)
           val = evaluate(v->expression);
        env.define(v->name.lexeme, val);
    }

    void visit(block_stmt* b) {
        execute_block(b, new environment(env));
    }
     
    void visit(if_stmt* s) {
        value condition = evaluate(s->condition);
        if (!is_truthy(condition))
            throw lox_runtime_error(token(), "Conditional must evalute to a boolean value.");
        if (condition.boolean_value){
            execute(s->then_branch);
            return;
        }
        execute(s->else_branch);
    }

    void visit(while_stmt* s){
        while(is_truthy(evaluate(s->condition))){
            execute(s->statement);
        }
    }

    value interpret(std::vector<stmt*>& statements) {
        try{
            for(auto& statement : statements) {
                execute(statement);
            }
        }
        catch (std::exception e) {
            std::cout << "error!";
        }
        return result;
    }

};