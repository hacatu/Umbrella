#include <parser.h>
#include <ptree.h>
#include <stdlib.h>
#include "parser.h"

int string(PRA_Position *p, PRA_Ptree *t){//note: need to add heredocs
	if(!PRA_acceptString(p, t, PRA_SKIP, "\"")){
		return 0;
	}
	if(!PRA_repeat(p, t, PRA_PASS, string_char, 0, 0)){
		return 0;
	}
	return PRA_acceptString(p, t, PRA_SKIP, "\"");
}

int string_char(PRA_Position *p, PRA_Ptree *t){
	if(PRA_noneOf(p, t, PRA_PASS, "\\\"")){
		return 1;
	}
	return PRA_accept(p, t, PRA_PASS, escape);
}

int escape(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "\\")){
		return 0;
	}
	switch(PRA_currentChar(p)){
		case 'f':
		PRA_setString(t, "\f", 1);
		return 1;
		case 'n':
		PRA_setString(t, "\n", 1);
		return 1;
		case 'r':
		PRA_setString(t, "\r", 1);
		return 1;
		case 't':
		PRA_setString(t, "\t", 1);
		return 1;
		case 'v':
		PRA_setString(t, "\v", 1);
		return 1;
		case '\\':
		PRA_setString(t, "\\", 1);
		return 1;
		case '\'':
		PRA_setString(t, "'", 1);
		return 1;
		case '"':
		PRA_setString(t, "\"", 1);
		return 1;
		case 'o':
		PRA_setString(t, (char[]){(char)strtol((char[]){PRA_getChar(p), PRA_getChar(p), PRA_getChar(p), '\0'}, NULL, 8), '\0'}, 1);
		return 1;
		case 'x':
		PRA_setString(t, (char[]){(char)strtol((char[]){PRA_getChar(p), PRA_getChar(p), '\0'}, NULL, 16), '\0'}, 1);
		return 1;
		default:
		return 0;
	}
}

int character(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "'")){
		return 0;
	}
	if(!PRA_noneOf(p, t, PRA_PASS, "\\'")){
		if(!PRA_accept(p, t, PRA_PASS, escape)){
			return 0;
		}
	}
	return PRA_acceptString(p, t, PRA_SKIP, "'");
}

