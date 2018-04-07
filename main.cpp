#include "ast_printer.h"

int main(){
	literal l1("1234");
	literal l2("fdsfsd");
	token t(PLUS, "+", "", 1); 
	binary expr(&l1, t, &l2);
	ast_printer pr;
    binary* bp = &expr;
	std::cout << pr.visit(bp);

    return 0;
}