#include <parser.h>
#include <ptree.h>
#include <stdlib.h>
#include "parser.h"

typedef struct{
	size_t indent;
} IndentState;

int indent(PRA_Position *p, PRA_Ptree *t){
	size_t margin = ((IndentState*)PRA_getState(p))->indent;
	if(!PRA_accept(p, t, PRA_SKIP, newline)){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	return margin < (((IndentState*)PRA_getState(p))->indent = PRA_currentColumn(p) - 1);
}

int nodent(PRA_Position *p, PRA_Ptree *t){
	size_t margin = ((IndentState*)PRA_getState(p))->indent;
	if(!PRA_accept(p, t, PRA_SKIP, newline)){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	return margin == (((IndentState*)PRA_getState(p))->indent = PRA_currentColumn(p) - 1);
}

int dedent(PRA_Position *p, PRA_Ptree *t){
	size_t margin = ((IndentState*)PRA_getState(p))->indent;
	if(!PRA_accept(p, t, PRA_SKIP, newline)){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, space);
	return margin > (((IndentState*)PRA_getState(p))->indent = PRA_currentColumn(p) - 1);
}

int start(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_allocState(p, sizeof(IndentState))){
		return 0;
	}
	*((IndentState*)PRA_getState(p)) = (IndentState){.indent = 0};
	if(!PRA_accept(p, t, PRA_PASS, statements)){
		return 0;
	}
	PRA_accept(p, t, PRA_SKIP, newline);
	return 1;
}

int newline(PRA_Position *p, PRA_Ptree *t){
	PRA_accept(p, t, PRA_SKIP, space);
	if(!PRA_acceptString(p, t, PRA_SKIP, "\n")){
		return 0;
	}
	((IndentState*)PRA_getState(p))->indent = 0;
	return 1;
}

