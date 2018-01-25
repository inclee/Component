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
    BlockingQueue(size_t capacity):
    _queue(),
    _mtx(),
    _cond(),
    _capacity(capacity){
    }
    void push(const T& t){
        if(_queue.size() < _capacity){
            _queue.push(t);
            _cond.notify_all();
        }else {
            std::unique_lock<std::mutex> lock(_mtx);
            _cond.wait(lock);
        }
    }
    T& pop(){
        if(_queue.size() == 0){
            std::unique_lock<std::mutex> lock(_mtx);
            _cond.wait(lock);
        }
        T& t = _queue.front();
        _queue.pop();
        _cond.notify_all();
        return t;
    }
    size_t size (){ return _queue.size();}
    virtual ~BlockingQueue(){};
private:
	std::queue<T> _queue;
	std::mutex _mtx;
	std::condition_variable _cond;
	size_t _capacity;
};

#endif /* SRC_BLOCKINGQUEUE_H_ */
