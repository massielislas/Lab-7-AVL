#pragma once
#include "NodeInterface.h"
#include <iostream>

using namespace std;

class Node : public NodeInterface
{
	friend class AVL;

private:
	int data;
	Node* left;
	Node* right;
	int balance;

public:
	Node() {};
	Node(int);
	~Node() {};
	int getData() const;
	Node* getLeftChild() const;
	Node* getRightChild() const;
	int getHeight();
	int getHeight(Node*);

};