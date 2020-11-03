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
int subtract(stack *s);
void multiply(stack *s);
void delete(list *l);
void traverse_fwd(list l);
void pop_once(list *l,int d);
void divide(stack *s);

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
	
	char c4[4] = "110";
	push_opd(&S,c4);
//	printf("%d ",s->top);
	printf("\n");
	traverse_fwd(s->l[s->top]);
	
	char c5[4] = "120";
	push_opd(&S,c5);
//	printf("%d ",s->top);
	printf("\n");
	traverse_fwd(s->l[s->top]);
	//subtract(&S);
	//add(&S);
	//subtract(&S);
	divide(&S);
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
	if(s->sign[s->top] != s->sign[s->top]) {
		subtract(s);
		return;
	}
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
			insert_beg(&s->l[s->top - 1],0);
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

int subtract(stack *s) {
	if(s->sign[s->top] != s->sign[s->top]) {
		add(s);
		return 0;
	}
	list l3, p , q;
	init(&l3);
	int k, i, data;
	//Sets the stating character to  zero
	while(s->l[s->top]->data == 0) {
		pop_once(&s->l[s->top],0);
	} 
	printf("\n");

	while(s->l[s->top - 1]->data == 0) {
		pop_once(&s->l[s->top - 1],0);
	} 

	k = len(s->l[s->top]) - len(s->l[s->top - 1]);
	
	if(k < 0) {
		for(i=0;i< -1*k; i++) {
			insert_beg(&s->l[s->top],0);
		}
	}
	else if(k > 0) {
		for(i=0;i< k; i++) {
			insert_beg(&s->l[s->top - 1],0);
		}
	}
//	traverse_fwd(s->l[s->top-1]);
	p = s->l[s->top];
	q = s->l[s->top - 1];
	int flag = 2;
	while(p && q) {               //checks which list is bigger
		if(p->data > q->data) {
			flag = 1;				//	q is to be subtracted from p
			break;
		}
		else if(q->data > p->data) {    // p is to be subtracted from q
			flag = 0;
			break;
		}
		p = p->next;
		q = q->next;
	}

	p = s->l[s->top];
	q = s->l[s->top - 1];
	while(p->next)
		p = p->next;
	while(q->next)
		q = q->next;
	printf("%d",flag);
	int borrow = 0,result;
	if(flag == 0) {
		while(p && q) {
			if(q->data >= (p->data+borrow)){
				result = q->data - (p->data + borrow);
				insert_beg(&l3,result);
				borrow = 0;
			}
			else if(q->data <(p->data+borrow)){
				result = 10 + q->data - (p->data + borrow);
				insert_beg(&l3,result);
				borrow = 1;
			}
			p = p->prev;
			q = q->prev;
		}
	}
		
	
	else if(flag == 1) {
		while(p && q) {
			if(p->data >= (q->data+borrow)){
				result = p->data - (q->data + borrow);
				insert_beg(&l3,result);
				borrow = 0;
			}
			else if(p->data <(q->data+borrow)){
				result = 10 + p->data - (q->data + borrow);
				insert_beg(&l3,result);
				borrow = 1;
			}
			p = p->prev;
			q = q->prev;
		}
	}
	
	else if(flag == 2) 
		insert_beg(&l3,0);
		
	pop_opd(s);
	pop_opd(s);
	s->top = s->top + 1;
	if(borrow == 1)
		s->sign[s->top] = -1;
	else
		s->sign[s->top] = 1;
	s->l[s->top] = l3;
	return flag;
}		

	
void pop_once(list *l,int d) {
	if(*l == NULL) {
		return;
	}
	node *p,*q;
	p = *l;
	q = NULL;
	if(p->data == d) {
		*l = p->next;
		free(p);
		return;
	}
	q = p;
	p = p->next;
	while(p->next) {
		if(p->data == d) {
			q->next = p->next;
			p->next->prev = q;
			free(p);
			return;
		}
	q = p;
	p = p->next;
	}
	if(p->data == d) {
		q->next = NULL;
		free(p);
	}
}	

void multiply(stack *s) {
	list p = s->l[s->top];
	list q = s->l[s->top - 1];
	int k = len(s->l[s->top]) + len(s->l[s->top - 1]);
	//printf("%d",k);
	while(q->next)
		q = q->next;
	while(p->next)
		p = p->next;
	int carry = 0;
	list l3;
	init(&l3);
	int i;
	for(i=0;i<k;i++)
		append(&l3,0);
	
	list l = l3, p1 = p, q1 = q;
	while(l->next)
		l = l->next;	
	list r = l,r1 = l;
	//printf("\n%d %d\n",p->prev->data ,q->prev->data);
	while(q1) {
		while(p1) {
			r1->data = (r1->data + carry + p1->data * q1->data)%10;
			carry = (r1->data + carry + p1->data * q1->data)/10;
			r1 = r1->prev;
			p1 = p1->prev;
		}
		r1->data = carry;
		p1 = p;
		r = r->prev;
		r1 = r;
		q1 = q1->prev;
		carry = 0;
	}
	pop_opd(s);
	pop_opd(s);
	s->top = s->top + 1;
//	printf("%d",s->top);
	s->l[s->top] = l3;
}
		
void divide(stack *s) {
	int k, carry = 0,borrow = 0, i, result;				
	list l3, one, p, q, p1, q1, l, l1, one1, one2, l2;
	init(&l3);
	init(&one);
	init(&l);
	insert_beg(&l,0);
	l1 = l;
	one1 = one;
	insert_beg(&one,1);
	insert_beg(&l3,0);
	p = s->l[s->top];
	q = s->l[s->top - 1];
	while(p->next)
		p = p->next;
	p1 = p;
	while(q->next)
		q = q->next;	
	q1 = q;
	while(one1->next)
		one1 = one1->next;
	one2 = one1;
/*	while(l1->next)
		l1 = l1->next;
	l2 = l1;
	
	while(1) {
	
		while(s->l[s->top]->data == 0) {
			pop_once(&s->l[s->top],0);
		} 

		while(s->l[s->top - 1]->data == 0) {
			pop_once(&s->l[s->top - 1],0);
		} 
		
		k = len(s->l[s->top]) - len(s->l[s->top - 1]);
		
		if(k > 0) {
			
			break;
		}
		else if(k < 0) {
			for(i=0;i< k; i++) {
				insert_beg(&s->l[s->top - 1],0);
			}
		}		
		
		q1 = q;
		p1 = p;
		delete(&l3);
		while(p1 && q1) {
			if(p1->data >= (q1->data+borrow)){
				result = q->data - (p->data + borrow);
				insert_beg(&l3,result);
				borrow = 0;
			}
			else if(p1->data <(q1->data+borrow)){
				result = 10 + p1->data - (q1->data + borrow);
				insert_beg(&l3,result);
				borrow = 1;
			}
			p1 = p1->prev;
			q1 = q1->prev;
		}
		s->l[s->top - 1] = l3;
		k = len(l) - len(one);
	
		if(k < 0) {
			for(i=0;i< -1*k; i++) {
				insert_beg(&l,0);
			}
		}
		else if(k > 0) {
			for(i=0;i< k; i++) {
				insert_beg(&one,0);
			}
		}
		one2 = one1;
		l2 = l1;
		while(one2 && l2) {
			l2->data = (l2->data + one2->data + carry)%10;
			carry = (l2->data + one2->data + carry)/10;
			l2 = l2->prev;
			one2 = one2->prev;
		}
		if(one2->prev)
			one2->prev->data = one2->prev->data + 1;
		else
			insert_beg(&one2,1);
		carry = 0;
	}

	traverse_fwd(one);*/
}




































