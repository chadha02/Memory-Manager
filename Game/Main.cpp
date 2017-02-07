
#include <iostream>
#include <conio.h>
#include<vector>
#include <assert.h>
#include <ctime> 
#include "Assert\ConsolePrint.h"
#include "HeapManager.h"
#include "Assert\Assert.h"

using namespace std;
using namespace Engine;

void testallocate()
{
	const size_t sizeHeap = 1024 * 1024;
	void * pHeapMemory = malloc(sizeHeap);
	assert(pHeapMemory);
	HeapManager  *ppHeap = new HeapManager();
	ppHeap->Initialize(pHeapMemory, sizeHeap, 1024);

	assert(ppHeap);
	unsigned int totalAllocations = 0;
	long sizeAllocations = 0;
	void * pMemory = 0;

	do
	{

		size_t sizeAlloc = static_cast<size_t>(rand());
		pMemory = ppHeap->Allocate(rand());
		if (pMemory)
		{
			sizeAllocations += sizeAlloc;
			totalAllocations++;
		}
	} while (pMemory != NULL);

	DEBUG_PRINT("Made %d allocations totaling %d from heap of %d deleting the block now", totalAllocations, sizeAllocations, sizeHeap);

}

void testfree()
{
	const size_t sizeHeap = 1024 * 1024;
	int totalAllocations = 0;
	size_t sizeAllocations = 0;
	std::vector<void*> allocatedMemList;

	DEBUG_PRINT("Made %d allocations totaling %d from heap of size %u\n", totalAllocations, sizeAllocations, sizeHeap);
	HeapManager *heap = new HeapManager();
	void * pHeapMemory = malloc(sizeHeap);
	heap->Initialize(pHeapMemory, sizeHeap, 10000);
	
	void * pMemory = 0;

	// allocating the memory
	do
	{
		size_t sizeAlloc = static_cast<size_t>(rand());
		DEBUG_PRINT("Requesting %ld memory\n", (long)sizeAlloc);
		pMemory = heap->Allocate(sizeAlloc);

		if (pMemory)
		{
			sizeAllocations += sizeAlloc;
			totalAllocations++;
			allocatedMemList.push_back(pMemory);
		}

	} while (pMemory != NULL);
	DEBUG_PRINT("Made %d allocations totaling %d from heap of size %u\n", totalAllocations, sizeAllocations, sizeHeap);

	// deallocating the memory
	for (std::vector<void*>::iterator itr = allocatedMemList.begin(); itr != allocatedMemList.end(); itr++)
	{
		heap->Free(*itr);
	}
	DEBUG_PRINT("Deallocated %d allocations.\n", totalAllocations);

	DEBUG_PRINT("MemoryAllocator Unit Test Sucessfull !!!\n");


}
bool GarbageCollector_UnitTest()
{

	const size_t sizeHeap = 1024 * 1024;
	int totalAllocations = 0;
	size_t sizeAllocations = 0;
	std::vector<void*> allocatedMemList;
	void * pHeapMemory = malloc(sizeHeap);
	HeapManager  *ppHeap = new HeapManager();
	ppHeap->Initialize(pHeapMemory,sizeHeap, 100);
	void * pMemory = 0;

	// allocating the memory
	do
	{
		size_t sizeAlloc = static_cast<size_t>(rand());
		std::cout << "Requesting " << sizeAlloc << " Bytes\n";
		pMemory = ppHeap->Allocate(sizeAlloc);

		if (pMemory)
		{
			sizeAllocations += sizeAlloc;
			totalAllocations++;
			allocatedMemList.push_back(pMemory);
		}

	} while (pMemory != NULL);
	std::cout << "Made " << totalAllocations << " allocations totaling " << sizeAllocations << " from heap of size " << sizeHeap << std::endl;

	// deallocating the memory
	for (std::vector<void*>::iterator itr = allocatedMemList.begin(); itr != allocatedMemList.end(); itr++)
	{
		ppHeap->Free(*itr);
	}
	std::cout << "Deallocated " << totalAllocations << " allocations.\n";

	ppHeap->GarbageCollect();
	std::cout << "Memeory returned" << ppHeap->getAvailableMem() << "\n";
	std::cout << "heap size" << sizeHeap << "\n";
	if (ppHeap->getAvailableMem() == sizeHeap)
	{
		std::cout << "Garbage collection succeded.\n";
		return true;
	}
	else
	{
		std::cout << "Garbage collection failed.\n";
		return false;
	}
}


void main(int argc, char *argv)
{
	if (GarbageCollector_UnitTest())
	{
		std::cout << "Passed GarbageCollector Unit Test !" << std::endl;
	}
	//testallocate();
	//testfree();
	_getch();
	
}



