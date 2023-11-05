//
// Created by bia on 29/10/2023.
//

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

std::queue<int> buffer;
int count = 0;  // fixed size buffer logic
std::mutex mtx;
std::condition_variable cv;
std::vector<int> vector1;
std::vector<int> vector2;

//std::vector<int> vector1 = {1, 2, 3, 4, 5};
//std::vector<int> vector2 = {5, 4, 3, 2, 1};

int res = 0;


void producer() {
    for (int i = 0; i < vector1.size(); i++) {
        int product = vector1[i] * vector2[i];

        // acquire lock for count variable
        std::unique_lock<std::mutex> lock(mtx);

        // wait until count is less than 3
        cv.wait(lock, [] { return count < 3; });

        buffer.push(product);
        count++;
        std::cout << "Produced: " << product << "\n";

        lock.unlock();
        cv.notify_all();
    }
}

void consumer() {
    int counter = 100;
    while (counter) {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until count is greater than 0
        cv.wait(lock, [] { return count > 0; });

        int data = buffer.front();
        buffer.pop();
        count--;
        std::cout << "Consumed: " << data << "\n";
        res += data;

        lock.unlock();
        cv.notify_all();
        std::cout << "Result: " << res << "\n";
        counter--;
    }
}


int main() {
//    vector1 = {1, 2, 3, 4, 5};
//    vector2 = {5, 4, 3, 2, 1};

    for(int i = 0; i < 100; i++) {
        vector1.push_back(i);
    }
    for(int i = 0; i < 100; i++) {
        vector2.push_back(i);
    }

    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}

/// Wrong implementation, but will keep it here

//void producer() {
//    for (int i = 0; i <= vector1.size(); i++) {
//        int product = vector1[i] * vector2[i];
//
//        // lock mutex for buffer
//        mtx.lock();
//
//        // wait for buffer to empty a slot
//        while (count >= 3) {
//            mtx.unlock();  // release the lock while waiting
//            std::this_thread::sleep_for(std::chrono::milliseconds(100));
//            mtx.lock();
//        }
//
//        // add product to buffer
//        if(count < 3) {
//            buffer.push(product);
//            count++;
//            std::cout << "Produced: " << product << "\n";
//        }
//        // unlock mutex for buffer
//        mtx.unlock();
//
//    }
//}
//
//void consumer() {
//    while (true) {
//        // lock mutex for buffer
//        mtx.lock();
//        // add product to buffer
//        if(count > 0) {
//            count--;
//            int data = buffer.front();
//            buffer.pop();
//            res += data;
//            std::cout << "Consumed: " << data << "\n";
//        }
//        // unlock mutex for buffer
//        mtx.unlock();
//        std::cout << "Result: " << res << "\n";
//
//    }
//}
