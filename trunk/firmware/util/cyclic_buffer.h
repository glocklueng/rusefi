/**
 * @file	cyclic_buffer.h
 *
 * @date Dec 8, 2013
 * @author Andrey Belomutskiy, Daniel Hill
 *
 * Daniel Hill - Modified to use C++ - Mar 2, 2014
*/

#ifndef CYCLIC_BUFFER_H
#define CYCLIC_BUFFER_H

#include <string.h>

static const short CB_MAX_SIZE = 64;

template<typename T>
class cyclic_buffer
{
  public:
	cyclic_buffer();
    cyclic_buffer(int size);
  //cpctor
    cyclic_buffer(const cyclic_buffer& cb);
  //dtor
    ~cyclic_buffer();

  public:
  //overloaded =operator
    cyclic_buffer& operator=(const cyclic_buffer& rhCb);

  public:
    void add(int value);
    int get(int index);
    int sum(int length);
    void setSize(int size);
    void clear();

  private:
    void baseC(int size);
    volatile int elements[CB_MAX_SIZE];
    volatile int currentIndex;
    volatile int count;
    int size;
};

template<typename T>
cyclic_buffer<T>::cyclic_buffer() {
  baseC(CB_MAX_SIZE);
}

template<typename T>
cyclic_buffer<T>::cyclic_buffer(int size) {
  baseC(size);
}

template<typename T>
void cyclic_buffer<T>::baseC(int size) {
	currentIndex = 0;
	setSize(size);
}

template<typename T>
cyclic_buffer<T>::cyclic_buffer(const cyclic_buffer& cb) {
	//Deep copy the data
	currentIndex = cb.currentIndex;
	count = cb.count;
	size = cb.size;
	for (int i = 0; i < size; ++i) {
		elements[i] = cb.elements[i];
	}
}

template<typename T>
cyclic_buffer<T>::~cyclic_buffer() {
	//No dynamic allocation - safe to leave
}

//template<typename T>
//cyclic_buffer& cyclic_buffer<T>::operator=(const cyclic_buffer<T>& rhCb) {
//	//Deep copy
//	currentIndex = rhCb.currentIndex;
//	count = rhCb.count;
//	for (int i = 0; i < size; ++i) {
//		elements[i] = rhCb.elements[i];
//	}
//	return *this;
//}

template<typename T>
void cyclic_buffer<T>::add(int value) {
	++currentIndex;
	if (currentIndex == size) {
		currentIndex = 0;
	}
	elements[currentIndex] = value;

	++count;
}

template<typename T>
void cyclic_buffer<T>::setSize(int size) {
	clear();
	this->size = size;
}

template<typename T>
int cyclic_buffer<T>::get(int index) {
	return 0;
}

template<typename T>
int cyclic_buffer<T>::sum(int length) {
	if (length > count) {
		length = count;
	}

	int ci = currentIndex; // local copy to increase thread-safety
	int result = 0;

	for (int i = 0; i < length; ++i) {
		int index = ci - i;
		while (index < 0) {
			index += size;
		}

		result += elements[index];
	}

	return result;
}

template<typename T>
void cyclic_buffer<T>::clear() {
	memset((void*) elements, 0, sizeof(elements)); // I would usually use static_cast, but due to the elements being volatile we cannot.
	count = 0;
	count = 0;
}

#endif //CYCLIC_BUFFER_H
