/*
** EPITECH PROJECT, 2022
** PLAZZA_BOOTSTRAP
** File description:
** ISafeQueue
*/

#ifndef ISAFEQUEUE_HPP_
#define ISAFEQUEUE_HPP_

/**
 * @brief ISafeQueue interface
 * @tparam T
 */
template <typename T>
class ISafeQueue {
    public:
        virtual ~ISafeQueue() = default;
        virtual void Push(T value) = 0;
        virtual bool TryPop(T &value) = 0;
        virtual void PrintValues() = 0;
        virtual T Pop() = 0;
        virtual bool isEmpty() = 0;
        // virtual void stop() = 0;
        virtual T getFront() = 0;
    protected:
    private:
};
#endif /* !ISAFEQUEUE_HPP_ */
