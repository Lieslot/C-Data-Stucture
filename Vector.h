template<typename T>
class VectorIterator {

private:
	T* begin;
	T* cur;
public:

	VectorIterator(T* begin = nullptr) : begin(begin), cur(begin) {}

	VectorIterator& operator++() {
		cur++;

		return *this;
	}

	VectorIterator& operator--() {
		if (begin == cur) return *this;
		cur--;
		return *this;
	}

	bool operator!=(const VectorIterator& other) const {
		return this->cur != other.cur;
	}

	bool operator==(const VectorIterator& other) const {
		return this->cur == other.cur;
	}


	T& operator*() {
		return *cur;
	}
	T operator*() const {
		return *cur;
	}




};


#include<iostream>

template<typename T>
class Vector {



private:
	int capacity;
	int len;
	T* array;


public:

	Vector() : capacity(1), array(new T[1]), len(0) {}

	Vector(int count, T initValue = T()) : array(new T[count]), capacity(count), len(count) {

		for (int i = 0; i < count; i++) {
			this->array[i] = initValue;
		}

	}
	~Vector() {
		if (capacity > 0) {
			delete[] array;
			array = nullptr;
		}
	}

	 //using iterator = VectorIterator<T>;



	void arrayCopy(T dest[], T src[], int startIndex) {
		for (int i = startIndex, j = 0; j < len; i++, j++) {
			dest[i] = src[j];
		}
	}

	bool isEmpty() {
		return len == 0;
	}

	void resize(int newSize, int startIndex = 0) {
		T* temp = new T[newSize];

		arrayCopy(temp, array, startIndex);


		delete[] array;
		array = nullptr;
		array = temp;

		capacity = newSize;
		len = std::min(len, newSize);
	}

	void pushBack(T value) {



		if (capacity == len) {
			resize(capacity * 2, 0);
		}


		array[len++] = value;


	}



	void popBack() {
		if (this->isEmpty()) {
			return;
		}
		len--;

				

	}

	void pushFront(T value) {
		if (capacity == len) {
			resize(capacity * 2, 1);

		}

		for (int i = capacity - 1; i >= 0; i--) {
			array[i + 1] = array[i];
		
		len++;
		array[0] = value;

		}
	}
	void popFront(T value) {
		for (int i = capacity - 2; i >= 0; i--) {
			array[i] = array[i + 1];
		}
		len--;
	}

	int size() {
		return len;
	}

	T operator[](int index) const {
		return array[index];
	}
	T& operator[](int index) {
		return array[index];
	}

	iterator begin() {
		return iterator(array);
	}
	iterator end() {
		return iterator(array + len);
	}

	 







};