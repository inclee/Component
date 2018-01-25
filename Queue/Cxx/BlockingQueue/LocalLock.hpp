//
//  LocalLock.hpp
//  BlockingQueue
//
//  Created by lixu on 2018/1/25.
//  Copyright © 2018年 lixu. All rights reserved.
//

#ifndef LocalLock_hpp
#define LocalLock_hpp

#include <ostream>
#include <mutex>

class LocalLock{
public:
    LocalLock(std::mutex & mutx):mtx(mutx){
        mtx.lock();
    };
    void unlock(){
        mtx.unlock();
    }
    ~LocalLock(){
        mtx.unlock();
    }
    LocalLock(LocalLock const& other) = delete;
    LocalLock& operator=(LocalLock const& other) = delete;
private:
    std::mutex& mtx;
};

#endif /* LocalLock_hpp */
