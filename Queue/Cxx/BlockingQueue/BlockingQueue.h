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
#include "LocalLock.hpp"

template<typename T>
class BlockingQueue {
public:
    BlockingQueue(size_t capacity):
    _queue(),
    _mtx(),
    _empty_cont(),
    _full_cont(),
    _capacity(capacity){
    }
    void push(const T& t){
        while(_queue.size() == _capacity){
            std::unique_lock<std::mutex> lock(_mtx);
            _full_cont.wait(lock);
        }
        _queue.push(t);
        _empty_cont.notify_one();
    }
    T& pop(){
        while(_queue.empty()){
            std::unique_lock<std::mutex> lock(_mtx);
            _empty_cont.wait(lock);
        }
        T& t = _queue.front();
        _queue.pop();
        _full_cont.notify_one();
        return t;
    }
    size_t size (){ return _queue.size();}
    virtual ~BlockingQueue(){};
private:
	std::queue<T> _queue;
	std::mutex _mtx;
	std::condition_variable _empty_cont;
    std::condition_variable _full_cont;
	size_t _capacity;
};

#endif /* SRC_BLOCKINGQUEUE_H_ */
