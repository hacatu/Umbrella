#include <parser.h>
#include <ptree.h>

int space(PRA_Position *p, PRA_Ptree *t);//
int whitespace_char(PRA_Position *p, PRA_Ptree *t);//
int indent(PRA_Position *p, PRA_Ptree *t);//####
int nodent(PRA_Position *p, PRA_Ptree *t);//####
int dedent(PRA_Position *p, PRA_Ptree *t);//####
int identifier(PRA_Position *p, PRA_Ptree *t);//
int identifier_char(PRA_Position *p, PRA_Ptree *t);//
int operator(PRA_Position *p, PRA_Ptree *t);//
int operatorBesidesSpace(PRA_Position *p, PRA_Ptree *t);//
int sigils(PRA_Position *p, PRA_Ptree *t);//
int sigil(PRA_Position *p, PRA_Ptree *t);//
int integer(PRA_Position *p, PRA_Ptree *t);//
int int_2(PRA_Position *p, PRA_Ptree *t);//
int int_8(PRA_Position *p, PRA_Ptree *t);//
int int_10(PRA_Position *p, PRA_Ptree *t);//
int int_16(PRA_Position *p, PRA_Ptree *t);//
int int_64(PRA_Position *p, PRA_Ptree *t);//
int digit_2(PRA_Position *p, PRA_Ptree *t);//
int digit_8(PRA_Position *p, PRA_Ptree *t);//
int digit_10(PRA_Position *p, PRA_Ptree *t);//
int digit_16(PRA_Position *p, PRA_Ptree *t);//
int digit_64(PRA_Position *p, PRA_Ptree *t);//
int decimal(PRA_Position *p, PRA_Ptree *t);//
int decimal_sub(PRA_Position *p, PRA_Ptree *t);//
int literal(PRA_Position *p, PRA_Ptree *t);//
int string(PRA_Position *p, PRA_Ptree *t);//
int string_char(PRA_Position *p, PRA_Ptree *t);//
int character(PRA_Position *p, PRA_Ptree *t);//
int tuple(PRA_Position *p, PRA_Ptree *t);//
int dict(PRA_Position *p, PRA_Ptree *t);//
int start(PRA_Position *p, PRA_Ptree *t);//
int statements(PRA_Position *p, PRA_Ptree *t);//
int statement(PRA_Position *p, PRA_Ptree *t);//
int statement_let(PRA_Position *p, PRA_Ptree *t);//
int statement_continue(PRA_Position *p, PRA_Ptree *t);//
int statement_break(PRA_Position *p, PRA_Ptree *t);//
int statement_return(PRA_Position *p, PRA_Ptree *t);//
int statement_yield(PRA_Position *p, PRA_Ptree *t);//
int statement_throw(PRA_Position *p, PRA_Ptree *t);//
int statement_infix(PRA_Position *p, PRA_Ptree *t);//
int statement_type(PRA_Position *p, PRA_Ptree *t);//
int statement_trait(PRA_Position *p, PRA_Ptree *t);//
int type_sep(PRA_Position *p, PRA_Ptree *t);//
int newline(PRA_Position *p, PRA_Ptree *t);//
int block(PRA_Position *p, PRA_Ptree *t);//
int expr_c(PRA_Position *p, PRA_Ptree *t);//
int expr_c_sub(PRA_Position *p, PRA_Ptree *t);//
int op_c(PRA_Position *p, PRA_Ptree *t);//
int l_expr(PRA_Position *p, PRA_Ptree *t);//
int l_expr_3(PRA_Position *p, PRA_Ptree *t);//
int l_expr_1(PRA_Position *p, PRA_Ptree *t);//
int l_expr_2(PRA_Position *p, PRA_Ptree *t);//
int l_expr_0(PRA_Position *p, PRA_Ptree *t);//
int parens(PRA_Position *p, PRA_Ptree *t);//
int parens_sub(PRA_Position *p, PRA_Ptree *t);//
int synonym(PRA_Position *p, PRA_Ptree *t);//
int constraint(PRA_Position *p, PRA_Ptree *t);//
int constraint_rec(PRA_Position *p, PRA_Ptree *t);//
int constraint_head(PRA_Position *p, PRA_Ptree *t);//
int constraint_sub(PRA_Position *p, PRA_Ptree *t);//
int constraint_sep(PRA_Position *p, PRA_Ptree *t);//
int fbind(PRA_Position *p, PRA_Ptree *t);//
int r_expr(PRA_Position *p, PRA_Ptree *t);//
int r_expr_0(PRA_Position *p, PRA_Ptree *t);//
int section(PRA_Position *p, PRA_Ptree *t);//
int escape(PRA_Position *p, PRA_Ptree *t);//
int element(PRA_Position *p, PRA_Ptree *t);//
int element_separator(PRA_Position *p, PRA_Ptree *t);//
int subscript(PRA_Position *p, PRA_Ptree *t);//
int subscript_sub(PRA_Position *p, PRA_Ptree *t);//

