#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <future>

#define NUM_THREADS 4

class ThreadPool {
    public:
        ThreadPool();
        ~ThreadPool();
        std::future<void> enqueue(std::function<void()> task);
    private:
        std::vector<std::thread> threads_;
        std::queue<std::function<void()> > tasks_;
        std::mutex queue_mutex_;
        std::condition_variable cv_;
        bool stop_ = false;
};

#endif