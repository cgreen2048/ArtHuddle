#include "ThreadPool.hpp"

ThreadPool::ThreadPool() {
    size_t num_threads = NUM_THREADS;
    for (size_t i = 0; i < num_threads; ++i) {
        threads_.emplace_back([this] {
            while (true) {
                std::function<void()> task; {
                    std::unique_lock<std::mutex> lock(queue_mutex_);
                    cv_.wait(lock, [this] {
                        return !tasks_.empty() || stop_;
                    });
                    if (stop_ && tasks_.empty()) {
                        return;
                    }
                    task = std::move(tasks_.front());
                    tasks_.pop();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            stop_ = true;
        }
        cv_.notify_all();
        for (auto& thread : threads_) {
            thread.join();
        }
    }

std::future<void> ThreadPool::enqueue(std::function<void()> task) {
    auto packaged = std::make_shared<std::packaged_task<void()>>(std::move(task));
    std::future<void> res = packaged->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        tasks_.emplace([packaged]() {
            (*packaged)();
        });
    }
    cv_.notify_one();
    return res;
}