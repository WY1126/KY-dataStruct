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

using namespace std; 

/*
	Name: ���Ա� 
	Copyright: WonYno
	Author: ���� 
	Date: 03/02/21 20:51
	Description: 2022����-���ݽṹ��ϰ 
*/

//-------���Ա�Ķ�̬����˳��洢�ṹ-------03/02/21 20:50 
#define LIST_INIT_SIZE 100 						// ���Ա�洢�ռ�ĳ�ʼ������ 
#define LISTINCREMENT  10 						// ���Ա�洢�ռ�ķ������� 
typedef int ElemType;
typedef struct {
	ElemType *elem;								// �洢�ռ��ַ 
	int length;									// ��ǰ���� 
	int listsize;								// ��ǰ����Ĵ洢��������sizeof(ElemType)Ϊ��λ�� 
}SqList; 

//��ʼ�����Ա�
Status InitList_Sq(SqList &L) {
	// ����һ���յ����Ա�L�� - malloc ����洢�ռ� 
	L.elem = ( ElemType * ) malloc ( LIST_INIT_SIZE * sizeof( ElemType ));  
	if (!L.elem) exit(OVERFLOW); 				//�洢����ʧ�� 
	L.length = 0; 								//�ձ���Ϊ0 
	L.listsize = LIST_INIT_SIZE;				//��ʼ�洢���� 
	return OK;
} // InitList_Sq

// �����Ա��в���ֵ 
Status ListInsert_Sq(SqList &L,int i,ElemType e) {
	// ��˳�����Ա�L�е�i��λ��֮ǰ�����µ�Ԫ��e��
	// i�ĺϷ�ֵΪ1 =< i =<ListLength_Sq(L)+1 
	if(i>L.listsize+1) return ERROR;
	if(L.length >= L.listsize) {
		// realloc ���ӷ���ռ䣬������ʼ��ԭ�ڴ� 
		ElemType *newbase = (ElemType *) realloc (L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase)exit(OVERFLOW);
		L.elem = newbase;						// �»�ַ 
		L.listsize +=  LISTINCREMENT; 			// ���Ӵ洢����	
		printf("++\n");
	} 
	ElemType *q = &(L.elem[i-1]);				// qΪ����λ�� 
	for(ElemType *p = &(L.elem[L.length-1]); p >= q; --p) 
		*(p+1) = *p;							// ����λ�ü�֮���Ԫ������ 
	*q = e;										// ����e 
	++L.length;									// ����1  
	return OK;
}//ListInsert_Sq

//ɾ������
Status ListDelete_Sq(SqList &L,int i,ElemType &e) {
	if((i<1||(i>L.length))) return ERROR;		// iֵ���Ϸ� 
	ElemType *p = &(L.elem[i-1]);				// pΪ��ɾ��Ԫ�ص�λ�� 
	e = *p;										// ��ɾ��Ԫ�ص�ֵ����e 
	ElemType *q = L.elem + L.length - 1;		// ��βԪ�ص�λ�� 
	for(++p ; p <= q ; ++p) 					// ��ɾ��Ԫ��֮���λ������ 
		*(p-1) = *p;
	--L.length;									//����1
	return OK;									
}// ListDelete_Sq
 
//���ұ��е�һ����e��ȵ�ֵ��λ�� 
int LocateElem_Sq( SqList L,ElemType e, 
//����ָ�� ���Ժ���ָ��Ķ��巽ʽΪ��
//��������ֵ���� (* ָ�������) (���������б�);
Status ( *compare)( ElemType , ElemType)) {
	int i = 1;
	ElemType *p = L.elem;
	while (i<=L.length && !(compare)( *p++, e)) ++i;			// ָ�����compare(a,b)���� 
	if(i<=L.length) return i;
	else return 0;
}// LocateElem_Sq

//�ȽϺ�����ȷ��� 1 ���ȷ���0 
Status compare(ElemType a,ElemType b) {
	return a == b ? 1:0;
}// compare

//˳���ĺϲ�
void MergeList_Sq(SqList La,SqList Lb,SqList &Lc) {
	//��֪˳���La,Lb��Ԫ�ذ�ֵ�ǵݼ�����
	//�鲢La��Lb�õ��µ�˳�����Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ����� 
	ElemType *pa , *pb , *pc, *pa_last , *pb_last;
	pa = La.elem;	pb = Lb.elem;
	Lc.listsize = Lc.length = Lb.length + La.length;
	pc = Lc.elem = (ElemType *) malloc (Lc.listsize * sizeof(ElemType));
	if(!Lc.elem) exit(OVERFLOW);
	pa_last = La.elem + La.length - 1;
	pb_last = Lb.elem + Lb.length - 1;
	while (pa <= pa_last && pb <= pb_last) { //�鲢 
		if( *pa <= *pb)	*pc ++ = *pa++;
		else *pc++ = *pb++;
	}
	while (pa <= pa_last) *pc++ = *pa++;
	while (pb <= pb_last) *pc++ = *pb++; 
} //MergeList_Sq

//���Ա�˳��洢������ 
int main(int argc, char *argv[]) {
	SqList La , Lb ,Lc;
	InitList_Sq(La);
	InitList_Sq(Lb);
	int a = 0;
	//������ֵ 
	for(int i=1;i<=5;i++) {
		ListInsert_Sq(La,i,i+8);
		ListInsert_Sq(Lb,i,i+3);
	}
	MergeList_Sq(Lb,La,Lc);
	for(int i=0;i<10;i++)
		printf("%d\t",Lc.elem[i]);
	printf("\n");
	//��ӡ 
//	for(int i=0 ; i < 5;i++) {
//		printf("%d \t",L.elem[i]);
//	}	
	printf("\n");
	//ɾ����һ��Ԫ�ز�����ֵ���ظ�a 
	ListDelete_Sq(Lc,1,a);
	
	printf("%d \t %d\n",Lc.elem[0],a);
	
	printf("%d\n",LocateElem_Sq(Lc,12,compare));
	return 0;
}
