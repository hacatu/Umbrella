#include <parser.h>
#include <ptree.h>
#include <stdlib.h>
#include "parser.h"

int sigil(PRA_Position *p, PRA_Ptree *t){
	return PRA_oneOf(p, t, PRA_PASS, "~!$%^&*-+|\\'\":;?/<>,.");
}

int sigils(PRA_Position *p, PRA_Ptree *t){
	return PRA_repeat(p, t, PRA_PASS, sigil, 1, 0);
}

int operator(PRA_Position *p, PRA_Ptree *t){
	if(PRA_accept(p, t, PRA_SKIP, space)){
		if(!PRA_accept(p, t, PRA_PASS, operatorBesidesSpace)){
			PRA_setString(t, " ", 1);
			return 1;
		}
		PRA_accept(p, t, PRA_SKIP, space);
		return 1;
	}
	return PRA_accept(p, t, PRA_PASS, operatorBesidesSpace);
}

int operatorBesidesSpace(PRA_Position *p, PRA_Ptree *t){
	if(PRA_accept(p, t, PRA_PASS, sigils)){
		return 1;
	}
	if(!PRA_acceptString(p, t, PRA_SKIP, "`")){
		return 0;
	}
	PRA_setString(t, "(infixed_operator)", 18);
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_accept(p, t, PRA_ADD, r_expr)){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_acceptString(p, t, PRA_SKIP, "`")){
		return 0;
	}
	return 1;
}

int identifier(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_noneOf(p, t, PRA_PASS, "0123456789`~!$%^&*()-+=|\\{}[]'\":;?/<>,. \n\t\v\n\f")){
		return 0;
	}
	PRA_repeat(p, t, PRA_PASS, identifier_char, 0, 0);
	return 1;
}

int identifier_char(PRA_Position *p, PRA_Ptree *t){
	return PRA_noneOf(p, t, PRA_PASS, "`~!$%^&*()-+=|\\{}[]'\":;?/<>,. \n\t\v\n\f");
}

