#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

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

	struct PopResult
	{
		T result;
		bool isValid;
	};

	void wake()
	{
		m_cond.notify_one();
	}

	void push(T item)
	{
		// lock the mutex
		std::lock_guard<std::mutex> lock(m_mutex);
		// push the item
		m_queue.push(item);
		// trigger the condition variable if there is a thread waiting on it
		m_cond.notify_one();
	}

	/*
		Pop will wait until 
			1) the queue has an element
			2) the flag is false (exit pop with an error)
		if the flag is ever false while waiting, will return std::nullopt
	*/
	PopResult pop(const std::atomic<bool>& flag)
	{
		// lock the mutex
		std::unique_lock<std::mutex> lock(m_mutex);
		// wait until not empty or flag fails
		m_cond.wait(lock, [&]() { return !m_queue.empty() || !flag; });
		if (!flag)
		{
			/*
				To figure out later, this assumes that the type has a default constructor, which
				is ok for now since the purpose of this project is to build an animation viewer
			*/
			return { T(), false };	
		}
		// return and remove the front item from the queue
		T item = m_queue.front();
		m_queue.pop();
		return {item, true};
	}

	bool empty()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_queue.empty();
	}
};