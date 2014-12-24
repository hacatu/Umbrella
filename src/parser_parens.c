#include <parser.h>
#include <ptree.h>
#include <stdlib.h>
#include "parser.h"

int parens(PRA_Position *p, PRA_Ptree *t){
	if(PRA_try(p, t, PRA_ADD, section)){
		PRA_setString(t, "(section)", 9);
		return 1;
	}
	if(PRA_try(p, t, PRA_ADD, parens_sub)){
		PRA_setString(t, "(parens)", 8);
		return 1;
	}
	if(PRA_try(p, t, PRA_PASS, literal)){
		return 1;
	}
	if(PRA_try(p, t, PRA_ADD, identifier)){
		PRA_setString(t, "(identifier)", 12);
		return 1;
	}
	return 0;
}

int parens_sub(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "(")){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_accept(p, t, PRA_PASS, expr_c)){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	return PRA_acceptString(p, t, PRA_SKIP, ")");
}

