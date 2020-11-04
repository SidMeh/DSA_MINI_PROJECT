//#include "operator.h"
#include<limits.h>
#include<stdlib.h>
#include <stdio.h>

typedef struct stack{
    char *a;
    int size;
    int top;
}stack;

void init(stack *s, int len);
void opt_push(stack *s, char op);
int isFull(stack s) ;
int opt_empty(stack s);
char opt_pop(stack *s);
char opt_top(stack s);
/*
int main() {
    stack S;
    init(&S,100);
    opt_push(&S,'+');
    opt_push(&S,'*');
    opt_push(&S,'-');
    printf("%c",opt_pop(&S));
    printf("%c",opt_pop(&S));
    printf("%c",opt_top(S));
    return 0;

}

*/

void init(stack *s, int len){
    s->a = (char*)malloc(sizeof(char)*len);
    s->size = len;
    s->top = -1;
}
int isFull(stack s) {
    if(s.top == s.size-1)
        return 1;
    else
        return 0;
}

int opt_empty(stack s) {
    if(s.top == -1)
        return 1;
    else
        return 0;
}
void opt_push(stack *s, char op){
    if(isFull(*s))
        return ;
    else {
        s->top++;
        s->a[s->top] = op;
        return ;
    }
}

char opt_pop(stack *s) {
 	if(opt_empty(*s))
 		return '\0';
 	else {
 		char op = s->a[s->top];
 		s->top--;
 		return op;
 	}
}


char opt_top(stack s) {
	if(opt_empty(s))
		return '\0';
	else
		return s.a[s.top];
}
/*
#include<stdio.h>
#include<stack.h>
#include<limits.h>

int main() {
    stack s1, s2;
    init(&s1,100);
    init(&s2, 10);
    int item;
    while(scanf("%d", &item)!= -1)
        push(&s1, item);
    printf("Stack 1\n");
    while((item = pop(&s1))!= INT_MIN)
        printf("%d\n", item);
    return 0;
}
*/
