#include <parser.h>
#include <ptree.h>
#include <stdlib.h>
#include "parser.h"

int statements(PRA_Position *p, PRA_Ptree *t){
	return PRA_sepBy(p, t, PRA_ADD, PRA_SKIP, statement, nodent, 1, 0);
}

int block(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_accept(p, t, PRA_SKIP, indent)){
		return 0;
	}
	if(!PRA_accept(p, t, PRA_ADD, statements)){
		return 0;
	}
	return PRA_accept(p, t, PRA_SKIP, dedent);
}

int statement(PRA_Position *p, PRA_Ptree *t){
	if(PRA_try(p, t, PRA_ADD, statement_let)){
		PRA_setString(t, "(statement_let)", 15);
		return 1;
	}
	if(PRA_try(p, t, PRA_ADD, statement_continue)){
		PRA_setString(t, "(statement_continue)", 20);
		return 1;
	}
	if(PRA_try(p, t, PRA_ADD, statement_break)){
		PRA_setString(t, "(statement_break)", 17);
		return 1;
	}
	if(PRA_try(p, t, PRA_ADD, statement_return)){
		PRA_setString(t, "(statement_return)", 18);
		return 1;
	}
	if(PRA_try(p, t, PRA_ADD, statement_yield)){
		PRA_setString(t, "(statement_yield)", 17);
		return 1;
	}
	if(PRA_try(p, t, PRA_ADD, statement_throw)){
		PRA_setString(t, "(statement_throw)", 17);
		return 1;
	}
	if(PRA_try(p, t, PRA_ADD, statement_infix)){
		PRA_setString(t, "(statement_infix)", 17);
		return 1;
	}
	if(PRA_try(p, t, PRA_ADD, statement_type)){
		PRA_setString(t, "(statement_type)", 16);
		return 1;
	}
	if(PRA_try(p, t, PRA_ADD, statement_trait)){
		PRA_setString(t, "(statement_trait)", 17);
		return 1;
	}
	if(PRA_try(p, t, PRA_ADD, expr_c)){
		PRA_setString(t, "(statement_expr)", 16);
		return 1;
	}
	return 0;
}

int statement_let(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "let")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_accept(p, t, PRA_ADD, l_expr)){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_acceptString(p, t, PRA_SKIP, "=")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	return PRA_accept(p, t, PRA_ADD, expr_c);
}

int statement_continue(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "continue")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	PRA_accept(p, t, PRA_ADD, identifier);
	return 1;
}

int statement_break(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "break")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	PRA_accept(p, t, PRA_ADD, identifier);
	return 1;
}

int statement_return(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "return")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	PRA_accept(p, t, PRA_ADD, r_expr);
	return 1;
}

int statement_yield(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "yield")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_accept(p, t, PRA_ADD, r_expr)){
		return 1;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	PRA_accept(p, t, PRA_ADD, identifier);
	return 1;
}

int statement_throw(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "throw")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	return PRA_accept(p, t, PRA_ADD, r_expr);
}

int statement_infix(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "infix")){
		return 0;
	}
	if(!PRA_acceptString(p, t, PRA_ADD, "r")){
		if(!PRA_acceptString(p, t, PRA_ADD, "l")){
			return 0;
		}
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_accept(p, t, PRA_ADD, sigils)){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	return PRA_accept(p, t, PRA_PASS, integer);
}

int statement_type(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "type")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_accept(p, t, PRA_ADD, l_expr)){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_acceptString(p, t, PRA_SKIP, "=")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	return PRA_sepBy(p, t, PRA_ADD, PRA_SKIP, l_expr, type_sep, 1, 0);
}

int statement_trait(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "trait")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_accept(p, t, PRA_ADD, l_expr)){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_acceptString(p, t, PRA_SKIP, "=")){
		return 0;
	}
	return PRA_accept(p, t, PRA_SKIP, block);
}

int type_sep(PRA_Position *p, PRA_Ptree *t){
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_acceptString(p, t, PRA_SKIP, "|")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	return 1;
}

