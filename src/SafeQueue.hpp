/*
** EPITECH PROJECT, 2022
** PLAZZA_BOOTSTRAP
** File description:
** SafeQueue
*/

#ifndef SAFEQUEUE_HPP_
#define SAFEQUEUE_HPP_

#include "ISafeQueue.hpp"
#include <mutex>
#include <condition_variable>
#include <queue>
#include <iostream>

// Template SafeQueue
/**
 * @brief SafeQueue use to store data (event) safely
 * @tparam T
 */
template <typename T>
class SafeQueue: public ISafeQueue<T> {
    public:
        SafeQueue() {};
        virtual ~SafeQueue() {};

        /**
         * @brief Push value in the queue
         * @param T value to push
         */
        void Push(T value) {
            std::unique_lock<std::mutex> _lock(_mtx);
            _queue.push(value);
            _lock.unlock();
            _cv.notify_one();
        }

        // void Stop() {
        //     std::unique_lock<std::mutex> _lock(_mtx);
        //     _isRunning = false;
        //     _lock.unlock();
        //     _cv.notify_all();
        // }

        /**
         * @brief Pop a value from the queue if it's possible
         * @return true if the value is pop
         * @return false if the queue is empty
         */
        bool TryPop(T &value) {
            std::unique_lock<std::mutex> _lock(_mtx);
            _cv.wait(_lock, [this] { return !_queue.empty() || !_isRunning; });
            if (!_isRunning)
                return false;
            value = _queue.front();
            _queue.pop();
            return true;
        }

        /**
         * @brief Print value of the queue
         */
        void PrintValues() {
            std::unique_lock<std::mutex> _lock(_mtx);
            while (!_queue.empty()) {
                // std::cout << queue.front() << std::endl;
                _queue.pop();
            }
        }

        /**
         * @brief Pop a value from the queue
         * @return T return the queue
         */
        T Pop() {
            std::unique_lock<std::mutex> _lock(_mtx);
            _cv.wait(_lock, [this] { return !_queue.empty(); });
            T value = _queue.front();
            _queue.pop();
            return value;
        }

        /**
         * @brief Get the Size queue
         * @return size_t return the size of the queue
         */
        size_t GetQueueSize() {
            std::unique_lock<std::mutex> _lock(_mtx);
            return _queue.size();
        }

        /**
         * @brief Get if the queue is empty
         * @return true if the queue is not empty
         * @return false if the queue is empty
         */
        bool isEmpty() {
            std::unique_lock<std::mutex> _lock(_mtx);
            return _queue.empty();
        }

        /**
         * @brief Get the first element of the queue
         * @return T the first element of the queue
         */
        T getFront() {
            std::unique_lock<std::mutex> _lock(_mtx);
            return _queue.front();
        }

    private:
        std::queue<T> _queue;
        std::mutex _mtx;
        std::condition_variable _cv;
        bool _isRunning = true;
};

#endif /* !SAFEQUEUE_HPP_ */
