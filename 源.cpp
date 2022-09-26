#define _CRT_SECURE_NO_DEPRECATE 
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <string>
#include "s.h"
using namespace std;
void ShortestLine();

int initPath(FILE* fp, Route r[]) {

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
		r[i].name[j] = '\0';//字符串结束标志
		//cout << r[i].name << "线" << endl;

		p = r[i].first = (node)malloc(sizeof(N));
		for (j = 0; temp != ' '; j++) {
			temp = fgetc(fp);
			//_putch(temp);
			if (!p) {//空指针判断
				cout << "p is null" << endl;
			}
			else {
				p->NodeName[j] = temp;
			}
		}
		if (!p) {//空指针判断
			cout << "p is null" << endl;
		}
		else {
			p->NodeName[j] = '\0';
			p->pre = NULL;
			temp = fgetc(fp);
			//cout << p->NodeName;
		}
		while (temp != ':') {//后续站点
			q = (node)malloc(sizeof(N));
			if (!q) {//空指针判断
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
				if (!p) {//空指针判断
					cout << "p is null" << endl;
				}
				else {
					p->NodeName[j] = temp;
					temp = fgetc(fp);
				}
			}
			if (!p) {//空指针判断
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
		if (!p) {//空指针判断
			cout << "p is null" << endl;
		}
		else {
			p->next = NULL;
		}
		temp = fgetc(fp);
		if (temp == '\n') {//换行判断
			i++;
		}
	}
	return 0;
}
int search(Route r[]) {
	int num;
	cout << "请输入线路名称" << endl;
	cin >> num;
	for (int i = 0; i <= 100; i++) {
		int s = atoi(r[i].name);
		//cout << s<<endl;
		if (s == num) {
			cout << r[i].name << " " << r[i].first->NodeName;
			node n = r[i].first->next;
			while (n->next != NULL) {
				cout << n->NodeName << " ";
				n = n->next;
			}
			cout << n->NodeName << endl;
			return 0;
		}
		else {
			continue;
		}
	}
	cout << "请输入正确的线路名称！" << endl;
	search(r);
	return 0;
}

node record(Route r[],node n,string nn) {
	for (int i = 0; i < 3; i++) {
		n = r[i].first;
		while (n->NodeName != nn&&n->next!=NULL) {
				n = n->next;
		}
		if (n->NodeName == nn) {
			break;
		}
	}
	if (n->NodeName != nn) {
		return NULL;
	}
	else {
		return n;
	}
	
}

void ShortestLine(Route r[]) {
	node n1 = (node)malloc(sizeof(N)), n2=(node)malloc(sizeof(N));
	string nn1, nn2;
	cout << "输入两个站点" << endl;
	cin >> nn1;
	cin >> nn2;
	n1=record(r, n1, nn1);
	n2=record(r, n2, nn2);
	if (n1 ==NULL || n2 == NULL) {
		cout << "无此站点" << endl;
		ShortestLine(r);
	}
	else {
		cout << n1->NodeName << n2->NodeName;
	}
}

int main() {
	FILE* fp;
	fp = fopen("busroute.txt", "r");
	Route r[100];
	initPath(fp, r);
	//search(r);
	ShortestLine(r);
	return 0;
}