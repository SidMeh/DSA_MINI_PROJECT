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
void mod(stack *s);
int iszero(list s);
//void power(stack *s);
/*
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
	
	char c4[10] = "14";
	push_opd(&S,c4);
//	printf("%d ",s->top);
	printf("\n");
	traverse_fwd(s->l[s->top]);
	
	char c5[300] = "50";
	push_opd(&S,c5);
//	printf("%d ",s->top);
	printf("\n");
	traverse_fwd(s->l[s->top]);
//	power(&S);
	multiply(&S);
//	add(&S);
//	subtract(&S);
//	subtract(&S);
//	divide(&S);
//	add(&S);
//	mod(&S);
	printf("\n");
	traverse_fwd(s->l[s->top]);

	return 0;
}
*/



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
		if(s->sign[s->top] == -1){
			list temp;
			temp = s->l[s->top];
			s->l[s->top] = s->l[s->top - 1];
			s->l[s->top] = temp;
			subtract(s);
			return;
		}
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
//	delete(&s->l[s->top]);
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

	if(s->sign[s->top - 1] == 1 && s->sign[s->top] == -1){
		s->sign[s->top] = 1;
		add(s);
		return;
	}
	if(s->sign[s->top-1] == -1 && s->sign[s->top] == -1){
		list temp;
		temp = s->l[s->top];
		s->l[s->top] = s->l[s->top - 1];
		s->l[s->top] = temp;
		s->sign[s->top] = 1;
		s->sign[s->top-1] = 1;
		subtract(s);
		return;	
	}
	if(s->sign[s->top-1] == -1 && s->sign[s->top] == 1){
		s->sign[s->top] = -1;
		add(s);
		return;
	}
	list l3, p , q;
	init(&l3);
	int k, i, data;
	//Sets the stating character to  zero
	while(s->l[s->top]->data == 0) {
		pop_once(&s->l[s->top],0);
	} 
