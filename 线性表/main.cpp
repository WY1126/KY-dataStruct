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
	Name: 线性表 
	Copyright: WonYno
	Author: 王瑶 
	Date: 03/02/21 20:51
	Description: 2022考研-数据结构复习 
*/

//-------线性表的动态分配顺序存储结构-------03/02/21 20:50 
#define LIST_INIT_SIZE 100 						// 线性表存储空间的初始分配量 
#define LISTINCREMENT  10 						// 线性表存储空间的分配增量 
typedef int ElemType;
typedef struct {
	ElemType *elem;								// 存储空间基址 
	int length;									// 当前长度 
	int listsize;								// 当前分配的存储容量（以sizeof(ElemType)为单位） 
}SqList; 

//初始化线性表
Status InitList_Sq(SqList &L) {
	// 构造一个空的线性表L。 - malloc 分配存储空间 
	L.elem = ( ElemType * ) malloc ( LIST_INIT_SIZE * sizeof( ElemType ));  
	if (!L.elem) exit(OVERFLOW); 				//存储分配失败 
	L.length = 0; 								//空表长度为0 
	L.listsize = LIST_INIT_SIZE;				//初始存储容量 
	return OK;
} // InitList_Sq

// 向线性表中插入值 
Status ListInsert_Sq(SqList &L,int i,ElemType e) {
	// 在顺序线性表L中第i个位置之前插入新的元素e，
	// i的合法值为1 =< i =<ListLength_Sq(L)+1 
	if(i>L.listsize+1) return ERROR;
	if(L.length >= L.listsize) {
		// realloc 增加分配空间，并不初始化原内存 
		ElemType *newbase = (ElemType *) realloc (L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase)exit(OVERFLOW);
		L.elem = newbase;						// 新基址 
		L.listsize +=  LISTINCREMENT; 			// 增加存储容量	
		printf("++\n");
	} 
	ElemType *q = &(L.elem[i-1]);				// q为插入位置 
	for(ElemType *p = &(L.elem[L.length-1]); p >= q; --p) 
		*(p+1) = *p;							// 插入位置及之后的元素右移 
	*q = e;										// 插入e 
	++L.length;									// 表长增1  
	return OK;
}//ListInsert_Sq

//删除操作
Status ListDelete_Sq(SqList &L,int i,ElemType &e) {
	if((i<1||(i>L.length))) return ERROR;		// i值不合法 
	ElemType *p = &(L.elem[i-1]);				// p为被删除元素的位置 
	e = *p;										// 被删除元素的值赋给e 
	ElemType *q = L.elem + L.length - 1;		// 表尾元素的位置 
	for(++p ; p <= q ; ++p) 					// 被删除元素之后的位置左移 
		*(p-1) = *p;
	--L.length;									//表长减1
	return OK;									
}// ListDelete_Sq
 
//查找表中第一个与e相等的值的位置 
int LocateElem_Sq( SqList L,ElemType e, 
//函数指针 所以函数指针的定义方式为：
//函数返回值类型 (* 指针变量名) (函数参数列表);
Status ( *compare)( ElemType , ElemType)) {
	int i = 1;
	ElemType *p = L.elem;
	while (i<=L.length && !(compare)( *p++, e)) ++i;			// 指针调用compare(a,b)函数 
	if(i<=L.length) return i;
	else return 0;
}// LocateElem_Sq

//比较函数相等返回 1 不等返回0 
Status compare(ElemType a,ElemType b) {
	return a == b ? 1:0;
}// compare

//顺序表的合并
void MergeList_Sq(SqList La,SqList Lb,SqList &Lc) {
	//已知顺序表La,Lb的元素按值非递减排列
	//归并La和Lb得到新的顺序线性表Lc，Lc的元素也按值非递减排列 
	ElemType *pa , *pb , *pc, *pa_last , *pb_last;
	pa = La.elem;	pb = Lb.elem;
	Lc.listsize = Lc.length = Lb.length + La.length;
	pc = Lc.elem = (ElemType *) malloc (Lc.listsize * sizeof(ElemType));
	if(!Lc.elem) exit(OVERFLOW);
	pa_last = La.elem + La.length - 1;
	pb_last = Lb.elem + Lb.length - 1;
	while (pa <= pa_last && pb <= pb_last) { //归并 
		if( *pa <= *pb)	*pc ++ = *pa++;
		else *pc++ = *pb++;
	}
	while (pa <= pa_last) *pc++ = *pa++;
	while (pb <= pb_last) *pc++ = *pb++; 
} //MergeList_Sq

//线性表顺序存储主函数 
int main(int argc, char *argv[]) {
	SqList La , Lb ,Lc;
	InitList_Sq(La);
	InitList_Sq(Lb);
	int a = 0;
	//给链表赋值 
	for(int i=1;i<=5;i++) {
		ListInsert_Sq(La,i,i+8);
		ListInsert_Sq(Lb,i,i+3);
	}
	MergeList_Sq(Lb,La,Lc);
	for(int i=0;i<10;i++)
		printf("%d\t",Lc.elem[i]);
	printf("\n");
	//打印 
//	for(int i=0 ; i < 5;i++) {
//		printf("%d \t",L.elem[i]);
//	}	
	printf("\n");
	//删除第一个元素并将其值返回给a 
	ListDelete_Sq(Lc,1,a);
	
	printf("%d \t %d\n",Lc.elem[0],a);
	
	printf("%d\n",LocateElem_Sq(Lc,12,compare));
	return 0;
}
