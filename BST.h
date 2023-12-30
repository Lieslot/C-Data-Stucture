#include<queue> 
#include"Node.h"





class BST {


private:
	Node* root;
	int length; // 현재 존재하는 메모리의 갯수

	inline void preOrder(Node* cur) {
		
		std::cout << cur->value << " ";

		if (cur->leftChild != NULL) preOrder(cur->leftChild);


		if (cur->rightChild != NULL) preOrder(cur->rightChild);
	
	}
	inline void inOrder(Node* cur) {


		if (cur->leftChild != NULL) inOrder(cur->leftChild);

		std::cout << cur->value << " ";

		if (cur->rightChild != NULL) inOrder(cur->rightChild);
	}

	inline void postOrder(Node* cur) {

		if (cur->leftChild != NULL) postOrder(cur->leftChild);

		if (cur->rightChild != NULL) postOrder(cur->rightChild);

		std::cout << cur->value << " ";

	}


	// 공백 print
	inline void printSpace(int count) {

		for (int i = 0; i < count; i++) std::cout << " ";
	}
	// 노드 print
	inline void printNode(Node* node) {

		if (node != NULL) std::cout << node->value;
		else std::cout << "X";
	}

		// 최대 깊이 구하기
	inline int getMaxDep(Node* cur, int curDep) {

		

		int ret = curDep;

		if (cur->leftChild != NULL) ret = std::max(ret,getMaxDep(cur->leftChild, curDep+1));

		if (cur->rightChild != NULL) ret = std::max(ret,getMaxDep(cur->rightChild, curDep+1));

		return ret;
	}
	// 소멸자
	inline void clean(Node* cur) {
		if (cur->leftChild != NULL) clean(cur->leftChild);
		if (cur->rightChild != NULL) clean(cur->rightChild);
		delete cur;
	}
 
public:

	BST();
	~BST();

	void insert(const int& value);

	Node* find(const int& value);

	void remove(const int& value);

	void print();

	void preOrder();

	void inOrder();

	void postOrder();
	
	int getMaxDep();

};


BST::BST() {
	length = 0;
}
//소멸자
BST::~BST() {
	clean(root);
}
 
void BST::insert(const int& value) {



	if (length == 0) {
		
		root = new Node(value);
		length++;
		return;
	}


	Node* curNode = root;
	bool isLeft; // leftChild로 들어왔으면 true 아니면 false
	std:: cout << root;
	// 탐색과정
	while (true) {

		Node* prev = curNode;


		if (curNode->value >= value) {
			curNode = curNode->leftChild;

			isLeft = true;

		}

		else {

			curNode = curNode->rightChild;

			isLeft = false;
		}

		
		if (curNode == NULL) {

			Node * newNode = new Node(value);
			newNode->parent = prev;

			if (isLeft) prev->leftChild = newNode;
			else prev->rightChild = newNode;

			length++;


			return;
		}



	}
}

