#pragma once
#include "AVL.h"

AVL::AVL()
{
	root = NULL;
}


Node* AVL::find(Node* localRoot, int item)
{
	if (localRoot == NULL) //element not found
		return NULL;

	if (item < localRoot->data) //data is greater than root
		find(localRoot->left, item);

	else if (item > localRoot->data) //data is smaller than root
		find(localRoot->right, item);

	else
		return localRoot;
}

void AVL::updateAll(Node* curr)
{
	if (curr == NULL)
		return;

	else
	{
		updateAll(curr->right);
		updateAll(curr->left);

		assignBalance(curr);
	}
}

Node* AVL::getRootNode() const
{
	return root;
}

void AVL::assignBalance(Node* balancingNode)
{
	int heightOfLeft = 0;
	int heightOfRight = 0;

	//if(balancingNode->left != NULL)
		heightOfLeft = balancingNode->getHeight(balancingNode->left) * -1;

	//if (balancingNode->right != NULL)
		heightOfRight = balancingNode->getHeight(balancingNode->right);

	int balance = heightOfLeft + heightOfRight;

	balancingNode->balance = balance;
} 

void AVL::rebalance(Node*& rebalancingNode)
{
	updateAll(root);

	if (rebalancingNode->balance == -1 || rebalancingNode->balance == 1 || rebalancingNode->balance == 0)
		return;

	else
	{
		if (rebalancingNode->balance == -2 && rebalancingNode->left->balance <= 0) //LEFT LEFT, rotate right
		{
			Node* leftChild = rebalancingNode->left; //rotating right around the parent
			rebalancingNode->left = leftChild->right; //GOT FROM CLEMENT
			leftChild->right = rebalancingNode;
			rebalancingNode = leftChild;

		}

		else if (rebalancingNode->balance == -2 && rebalancingNode->left->balance == 1) //LEFT RIGHT
		{
			Node*& localRebalancingNode = rebalancingNode->left;

			Node* localRightChild = localRebalancingNode->right; //rotating left around the child
			localRebalancingNode->right = localRightChild->left;
			localRightChild->left = localRebalancingNode;
			localRebalancingNode = localRightChild;

			Node* leftChild = rebalancingNode->left; //rotating right around the parent
			rebalancingNode->left = leftChild->right; //GOT FROM CLEMENT
			leftChild->right = rebalancingNode;
			rebalancingNode = leftChild;
			
		}

		else if (rebalancingNode->balance == 2 && rebalancingNode->right->balance >= 0) //RIGHT RIGHT, rotate left
		{
			Node* rightChild = rebalancingNode->right; //rotating left around the parent
			rebalancingNode->right = rightChild->left;
			rightChild->left = rebalancingNode;
			rebalancingNode = rightChild;


		}

		else if (rebalancingNode->balance == 2 && rebalancingNode->right->balance == -1) //RIGHT LEFT
		{
			Node*& localRebalancingNode = rebalancingNode->right;
			
			Node* localLeftChild = localRebalancingNode->left; //rotating right around the child
			localRebalancingNode->left = localLeftChild->right;
			localLeftChild->right = localRebalancingNode;
			localRebalancingNode = localLeftChild;

			Node* rightChild = rebalancingNode->right; //rotating left around the parent
			rebalancingNode->right = rightChild->left;
			rightChild->left = rebalancingNode;
			rebalancingNode = rightChild;

		}
	}
}

bool AVL::insert(Node*& localRoot, int item) //AVL
{
	if (localRoot == NULL) //if this is the first node or if we found it
	{
		localRoot = new Node(item);
		return true;
	}

	else
	{
		if (item < localRoot->data)
		{
			bool returnValue = insert(localRoot->left, item);
			rebalance(localRoot);
			return returnValue;
		}

		else if (item > localRoot->data)
		{
			bool returnValue = insert(localRoot->right, item);
			rebalance(localRoot);
			return returnValue;
		}

		else
		{
			return false;

		}
	}
}

bool AVL::add(int data)
{
	return insert(this->root, data);
}

void AVL::replaceParent(Node*& oldRoot, Node*& localRoot)
{
	if (localRoot->right != NULL)
	{
		replaceParent(oldRoot, localRoot->right); 
		rebalance(localRoot);
	}

	else
	{
		oldRoot->data = localRoot->data;
		oldRoot = localRoot;
		localRoot = localRoot->left;
	}
}

bool AVL::erase(Node*& localRoot, int item)
{
	if (item < localRoot->data)
	{
		erase(localRoot->left, item);
		rebalance(localRoot);
		return true;
	}

	else if (item > localRoot->data)
	{
		erase(localRoot->right, item);
		rebalance(localRoot);
		return true;
	}

	else //if we found the node
	{
		Node* oldRoot = localRoot;
		if (localRoot->left == NULL)
			localRoot = localRoot->right;

		else if (localRoot->right == NULL)
			localRoot = localRoot->left;

		else //FOUND ITEM
		{
			replaceParent(oldRoot, oldRoot->left);
			rebalance(localRoot);

		}
		delete oldRoot;
		return true;
	}
}

bool AVL::remove(int item)
{
	if (find(root, item) == NULL)
		return false;

	else if (root == NULL)
		return false;

	else
	{
		return erase(root, item);
	}

	return false;
}

void AVL::clear()
{
	while (root != NULL)
	{
		remove(root->data);
	}
}