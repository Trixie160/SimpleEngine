#include "MemAlloc.h"
#include <new>
#define FRAME_PARTION_SIZE_MOD 0.3f

namespace MemAllocator
{
	char* memArena = nullptr;
	int64_t maxArenaSize;
	int currentIndex = 0;
	bool memInitialized = false;

	int frameMinPartition = 0;
	int currentFrameIndex = 0;
	int frameMaxPartition = 0;

	ReturnRes InitializeMem(int byteSize)
	{
		if (memArena != nullptr)
		{
			std::cout << "Mem already allocated" << std::endl;

			return ReturnRes::e_NO;
		}
		memArena = (char*)malloc(byteSize * sizeof(char));
		maxArenaSize += byteSize;
		memInitialized = true;

#pragma region PartioningFrameSize
		frameMinPartition = (int)maxArenaSize - (int)(maxArenaSize * FRAME_PARTION_SIZE_MOD);
		currentFrameIndex = frameMaxPartition;
		frameMaxPartition = (int)maxArenaSize;
#pragma endregion

		return ReturnRes::e_OK;
	}

	int GetMemLeft()
	{
		int res = int(maxArenaSize - currentIndex);
		return (res = (res < 0) ? NULL : (res));
	}

	int GetFrameMemLeft()
	{
		int res = frameMaxPartition - currentFrameIndex;
		return (res = (res < 0) ? NULL : (res));
	}

	ReturnRes DeAllocFrameMem(void* memAddress, size_t memSize)
	{
		for (int i = frameMinPartition; i < frameMaxPartition; i += (int)memSize)
		{
			if (&memArena[i] == memAddress)
			{
				SetMemAtAddressToNull(memAddress, i);
				return ReturnRes::e_OK;
			}
		}

		return ReturnRes::e_NO;
	}

	ReturnRes DeAllocMem(void* memAddress, size_t memSize)
	{
		for (int i = 0; i < maxArenaSize; i += (int)memSize)
		{
			if (&memArena[i] == memAddress)
			{
				SetMemAtAddressToNull(memAddress, i);
				return ReturnRes::e_OK;
			}
		}

		return ReturnRes::e_NO;

	}

	void ClearFrameMem()
	{
		memset(&memArena[frameMinPartition], '\0', sizeof(char) * frameMaxPartition);
		currentFrameIndex = frameMinPartition;
	}
}

void MemAllocator::SetMemAtAddressToNull(void*& memAddress, int pos)
{
	memArena[pos] = NULL;
	memAddress = nullptr;
}

#undef FRAME_PARTION_SIZE_MOD