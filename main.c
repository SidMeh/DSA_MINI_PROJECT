#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "evaluate.c"
//#include "Number2.c"

//char temp[100];
//char cpy[2];
//char zero[2] = "0";
stack s;
opt_stack q;
/*
int main() {
	printf("Enter your calculations here,\nit will provide an answer !!\n");
	char ch[1000];
	gets(ch);
	evaluate(ch);
	printf("The result is : \n");
	traverse_fwd(s.l[s.top]);
	return 0;
}

*/
int main() {
	init_opd(&s);
	opt_init(&q,100);
	printf("Enter a string : \n");
	char c[1000];
	gets(c);
//	char c[100000] = "15 * 2";
	char *psr = c;
	evaluate(c);
	printf("The result is : \n");
	traverse_fwd(s.l[s.top]);
return 0;
}

