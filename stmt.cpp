#include "stmt.h"

expr_stmt::expr_stmt(expr* ex) : expression(ex) {};
void expr_stmt::accept(stmt_visitor* visitor){
    visitor->visit(this);
}

print_stmt::print_stmt(expr* ex) : expression(ex) {};
void print_stmt::accept(stmt_visitor* visitor){
    visitor->visit(this);
}

var_stmt::var_stmt(expr* e, token t) : expression(e), name(t) {};
void var_stmt::accept(stmt_visitor* visitor){
    visitor->visit(this);
}

block_stmt::block_stmt(std::vector<stmt*> s) : statements(s) {};
void block_stmt::accept(stmt_visitor* visitor){
    visitor->visit(this);
}

if_stmt::if_stmt(expr* c, stmt* t, stmt* e) : condition(c), then_branch(t), else_branch(e) {};
void if_stmt::accept(stmt_visitor* visitor){
    visitor->visit(this);
}

while_stmt::while_stmt(expr* c, stmt* s) : condition(c), statement(s) { };
void while_stmt::accept(stmt_visitor* visitor){
    visitor->visit(this);
}

fun_stmt::fun_stmt(token n, std::vector<token> p, block_stmt* b) : name(n), parameters(p), body(b) {};
void fun_stmt::accept(stmt_visitor* visitor) {
    visitor->visit(this);
}
