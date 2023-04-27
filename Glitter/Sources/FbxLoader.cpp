#include "FbxLoader.hpp"
#include <fbxsdk.h>
#include <atomic>
#include <functional>
#include <iostream>

void LoadFbxThread(ThreadSafeQueue<std::string>& fbxPathQueue, ThreadSafeQueue<std::shared_ptr<AnimatedModel>>& m_completedModelQueue, const std::atomic<bool>& flag)
{
	while (flag)
	{
		std::cout << "FbxLoader thread running" << std::endl;
	}
	std::cout << "FbxLoader thread finished" << std::endl;
}

FbxLoader::FbxLoader() : m_flag(true)
{
	// Create a thread that loads fbx models on its own
	m_fbxLoaderThread = std::make_unique<std::thread>(LoadFbxThread, std::ref(m_fbxPathQueue), std::ref(m_completedModelQueue), std::cref(m_flag));
}

FbxLoader::~FbxLoader()
{
	m_flag = false;
	m_fbxLoaderThread->join();	// wait for the fbx loader thread to finish
}


void FbxLoader::Update()
{
	// check the "done" loading queue, if there is a model, add it to the render list

}

void FbxLoader::LoadFbx(std::string FbxPath)
{
	m_fbxPathQueue.push(FbxPath);
}

