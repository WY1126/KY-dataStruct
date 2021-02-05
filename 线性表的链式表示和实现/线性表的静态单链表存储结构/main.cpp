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

/*
	Name: 静态单链表 
	Copyright: WonYno 
	Author: 王瑶 
	Date: 05/02/21 11:22
	Description: 线性表的静态单链表存储结构 
*/

//——————线性表的静态单链表存储结构 ——————

#define MAXSIZE 1000			// 链表的最大长度 
typedef int ElemType;

typedef struct {
	ElemType data;
	int cur;
}component, SLinkList[MAXSIZE]; 

//查找第一个值为e的元素 
int LocateElem_SL(SLinkList S,ElemType e) {
	int i = S[0].cur;
	while(i && S[i].data != e) i = S[i].cur;
	return i;
}// LocateElem_SL 

//将一维数组space中各分量链成一个备用链表，space[0].cur为头指针。 
void InitSpace_SL(SLinkList &space) {
	for(int i = 0; i < MAXSIZE; ++ i) {
		space[i].cur = i+1;
	}
	space[MAXSIZE-1].cur = 0;
}// InitSpace_SL

//分配节点-通过头指针的指向 
int Malloc_SL(SLinkList &space) {
	int i = space[0].cur;
	if(space[0].cur) space[0].cur = space[i].cur; 		//头指针指向下一个节点 
	return i;
}// Malloc_SL 

//回收
void Free_SL(SLinkList &space,int k) {
	space[k].cur = space[0].cur;	space[0].cur = k;	//让头指针指向k 
}// Free_SL

void difference(SLinkList &space,int &S) {
	// 依次输入集合A和B的元素，在一维数组space中建立表示集合（A-B）U（B-A)
	// 的静态链表，S为其头指针。假设备用空间足够大，space[0].cur为其头指针。
	int r, m, n, i, j, b, k, p; 
	InitSpace_SL(space);						// 初始化备用空间
	S = Malloc_SL(space);						// 生成S的头结点 
	r = S;  									// r指向S的当前最后结点 
	scanf("%d%d",&m,&n);						// 输入A和B的元素个数
	for(j = 1; j <= m; ++ j) {					// 建立集合A的链表 
		i = Malloc_SL(space);					// 分配节点
		scanf("%d",&space[i].data);				// 输入A的元素值
		space[r].cur = i; r = i;				// 插入到表尾 
	}// for
	space[r].cur = 0;							// 尾节点的指针为空
	for(j = 1; j <= n; ++ j) {					// 依次输入B的元素，若不在当前表中则插入，否则删除
		scanf("%d",&b); p = S; k = space[S].cur; // k指向集合A中的第一个节点
		while (k != space[r].cur && space[k].data != b) { // 在当前表中查找
		 	p = k; k = space[k].cur; 
		}// while
		if(k == space[r].cur) {					// 当前表中不存在该元素，插入到r后 
		 	i = Malloc_SL(space);
		 	space[i].data = b;
		 	space[i].cur = space[r].cur;
		 	space[r].cur = i;
		}// if
		else {
			space[p].cur = space[k].cur;
			Free_SL(space,k);
			if(r == k) r = p;					// 若删除的是r所指节点，则需修改尾指针 
		}// else 
	}// for
}// difference

//输出函数 
void PrintSpace_SL(SLinkList space) {
	int i = space[0].cur;
	while(i) {
		printf("%d  ",space[i].data);
		i = space[i].cur;
	}
	printf("\n");
}// PrintSpace_SL

//主函数 
int main(int argc, char** argv) {
	SLinkList S;
	// 赋值 
	for(int i=0;i<10;i++) {
		if(i == 0) {
			S[i].cur = 1;
			S[i].data = 9;
			continue;
		}
		S[i].cur = i+1;
		S[i].data = i+8;
		if(i == 9) S[i].cur = 0;
	}
	PrintSpace_SL(S);
	printf("\n%d\n",LocateElem_SL(S,12));		// 查找12 的位置。 
	
	SLinkList space; int SS;
	
	difference(space, SS);
	for(int i=0;i<=11;i++)
	printf("%d\t%d\n",space[i].data,space[i].cur);
//	PrintSpace_SL(space);
	return 0;
}
