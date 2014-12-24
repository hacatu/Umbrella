#include <parser.h>
#include <ptree.h>
#include <stdlib.h>
#include "parser.h"

int digit_2(PRA_Position *p, PRA_Ptree *t){
	return PRA_oneOf(p, t, PRA_PASS, "01");
}

int digit_8(PRA_Position *p, PRA_Ptree *t){
	return PRA_oneOf(p, t, PRA_PASS, "01234567");
}

int digit_10(PRA_Position *p, PRA_Ptree *t){
	return PRA_oneOf(p, t, PRA_PASS, "0123456789");
}

int digit_16(PRA_Position *p, PRA_Ptree *t){
	return PRA_oneOf(p, t, PRA_PASS, "0123456789abcdefABCDEF");
}

int digit_64(PRA_Position *p, PRA_Ptree *t){
	return PRA_oneOf(p, t, PRA_PASS, "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

int int_2(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "0b")){
		return 0;
	}
	return PRA_repeat(p, t, PRA_PASS, digit_2, 1, 0);
}

int int_8(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "0o")){
		return 0;
	}
	return PRA_repeat(p, t, PRA_PASS, digit_8, 1, 0);
}

int int_10(PRA_Position *p, PRA_Ptree *t){
	return PRA_repeat(p, t, PRA_PASS, digit_10, 1, 0);
}

int int_16(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "0x")){
		return 0;
	}
	return PRA_repeat(p, t, PRA_PASS, digit_16, 1, 0);
}

int int_64(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_acceptString(p, t, PRA_SKIP, "0s")){
		return 0;
	}
	return PRA_repeat(p, t, PRA_PASS, digit_64, 1, 0);
}

int integer(PRA_Position *p, PRA_Ptree *t){
	if(PRA_try(p, t, PRA_ADD, int_2)){
		PRA_setString(t, "(int_2)", 7);
		return 1;
	}
	if(PRA_try(p, t, PRA_ADD, int_8)){
		PRA_setString(t, "(int_8)", 7);
		return 1;
	}
	if(PRA_try(p, t, PRA_ADD, int_16)){
		PRA_setString(t, "(int_16)", 8);
		return 1;
	}
	if(PRA_try(p, t, PRA_ADD, int_64)){
		PRA_setString(t, "(int_64)", 8);
		return 1;
	}
	if(PRA_try(p, t, PRA_ADD, int_10)){
		PRA_setString(t, "(int_10)", 8);
		return 1;
	}
	return 0;
}

int decimal(PRA_Position *p, PRA_Ptree *t){
	PRA_setString(t, "(decimal)", 9);
	if(PRA_accept(p, t, PRA_ADD, decimal_sub)){
		return 1;
	}
	return 0;
}

int decimal_sub(PRA_Position *p, PRA_Ptree *t){
	if(!PRA_accept(p, t, PRA_PASS, int_10)){
		return 0;
	}
	if(!PRA_acceptString(p, t, PRA_PASS, ".")){
		return 0;
	}
	if(!PRA_accept(p, t, PRA_PASS, int_10)){
		return 0;
	}
	if(!PRA_oneOf(p, t, PRA_PASS, "eE")){
		return 1;
	}
	PRA_acceptString(p, t, PRA_PASS, "-");
	if(!PRA_accept(p, t, PRA_PASS, int_10)){
		return 0;
	}
	return 1;
}

