#ifndef STACK_H
#define STACK_H
#include <cstddef>

template<typename T>
struct stack{
	size_t size_ = 0;
	size_t current_ = 0;
	T* pT_;
	
	public:
	explicit stack(size_t size = 100) : size_{size}, pT_{new T[size_]} {};

	void push(const T& elem) { 
		pT_[current_] = elem; 
		++current_; //basic garantee 
	};

	T& top() {
		return pT_[current_-1];
	};

	void pop() {
		--current_;
	};

	bool empty(){
		return current_ == 0;
	};

	~stack() { delete[] pT_; };
};

#endif
