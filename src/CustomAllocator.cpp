#include "../include/CustomAllocator.h"
#include <iostream>
#include <cstdlib>

void* CustomMemoryResource::do_allocate(size_t bytes, size_t alignment) {
    void* ptr = std::malloc(bytes);
    if (!ptr) {
        throw std::bad_alloc();
    }
    
    allocated_blocks[ptr] = bytes;
    if (verbose) {
        std::cout << "Allocated " << bytes << " bytes at " << ptr << std::endl;
    }
    return ptr;
}

void CustomMemoryResource::do_deallocate(void* p, size_t bytes, size_t alignment) {
    auto it = allocated_blocks.find(p);
    if (it != allocated_blocks.end()) {
        if (verbose) {
            std::cout << "Deallocated " << it->second << " bytes from " << p << std::endl;
        }
        allocated_blocks.erase(it);
        std::free(p);
    }
}

bool CustomMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}

CustomMemoryResource::~CustomMemoryResource() {
    if (verbose) {
        std::cout << "CustomMemoryResource destructor: " << allocated_blocks.size() << " blocks remaining" << std::endl;
    }
    
    for (auto it = allocated_blocks.begin(); it != allocated_blocks.end(); ) {
        void* ptr = it->first;
        size_t size = it->second;
        if (verbose) {
            std::cout << "Cleaning up " << size << " bytes at " << ptr << std::endl;
        }
        std::free(ptr);
        it = allocated_blocks.erase(it);
    }
}

void CustomMemoryResource::print_allocated_blocks() const {
    std::cout << "Currently allocated blocks: " << allocated_blocks.size() << std::endl;
    for (const auto& pair : allocated_blocks) {
        std::cout << "  " << pair.first << ": " << pair.second << " bytes" << std::endl;
    }
}