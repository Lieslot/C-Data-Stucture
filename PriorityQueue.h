#include "Vector.h"

template<typename T>
void swap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}




template<typename T>
class PriorityQueue {
	


private:
	Vector<T> data;
	int len;

public:
	
	PriorityQueue<T>() {
		len = 0;
		data.pushBack(T());


	}

	void push(T value) {


		data.pushBack(value);
		len++;

		int curPosition = len;

		while (curPosition != 1) {
			int parent = curPosition / 2;

			if (data[parent] > data[curPosition]) break;
			
			swap(data[parent], data[curPosition]);

			curPosition = parent;
			
		}
		
	}

	void pop() {
		if (len == 0) {
			
			return;

		}

		swap(data[1], data[len]);
		len--;

		data.popBack();

		if (len == 0) return;

		int curPosition = 1;

		while (curPosition*2 <= len) {
			int leftIndex = curPosition * 2;
			int rightIndex = curPosition * 2+1;

			int nxtIndex = leftIndex;
			if (rightIndex <=  len && data[rightIndex] > data[leftIndex]) {


				nxtIndex = rightIndex;

		
			}
		

			if (data[nxtIndex] > data[curPosition]) {
					swap(data[curPosition], data[nxtIndex]);
					curPosition = nxtIndex;
			}
			else {
					break;

			}
		
			
			

		}
		
		
		
		


		
	}

	T top() {
		return data[1];
	}

	int size() {
		return len;
	}

	bool isEmpty() {
		return this->size() == 0;
	}

	
	
	
	


};


