#include <mutex>

template <typename T>
class safeVariable {
    public:
        safeVariable() = default;
        ~safeVariable() = default;

        void set(T value) {
            std::unique_lock<std::mutex> _lock(_mtx);
            _value = value;
            _lock.unlock();
        }
        T get(void) {
            std::unique_lock<std::mutex> _lock(_mtx);
            return _value;
        }
        void increment(void) {
            std::unique_lock<std::mutex> _lock(_mtx);
            _value++;
            _lock.unlock();
        }
        void decrement(void) {
            std::unique_lock<std::mutex> _lock(_mtx);
            _value--;
            _lock.unlock();
        }

    protected:
    private:
        std::mutex _mtx;
        T _value;
};