// 특정 value를 가지는 노드 포인터를 반환
Node* BST::find(const int& value) {

	Node* curNode = root;

	// 이분 탐색 과정 
	while (true) {
		
		if (curNode->value < value) {
			curNode = curNode->rightChild;

		}

		else if (curNode->value > value) {
			curNode = curNode->leftChild;
		}

		else {
			return curNode;
		}

		if (curNode == NULL) {
			return NULL;
		}

	}

}
// 특정 value를 갖는 노드를 찾았을 경우 제거
void BST::remove(const int& value) {

	Node* target = find(value);

	if (target == NULL) return;


	std::cout << value <<  "del\n";


	length--;


	// 제거할 노드의 왼쪽 노드가 존재하는 경우
	if (target->leftChild != NULL) {


		Node* substitue = target->leftChild;

		// 왼쪽 노드에서 가장 오른쪽으로 갈수록 target 노드와 가까운 값을 가지는 노드를 얻을 수 있음.
		while (substitue->rightChild != NULL) {
			substitue = substitue->rightChild;

		}

		// 대체할 값을 찾으면 target에 덮어쓰기
		target->value = substitue->value;

		Node* subParent = substitue->parent;

		// substitue에게 자식이 있으면 substitue의 부모와 이어주어서 substitue 제거
		if (substitue->leftChild != NULL) {
			substitue->leftChild->parent = subParent;

			// 타겟의 왼쪽이 오른쪽 자식을 가지지 않는 경우
			if (subParent->leftChild == substitue) {
				subParent->leftChild = substitue->leftChild;
			}

			if (subParent->rightChild == substitue) {
				subParent->rightChild = substitue->leftChild;

			}
		}
		// substitue에게 자식이 없으면 그냥 제거
		else {
			if (subParent->leftChild == substitue) {
				subParent->leftChild = NULL;
			}

			if (subParent->rightChild == substitue) {
				subParent->rightChild = NULL;

			}
		}
		// substitue 메모리 해제
		delete substitue;

		return;

	}
	// 왼쪽 노드가 없고 오른쪽 노드만 존재하는 경우
	if (target->rightChild != NULL) {
		Node* substitue = target->rightChild;


		while (substitue->leftChild != NULL) {
			substitue = substitue->leftChild;

		}

		target->value = substitue->value;

		Node* subParent = substitue->parent;

		if (substitue->rightChild != NULL) {
			substitue->rightChild->parent = subParent;

			if (subParent->leftChild == substitue) {
				subParent->leftChild = substitue->rightChild;
			}
			// 타겟의 오른쪽이 왼쪽 자식을 가지지 않는 경우
			if (subParent->rightChild == substitue) {
				subParent->rightChild = substitue->rightChild;

			}
		}
		else {
			if (subParent->leftChild == substitue) {
				subParent->leftChild = NULL;
			}
			// 타겟의 오른쪽이 왼쪽 자식을 가지지 않는 경우
			if (subParent->rightChild == substitue) {
				subParent->rightChild = NULL;

			}
		}

		delete substitue;

		return;


	}

	// 왼쪽 자식 오른쪽 자식 모두 없는 경우

	target->value = NULL;

	//length가 1인 경우
	if (target == root) {
		
		return;
	}


	if (target->parent->leftChild == target) {
		target->parent->leftChild = NULL;

	}

	if (target->parent->rightChild == target) {
		target->parent->rightChild = NULL;

	}

}


void BST::preOrder() {

	std::cout << "preorder: ";

	
	if (length == 0) return;

	preOrder(root);
}

void BST::inOrder() {

	std::cout << "inorder: ";

	if (length == 0) return;

	inOrder(root);
}

void BST::postOrder() {

	std::cout << "postorder: ";

	if (length == 0) return;

	postOrder(root);

}

int BST::getMaxDep() {
	return getMaxDep(root, 0);
}

// BFS를 이용해서 level order로 출력
void BST::print() {


	std::queue<Node*> nodesQueue;

	int maxDep = getMaxDep()+1;

	// 이진 트리에서 높이가 maxDep인 경우 가질 수 있는 최대 노드의 갯수 
	int width = (1 << maxDep+1)-1;

	nodesQueue.push(root);

	for (int curDep = 0; curDep < maxDep; curDep++) {


		for (int i = 0; i < (1 << curDep); i++) {

			Node* curNode = nodesQueue.front();
			nodesQueue.pop();

			// 서브트리에 대한 균형을 맞추기 위해 첫 노드의 간격은 절반으로
			if (i == 0)
			printSpace(width / (1 << curDep+1));
			else {
				printSpace(width / (1 << curDep));
			}
			printNode(curNode);
			// 더미 노드 채우기
			if (curNode == NULL) {
				nodesQueue.push(NULL);
				nodesQueue.push(NULL);
			}
			
			else {
				nodesQueue.push(curNode->leftChild);
				nodesQueue.push(curNode->rightChild);

			}
			
		}

		std::cout << "\n";


	}
	



}