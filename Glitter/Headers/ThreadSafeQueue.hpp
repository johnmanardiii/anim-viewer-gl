#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

// reference: https://www.geeksforgeeks.org/implement-thread-safe-queue-in-c/#
template <typename T>
class ThreadSafeQueue
{
private:
	std::queue<T> m_queue;

	// mutex for thread synchronization
	std::mutex m_mutex;

	// condition variable for signaling the "popping" thread
	std::condition_variable m_cond;
public:
	void push(T item)
	{
		// lock the mutex
		std::unique_lock<std::mutex> lock(m_mutex);
		// push the item
		m_queue.push(item);
		// trigger the condition variable if there is a thread waiting on it
		m_cond.notify_one();
	}

	T pop()
	{
		// lock the mutex
		std::unique_lock<std::mutex> lock(m_mutex);
		// wait until not empty
		m_cond.wait(lock[this]() { return !m_queue.empty(); });
		// return and remove the front item from the queue
		T item = m_queue.front();
		m_queue.pop();
		return item;
	}
};