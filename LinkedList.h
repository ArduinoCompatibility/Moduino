// test1.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#ifndef LinkedList_h
#define LinkedList_h

#include <stddef.h>



typedef struct {				//계속 변경
	long unsigned int id;
	string type;
	int time_stamp;
	int property_number;
	//모듈 정보로 바꿔야댐
}mModule;

template<class T>
struct ListNode
{
	T data;
	ListNode<T> *next;
};

template <typename T>
class LinkedList {

protected:
	int _size;
	ListNode<T> *root;
	ListNode<T>	*last;

	// Helps "get" method, by saving last position
	// get메소드에서 마지막친구 데려올때 필요
	ListNode<T> *lastNodeGot;
	int lastIndexGot;
	// isCached should be set to FALSE
	// everytime the list suffer changes
	bool isCached;

	ListNode<T>* getNode(int index);

public:
	LinkedList();
	~LinkedList();

	/*
	return LinkedList size
	*/
	virtual int size();
	/*
	특정 인덱스에 node추가,
	링크 해제하고 다시연결

	*/
	virtual bool add(int index, T);
	/*
	마지막 노드 뒤에 node추가
	Increment _size;
	*/
	virtual bool add(T);
	/*
	list시작부분에 node추가
	Adds a T object in the start of the LinkedList;
	Increment _size;
	*/
	virtual bool unshift(T);
	/*
	Set the object at index, with T;
	Increment _size;
	*/
	virtual bool set(int index, T);
	/*
	특정 인덱스 객체지움
	인덱스 존재하지않으면 false
	존재하면 size하나 감소
	*/
	virtual T remove(int index);
	/*
	Remove last object;
	*/
	virtual T pop();
	/*
	Remove first object;
	*/
	virtual T shift();
	/*
	list에서 index위치의 데이터가져옴
	없으면 false

	*/
	virtual T get(int index);

	/*
	리스트비움
	*/
	virtual void clear();

	/*
	Sort the list
	*/
	virtual void sort();
	virtual void Swap(unsigned long int* _X, unsigned long int* _Y);
	virtual T search(unsigned long int key);
};

// Initialize LinkedList with false values
template<typename T>
LinkedList<T>::LinkedList()
{
	root = NULL;
	last = NULL;
	_size = 0;

	lastNodeGot = root;
	lastIndexGot = 0;
	isCached = false;
}

// 노드지우고 메모리비우는거
template<typename T>
LinkedList<T>::~LinkedList()
{
	ListNode<T>* tmp;
	while (root != NULL)
	{
		tmp = root;
		root = root->next;
		delete tmp;
	}
	last = NULL;
	_size = 0;
	isCached = false;
}

template<typename T>
ListNode<T>* LinkedList<T>::getNode(int index) {

	int _pos = 0;
	ListNode<T>* current = root;

	// 얻을 노드가 있는지 확인
	// 이전꺼 바로 get
	if (isCached && lastIndexGot <= index) {
		_pos = lastIndexGot;
		current = lastNodeGot;
	}

	while (_pos < index && current) {
		current = current->next;

		_pos++;
	}

	// 가져온 객체 index가 요구되는거랑 같은지 확인
	if (_pos == index) {
		isCached = true;
		lastIndexGot = index;
		lastNodeGot = current;

		return current;
	}

	return false;
}

template<typename T>
int LinkedList<T>::size() {
	return _size;
}

template<typename T>
bool LinkedList<T>::add(int index, T _t) {

	if (index >= _size)
		return add(_t);

	if (index == 0)
		return unshift(_t);

	ListNode<T> *tmp = new ListNode<T>(),
		*_prev = getNode(index - 1);
	tmp->data = _t;
	tmp->next = _prev->next;
	_prev->next = tmp;

	_size++;
	isCached = false;

	return true;
}

template<typename T>
bool LinkedList<T>::add(T _t) {

	ListNode<T> *tmp = new ListNode<T>();
	tmp->data = _t;
	tmp->next = NULL;

	if (root) {
		// 이미여러번 add했을때
		last->next = tmp;
		last = tmp;
	}
	else {
		// 첫번째 call add일때 
		root = tmp;
		last = tmp;
	}

	_size++;
	isCached = false;

	return true;
}

template<typename T>
bool LinkedList<T>::unshift(T _t) {

	if (_size == 0)
		return add(_t);

	ListNode<T> *tmp = new ListNode<T>();
	tmp->next = root;
	tmp->data = _t;
	root = tmp;

	_size++;
	isCached = false;

	return true;
}

template<typename T>
bool LinkedList<T>::set(int index, T _t) {
	// 인덱스가 범위내에 있는지 확인
	if (index < 0 || index >= _size)
		return false;

	getNode(index)->data = _t;
	return true;
}

template<typename T>
T LinkedList<T>::pop() {
	if (_size <= 0)
		return T();

	isCached = false;

	if (_size >= 2) {
		ListNode<T> *tmp = getNode(_size - 2);
		T ret = tmp->next->data;
		delete(tmp->next);
		tmp->next = NULL;
		last = tmp;
		_size--;
		return ret;
	}
	else {
		// Only one element left on the list
		T ret = root->data;
		delete(root);
		root = NULL;
		last = NULL;
		_size = 0;
		return ret;
	}
}

template<typename T>
T LinkedList<T>::shift() {
	if (_size <= 0)
		return T();

	if (_size > 1) {
		ListNode<T> *_next = root->next;
		T ret = root->data;
		delete(root);
		root = _next;
		_size--;
		isCached = false;

		return ret;
	}
	else {
		// Only one left, then pop()
		return pop();
	}

}

template<typename T>
T LinkedList<T>::remove(int index) {
	if (index < 0 || index >= _size)
	{
		return T();
	}

	if (index == 0)
		return shift();

	if (index == _size - 1)
	{
		return pop();
	}

	ListNode<T> *tmp = getNode(index - 1);
	ListNode<T> *toDelete = tmp->next;
	T ret = toDelete->data;
	tmp->next = tmp->next->next;
	delete(toDelete);
	_size--;
	isCached = false;
	return ret;
}


template<typename T>
T LinkedList<T>::get(int index) {
	ListNode<T> *tmp = getNode(index);

	return (tmp ? tmp->data : T());
}

template<typename T>
void LinkedList<T>::clear() {
	while (size() > 0)
		shift();
}

template<typename T>
void LinkedList<T>::sort() {
	ListNode<T>* pCur1 = root;
	ListNode<T>* pCur2;

	for (pCur1 = root; pCur1 != NULL; pCur1 = pCur1->next) {
		for (pCur2 = pCur1->next; pCur2 != NULL; pCur2 = pCur2->next) {
			if (pCur1->data.id > pCur2->data.id)
				Swap(&pCur1->data.id, &pCur2->data.id);
		}

	}
}

template<typename T>
T LinkedList<T>::search(unsigned long int key) {
	ListNode<T>* pCur1 = root;
	for (pCur1 = root; pCur1 != NULL; pCur1 = pCur1->next)
		if (pCur1->data.id == key) {
			return pCur1->data;
		}
}

template<typename T>
void LinkedList<T>::Swap(unsigned long int* _X, unsigned long int* _Y){
	unsigned long int temp = *_X;
	*_X = *_Y;
	*_Y = temp;
}

#endif