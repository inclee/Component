//
//  main.cpp
//  BlockingQueue
//
//  Created by lixu on 2018/1/25.
//  Copyright © 2018年 lixu. All rights reserved.
//
#include <thread>
#include <iostream>
#include <chrono>
#include "BlockingQueue.h"

BlockingQueue<int> bQueue(10);
std::mutex  mtx;
std::mutex  pmtx;
std::mutex  cmtx;

int product = 2;
bool stop_product = false;

void producer_log(int p,int i){
    LocalLock lock(mtx);
    std::cout << " producer : " << i <<" : "<<p <<std::endl;
    std::flush(std::cout);
}
void consumer_log(int p,int consumer){
    LocalLock lock(mtx);
    std::cout << " consumer : "<< consumer << " : " << p <<std::endl;
    std::flush(std::cout);
}

void producer(int i){
    while(product <10000){
        LocalLock lock(pmtx);
        producer_log(product,i);
        bQueue.push(product++);
        srand(time(NULL));
        int random_variable = rand() % 1;
        std::this_thread::sleep_for(std::chrono::seconds(random_variable));
    }
    stop_product = true;
}

void consumer(int i){

    while(!stop_product || bQueue.size() > 0){
        LocalLock lock(cmtx);
        int p = bQueue.pop();
        consumer_log(p,i);
        srand(time(NULL));
        int random_variable = rand() % 1;
        std::this_thread::sleep_for(std::chrono::seconds(random_variable));
    }
}

#define PRODUCERS 20
#define CONSUMERS 30

int main(int argc, const char * argv[]) {
    std::thread producers [PRODUCERS];
    std::thread consumers [CONSUMERS];
    for(int i = 0;i < PRODUCERS; i++){
        producers[i] = std::thread(producer,i);
    }
    for(int i = 0;i < CONSUMERS; i++){
        consumers[i] = std::thread(consumer,i);
    }
    for(int i = 0;i < PRODUCERS; i++){
        producers[i].join();
    }
    for(int i = 0;i < CONSUMERS; i++){
        consumers[i].join();
    }
    return 0;
}
