#define _CRT_SECURE_NO_DEPRECATE 
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <string>
#include "s.h"
using namespace std;

void ShortestLine(Route r[]);

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
	int num;
	cout << "��������·����" << endl;
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
	cout << "��������ȷ����·���ƣ�" << endl;
	search(r);
	return 0;
}

//��λվ�����ڵ�·��
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

void FindPath(Route r[],ran ranA,ran ranB) {
	if (ranA == NULL || ranB == NULL) {
		cout << "�޴�վ��,����������" << endl;
		ShortestLine(r);
	}
	else {
		cout << ranA->r->name << ranA->n->NodeName << ranB->r->name << ranB->n->NodeName << endl;
		int x = atoi(ranA->r->name);
		int y = atoi(ranB->r->name);
		if (x == y) {//����վ����ͬһ����·
			node s = ranA->n;
			int i = 0;
			while (s->NodeName != ranB->n->NodeName) {
				s = s->next;
				if (s->NodeName == ranB->n->NodeName) {
					i = 0;
					break;
				}
				else if (s->next == NULL) {
					s = ranA->n;
					while (s->NodeName != ranB->n->NodeName) {
						s = s->pre;
						if (s->NodeName == ranB->n->NodeName) {
							i = 1;
							break;
						}
					}
					break;
				}
			}
			switch (i) {
			case 0://�������
				while (ranA->n->NodeName != ranB->n->NodeName) {
					cout << ranA->n->NodeName << endl;
					ranA->n = ranA->n->next;
				}
				cout << ranA->n->NodeName << endl;
				break;
			case 1://���ǰ��
				while (ranA->n->NodeName != ranB->n->NodeName) {
					cout << ranA->n->NodeName << endl;
					ranA->n = ranA->n->pre;
				}
				cout << ranA->n->NodeName << endl;
				break;
			}
		}
		else {//0������  1 ֻ�辭��2����
			int i = 0;
			string c1, c2;
			node s1 = ranA->r->first;
			node t = new N;
			while (s1 != NULL) {
				node s2 = ranB->r->first;
				while (s2 != NULL) {
					c1 = s1->NodeName;
					c2 = s2->NodeName;
					//cout << c1<<c2<<endl;
					if (c1 == c2) {
						cout << "---------------1���----------------" << endl;
						break;
					}
					s2 = s2->next;
				}
				if (c1 == c2) {
					i = 1;
					t = s2;
					break;
				}
				s1 = s1->next;
			}
			switch (i) {
			case 0:
			{
				int x = 0;
				while (r[x].name != NULL) {
					if (atoi(r[x].name) == atoi(ranA->r->name) || atoi(r[x].name) == atoi(ranB->r->name)) {
						//cout << "����" << r[x].name;
						x++;
						continue;
					}
					s1 = r[x].first;
					while (s1 != NULL) {
						node s2 = ranB->r->first;
						while (s2 != NULL) {
							c1 = s1->NodeName;
							c2 = s2->NodeName;
							if (c1 == c2) {
								cout << "---------------2���----------------" <<endl;
								break;
							}
							s2 = s2->next;
						}
						if (c1 == c2) {
							break;
						}
						s1 = s1->next;
					}
					if (c1 == c2) {
						break;
					}
					x++;
				}
				//cout << r[x].name << s1->NodeName << endl;
				ran ranl=new Ran;
				int n = *r[x].name;
				ranl->n = s1;
				ranl->r[0] = r[x];
				ranl->r[0].name[30] = n;
				FindPath(r, ranA, ranl);
				FindPath(r, ranl, ranB);
			}
			break;
			case 1:
				c1 = ranA->n->NodeName;
				while (c1 != c2) {
					cout << ranA->n->NodeName << endl;
					ranA->n = ranA->n->next;
					c1 = ranA->n->NodeName;
				}
				cout << ranA->n->NodeName << endl;
				cout << "��" << ranB->r->name << "��" << endl;
				while (ranA->n->NodeName != ranB->n->NodeName) {
					t = t->next;
					ranA->n = t;
					cout << ranA->n->NodeName << endl;
				}
				break;
			}
		}
	}
}

void ShortestLine(Route r[]) {
	ran ran1=(ran)malloc(sizeof(Ran)), ran2=(ran)malloc(sizeof(Ran));
	string nn1, nn2;
	cout << "��������վ��" << endl;
	cin >> nn1;
	cin >> nn2;
	ran1=record(r, nn1);
	ran2=record(r, nn2);

	FindPath(r, ran1, ran2);

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