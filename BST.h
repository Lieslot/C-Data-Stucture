#include<iostream>



//
//template<typename T>
//class BstIterator {
//private:
//	Node<T>* cur, subRoot;
//

//
//	
//public:
//	BstIterator(Node<T>* initPointer) : {}
//
//
//	T& operator*() {
//		return cur->data;
//	}
//	T operator*() {
//		return cur->data;
//	}
//
//	
//	BstIterator search() {
//		
//	}
//
//
//	BstIterator operator++() {
//
//		
//
//
//
//	}
//
//
//
//
//
//
//};

using namespace std;

template<typename T>
struct Node {

	Node* parent;
	Node* leftChild;
	Node* rightChild;
	T data;
	int cnt;

	Node<T>(T data) : parent(nullptr), data(data), leftChild(nullptr), rightChild(nullptr), cnt(1) {}


	
};




template<typename T>
class BinarySearchTree {

private:

	Node<T>* root;
	int len;
	void dfs(Node<T>* cur) {
		if (cur->leftChild != nullptr) dfs(cur->leftChild);

		for (int i = 0; i < cur->cnt; i++)cout << cur->data << " ";

		if (cur->rightChild != nullptr) dfs(cur->rightChild);
	}

	void clear(Node<T>* node) {
		if (node != nullptr) {
			clear(node->leftChild);
			clear(node->rightChild);
			delete node;
		}
	}



public:
	BinarySearchTree<T>() {
		len = 0;
		root = nullptr;
	}
	BinarySearchTree<T>(T initData) {
		root = new Node<T>(initData);
		len = 1;
	}

	~BinarySearchTree<T>() {
		clear(root);
	}

	void add(T value) {

		Node<T>* newNode = new Node(value);
		

		len++;


		if (len == 1) {
			root = newNode;
			return;
		}

		Node<T>* curNode = root;
		while (1) {
	

			if (curNode->data == newNode->data) {
				curNode->cnt++;
				break;
			}

			if (curNode->data < newNode->data) {
				if (curNode->rightChild == nullptr) {
					curNode->rightChild = newNode;
					newNode->parent = curNode;
					break;
				}
				curNode = curNode->rightChild;

			}
			else {
				if (curNode->leftChild == nullptr) {
					curNode->leftChild = newNode;
					newNode->parent = curNode;

					break;
				}
				curNode = curNode->leftChild;
			}




	

		}




	}

	pair<Node<T>*, bool> find(T value) {

		if (len == 0) {
			return { nullptr, 0 };
		}



		Node<T>* curNode = root;

		while (curNode != nullptr) {


			if (curNode->data == value) {
				return { curNode, 1 };
			}

			if (curNode->data < value) {
				curNode = curNode->rightChild;





			}
			else if (curNode->data > value) {
				curNode = curNode->leftChild;
			}







		}
		return { nullptr,0 };

	
	}


	bool del(T value) {

		auto [targetNode, isFound] = find(value);

		if (isFound == false) {
			return 0;
		}


		len -= targetNode->cnt;


		if (targetNode->leftChild == nullptr && targetNode->rightChild == nullptr) {

			if (root != targetNode) {
				if (targetNode->parent->leftChild == targetNode) targetNode->parent->leftChild = nullptr;
				if ( targetNode->parent->rightChild == targetNode) targetNode->parent->rightChild = nullptr;
			}

			delete targetNode;
			targetNode = nullptr;

			return 1;

		}


		Node<T>* nxt = targetNode->rightChild;
		Node<T>* pre = targetNode->leftChild;

		if (pre != nullptr) {



			while (pre->rightChild != nullptr) {
				pre = pre->rightChild;
			}

			targetNode->data = pre->data;
			targetNode->cnt = pre->cnt;

			 
				
			if (pre == pre->parent->rightChild) {
					pre->parent->rightChild = pre->leftChild;
			}
			else {
					pre->parent->leftChild = pre->leftChild;
			}
			
			if (pre->leftChild != nullptr) pre->leftChild->parent = pre->parent;
		

			

			delete pre;
			pre = nullptr;

			return 1;


		}

		if (nxt != nullptr) {
			while (nxt->leftChild != nullptr) {
				nxt = nxt->leftChild;
			}

			targetNode->data = nxt->data;
			targetNode->cnt = nxt->cnt;

			if (nxt == nxt->parent->rightChild) {
				nxt->parent->rightChild = nxt->rightChild;
			}
			else {
				nxt->parent->leftChild = nxt->rightChild;
			}

			if (nxt->rightChild != nullptr) nxt->rightChild->parent = nxt->parent;

			delete nxt;
			nxt = nullptr;

			return 1;
		}










	}




	void print() {
		if (len == 0) return;
		this->dfs(root);
	}





};