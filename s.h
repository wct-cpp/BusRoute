#pragma once
#include <iostream>
using namespace std;

typedef struct Node {
	char NodeName[100];
	struct Node* pre;
	struct Node* next;
}N,*node;

typedef struct Route {
	char name[30];
	struct Node* first;
	
}Route,*route;

typedef struct Ran {
	struct Route *r;
	struct Node* n;
}Ran,*ran;
