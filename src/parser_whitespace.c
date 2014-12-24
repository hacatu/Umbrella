#include <parser.h>
#include <ptree.h>
#include <stdlib.h>
#include "parser.h"

int space(PRA_Position *p, PRA_Ptree *t){
	return PRA_repeat(p, t, PRA_SKIP, whitespace_char, 1, 0);
}

int whitespace_char(PRA_Position *p, PRA_Ptree *t){
	return PRA_oneOf(p, t, PRA_SKIP, " \t\v");// note: \n and \r\f are newlines and should be considered seperately, and so should indentation
}