//	printf("\n");

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
	int ss;
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
//	printf("%d",flag);
	int borrow = 0,result;
	if(flag == 0) {
		ss = 1;
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
		ss = -1;
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
	s->sign[s->top] = ss;
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
/*
void multiply(stack *s) {
	int ss;
	ss =	s->sign[s->top] * s->sign[s->top - 1];
	s->sign[s->top] = 1;
	s->sign[s->top - 1] = 1;
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
	int carrym = 0,carrya = 0,mdata = 0,adata = 0;
	list l = l3, p1 = p, q1 = q;
	while(l->next)
		l = l->next;	
	list r = l,r1 = l;
	traverse_fwd(s->l[s->top]);
	traverse_fwd(s->l[s->top - 1]);
	//printf("\n%d %d\n",p->prev->data ,q->prev->data);
	while(q1) {
		while(p1) {
		printf("\n11");
		mdata = (carrym +  p1->data*q1->data)%10;
		carrym = (carrym + p1->data*q1->data)/10;
		r1->data = (r1->data + mdata + carrya)%10;
		carrya = (r1->data + mdata + carrya)/10;
		//	carrym = (carrym + p1->data*q1->data)/10;
		//	carrya = (carrya + (carrym + p->data*q->data)%10)/10;
		//	r->data = (carrym + carrya + r->data + p->data*q->data)%10;
			
	/*		r1->data = (r1->data + carry + p1->data * q1->data)%10;
			carry = (r1->data + carry + p1->data * q1->data)/10;
		r1 = r1->prev;
		p1 = p1->prev;
		}
		printf("\n");

		r1->data += carrya ;
		traverse_fwd(l3);
		p1 = p;
		r = r->prev;
		r1 = r;
		q1 = q1->prev;
		carry = 0;
		carrym = 0;
	
		carrya = 0;
	}
	pop_opd(s);
	pop_opd(s);
	s->top = s->top + 1;
//	printf("%d",s->top);
	s->l[s->top] = l3;
	 s->sign[s->top] = ss;
}
*/

void divide(stack *s) {
	int ss;
	ss = s->sign[s->top] * s->sign[s->top - 1];
	s->sign[s->top] = 1;
	list base = s->l[s->top],p,q;
	int k, flag;
	stack f,*d;
	init_opd(&f);
	d = &f;
	char c_1[2] = "1";
	char c_d[2] = "0";
	push_opd(&f,c_d);
	push_opd(&f,c_1);
	traverse_fwd(d->l[d->top]);
	traverse_fwd(d->l[d->top - 1]);
	list one = d->l[d->top];
	int i = 5,t;
	while(1) {
		while(s->l[s->top]->data == 0)
			pop_once(&s->l[s->top],0);
		while(s->l[s->top-1]->data == 0)
			pop_once(&s->l[s->top-1],0);		
	
		
		
		k = len(s->l[s->top]) - len(s->l[s->top - 1]);
		if(k>0)
			break;
		if(k == 0) {
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
		     if(flag == 1)
		     	break;
		}
		
		t =	subtract(s);
		if(t){
		/*	if(len(s->l[s->top]) <= 2)
				break;*/
			add(&f);
			d->top = d->top + 1;
			s->top = s->top +1;
			s->l[s->top] = base;
			d->l[d->top] = one;
			break;
		}
		add(&f);
		d->top = d->top + 1;
		s->top = s->top +1;
		s->l[s->top] = base;
		d->l[d->top] = one;
		
     }
     printf("\n");
     traverse_fwd(d->l[d->top - 1]);
     printf("\n");
     pop_opd(s);
     pop_opd(s);
     s->top++;
     s->l[s->top] = d->l[d->top - 1];
   //  traverse_fwd(s->l[s->top - 1]);
     s->sign[s->top] = ss;
}

/*
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
	stack g;
	init_opd(&g);
	list l3;
	init(&l3);
	int i;
	for(i=0;i<k;i++)
		append(&l3,0);
	
	list l = l3, p1 = p, q1 = q,ll = l3;
	while(l->next)
		l = l->next;	
	list r = l,r1 = l;
	r1->data = 0;
	//printf("\n%d %d\n",p->prev->data ,q->prev->data);
	while(q1) {
		while(p1) {
			printf("\n%d - carry",carry);
			r1->data = (carry + p1->data * q1->data)%10;
			carry = (carry  + p1->data * q1->data )/10;
			printf("\n%d - carry",carry);
			r1 = r1->prev;
			p1 = p1->prev;
		}
		//insert_beg(&l3,carry);
	//	if(carry <= 0)
		r1->data = carry ;
		traverse_fwd(l3);
		
	 	g.top = g.top + 1;
	 	init(&g.l[g.top]);
	 	ll = l3;
	 	while(ll) {
	 		append(&g.l[g.top],ll->data);
	 		ll = ll->next;
		 }
		p1 = p;
		r = r->prev;
		r1 = r;
		q1 = q1->prev;
		carry = 0;
	
	}
	pop_opd(s);
	pop_opd(s);
	int t = g.top;
	traverse_fwd(g.l[g.top]);
	traverse_fwd(g.l[g.top - 1]);
	traverse_fwd(g.l[g.top - 2]);

	while(g.top) {
		add(&g);
	}

	subtract(&g);
	traverse_fwd(g.l[g.top-2]);
	s->top = s->top + 1;
	printf("\n%d",g.top);
//	s->l[s->top] = prod;
}

*/

void mod(stack *s) {
	stack d;
	init_opd(&d);
	list p = s->l[s->top-1];
	list q = s->l[s->top];
//	traverse_fwd(q);
//	printf("%d\n",d.top);
	d.top = d.top + 1;
	
	init(&d.l[d.top]);
	while(p) {
		append(&d.l[d.top],p->data);
		p = p->next;		
	}
	printf("\n");
//	traverse_fwd(d.l[d.top]);
	d.top = d.top + 1;
	init(&d.l[d.top]);
	while(q) {
		append(&d.l[d.top],q->data);
		q = q->next;
	}
	list temp, p1, q1;
	int k,flag;
/*	temp = d.l[d.top];
	d.l[d.top] = d.l[d.top-1];
	d.l[d.top-1] = temp; */
	printf("\n");
	traverse_fwd(d.l[d.top]);
	printf("\n");
	traverse_fwd(d.l[d.top-1]);
	list d1, d2;
	while(1) {
		while(d.l[d.top]->data==0)
			pop_once(&d.l[d.top],0);
		while(d.l[d.top-1]->data==0)
			pop_once(&d.l[d.top-1],0);		
		k = len(d.l[d.top]) - len(d.l[d.top - 1]);
		if(k>0)
			break;
		if(k == 0) {
			p1 = d.l[d.top];
			q1 = d.l[d.top - 1];
			int flag = 2;
			while(p1 && q1) {               //checks which list is bigger
				if(p1->data > q1->data) {
					flag = 1;				//	q is to be subtracted from p
					break;
				}
				else if(q1->data > p1->data) {    // p is to be subtracted from q
					flag = 0;
					break;
				}
				p1 = p1->next;
				q1 = q1->next;
			}
		     if(flag == 1)
		     	break;
		}
		subtract(&d);
		printf("\n");
		traverse_fwd(d.l[d.top]);
		d.top = d.top + 1;
		q = s->l[s->top];
		while(p) {
			append(&d.l[d.top],p->data);
			p = p->next;		
		}
				
	}	
	printf("\n");
	traverse_fwd(d.l[d.top-1]);
	pop_opd(s);
     pop_opd(s);
     s->top++;
     s->l[s->top] = d.l[d.top - 1];
}

void multiply(stack *s){
	list r;
	init(&r);
	list t;
	t = s->l[s->top];
	while(t){
		append(&r,t->data);
		t = t->next;
	}
	traverse_fwd(t);
	stack g;
	init_opd(&g);
	g.top = g.top + 1;
	init(&g.l[g.top]);
	insert_beg(&g.l[g.top],0);
	g.top = g.top + 1;
	init(&g.l[g.top]);
	t = s->l[s->top-1];
	while(t){
		append(&g.l[g.top],t->data);
		t = t->next;
	}		
	stack d;
	init_opd(&d);
	d.top = d.top + 1;
	init(&d.l[d.top]);
	t = s->l[s->top];
	while(t){
		append(&d.l[d.top],t->data);
		t = t->next;
	}		
	d.top = d.top + 1;
	init(&d.l[d.top]);
	insert_beg(&d.l[d.top],1);
	int i, pd;
	if(s->l[s->top]->data%2 == 0)
		pd = 10;
	else
		pd = 10;
	for(i=0;i<0;i++){
		add(&g);
	//	traverse_fwd(g.l[g.top]);
	//	subtract(&d);
	pop_opd(&d);
		g.top = g.top + 1;
		init(&g.l[g.top]);
		t = s->l[s->top-1];
		while(t){
		append(&g.l[g.top],t->data);
		t = t->next;
		}		
		d.top = d.top + 1;
		init(&d.l[d.top]);
		append(&d.l[d.top],1);	
		printf("%d\n",i);
	}
/*	list h = d.l[d.top-1];
	t = s->l[s->top - 1];
	while(h){
		h->data = t->data;
		h = h->next;
		t=t->next;
	}*/
	while(iszero(d.l[0])) {
		add(&g);
	//	traverse_fwd(g.l[g.top]);
		subtract(&d);
		g.top = g.top + 1;
		init(&g.l[g.top]);
		t = s->l[s->top-1];
		while(t){
		append(&g.l[g.top],t->data);
		t = t->next;
		}		
		d.top = d.top + 1;
		init(&d.l[d.top]);
		append(&d.l[d.top],1);	
		
	}
	pop_opd(s);
    pop_opd(s);
    s->top++;
    s->l[s->top] = g.l[0];
	//traverse_fwd(d.l[d.top-1]);
}

int iszero(list s) {
	int sum = 0;
	while(s) {
		sum = sum + s->data;
		s = s->next;
	}
	printf("\n%d\n",sum);
	return sum;
	
}

/*
void power(stack *s) {

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
		append(&d.l[d.top - 1],p->data);
		p = p->next;
	}	
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
	traverse_fwd(d.l[d.top-1]);
	while(iszero(g.l[0])) {
		multiply(&d);
		traverse_fwd(d.l[d.top]);
		subtract(&g);
		g.top = g.top + 1;
		init(&g.l[g.top]);
		insert_beg(&g.l[g.top],1);
		d.top = d.top + 1;
		p = s->l[s->top-1];
		while(p) {
			append(&d.l[d.top],p->data);
			p = p->next;
		}
		
	}	
	traverse_fwd(d.l[d.top-1]);
}

*/
















