#ifndef CUSTOM_ALLOCATOR_H
#define CUSTOM_ALLOCATOR_H

#include <memory_resource>
#include <map>
#include <memory>

class CustomMemoryResource : public std::pmr::memory_resource {
private:
    std::map<void*, size_t> allocated_blocks;
    bool verbose;
    
protected:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* p, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

public:
    CustomMemoryResource(bool verbose = true) : verbose(verbose) {}
    ~CustomMemoryResource();
    
    size_t get_allocated_count() const { return allocated_blocks.size(); }
    void print_allocated_blocks() const;
};

#endif