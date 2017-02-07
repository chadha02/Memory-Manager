#include <assert.h>
#include "HeapManager.h"

#define ROUND_UP(addr,align) ((reinterpret_cast<uintptr_t>(addr) + (align - 1)) & ~(align-1))
#define ROUND_DOWN(addr,align) (reinterpret_cast<uintptr_t>(addr) & ~(align-1)

namespace Engine
{

	HeapManager::HeapManager(){};
	void HeapManager::Initialize(void *i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
	{
		assert(i_pMemory);
		assert(i_sizeMemory);
		assert(i_numDescriptors * sizeof(MemBlockDesc) < i_sizeMemory);

		MemBlockDesc * pMemBlocks = reinterpret_cast<MemBlockDesc *>(i_pMemory);

		InitializeFreeDescriptors(pMemBlocks, i_numDescriptors);
		m_pFreeMemory = GetFreeDescriptor();

		m_pFreeMemory->m_pNext = NULL;
		m_pFreeMemory->m_pBase = static_cast<uint8_t*>(i_pMemory) + i_numDescriptors * sizeof(MemBlockDesc);
		m_pFreeMemory->m_size = i_sizeMemory;
			
		m_pAllocatedMemory = NULL; // No memeory has been allocated yet

	}

	void HeapManager::InitializeFreeDescriptors(MemBlockDesc *i_pFirstDiscriptor, unsigned int i_numDecriptors)
	{
		m_pFreeDiscriptors = i_pFirstDiscriptor; // first descriptor

		MemBlockDesc * desc = i_pFirstDiscriptor;
		assert(i_numDecriptors != 0);
		while (i_numDecriptors-1 )
		{
			desc->m_pNext = desc + 1;
			desc = desc->m_pNext;
			i_numDecriptors--;
		}
		desc->m_pNext = NULL;
	}

	HeapManager::MemBlockDesc * HeapManager::GetFreeDescriptor()
	{
		MemBlockDesc * freeDesc = m_pFreeDiscriptors;
		if (freeDesc)
		{
			m_pFreeDiscriptors = freeDesc->m_pNext;
		}
		return freeDesc;
	}

	void * HeapManager::Allocate(const size_t i_sizeAlloc)
	{
		MemBlockDesc * freeMemoryDesc = FindBestFreeMemoryDescriptor(i_sizeAlloc); // find a discriptor suitable for this size first
		MemBlockDesc * desc = NULL;
		if (freeMemoryDesc)
			desc = AllocateFromBlockEnd(freeMemoryDesc, i_sizeAlloc);
		return desc ? reinterpret_cast<void *>(desc->m_pBase) : desc;  // return the base pointed by this discriptor else return null
	}

	HeapManager::MemBlockDesc * HeapManager::FindBestFreeMemoryDescriptor(const size_t i_size)
	{
		MemBlockDesc * desc = m_pFreeMemory;
		while (desc && desc->m_size < i_size) 
			desc = desc->m_pNext;
		return desc;
	}

	HeapManager::MemBlockDesc * HeapManager::AllocateFromBlockEnd(MemBlockDesc * i_Block, size_t i_size)
	{
		uint8_t * pNewBlockStart = i_Block->m_pBase + i_Block->m_size - i_size; 
		assert(pNewBlockStart >= i_Block->m_pBase);

		if (pNewBlockStart < i_Block->m_pBase)
			return NULL;

		MemBlockDesc * pDesc = GetFreeDescriptor();
		//assert(pDesc);

		if (!pDesc)
			return NULL;

		pDesc->m_size = i_Block->m_pBase + i_Block->m_size - pNewBlockStart;
		pDesc->m_pBase = pNewBlockStart;	// /confusion
		pDesc->m_pNext = NULL;

		i_Block->m_size = pNewBlockStart - i_Block->m_pBase;
			
		AddToAllocatedDescriptors(pDesc); //Adding pDesc to AllocatedMemory List
		assert(m_pAllocatedMemory);
		return pDesc;
	}

	

	bool HeapManager::Free(void * i_pMemory)
	{
		//Finding the i_pMemory in Allocated list and get the corresponding descriptor
		MemBlockDesc * desc = m_pAllocatedMemory;
		assert(m_pAllocatedMemory);
		MemBlockDesc * prevDesc = NULL;
		while (desc) {
			if (desc->m_pBase == i_pMemory)
			{
				break;
			}
			else
			{
				prevDesc = desc;
				desc = desc->m_pNext;
			}
		}

		assert(desc); //Cannot Find the descriptor

		//Move that descriptor to the free memory descriptors list
		if (prevDesc)
		{
			prevDesc->m_pNext = desc->m_pNext;
		}
		else
		{
			m_pAllocatedMemory = desc->m_pNext;		// in case you found the desc at first position
		}
		//Remove contents inside the memory but before that how can i call the deconstructor of that object?
		AddToFreeMemoryDescriptors(desc);
		return desc != NULL;
	}

	void HeapManager::AddToAllocatedDescriptors(MemBlockDesc * i_pAllocatedDesc)
	{
		i_pAllocatedDesc->m_pNext = m_pAllocatedMemory;
		m_pAllocatedMemory = i_pAllocatedDesc;
	}

	void HeapManager::AddToFreeMemoryDescriptors(MemBlockDesc * i_pFreeMemDesc)
	{
		i_pFreeMemDesc->m_pNext = m_pFreeMemory;  // get the freed discriptor to the initial memmory 
		m_pFreeMemory = i_pFreeMemDesc;  // initial memeory now points to this discriptor
	}

	void HeapManager::GarbageCollect()
	{
		MemBlockDesc* tempNode = m_pFreeMemory;
		if (m_pFreeMemory == nullptr)
			return;
		int i = 0;
		while (tempNode != nullptr && tempNode->m_pNext != nullptr)
		{
			MemBlockDesc* nextNode = tempNode->m_pNext;
			if (tempNode->m_pBase &&  nextNode->m_pBase)
			{
				if (tempNode->m_pBase + tempNode->m_size == nextNode->m_pBase)
				{
					tempNode->m_size = tempNode->m_size + nextNode->m_size;
					tempNode->m_pNext = nextNode->m_pNext;
					nextNode->m_size = 0;
					nextNode->m_pBase = nullptr;
					nextNode->m_pBase = nullptr;
					AddToFreeMemoryDescriptors(nextNode);
				}
				else
				{
					tempNode = tempNode->m_pNext;
				}
			}	
		}
	}

	size_t HeapManager::getAvailableMem()
	{
		size_t availableMem = 0;

		for (MemBlockDesc* node = m_pFreeMemory; node; node = node->m_pNext)
		{
			availableMem += node->m_size;
		}

		return availableMem;
	}
}