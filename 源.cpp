#define _CRT_SECURE_NO_DEPRECATE 
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <string>
#include "s.h"
using namespace std;

int initPath(FILE* fp,Route r[]) {
	
	int i = 0;
	int j = 0;
	char temp;
	
	node p, q;
	temp = fgetc(fp);
	while (temp != -1) {
		for (j = 0; temp != '#'; j++) {
			//_putch(temp);
			r[i].name[j] = temp;
			temp = fgetc(fp);
		}
		r[i].name[j] = '\0';//�ַ���������־
		//cout << r[i].name << "��" << endl;

		p = r[i].first = (node)malloc(sizeof(N));
		for (j = 0; temp != ' '; j++) {
			temp = fgetc(fp);
			//_putch(temp);
			if (!p) {//��ָ���ж�
				cout << "p is null" << endl;
			}
			else {
				p->NodeName[j] = temp;
			}
		}
		if (!p) {//��ָ���ж�
			cout << "p is null" << endl;
		}
		else {
			p->NodeName[j] = '\0';
			p->pre = NULL;
			temp = fgetc(fp);
			//cout << p->NodeName;
		}
		while (temp != ':') {//����վ��
			q = (node)malloc(sizeof(N));
			if (!q) {//��ָ���ж�
				cout << "q is null" << endl;
			}
			else if (!p) {
				cout << "p is null" << endl;
			}
			else {
				q->pre = p;
				p->next = q;
				p = q;
			}
			
			for (j = 0; temp != ' '; j++) {
				if (!p) {//��ָ���ж�
					cout << "p is null" << endl;
				}
				else {
					p->NodeName[j] = temp;
					temp = fgetc(fp);
				}
			}
			if (!p) {//��ָ���ж�
				cout << "p is null" << endl;
			}
			else {
				p->NodeName[j] = '\0';
			}
			if (temp == ' ') {
				temp = fgetc(fp);
			}
			//cout << p->NodeName << ' ';
		}
		if (!p) {//��ָ���ж�
			cout << "p is null" << endl;
		}
		else {
			p->next = NULL;
		}
		temp = fgetc(fp);
		if (temp == '\n') {//�����ж�
			i++;
		}
	}
	return 0;
}
int search(Route r[]) {
	int index=0;
	int num;
	cout << "��������·����" << endl;
	cin >> num;
	for (index;index<=100; index++) {
		int s = atoi(r[index].name);
		//cout << s<<endl;
		if (s==num) {
			cout << r[index].name << " " << r[index].first->NodeName;
			node n = r[index].first->next;
			while (n->next!=NULL) {
				cout << n->NodeName<<" ";
				n = n->next;
			}
			cout << n->NodeName;
			return 0;
		}
		else {
			continue;
		}
	}
	cout << "��������ȷ����·���ƣ�";
	search(r);
	return 0;
}
int main() {
	FILE* fp;
	fp = fopen("busroute.txt", "r");
	Route r[100];
	initPath(fp,r);
	search(r);
	return 0;
}
