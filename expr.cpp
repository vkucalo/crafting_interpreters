#include "expr.h"

grouping::grouping(expr* e) : expression(e) {};
void grouping::accept(expr_visitor* visitor){
    visitor->visit(this);
}

binary::binary(expr* l, token tok, expr* r) : left(l), op(tok), right(r) {};
void binary::accept(expr_visitor* visitor){
    visitor->visit(this);
}

unary::unary(expr* e, token t) : ex(e), op(t) {};
void unary::accept(expr_visitor* visitor){
    visitor->visit(this);
}

literal::literal(std::string v) : val(v) {};
literal::literal(double d) : val(d) {};
literal::literal(bool b) : val(b) {};
literal::literal() : val() {};
void literal::accept(expr_visitor* visitor) {
    visitor->visit(this);
}

var_expr::var_expr(token t) : tok(t) {};
void var_expr::accept(expr_visitor* visitor) {
    visitor->visit(this);
}


assignment_expr::assignment_expr(expr* e, token l) : ex(e), left(l) {};
void assignment_expr::accept(expr_visitor* visitor) {
    visitor->visit(this);
}

logical_expr::logical_expr(expr* l, token t, expr* r) : left(l), oper(t), right(r) {};
void logical_expr::accept(expr_visitor* visitor) {
    visitor->visit(this);
}


call_expr::call_expr(expr* c, token par, std::vector<expr*>& args) : callee(c), paren(par), arguments(args) {};
void call_expr::accept(expr_visitor* visitor){
    visitor->visit(this);
}

