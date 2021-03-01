// Array.h
#ifndef _ARRAY_H
#define _ARRAY_H

typedef signed long int Long;

template <typename T>
class Array {
public:
	Array(Long capacity = 256);
	Array(const Array& source);
	~Array();
	Long Store(Long index, T object);
	Long Insert(Long index, T object);
	Long AppendFromFront(T object);
	Long AppendFromRear(T object);
	Long Delete(Long index);
	Long DeleteFromFront();
	Long DeleteFromRear();
	void Clear();
	Long Modify(Long index, T object);
	Long LinearSearchUnique(void *key, int(*compare)(void*, void*));
	void LinearSearchDuplicate(void *key, Long *(*indexse), Long *count, int(*compare)(void*, void*));
	Long BinarySearchUnique(void *key, int(*compare)(void*, void*));
	void BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*));
	void BubbleSort(int(*compare)(void*, void*));
	void SelectionSort(int(*compare)(void*, void*));
	void InsertionSort(int(*compare)(void*, void*));
	void Merge(const Array& one, const Array& other, int(*compare)(void*, void*));
	T& GetAt(Long index);
	Array& operator =(const Array& source);
	T& operator [](Long index);
	T* operator +(Long index);
	Long GetCapacity() const;
	Long GetLength() const;

private:
	T(*front);
	Long capacity;
	Long length;
};

/*
��Ī : Array
��� : �迭�� �����Ѵ�.(������)
�Է� : �Ҵ緮
��� : X
*/
template <typename T>
Array<T>::Array(Long capacity) {
	this->front = new T[capacity];
	this->capacity = capacity;
	this->length = 0;
}

