#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
	int data;
//	int sign;
	struct node* prev;
	struct node* next;
}node;

typedef node* list;




typedef struct stack{
	int top;
//	int size;
	int sign[100];
	list l[100];
}stack; 


void init(list *l) ;
void append(list *l, int d);
void insert_beg(list *l,int d);
int len(list l);
void init_opd(stack *s);
void push_opd(stack *s,char *ptr);
void pop_opd(stack *s);
void add(stack *s);
void subtract(stack *s);
void multiply(stack *s);
void delete(list *l);
void traverse_fwd(list l);
void pop_once(list *l,int d);


int main() {
	stack S;
	init_opd(&S);
	stack *s = &S;
	
	char c0[4] = "246";
	push_opd(&S,c0);
	printf("%d ",s->top);
	printf("\n");
	traverse_fwd(s->l[s->top]);
	
	char c1[4] = "123";
	push_opd(&S,c1);
	printf("%d ",s->top);
	printf("\n");
	traverse_fwd(s->l[s->top]);
	
	char c2[4] = "128";
	push_opd(&S,&c2[0]);
	printf("%d ",s->top);
	printf("\n");
	traverse_fwd(s->l[s->top]);
	
	char c3[3] = "10";
	push_opd(&S,c3);
	printf("%d ",s->top);
	printf("\n");
	traverse_fwd(s->l[s->top]);
	
	char c4[7] = "246987";
	push_opd(&S,c4);
//	printf("%d ",s->top);
	printf("\n");
	traverse_fwd(s->l[s->top]);
	
	char c5[5] = "2465";
	push_opd(&S,c5);
//	printf("%d ",s->top);
	printf("\n");
	traverse_fwd(s->l[s->top]);
	//subtract(&S);
	add(&S);
	
	//multiply(&S);
	printf("\n");
	traverse_fwd(s->l[s->top]);

	return 0;
}




void init(list *l) {
	*l = NULL;
	return;
}

void append(list *l, int d) {
	node *p,*t;
	t = (node*)malloc(sizeof(node));
	if(t) {
		t->data = d;
		int sign = -1;
		t->next = NULL;
		t->prev = NULL;
	}
	if(*l == NULL) {
		*l = t;
		return;
	}
	p = *l;
	while(p->next) {
		p = p->next;
	}
	p->next = t;
	t->prev = p;
}



void insert_beg(list *l,int d) {
	node *p = *l,*t;
	t = (node*)malloc(sizeof(node));
	if(t) {
		t->data = d;
		t->next = NULL;
		t->prev = NULL;
	}
	if(*l == NULL) {
		*l = t;
		return;
	}
	t->next = p;
	p->prev = t;
	*l = t;
	return;
}


void traverse_fwd(list l) {
	node *p = l;
	while(p) {
		printf("%d ",p->data);
		p = p->next;
	}
}

int len(list l) {
	if(l == NULL) {
		return 0;
	}
	int i = 1;
	node *p = l;
	while(p) {
		i++;
		p = p->next;
	}
	return i;
}
//Initializes stack
void init_opd(stack *s) {
	s->top = -1;
}

void push_opd(stack *s,char *ptr) {
	s->top = s->top + 1;
	init(&s->l[s->top]);
	s->sign[s->top] = 1;
	int num;
	while(*ptr != '\0') {
		num = *ptr - '0';
//		printf("%d",num);
		append(&s->l[s->top],num);
		ptr++;
	}
}



void add(stack *s) {
	list l3;
	init(&l3);
	int i;
//	int k = s->top-1;
	int n1 = len(s->l[s->top]);
	int n2 = len(s->l[s->top-1]);
	list p = s->l[s->top];
	list q = s->l[s->top - 1];
	while(p->next)
		p = p->next;
	while(q->next)
		q = q->next;
	int k = len(s->l[s->top]) - len(s->l[s->top - 1]);
	
	if(k < 0) {
		for(i=0;i< -1*k; i++) {
			insert_beg(&s->l[s->top],0);
		}
	}
	else if(k > 0) {
		for(i=0;i< k; i++) {
			insert_beg(&s->l[s->top + 1],0);
		}
	}
	int carry = 0;
	int data;
	int sn = s->sign[s->top] ;
	if(s->sign[s->top] != s->sign[s->top - 1])
		return;
	while(q) {
		data = (p->data + q->data + carry)%10 ;
		carry = (p->data + q->data + carry)/10 ;
		insert_beg(&l3,data);
		q = q->prev;
		p = p->prev;
	}
	if(carry > 0) 
		insert_beg(&l3,1);
	list r = l3;
	/*if(p->sign == -1) {
		while(r != NULL) {
			r->sign = -1;
			r = r->next;
		}
	}
	else {
		while(r != NULL) {
			r->sign = -1;
			r = r->next;
		}
	}*/
	
	//traverse_fwd(l3);
	pop_opd(s);
	pop_opd(s);
	s->top = s->top + 1;
	s->l[s->top] = l3;
	s->sign[s->top] = sn;
}

void pop_opd(stack *s) {
	delete(&s->l[s->top]);
	s->top = s->top - 1;
}


void delete(list *l) {
	if(*l == NULL)
		return;
	node *p, *q;
	p = *l;
	q = NULL;
	*l = NULL;
	while(p) {
		q = p;
		free(q);
		p = p->next;
	}
}
