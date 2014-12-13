#include <parser.h>
#include <ptree.h>

/*
space=####
indent=####
dedent=####
identifier=
	[^0-9`~!$%^&*()-+=|\\{}[\]'":;?/<>,.] [`~!$%^&*()-+=|\\{}[\]'":;?/<>,.]*
operator=
	space? sigils space?
	space? "`" space? r_expr space? "`" space?
	space
sigils=
	[~!$%^&*-+|\\'":;?/<>,.]+
int=
	int_2
	int_8
	int_10
	int_16
	int_64
int_2=
	"0b" digit_2+
int_8=
	"0o" digit_8+
int_10=
	"0d"? digit_10+
int_16=
	"0x" digit_16+
int_64=
	"0s" digit_64+
digit_2=
	[01]
digit_8=
	[0-7]
digit_10=
	[0-9]
digit_16=
	[0-9a-fA-F]
digit_64=
	[0-9a-zA-Z]
literal=
	int
	decimal
	string
	char
	tuple
	dict
start=
	statements
statements=
	(statement space? "\n")*
block=
	indent statements dedent
statement=
	"let" space l_expr space? "=" space? expr_c
	"continue" (space identifier)?
	"break" (space identifier)?
	"return" (space r_expr)?
	"yield" (space r_expr (space identifier)?)?
	"throw" (space r_expr)
	"infixr"|"infixl" space sigils space int
	"type" l_expr space? "=" space? l_expr (space? "|" space? l_expr)*
	"trait" space l_expr space? "=" block
	expr_c
expr_c=
	l_expr space? op_c space? expr_c
	r_expr
op_c=
	sigils "="
	"`" space? r_expr space? "`" "="
l_expr=
	l_expr_3
l_expr_3=
	l_expr_0 (space l_expr_1)*
l_expr_1=
	parens (space? ";" space? parens)? (space? ":" space? constraint)*
l_expr_0=
	("*")* l_expr_2
l_expr_2=
	parens (space? ("." space? identifier)|("[" space? expr_c space? "]"))*
parens=
	section
	"(" space? expr_c space? ")"
	literal
	identifier
constraint=
	(identifer space? ":" space? constraint space? ("," space? identifier space? ":" space? constraint space?)* "=>" space?)? l_expr_2 (space? "->" space? l_expr_2)*
r_expr=
	r_expr_0 (operator r_expr_0)*
r_expr_0=
	([*&!-] | "..")* l_expr_2
section=####
string=
	"\"" ([^\\"] | escape)* "\""
	"'" <HEREDOC> "\"" ... "\"" <HEREDOC> "'"
char=
	"'" ([^\\'] | escape)? "'"
escape=####
tuple=
	"(" space? ")"
	"(" (space? element space? ",")+ (space? element space?)? ")"
dict=
	"[" (space? element space? ",")* (space? element space?)? "]"
element=
	index? expr_c
index=
	"[" (space? expr_c space?)? "]" space? "=" space?
	"." identifier? space? "=" space?
decimal=####
*/

int space(PRA_Position *p, PRA_Ptree *t);
int optionalSpace(PRA_Position *p, PRA_Ptree *t);
int indent(PRA_Position *p, PRA_Ptree *t);
int dedent(PRA_Position *p, PRA_Ptree *t);
int identifier(PRA_Position *p, PRA_Ptree *t);
int operator(PRA_Position *p, PRA_Ptree *t);
int operatorBesidesSpace(PRA_Position *p, PRA_Ptree *t);
int sigils(PRA_Position *p, PRA_Ptree *t);
int sigil(PRA_Position *p, PRA_Ptree *t);
int integer(PRA_Position *p, PRA_Ptree *t);
int int_2(PRA_Position *p, PRA_Ptree *t);
int int_8(PRA_Position *p, PRA_Ptree *t);
int int_10(PRA_Position *p, PRA_Ptree *t);
int int_16(PRA_Position *p, PRA_Ptree *t);
int int_64(PRA_Position *p, PRA_Ptree *t);
int digit_2(PRA_Position *p, PRA_Ptree *t);
int digit_8(PRA_Position *p, PRA_Ptree *t);
int digit_10(PRA_Position *p, PRA_Ptree *t);
int digit_16(PRA_Position *p, PRA_Ptree *t);
int digit_64(PRA_Position *p, PRA_Ptree *t);
int decimal(PRA_Position *p, PRA_Ptree *t);
int literal(PRA_Position *p, PRA_Ptree *t);
int string(PRA_Position *p, PRA_Ptree *t);
int character(PRA_Position *p, PRA_Ptree *t);
int tuple(PRA_Position *p, PRA_Ptree *t);
int dict(PRA_Position *p, PRA_Ptree *t);
int start(PRA_Position *p, PRA_Ptree *t);
int statements(PRA_Position *p, PRA_Ptree *t);
int statement(PRA_Position *p, PRA_Ptree *t);
int newline(PRA_Position *p, PRA_Ptree *t);
int block(PRA_Position *p, PRA_Ptree *t);
int expr_c(PRA_Position *p, PRA_Ptree *t);
int op_c(PRA_Position *p, PRA_Ptree *t);
int l_expr(PRA_Position *p, PRA_Ptree *t);
int l_expr_3(PRA_Position *p, PRA_Ptree *t);
int l_expr_1(PRA_Position *p, PRA_Ptree *t);
int l_expr_2(PRA_Position *p, PRA_Ptree *t);
int l_expr_0(PRA_Position *p, PRA_Ptree *t);
int parens(PRA_Position *p, PRA_Ptree *t);
int constraint(PRA_Position *p, PRA_Ptree *t);
int r_expr(PRA_Position *p, PRA_Ptree *t);
int r_expr_0(PRA_Position *p, PRA_Ptree *t);
int section(PRA_Position *p, PRA_Ptree *t);
int escape(PRA_Position *p, PRA_Ptree *t);
int element(PRA_Position *p, PRA_Ptree *t);
int subscript(PRA_Position *p, PRA_Ptree *t);



