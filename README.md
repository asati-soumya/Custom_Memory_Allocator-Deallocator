# Custom_Memory_Allocator-Deallocator
A simple implementation of a custom memory allocator in C++ using a fixed-size heap and a free-list based allocation strategy.

# Features
Fixed-size heap memory management
Dynamic allocation using myAllocate()
Manual deallocation using deallocate()
Block splitting for efficient memory usage
Adjacent free block merging (coalescing)
Heap visualization using printHeap()

# Overview
This project demonstrates how low-level memory allocation works internally, similar to how malloc() and free() operate in operating systems and runtime libraries.

# The allocator:
Maintains a contiguous heap buffer
Tracks memory blocks using metadata headers
Splits larger blocks during allocation
Merges adjacent free blocks during deallocation

# Memory Layout
Each memory block contains metadata:

struct block {
    size_t size;
    bool isfree;
    block* next;
};
Block Fields

Field	Description
size	Size of usable memory
isfree	Indicates whether block is free
next	Pointer to next block
Heap Initialization

The allocator uses a fixed-size heap:

char heap[1024];

Initially, the entire heap is one large free block.

# Allocation Strategy
myAllocate(size_t size)

Steps:
Traverse free list
Find first suitable free block
Split block if large enough
Mark block as allocated
Return pointer to usable memory
Block Splitting

If the selected block is larger than required:

Before:
+---------------------------+
| Free Block (Large)       |
+---------------------------+

After:
+-------------+-------------+
| Allocated   | Free Block  |
+-------------+-------------+

# Deallocation Strategy
deallocate(void* ptr)

Steps:
Retrieve block metadata
Mark block as free
Merge adjacent free blocks
Free Block Coalescing

Adjacent free blocks are merged to reduce fragmentation.

Before:
+---------+---------+
| Free    | Free    |
+---------+---------+

After:
+-------------------+
| Combined Free     |
+-------------------+

# Example Usage
int main() {
    MemoryAllocator alloc;

    void* p1 = alloc.myAllocate(128);
    void* p2 = alloc.myAllocate(256);

    alloc.printHeap();

    alloc.deallocate(p1);

    alloc.printHeap();

    return 0;
}

# Sample Output
Heap Layout:
Size: 128 Free: 0
Size: 256 Free: 0
Size: 568 Free: 1

# Important Concepts Demonstrated
Pointer arithmetic
Manual memory management
Heap fragmentation
Free list management
Memory coalescing
Internal allocator design
