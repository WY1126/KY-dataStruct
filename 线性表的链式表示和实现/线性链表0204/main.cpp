#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 //infeasible 不能实现的； 
#define OVERFLOW -2   //overflow   溢出
//Status是函数类型
typedef int Status;

using namespace std; 

/*
	Name: 线性链表 
	Copyright: WonYno 
	Author: 王瑶 
	Date: 04/02/21 09:53
	Description: 线性表的链式存储结构 
*/

// - - - - - - - - 线性表的单链表存储结构 - - - - - -
typedef int ElemType; 
typedef struct LNode {
	ElemType data;
	struct LNode *next;
} LNode , *LinkList; 

//获取单链表中第i个元素并返回e 
Status GetElem_L(LinkList L,int i,ElemType &e) {
	LinkList p;				
	p = L->next;	int j = 1;					// 初始化，p指向第一个节点，j为计数器 
	while (p && j < i) {						//	查找 
		p = p->next;	++j;
	}
	if( !p || j>i)	return ERROR;
	e = p->data;								//取第i个元素 
	return OK;
}// GetElem_L

// 创建单链表 
void CreateList_L(LinkList &L,int n) {
	L = (LinkList) malloc (sizeof(LNode));
	L->next = NULL;
	LinkList head = L;							//代理头节点 
	for(int i = 0 ; i < n ; ++i) {
		LinkList p = (LinkList) malloc (sizeof(LNode));
//		scanf("%d",&p->data);
		p->data = i+6;
//		p->next = L->next;	L->next = p;		//插到表头
		p->next = NULL;		head->next = p;		head = p;			//插到表尾		 
	}
}// CreateList_L

//在i位置插入新元素值为e 
Status ListInsert_L(LinkList &L,int i,ElemType e) {
	LinkList p = L , s; int j = 0;
	while (p && j < i-1) {
		p = p->next;	++j;
	}
	if(!p || j > i-1)	return ERROR;
	s = (LinkList) malloc (sizeof(LNode));
	s->data = e;	s->next = p->next;
	p->next = s;
	return OK;
}//	ListInsert_L

//删除 
Status ListDelete_L(LinkList &L,int i,ElemType &e) {
	LinkList p = L , q;	int j=0;
	while (p->next && j < i-1) {
		p = p->next ; ++j;
	}
	if(!(p->next) || j > i-1)	return ERROR;
	q = p->next;	p->next = q->next;
	e = q->data;	free(q);
	return OK;
}// Listdelete_L 

//非递减合并 
void MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc) {
	LinkList pa , pb , pc;
	pa = La->next;	pb = Lb->next;
	Lc = pc = La;										// 用La的头节点做lc的头节点 
	while (pa && pb) {
		if(pa->data <= pb->data) {
			pc->next = pa;	pc = pa ; pa = pa->next;
		}
		else {
			pc->next = pb;	pc = pb;  pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;							//插入剩余段 
	free(Lb); 	
}// MergeList_L

//打印单链表 
void PrintList(LinkList L) {
	LinkList p = L->next;
	while (p) {
		printf("%d\t",p->data);
		p = p->next;
	}
	printf("\n");
}

//主函数 
int main(int argc, char** argv) {
	LinkList L , Lb ,Lc;

	//创建单链表 
	CreateList_L(L,5);	LinkList p = L->next;
	CreateList_L(Lb,15);
//	printf("%d\n",L->next->data);
	int e;
	GetElem_L(L,1,e);
	printf("e = %d\n",e);
	
	ListInsert_L(L,6,100000);
	PrintList(L);
	
	ListDelete_L(L,2,e);
	PrintList(L);
	MergeList_L(L,Lb,Lc);
	PrintList(Lc); 
	return 0;
}
