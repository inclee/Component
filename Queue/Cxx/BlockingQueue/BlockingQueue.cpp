/*
 * BlockingQueue.cpp
 *
 *  Created on: 2018年1月24日
 *      Author: lixu
 */

#include "BlockingQueue.h"
#include <iostream>

template<typename T>
BlockingQueue<T>::BlockingQueue(unsigned int capacity):
	_capacity(capacity),
	_queue(),
	_cond(),
	_mtx(),
	_lock(_mtx){

}
template<typename T>
void BlockingQueue<T>::push(const T& t){
	if(_queue.size() < _capacity){
		_queue.push(t);
		_cond.notify_all();
	}else {
		std::cout<< "block wait pop item\n";
		_lock.lock();
		_cond.wait(_lock);
	}
}
template<typename T>
T& BlockingQueue<T>::pop(){
	if(_queue.size()>0){
		T& t = _queue.front();
		_queue.pop();
		_cond.notify_all();
		return t;
	}else {
		std::cout<< "block wait push item\n";
		_lock.lock();
		_cond.wait(_lock);
	}
}
template<typename T>
BlockingQueue<T>::~BlockingQueue() {

}

