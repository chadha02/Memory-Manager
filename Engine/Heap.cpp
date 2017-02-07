#include "heap.h"   
#include <assert.h> 
#include "Assert\ConsolePrint.h"  
#include <stddef.h>

namespace Engine
{
	//Heap* Heap::heap;
	struct AllocHeader {
		
		int           nSize;
		void *        actualpos;
		AllocHeader * pNext;
		AllocHeader * pPrev;
		
	};

	Heap* Heap::createHeap( void * pMem, size_t size)
	{
		m_pHeadAlloc = NULL;
		if (heap == NULL)
		{
			heap = new Heap();
		}
		heap->startPositionInHeap = pMem;
		heap->currentPostionInHeap = pMem;
		heap->currentSizeOfHeap = size;

		return heap;

	}

	void Heap::deleteHeap()
	{
		delete startPositionInHeap;
		delete heap;
	}
	Heap::Heap()
	{
	}
	void* Heap::allocate(const size_t  size)
	{
		
		if (currentSizeOfHeap < size)
		{
			return NULL;
		}
		void* positionInHeap = currentPostionInHeap;
		currentPostionInHeap = (char*)currentPostionInHeap + size + sizeof(AllocHeader);
		currentSizeOfHeap -= size;
		AllocHeader * a = new AllocHeader;
		a->nSize = size;
		
		a->actualpos = (char *)startPositionInHeap + sizeof(AllocHeader);
		startPositionInHeap = currentPostionInHeap;
		if (m_pHeadAlloc == NULL)
		{
			a->pNext = NULL;
			a->pPrev = NULL;
		}
		else
		{
			a->pNext = m_pHeadAlloc;
			m_pHeadAlloc->pPrev = a;
		}
		m_pHeadAlloc = a;
		return positionInHeap;
	}

	void Heap::deallocate(const size_t  size)
	{
		int i=0;
		while (m_pHeadAlloc != NULL)
		{
			AllocHeader *temp = m_pHeadAlloc;
			m_pHeadAlloc = m_pHeadAlloc->pNext;
			//temp->actualpos = NULL; 
			temp->actualpos = (char*)currentPostionInHeap - size - sizeof(AllocHeader);
			delete temp;
			i++; //DEBUG_PRINT("loop ran %d times", i);
			
		}
		DEBUG_PRINT("Made a deallocation of size %d",size);
	}


}