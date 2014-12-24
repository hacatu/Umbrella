#include <parser.h>
#include <ptree.h>
#include <stdlib.h>
#include "parser.h"

int synonym(PRA_Position *p, PRA_Ptree *t){
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_acceptString(p, t, PRA_SKIP, ";")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	return PRA_accept(p, t, PRA_PASS, parens);
}

int constraint(PRA_Position *p, PRA_Ptree *t){
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_acceptString(p, t, PRA_SKIP, ":")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	return PRA_accept(p, t, PRA_PASS, constraint_rec);
}

int constraint_rec(PRA_Position *p, PRA_Ptree *t){
	PRA_try(p, t, PRA_ADD, constraint_head);
	return PRA_sepBy(p, t, PRA_ADD, PRA_SKIP, l_expr_2, fbind, 1, 0);
}

int fbind(PRA_Position *p, PRA_Ptree *t){
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_acceptString(p, t, PRA_SKIP, "->")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	return 1;
}

int constraint_head(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_sepBy(p, t, PRA_ADD, PRA_SKIP, constraint_sub, constraint_sep, 1, 0)){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_acceptString(p, t, PRA_SKIP, "=>")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	return 1;
}

int constraint_sub(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_accept(p, t, PRA_ADD, identifier)){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_acceptString(p, t, PRA_SKIP, ":")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_accept(p, t, PRA_ADD, constraint_rec)){
		return 0;
	}
	return 1;
}

int constraint_sep(PRA_Position *p, PRA_Ptree *t){
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_acceptString(p, t, PRA_SKIP, ",")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	return 1;
}

