#pragma once
#include <stdint.h>
#include <vector>
#include <iostream>
#include <cassert>

// Scufftely made memoryallocator. Honestly, should probably not be used

#pragma warning (disable : 4127)

namespace MemAllocator
{

	// If you see this function, you've ventured too far.
	extern __forceinline void SetMemAtAddressToNull(void*& memAddress, int pos);

	extern char* memArena;
	extern int64_t maxArenaSize;
	extern int currentIndex;
	extern bool memInitialized;

	extern int frameMinPartition;
	extern int currentFrameIndex;
	extern int frameMaxPartition;

	enum ReturnRes
	{
		e_NO,
		e_OK
	};

	extern ReturnRes InitializeMem(int byteSize);

	extern int GetMemLeft();

	extern int GetFrameMemLeft();

#undef new
	template<typename DataType>
	DataType* AllocMem(size_t memSize)
	{
		if (CheckIfSmartPointer<DataType>())
		{
			return nullptr;
		}

		if (!memInitialized)
		{
			std::cout << "Mem not initialized" << std::endl;
			return nullptr;
		}
		if ((int64_t)currentIndex >= maxArenaSize && (int64_t)(currentIndex + memSize) >= maxArenaSize)
		{
			return nullptr;
		}

		DataType* memAddress = nullptr;
		memAddress = new (&memArena[currentIndex]) DataType();
		currentIndex += (int)memSize;

		return memAddress;
	}

#undef new
	template<typename DataType>
	DataType* AllocFrameMem(size_t memSize)
	{
		if (CheckIfSmartPointer<DataType>())
		{
			return nullptr;
		}

		if (!memInitialized)
		{
			std::cout << "Mem not initialized" << std::endl;
			return nullptr;
		}
		if ((int64_t)currentFrameIndex >= frameMaxPartition && (int64_t)(currentFrameIndex + memSize) >= frameMaxPartition)
		{
			return nullptr;
		}

		DataType* memAddress = nullptr;
		memAddress = new (&memArena[currentFrameIndex]) DataType();
		currentFrameIndex += (int)memSize;

		return memAddress;
	}

	// If you have a destructor, though shit. Call it yourself. I ain't gonna
	// -Lukas
	extern ReturnRes DeAllocFrameMem(void* memAddress, size_t memSize);

	// If you have a destructor, though shit. Call it yourself. I ain't gonna
	// -Lukas
	extern ReturnRes DeAllocMem(void* memAddress, size_t memSize);



   /**
	 * To the person who will use this function, you are weak c++ programmer.
	 * Not being able to call destructors on your own. Eat shit and die
	 *
	 *	⠀⠀⠀  ⣠⣤⣤⣤⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
	 *⠀⠀⠀⠀⠀⢰⡿⠋⠁⠀⠀⠈⠉⠙⠻⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
	 *⠀⠀⠀⠀⢀⣿⠇⠀⢀⣴⣶⡾⠿⠿⠿⢿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
	 *⠀⠀⣀⣀⣸⡿⠀⠀⢸⣿⣇⠀⠀⠀⠀⠀⠀⠙⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
	 *⠀⣾⡟⠛⣿⡇⠀⠀⢸⣿⣿⣷⣤⣤⣤⣤⣶⣶⣿⠇⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀
	 *⢀⣿⠀⢀⣿⡇⠀⠀⠀⠻⢿⣿⣿⣿⣿⣿⠿⣿⡏⠀⠀⠀⠀⢴⣶⣶⣿⣿⣿⣆
	 *⢸⣿⠀⢸⣿⡇⠀⠀⠀⠀⠀⠈⠉⠁⠀⠀⠀⣿⡇⣀⣠⣴⣾⣮⣝⠿⠿⠿⣻⡟
	 *⢸⣿⠀⠘⣿⡇⠀⠀⠀⠀⠀⠀⠀⣠⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠉⠀
	 *⠸⣿⠀⠀⣿⡇⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠉⠀⠀⠀⠀
	 *⠀⠻⣷⣶⣿⣇⠀⠀⠀⢠⣼⣿⣿⣿⣿⣿⣿⣿⣛⣛⣻⠉⠁⠀⠀⠀⠀⠀⠀⠀
	 *⠀⠀⠀⠀⢸⣿⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀
	 *⠀⠀⠀⠀⢸⣿⣀⣀⣀⣼⡿⢿⣿⣿⣿⣿⣿⡿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀
	 *⠀⠀⠀⠀⠀⠙⠛⠛⠛⠋⠁⠀⠙⠻⠿⠟⠋⠑⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
	 */
	template<typename DataType>
	void CringeDeAllocMem(void* memAddress)
	{
		std::is_destructible<DataType> isDestructible;
		std::is_pod<DataType> isPod;
		size_t typeSize = sizeof(DataType);
		if (isPod.value == false && isDestructible.value == true)
		{
			memAddress.~DataType();
			for (int i = 0; i < maxArenaSize; i += (int)typeSize)
			{
				if (&memArena[i] == memAddress)
				{
					SetMemAtAddressToNull(memAddress, i);
					return;
				}
			}
		}
		else
		{
			for (int i = 0; i < maxArenaSize; i += (int)typeSize)
			{
				if (&memArena[i] == memAddress)
				{
					SetMemAtAddressToNull(memAddress, i);
					return;
				}
			}
		}

	}

	extern void ClearFrameMem();

	template<typename DataType>
	bool CheckIfSmartPointer()
	{
		std::is_base_of<std::shared_ptr<typename DataType::element_type>, DataType> shrdPtr;
		std::is_base_of<std::unique_ptr<typename DataType::element_type>, DataType> uniqPtr;
		if (shrdPtr.value || uniqPtr.value)
		{
			std::cout << "Fuck off" << std::endl;
			return true;
		}
		return false;
	}

}
