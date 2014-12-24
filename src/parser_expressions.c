#include <parser.h>
#include <ptree.h>
#include <stdlib.h>
#include "parser.h"

int expr_c(PRA_Position *p, PRA_Ptree *t){
	if(PRA_try(p, t, PRA_PASS, expr_c_sub)){
		return 1;
	}
	return PRA_accept(p, t, PRA_PASS, r_expr);
}

int expr_c_sub(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_accept(p, t, PRA_ADD, l_expr)){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_accept(p, t, PRA_ADD, op_c)){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	return PRA_accept(p, t, PRA_ADD, expr_c);
}

int op_c(PRA_Position *p, PRA_Ptree *t){
	PRA_setString(t, "(op_c)", 6);
	if(!PRA_accept(p, t, PRA_ADD, operatorBesidesSpace)){
		return 0;
	}
	return PRA_acceptString(p, t, PRA_SKIP, "=");
}

int l_expr(PRA_Position *p, PRA_Ptree *t){
	return PRA_accept(p, t, PRA_PASS, l_expr_3);
}

int l_expr_3(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_accept(p, t, PRA_ADD, l_expr_0)){
		return 0;
	}
	PRA_alternate(p, t, PRA_SKIP, PRA_ADD, space, l_expr_1);
	return 1;
}

int l_expr_1(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_accept(p, t, PRA_ADD, parens)){
		return 0;
	}
	PRA_repeat(p, t, PRA_ADD, synonym, 0, 0);
	PRA_repeat(p, t, PRA_ADD, constraint, 0, 0);
	return 1;
}

int l_expr_0(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_ADD, "*")){
		return PRA_accept(p, t, PRA_ADD, l_expr_2);
	}
	return PRA_accept(p, t, PRA_ADD, l_expr_0);
}

int l_expr_2(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_accept(p, t, PRA_ADD, parens)){
		return 0;
	}
	PRA_accept(p, t, PRA_ADD, subscript_sub);
	return 1;
}

int r_expr(PRA_Position *p, PRA_Ptree *t){
	return PRA_sepBy(p, t, PRA_ADD, PRA_ADD, r_expr_0, operator, 1, 0);
}

int r_expr_0(PRA_Position *p, PRA_Ptree *t){
	if(PRA_oneOf(p, t, PRA_ADD, "*&!-")){
		return PRA_accept(p, t, PRA_ADD, r_expr_0);
	}
	if(PRA_acceptString(p, t, PRA_ADD, "..")){
		return PRA_accept(p, t, PRA_ADD, r_expr_0);
	}
	return PRA_accept(p, t, PRA_ADD, l_expr_2);
}

