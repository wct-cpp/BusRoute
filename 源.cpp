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
	char temp=NULL;

	node p, q;
	while (temp != -1) {
		for (j = 0;; j++) {
			temp = fgetc(fp);
			if (temp == '#') {
				break;
			}
			r[i].name[j] = temp;
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

ran record(Route r[],string nn) {
	node n;
	ran RaN = (ran)malloc(sizeof(Ran));
	for (int i = 0; i < 100; i++) {
		n = r[i].first;
		while (n->NodeName != nn&&n->next!=NULL) {
				n = n->next;
		}
		if (n->NodeName == nn) {
			RaN->r[0] = r[i];
			RaN->n = n;
			break;
		}
	}
	if (n->NodeName != nn) {
		return NULL;
	}
	else {
		return RaN;
	}
}

void ShortestLine(Route r[]) {
	ran ran1=(ran)malloc(sizeof(Ran)), ran2=(ran)malloc(sizeof(Ran));
	string nn1, nn2;
	cout << "输入两个站点" << endl;
	cin >> nn1;
	cin >> nn2;
	ran1=record(r, nn1);
	ran2=record(r, nn2);
	if (ran1 ==NULL || ran2 == NULL) {
		cout << "无此站点,请重新输入" << endl;
		ShortestLine(r);
	}
	else {
		cout << ran1->r->name << ran1->n->NodeName <<ran2->r->name<<ran2->n->NodeName<<endl;
		int x = atoi(ran1->r->name);
		int y = atoi(ran2->r->name);
		if (x==y) {//两个站点在同一条线路
			node s=ran1->n;
			int i=0;
			while (s->NodeName != ran2->n->NodeName) {
				s = s->next;
				if (s->NodeName == ran2->n->NodeName) {
					i = 0;
					break;
				}
				else if (s->next == NULL) {
					s = ran1->n;
					while (s->NodeName != ran2->n->NodeName) {
						s = s->pre;
						if (s->NodeName == ran2->n->NodeName) {
							i = 1;
							break;
						}
					}
					break;
				}
			}
			switch (i) {
				case 0:
					while (ran1->n->NodeName != ran2->n->NodeName) {
						cout << ran1->n->NodeName << endl;
						ran1->n = ran1->n->next;
					}
					cout << ran1->n->NodeName << endl;
					break;
				case 1:
					while (ran1->n->NodeName != ran2->n->NodeName) {
						cout << ran1->n->NodeName << endl;
						ran1->n = ran1->n->pre;
					}
					cout << ran1->n->NodeName << endl;
					break;
			}
		}
		else {//1 两个站点在不同线路,0 两个站点在同一条线路但站点在不同线路有重复
			node s2=ran2->r->first;
			string c1, c2;
			while (s2 != NULL) {
				node s1 = ran1->r->first;
				while(s1!=NULL) {
					c1 = s1->NodeName;
					c2 = s2->NodeName;
					//cout << c1<<c2<<endl;
					if (c1==c2) {
						//cout << "---------------相等----------------" << endl;
						break;
					}
					s1 = s1->next;
				}
				if (c1 == c2) {
					//cout << "相等" <<s2->NodeName<< endl;
					break;
				}
				s2 = s2->next;
			}
			c1 = ran1->n->NodeName;
			int i = 0;
			while ( c1!= c2) {
				cout << ran1->n->NodeName << endl;
				ran1->n = ran1->n->next;
				c1= ran1->n->NodeName;
				i=1;
			}
			switch(i) {
			case 0:
				cout << ran1->n->NodeName << endl;
				while (ran1->n->NodeName != ran2->n->NodeName) {
					s2 = s2->next;
					ran1->n = s2;
					cout << ran1->n->NodeName << endl;
				}
				break;
			case 1:
				cout << ran1->n->NodeName << endl;
				cout << "换"<<ran2->r->name<<"线"<<endl;
				while (ran1->n->NodeName != ran2->n->NodeName) {
					s2 = s2->next;
					ran1->n = s2;
					cout << ran1->n->NodeName << endl;
				}
				break;
			}
			
		}
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