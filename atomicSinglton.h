#ifndef __ATOMIC_SINGLTON__
#define __ATOMIC_SINGLTON__
/*
	c++ - Implementation of multithread safe Singleton with atomic built-in functions.
*/

namespace advcpp
{

template <typename T> 
class Singleton
{
    public:
        static T& getInstance();

    private:
        static T* instance;
        static volatile int lock;
        Singleton();
        ~Singleton();

}; // class Singleton

template <typename T> 
T* Singleton<T>::instance = 0;

template <typename T> 
volatile int Singleton<T>::lock = 0;

template <typename T> 
T& Singleton<T>::getInstance()
{
	while (__sync_lock_test_and_set(&lock, 1)) while (lock);
    // critical section
    __sync_bool_compare_and_swap(&instance, 0, new T);
    __sync_lock_release(&lock);

    return *instance;
}

template <typename T> 
Singleton<T>::Singleton(){}


template <typename T> 
Singleton<T>::~Singleton()
{
	delete instance;
}

} // namespace advcpp


#endif /* __ATOMIC_SINGLTON__ */
