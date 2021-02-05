#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 //infeasible ����ʵ�ֵģ� 
#define OVERFLOW -2   //overflow   ���
//Status�Ǻ�������
typedef int Status;

/*
	Name: ��̬������ 
	Copyright: WonYno 
	Author: ���� 
	Date: 05/02/21 11:22
	Description: ���Ա�ľ�̬������洢�ṹ 
*/

//���������������Ա�ľ�̬������洢�ṹ ������������

#define MAXSIZE 1000			// �������󳤶� 
typedef int ElemType;

typedef struct {
	ElemType data;
	int cur;
}component, SLinkList[MAXSIZE]; 

//���ҵ�һ��ֵΪe��Ԫ�� 
int LocateElem_SL(SLinkList S,ElemType e) {
	int i = S[0].cur;
	while(i && S[i].data != e) i = S[i].cur;
	return i;
}// LocateElem_SL 

//��һά����space�и���������һ����������space[0].curΪͷָ�롣 
void InitSpace_SL(SLinkList &space) {
	for(int i = 0; i < MAXSIZE; ++ i) {
		space[i].cur = i+1;
	}
	space[MAXSIZE-1].cur = 0;
}// InitSpace_SL

//����ڵ�-ͨ��ͷָ���ָ�� 
int Malloc_SL(SLinkList &space) {
	int i = space[0].cur;
	if(space[0].cur) space[0].cur = space[i].cur; 		//ͷָ��ָ����һ���ڵ� 
	return i;
}// Malloc_SL 

//����
void Free_SL(SLinkList &space,int k) {
	space[k].cur = space[0].cur;	space[0].cur = k;	//��ͷָ��ָ��k 
}// Free_SL

void difference(SLinkList &space,int &S) {
	// �������뼯��A��B��Ԫ�أ���һά����space�н�����ʾ���ϣ�A-B��U��B-A)
	// �ľ�̬����SΪ��ͷָ�롣���豸�ÿռ��㹻��space[0].curΪ��ͷָ�롣
	int r, m, n, i, j, b, k, p; 
	InitSpace_SL(space);						// ��ʼ�����ÿռ�
	S = Malloc_SL(space);						// ����S��ͷ��� 
	r = S;  									// rָ��S�ĵ�ǰ����� 
	scanf("%d%d",&m,&n);						// ����A��B��Ԫ�ظ���
	for(j = 1; j <= m; ++ j) {					// ��������A������ 
		i = Malloc_SL(space);					// ����ڵ�
		scanf("%d",&space[i].data);				// ����A��Ԫ��ֵ
		space[r].cur = i; r = i;				// ���뵽��β 
	}// for
	space[r].cur = 0;							// β�ڵ��ָ��Ϊ��
	for(j = 1; j <= n; ++ j) {					// ��������B��Ԫ�أ������ڵ�ǰ��������룬����ɾ��
		scanf("%d",&b); p = S; k = space[S].cur; // kָ�򼯺�A�еĵ�һ���ڵ�
		while (k != space[r].cur && space[k].data != b) { // �ڵ�ǰ���в���
		 	p = k; k = space[k].cur; 
		}// while
		if(k == space[r].cur) {					// ��ǰ���в����ڸ�Ԫ�أ����뵽r�� 
		 	i = Malloc_SL(space);
		 	space[i].data = b;
		 	space[i].cur = space[r].cur;
		 	space[r].cur = i;
		}// if
		else {
			space[p].cur = space[k].cur;
			Free_SL(space,k);
			if(r == k) r = p;					// ��ɾ������r��ָ�ڵ㣬�����޸�βָ�� 
		}// else 
	}// for
}// difference

//������� 
void PrintSpace_SL(SLinkList space) {
	int i = space[0].cur;
	while(i) {
		printf("%d  ",space[i].data);
		i = space[i].cur;
	}
	printf("\n");
}// PrintSpace_SL

//������ 
int main(int argc, char** argv) {
	SLinkList S;
	// ��ֵ 
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
	printf("\n%d\n",LocateElem_SL(S,12));		// ����12 ��λ�á� 
	
	SLinkList space; int SS;
	
	difference(space, SS);
	for(int i=0;i<=11;i++)
	printf("%d\t%d\n",space[i].data,space[i].cur);
//	PrintSpace_SL(space);
	return 0;
}
