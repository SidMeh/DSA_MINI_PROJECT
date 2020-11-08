#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "Number2.c"
#include "operator.c"
void power(stack *s);
#define START 10 
#define DIGIT 20
#define OPERATOR 30
#define ERROR 40
#define STOP 50
#define SPACEN 60
#define SPACEP 70
char temp[100];
char cpy[2];
char zero[2] = "0";
stack s;
opt_stack q;

typedef struct token{
 int type;
}token;

void evaluate(char *ch);
int precedence(char op);
void applyop(char op);

int main() {
	init_opd(&s);
	opt_init(&q,100);
	printf("Enter a string : ");
	char c[100000] = "60 ^ 6";
	char *psr = c;
	evaluate(c);
	printf("The result is : \n");
	traverse_fwd(s.l[s.top]);
return 0;
}
//printf("Worked fine");
void evaluate(char *c) {
	char op;
	int currstate = START;
	token t;
	int i = 0;
	while(c[i] != '\0') {
	
	switch(currstate) {
		
		case START : 
		printf("Worked fine 0 ");
			if(isdigit(c[i])) {
				t.type = DIGIT;
				currstate = DIGIT;
				strcpy(temp,zero);
				while(isdigit(c[i])) {
					cpy[0] = c[i];
					strcat(temp,cpy);
					i++;
					
				}
				push_opd(&s,temp);
				traverse_fwd(s.l[s.top]);
				printf("\n");
				//while(isdigit(c[i]))
				//	i++ ;
			}
					
			else if(c[i] == '\0') {
				currstate = STOP;
				t.type = STOP;
			}
				
			else if(c[i] == ' '){
				currstate = SPACEN;
				t.type = SPACEN;
			}
				
			else if(isalpha(c[i]))
				currstate == ERROR;
				
			else if(c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/' || c[i] == '%' || c[i] == '^')
				currstate == ERROR;
			i--;
			printf("\n%c    %d\n",c[i],i);
			break;
			
	
		case DIGIT:
			printf("Worked fine 1 ");
			
			if(c[i] == ' '){
				currstate = SPACEN;
				t.type = SPACEN;
			//	printf(" 13 ");
			}
			
			else if(c[i] == '\0'){
				currstate = STOP;
				t.type = STOP;
			//	printf(" 23 ");
			}
				
			else if(isalpha(c[i]))
				currstate == ERROR;
				
			else if(c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/' || c[i] == '%' || c[i] == '^'){
			//	printf(" 231 ");
				currstate == ERROR;
				return;
			}
			printf("\n%c    %d\n",c[i],i);
			break;
		
			
		case SPACEN:
			printf("Worked fine 2 ");
		//	i--;
			if(c[i] == ' ') {
				currstate = SPACEN;
				t.type = SPACEN;
			//		printf(" 23d ");
			}
			
			else if(c[i] == '\0') {
				currstate = STOP;
				t.type = STOP;
			}
				
			else if(isalpha(c[i]))
				currstate == ERROR;
				
			else if(c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/' || c[i] == '%' || c[i] == '^'){
				currstate = OPERATOR;
				printf(" 2ty3 %d",currstate+1);
		 	    //i--;
			}
			
			break;

		case OPERATOR:
			printf("Worked fine 4 ");
			printf("\n%c    %d\n",c[i],i);
		//	i--;
			if(c[i] == '(') {
				opt_push(&q,'(');
				i++;
				printf("1");
			}

			else if(c[i] == ')') {
				while(!opt_empty(q) && opt_top(q) != '(') {
					op = opt_pop(&q);
					applyop(op);
				}
				if(!opt_empty(q))
					opt_pop(&q);
				
					printf("2");
			}
			
			else {
				printf("\n%c    %d\n",c[i],i);
				printf("3");
				while(!opt_empty(q) && (precedence(opt_top(q)) >= precedence(c[i]))){
					op = opt_pop(&q);
					applyop(op);
				
				}
			
				opt_push(&q, c[i]);
				printf("%c  -So this is the required operator.",opt_top(q));
				i++;
			}
			//printf("1");
			
			if(isdigit(c[i]))
				currstate = ERROR;
			else if(c[i] == ' ')
				currstate = SPACEP;
			else if(c[i] == '\0')
				currstate = ERROR;
			else if(c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/' || c[i] == '%' || c[i] == '^'){
				currstate == ERROR;
			}      
			printf("\n%c    %d  %d\n operator state successfully completed",c[i],i,currstate);	  
			printf("\n%c",c[i]);
			i--;   
			break;

		case STOP:
			return;
			
		
		case ERROR:
			printf("\nError in input values!\n PLease try some other input.");
			return ;
			
				
		case SPACEP:
			printf("Worked fine 3 ");
			//	printf("\n%c    %d\n",c[i],i);
			
			if(c[i] == ' ') {
				currstate = SPACEP;
				t.type = SPACEP;
				printf("Succeed");	
			}
			
			else if(c[i] == '\0') {
				currstate = STOP;
				t.type = STOP;
			}
				
			else if(isdigit(c[i])){
				currstate = START;
				t.type = DIGIT;
				i--;
				printf("Succeed");
			}
				
			else if(c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/' || c[i] == '%' || c[i] == '^'){
				currstate == ERROR;
			}
			printf("\n%c    %d %d\n",c[i],i,currstate);
			break;
		}
	
		if(currstate != OPERATOR)
		i++;
	//	printf("\n%c    %d\n",c[i],i+100);
	}
	while(!opt_empty(q)) {
		op = opt_pop(&q);
		applyop(op);
	}
	
}


int precedence(char op) {
	if(op == '^')
		return 3;
	if(op == '+' || op == '-')
		return 1;
	if(op == '*' || op == '/' || op == '%')
		return 2;
	return 0;

}

void applyop(char op){
	
	switch (op) {
	
	case '+':
		add(&s);
		break;
	case '-':
		subtract(&s);
		break;
	case '*':
		multiply(&s);
		break;
	case '/':
		divide(&s);
		break;
	case '%' :
		mod(&s);
		break;
	case '^':
		power(&s);
		break;
}		

}


void power(stack *s) {
	int ss;
	ss = s->sign[s->top] * s->sign[s->top - 1];
	s->sign[s->top] = 1;
	stack d; //Meant for multiplication
	stack g;  //Meant for subtraction
	init_opd(&d);
	init_opd(&g);
	list p = s->l[s->top-1];
	list q = s->l[s->top];
	d.top = d.top + 1;
	init(&d.l[d.top]);
	d.top = d.top + 1;
	init(&d.l[d.top]);
	while(p) {
		append(&d.l[d.top],p->data);
	//	append(&d.l[d.top - 1],1);
		p = p->next;
	}
	insert_beg(&d.l[d.top-1],1);	
	g.top = g.top + 1;
	init(&g.l[g.top]);
	while(q) {
		append(&g.l[g.top],q->data);
		q = q->next;
	}
	g.top = g.top + 1;
	init(&g.l[g.top]);
	insert_beg(&g.l[g.top],1);
/*	traverse_fwd(g.l[g.top]);
	traverse_fwd(g.l[g.top-1]);
	traverse_fwd(d.l[d.top]);
	traverse_fwd(d.l[d.top-1]);*/
	int i = 12;
	int k = iszero(g.l[g.top]); 
	while(iszero(g.l[g.top-1])) {
	//	k = iszero(g.l[g.top]);
	//	if(k == 1)
	//		break;
		multiply(&d);
		traverse_fwd(d.l[d.top]);
	//	if(!iszero(g.l[g.top]))
	//		break;
		printf("%d",i*123);
	//	return;
		subtract(&g);

		g.top = g.top + 1;
		init(&g.l[g.top]);
		insert_beg(&g.l[g.top],1);
		d.top = d.top + 1;
		p = s->l[s->top-1];
		init(&d.l[d.top]);
		while(p) {
			append(&d.l[d.top],p->data);
			p = p->next;
		}
		printf("\n");
		traverse_fwd(g.l[g.top]);	
	}	
	printf("\n");
/*	d.top = d.top + 1;
	init(&d.l[d.top]);
	p = s->l[s->top-1];	
		while(p) {
			append(&d.l[d.top],p->data);
			p = p->next;
		}
	divide(&d);*/
	printf("No  ");
		pop_opd(s);
    pop_opd(s);
    s->top++;
    s->l[s->top] = d.l[d.top-1];
    s->sign[s->top] = ss;
	traverse_fwd(d.l[d.top-1]);
}