/*
��Ī : Array
��� : ���� �����ڸ� �����.
�Է� : �迭�� �ּҿ� ���� ����
��� : X
*/
template <typename T>
Array<T>::Array(const Array& source) {
	Long i = 0;
	this->front = new T[source.capacity];
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

/*
��Ī :  ~Array
��� : �迭�� �Ҹ��Ų��.
�Է� : X
��� : X
*/
template <typename T>
Array<T>::~Array() {
	if (this->front != 0) {
		delete[] this->front;
	}
}

/*
��Ī : Store
��� : �迭���� �����Ѵ�.
�Է� : ��ġ, ������Ʈ
��� : ��ġ
*/
template <typename T>
Long Array<T>::Store(Long index, T object) {
	this->front[index] = object;
	this->length++;
	
	return index;
}

/*
��Ī : Insert
��� : �迭���� �����Ѵ�.
�Է� : ��ġ, ������Ʈ
��� : ��ġ
*/
template <typename T>
Long Array<T>::Insert(Long index, T object) {
	T(*front);
	Long i = 0;
	Long j = 0;

	front = new T[this->capacity + 1];
	while (i < index) {
		front[j] = this->front[i];
		j++;
		i++;
	}
	j++;
	while (i < this->length) {
		front[j] = this->front[i];
		j++;
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = front;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}

/*
��Ī : AppendFromFront
��� : �迭���� �տ� �����.
�Է� : ������Ʈ
��� : ��ġ
*/
template <typename T>
Long Array<T>::AppendFromFront(T object) {
	T(*front);
	Long index;
	Long i = 0;
	Long j = 1;

	front = new T[this->capacity + 1];
	while (i < this->length) {
		front[j] = this->front[i];
		j++;
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = front;
	this->capacity++;
	index = 0;
	this->front[index] = object;
	this->length++;

	return index;
}

/*
��Ī : AppendFromRear
��� : �迭���� �ڿ� �����.
�Է� : ������Ʈ
��� : ��ġ
*/
template <typename T>
Long Array<T>::AppendFromRear(T object) {
	T(*front);
	Long index;
	Long i = 0;
	
	front = new T[this->capacity + 1];
	while (i < this->length) {
		front[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = front;
	this->capacity++;
	index = this->length;
	this->front[index] = object;
	this->length++;

	return index;
}

/*
��Ī : Delete
��� : �迭���� �����.
�Է� : ��ġ
��� : ��ġ(0)
*/
template <typename T>
Long Array<T>::Delete(Long index) {
	T(*front) = 0;
	Long i = 0;
	Long j = 0;

	if (this->capacity > 0) {
		front = new T[this->capacity - 1];
	}
	while (i < index) {
		front[i] = this->front[j];
		j++;
		i++;
	}
	j++;
	while (i < this->length - 1) {
		front[i] = this->front[j];
		j++;
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 0) {
		this->front = front;
	}
	this->capacity--;
	this->length--;
	index = -1;

	return index;
}

/*
��Ī : DeleteFromFront
��� : �迭���� �� ���� �����.
�Է� : X
��� : ��ġ
*/
template <typename T>
Long Array<T>::DeleteFromFront() {
	T(*front);
	Long index;
	Long i = 1;
	Long j = 0;

	if (this->capacity > 0) {
		front = new T[this->capacity - 1];
	}
	while (i < this->length - 1) {
		front[j] = this->front[i];
		j++;
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 0) {
		this->front = front;
	}
	this->capacity--;
	this->length--;
	index = -1;

	return index;
}

/*
��Ī : DeleteFromRear
��� : �迭���� �� �ڸ� �����.
�Է� : X
��� : ��ġ
*/
template <typename T>
Long Array<T>::DeleteFromRear() {
	T(*front);
	Long index;
	Long i = 0;

	if (this->capacity > 0) {
		front = new T[this->capacity - 1];
	}
	while (i < this->length - 1) {
		front[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 0) {
		this->front = front;
	}
	this->capacity--;
	this->length--;
	index = -1;

	return index;
}

/*
��Ī : Clear
��� : �迭���� ����ġ�Ѵ�.
�Է� : X
��� : X
*/
template <typename T>
void Array<T>::Clear() {
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	this->capacity = 0;
	this->length = 0;
}

/*
��Ī : Modify
��� : �迭���� �����Ѵ�.
�Է� : ��ġ, ������Ʈ
��� : ��ġ
*/
template <typename T>
Long Array<T>::Modify(Long index, T object) {
	this->front[index] = object;

	return index;
}

/*
��Ī : LinearSearchUnique
��� : �迭���� �����˻��� �Ѵ�.
�Է� : Ű
��� : ��ġ
*/
template <typename T>
Long Array<T>::LinearSearchUnique(void *key, int(*compare)(void*, void*)) {
	Long index = -1;
	Long i = 0;

	while (i < this->length && compare(this->front + i, key) != 0) {
		i++;
	}
	if (i < this->length) {
		index = i;
	}

	return index;
}

/*
��Ī : LinearSearchDuplicate
��� : �迭���� �ߺ� �����˻��� �Ѵ�.
�Է� : Ű
��� : ��ġ��, ����
*/
template <typename T>
void Array<T>::LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	*count = 0;

	*indexes = new Long[this->length];

	while (i < this->length) {
		if (compare(this->front + i, key) == 0) {
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
}

/*
��Ī : BinarySearchUnique
��� : �迭���� �����˻��Ѵ�.
�Է� : Ű
��� : ��ġ
*/
template <typename T>
Long Array<T>::BinarySearchUnique(void *key, int(*compare)(void*, void*)) {
	Long index = -1;
	Long front = 0;
	Long rear;
	Long middle;

	rear = this->length - 1;
	middle = (front + rear) / 2;
	while (front <= rear && compare(this->front + middle, key) != 0) {
		if (compare(this->front + middle, key) < 0) {
			front = middle + 1;
		}
		else {
			rear = middle - 1;
		}
		middle = (front + rear) / 2;
	}
	if (front <= rear) {
		index = middle;
	}

	return index;
}

/*
��Ī : BinarySearchDuplicate
��� : �迭���� �ߺ� �����˻��Ѵ�.
�Է� : Ű
��� : ��ġ��, ����
*/
template <typename T>
void Array<T>::BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*)) {
	Long front = 0;
	Long rear;
	Long middle;
	Long i = 0;
	Long j = 0;
	*count = 0;

	rear = this->length - 1;
	middle = (front + rear) / 2;
	while (front <= rear && compare(this->front + middle, key) != 0) {
		if (compare(this->front + middle, key) < 0) {
			front = middle + 1;
		}
		else {
			rear = middle - 1;
		}
		middle = (front + rear) / 2;
	}

	front = middle - 1;
	while (front >= 0 && compare(this->front + front, key) == 0) {
		front--;
	}
	*indexes = new Long[this->length];

	i = front + 1;
	while (i <= rear && compare(this->front + i, key) == 0) {
		(*indexes)[j] = i;
		j++;
		(*count)++;
		i++;
	}
}

/*
��Ī : BubbleSort
��� : �迭���� ���������Ѵ�.
�Է� : X
��� : X
*/
template <typename T>
void Array<T>::BubbleSort(int (*compare)(void*, void*)) {
	T temp;
	Long i;
	Long j;
	
	i = this->length - 1;
	while (i >= 0) {
		j = 0;
		while (j < i) {
			if (compare(this->front + j, this->front + (j + 1)) > 0) {
				temp = this->front[j];
				this->front[j] = this->front[j + 1];
				this->front[j + 1] = temp;
			}
			j++;
		}
		i--;
	}
}

/*
��Ī : SelectionSort
��� : �迭���� ���������Ѵ�.
�Է� : X
��� : X
*/
template <typename T>
void Array<T>::SelectionSort(int(*compare)(void*, void*)) {
	T temp;
	Long i = 0;
	Long j;
	while (i < this->length - 1) {
		j = i + 1;
		while (j < this->length) {
			if (compare(this->front + i, this->front + j) > 0) {
				temp = this->front[i];
				this->front[i] = this->front[j];
				this->front[j] = temp;
			}
			j++;
		}
		i++;
	}
}

/*
��Ī : InsertionSort
��� : �迭���� ���������Ѵ�.
�Է� : X
��� : X
*/
template <typename T>
void Array<T>::InsertionSort(int(*compare)(void*, void*)) {
	T temp;
	Long i = 1;
	Long j;
	while (i < this->length) {
		temp = this->front[i];
		j = i - 1;
		while (j >= 0 && compare(this->front + j, &temp) > 0) {
			this->front[j + 1] = this->front[j];
			j--;
		}
		this->front[j + 1] = temp;
		i++;
	}
}

/*
��Ī : Merge
��� : �迭���� �����Ѵ�.
�Է� : one, other
��� : X
*/
template <typename T>
void Array<T>::Merge(const Array& one, const Array& other, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	Long k = 0;
	
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = new T[one.length + other.length];
	this->capacity = one.length + other.length;

	while (i < one.length && j < other.length) {
		if (compare(one.front + i, other.front + j) < 0) {
			this->front[k] = one.front[i];
			i++;
		}
		else {
			this->front[k] = other.front[j];
			j++;
		}
		k++;
	}

	while (i < one.length) {
		this->front[k] = one.front[i];
		k++;
		i++;
	}

	while (j < other.length) {
		this->front[k] = other.front[j];
		k++;
		j++;
	}

	this->length = one.length + other.length;
}

/*
��Ī : GetAt
��� : �迭���� �д´�.
�Է� : ��ġ
��� : ������Ʈ
*/
template <typename T>
T& Array<T>::GetAt(Long index){
	return this->front[index];
}

/*
��Ī : operator =
��� : = �����ڸ� �����Ѵ�.
�Է� : �ҽ�
��� : �迭
*/
template <typename T>
Array<T>& Array<T>::operator =(const Array& source) {
	Long i = 0;
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = new T[source.capacity];
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

/*
��Ī : operator []
��� : [] �����ڸ� �����Ѵ�.
�Է� : ��ġ
��� : ������Ʈ
*/
template <typename T>
T& Array<T>::operator [](Long index) {
	return this->front[index];
}

/*
��Ī : operator +
��� : + �����ڸ� �����Ѵ�.
�Է� : ��ġ
��� : ������Ʈ �ּ�
*/
template <typename T>
T* Array<T>::operator +(Long index) {
	return this->front + index;
}

/*
��Ī : GetCapacity
��� : �Ҵ緮�� �д´�.
�Է� : X
��� : �Ҵ緮
*/
template <typename T>
Long Array<T>::GetCapacity() const {
	return this->capacity;
}

/*
��Ī : GetLength
��� : ��뷮�� �д´�.
�Է� : X
��� : ��뷮
*/
template <typename T>
Long Array<T>::GetLength() const {
	return this->length;
}

#endif // _ARRAY_H