#pragma once
#include "Node.h"

using namespace std;

Node::Node(int data)
{
	this->data = data;
	this->left = NULL;
	this->right = NULL;
	balance = 0;
}

int Node::getData() const
{
	return data;
}

Node* Node::getLeftChild() const
{
	return left;
}

Node* Node::getRightChild() const
{
	return right;
}

int Node::getHeight()
{
	return 0;
}

int Node::getHeight(Node* curr)
{
	if (curr == NULL)
		return 0;

	else
	{
		int leftHeight = getHeight(curr->left);
		int rightHeight = getHeight(curr->right);

		if (leftHeight > rightHeight)
			return (leftHeight + 1);

		else
			return (rightHeight + 1);
	}
}