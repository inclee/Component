/*
 * BlockingQueue.h
 *
 *  Created on: 2018年1月24日
 *      Author: lixu
 */

#ifndef SRC_BLOCKINGQUEUE_H_
#define SRC_BLOCKINGQUEUE_H_

#include <condition_variable>
#include <mutex>
#include <queue>

template<typename T>
class BlockingQueue {
public:
	BlockingQueue(unsigned int capacity);
	void push(const T& t);
	T& pop();
	virtual ~BlockingQueue();
private:
	std::queue<T> _queue;
	std::mutex _mtx;
	std::condition_variable _cond;
	std::unique_lock<std::mutex>& _lock;
	unsigned int _capacity;
};

#endif /* SRC_BLOCKINGQUEUE_H_ */
