#pragma once

#include <string>
#include "ThreadSafeQueue.hpp"
#include "IUpdatable.hpp"
#include <memory>
#include <thread>
#include <mutex>

#include "AnimatedModel.hpp"

// void FbxLoaderThread()

/*
	The fbx loader is a class that manages a separate thread that loads fbx files.
	It maintains two queues, one for paths to load, and another for completed animated models.
	When a path is added to the queue, the thread will load the fbx file and add the
	completed animated model to the completed model queue.
*/
class FbxLoader : public IUpdatable
{
public:
	FbxLoader();
	~FbxLoader();

	void Update(float dt) override;
	void LoadFbx(std::string FbxPath);
private:
	std::unique_ptr<std::thread> m_fbxLoaderThread;
	std::atomic<bool> m_flag;
	ThreadSafeQueue<std::string> m_fbxPathQueue;
	ThreadSafeQueue<std::shared_ptr<AnimatedModel>> m_completedModelQueue;
};