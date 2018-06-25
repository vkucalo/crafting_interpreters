struct expr_stmt;
struct print_stmt;
struct block_stmt;
struct var_stmt;
struct if_stmt;
struct while_stmt;
struct fun_stmt;

struct stmt_visitor {
    virtual void visit(expr_stmt*) = 0;
    virtual void visit(print_stmt*) = 0;
    virtual void visit(var_stmt* v) = 0;
    virtual void visit(block_stmt* v) = 0;
    virtual void visit(if_stmt* v) = 0;
    virtual void visit(while_stmt* v) = 0;
    virtual void visit(fun_stmt* v) = 0;
};