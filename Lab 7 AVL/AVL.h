#pragma once
#include "AVLInterface.h"
#include "AVL.h"
#include "Node.h"

class AVL : public AVLInterface
{
private:
	Node* root;
	Node* find(Node* localRoot, int data);
	bool insert(Node*& localRoot, int item);
	bool erase(Node*& localRoot, int item);
	void rebalance(Node*& rebalancingNode);
	void assignBalance(Node* rebalancingNode);
	void replaceParent(Node*&, Node*&);
	void updateAll(Node* node);
	//Node* findParent(Node*, int data);

public:
	AVL();
	~AVL() { clear(); };
	Node* getRootNode() const;
	bool add(int data);
	bool remove(int data);
	void clear();

};
