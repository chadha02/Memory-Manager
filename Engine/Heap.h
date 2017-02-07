#ifndef HEAP_H_ 
#define HEAP_H_ 

namespace Engine
{

	struct AllocHeader;
	class Heap
	{
	public:
		 Heap* createHeap( void * pMem, size_t size);
		 void* allocate(const size_t  size);
		void deleteHeap();
		void deallocate(const size_t  size);
		Heap();
	private:
		void * startPositionInHeap;
		void * currentPostionInHeap;
		size_t maxSizeofHeap;
		size_t currentSizeOfHeap;
		 Heap* heap;
		AllocHeader * m_pHeadAlloc;
		
	};
}

#endif