#include <iostream>
#include <bits/stdc++.h>
#define HEAP_SIZE 1024
using namespace std;

class MemoryAllocator{
private:
    struct block{
      size_t size;
      bool isfree;
      block *next;
    };
    char heap[HEAP_SIZE];
    block *freelist;
public:
    MemoryAllocator(){
        freelist = (block*)heap;
        freelist->size = HEAP_SIZE-sizeof(block);
        freelist->isfree=true;
        freelist->next=NULL;
    }
    
    void splitblock(block *curr, size_t size){
        block *newBlock = (block*)((char*)(curr) + sizeof(block) + size);
    
        newBlock->size = curr->size - size - sizeof(block);
        newBlock->isfree = true;
        newBlock->next = curr->next;
    
        curr->size = size;
        curr->isfree = false;
        curr->next = newBlock;
    }
    
    void* myAllocate(size_t size){
        block *curr=freelist;
        while(curr){
            if(curr->isfree && curr->size >= size){
                if(curr->size > size+sizeof(block)){
                    splitblock(curr,size);
                }
                else{
                    curr->isfree=false;
                }
                return (void*)(curr+1);
            }
            curr=curr->next;
        }
        return NULL;
    }
    
    void mergefreeblocks(){
        block *curr=freelist;
        while(curr && curr->next){
            if(curr->isfree && curr->next->isfree){
                curr->size += curr->next->size + sizeof(block);
                curr->next=curr->next->next;
            }
            else
                curr=curr->next;
        }
    }
    
    void deallocate(void *ptr){
        if(!ptr) return;
        block *curr = (block*)(ptr) - 1;
        curr->isfree = true;
        mergefreeblocks();
    }
    
    void printHeap() {
        block* curr = freelist;
        std::cout<< sizeof(block);
        std::cout << "\nHeap Layout:\n";

        while (curr) {
            std::cout
                << "Size: " << curr->size
                << " Free: " << curr->isfree
                << "\n";

            curr = curr->next;
        }
    }
};

int main() {
    MemoryAllocator alloc;
    void *p1 = alloc.myAllocate(128);
    alloc.printHeap();
    void *p2 = alloc.myAllocate(256);
    alloc.printHeap();
    alloc.deallocate(p1);
    alloc.printHeap();
    return 0;
}
