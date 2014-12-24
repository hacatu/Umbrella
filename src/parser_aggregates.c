#include <parser.h>
#include <ptree.h>
#include <stdlib.h>
#include "parser.h"

int section(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "(")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(PRA_try(p, t, PRA_ADD, r_expr)){
		PRA_accept(p, t, PRA_SKIP, space);
		if(!PRA_accept(p, t, PRA_ADD, operator)){
			return 0;
		}
		PRA_accept(p, t, PRA_SKIP, space);
		return PRA_acceptString(p, t, PRA_SKIP, ")");
	}
	if(!PRA_accept(p, t, PRA_ADD, operator)){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	PRA_accept(p, t, PRA_ADD, r_expr);
	PRA_accept(p, t, PRA_SKIP, space);
	return PRA_acceptString(p, t, PRA_SKIP, ")");
}


int tuple(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "(")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_alternate(p, t, PRA_ADD, PRA_SKIP, element, element_separator)){
		return 0;
	}
	PRA_accept(p, t, PRA_ADD, element);
	PRA_accept(p, t, PRA_SKIP, space);
	return PRA_acceptString(p, t, PRA_SKIP, ")");
}

int dict(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "[")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_alternate(p, t, PRA_ADD, PRA_SKIP, element, element_separator)){
		return 0;
	}
	PRA_accept(p, t, PRA_ADD, element);
	PRA_accept(p, t, PRA_SKIP, space);
	return PRA_acceptString(p, t, PRA_SKIP, ")");
}

int element(PRA_Position *p, PRA_Ptree *t){
	PRA_accept(p, t, PRA_ADD, subscript);
	return PRA_accept(p, t, PRA_ADD, expr_c);
}

int element_separator(PRA_Position *p, PRA_Ptree *t){
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_acceptString(p, t, PRA_SKIP, ",")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	return 1;
}

int subscript(PRA_Position *p, PRA_Ptree *t){
	PRA_setString(t, "(index)", 7);
	if(!PRA_accept(p, t, PRA_PASS, subscript_sub)){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	PRA_acceptString(p, t, PRA_SKIP, "=");
	PRA_accept(p, t, PRA_SKIP, space);
	return 1;
}

int subscript_sub(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "[")){
		if(!PRA_accept(p, t, PRA_ADD, identifier)){
			return 0;
		}
	}else{
		PRA_accept(p, t, PRA_SKIP, space);
		PRA_accept(p, t, PRA_ADD, expr_c);
		PRA_accept(p, t, PRA_SKIP, space);
		if(!PRA_acceptString(p, t, PRA_SKIP, "]")){
			return 0;
		}
	}
	return 1;
}

