#pragma once
#include<iostream>


struct Node {

	int value;
	Node* leftChild;
	Node* rightChild;
	Node* parent;

	Node(const int& value = NULL) : value(value), leftChild(NULL), rightChild(NULL), parent(NULL) {};



};
