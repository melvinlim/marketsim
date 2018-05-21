#ifndef _STACK_H
#define _STACK_H
#include<stdio.h>
#include<stdlib.h>
template<typename T>
class Stack{
private:
public:
	int maxSize;
	int size;
	T *item;
	Stack(int maxSize){
		size=0;
		this->maxSize=maxSize;
		item=new T[maxSize];
	}
	~Stack(){
		delete[] item;
	}
	void push_back(T &x){
/*
		T *p=item;
		p+=size;
		*p=x;
		size++;
*/
		assert(size<maxSize);
		item[size++]=x;
	}
	void setIndex(T &x,int i){
		item[i]=x;
	}
	T &pop_back(){
		assert(size>0);
		return item[--size];
	}
	bool empty(){
		return size==0;
	}
	const T atIndex(int i) const{
		return item[i];
	}
	T &atIndex(int i){
		return item[i];
	}
	T &back(){
		return item[size-1];
	}
	void clear(){
		size=0;
	}
	T &operator[](int i){
		return item[i];
	}
	const T &operator[](int i) const{
		return item[i];
	}
	void print(int lineSz=0){
		int i;
		if(lineSz==0)	lineSz=size;
		for(i=0;i<size;i++){
			printf("[%3i] %+.09f ",i,atIndex(i));
			if(i%lineSz==0)
				printf("\n");
		}
		printf("\n");
	}
	friend bool operator==(const Stack &lhs,const Stack &rhs){
		T tol=0.0001;
		for(int i=0;i<lhs.size;i++){
			if(fabs(lhs.item[i]-rhs.item[i])>tol){
				return false;
			}
		}
		return true;
	}
};
#endif
