#ifndef HEAPMANAGER_H_ 
#define HEAPMANAGER_H_
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

namespace Engine
{
	class HeapManager
	{
	public:
		void Initialize(void *i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors);

		void * Allocate(const size_t);
		void GarbageCollect();
		bool Free(void *);
		size_t getAvailableMem();
		HeapManager();
		
	private:
		
		typedef struct MemBlockDescriptor
		{
			size_t m_size;
			uint8_t* m_pBase;
			struct MemBlockDescriptor* m_pNext;
		} MemBlockDesc;
		
		MemBlockDesc * m_pFreeDiscriptors;
		MemBlockDesc * m_pFreeMemory;
		MemBlockDesc * m_pAllocatedMemory;

		void InitializeFreeDescriptors(MemBlockDesc *i_pFirstDiscriptor, unsigned int i_numDecriptors);
		
		MemBlockDesc * GetFreeDescriptor();
		MemBlockDesc * AllocateFromBlockEnd(MemBlockDesc * i_Block, size_t size);	
		
		MemBlockDesc * FindBestFreeMemoryDescriptor(size_t);
		
		void AddToFreeMemoryDescriptors(MemBlockDesc *);
		void AddToAllocatedDescriptors(MemBlockDesc *);		
	
	};
}
#endif