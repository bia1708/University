//
// Created by bia on 05/11/2023.
//

#include <iostream>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>

class ThreadPool {
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable cv;
    bool stop = false;

public:
    ThreadPool(int numThreads) {
        for (int i = 0; i < numThreads; i++) {
            threads.emplace_back([this]() {
                while (true) {
                    std::function<void()> task;

                    // unique lock for the queue of tasks, for the cv and for the stop variable
                    std::unique_lock<std::mutex> lock(queueMutex);
                    // wait for tasks to be assigned or until there are no more tasks
                    cv.wait(lock, [this] {
                        return stop || !tasks.empty();
                    });

                    if (stop && tasks.empty()) {
                        return;
                    }

                    // get first task from queue
                    task = tasks.front();
                    tasks.pop();
                    lock.unlock();

                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        // notify all threads to stop and join them
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
        lock.unlock();
        cv.notify_all();
        for (std::thread& thread : threads) {
            thread.join();
        }
    }

    void enqueue(std::function<void()> task) {
        // add a task to the queue and notify threads
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.push(task);
        lock.unlock();
        cv.notify_one();
    }
};