#include <parser.h>
#include <ptree.h>
#include <stdlib.h>
#include "parser.h"

int literal(PRA_Position *p, PRA_Ptree *t){
	if(PRA_try(p, t, PRA_PASS, integer)){
		return 1;
	}
	if(PRA_accept(p, t, PRA_ADD, decimal)){
		PRA_setString(t, "(decimal)", 9);
		return 1;
	}
	if(PRA_accept(p, t, PRA_ADD, string)){
		PRA_setString(t, "(string)", 8);
		return 1;
	}
	if(PRA_accept(p, t, PRA_ADD, character)){
		PRA_setString(t, "(char)", 6);
		return 1;
	}
	if(PRA_accept(p, t, PRA_ADD, tuple)){
		PRA_setString(t, "(tuple)", 7);
		return 1;
	}
	if(PRA_accept(p, t, PRA_ADD, dict)){
		PRA_setString(t, "(dict)", 6);
		return 1;
	}
	return 0;
}

