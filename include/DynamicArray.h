#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <memory_resource>
#include <iterator>
#include <memory>

template<typename T>
class DynamicArray {
private:
    std::pmr::polymorphic_allocator<T> allocator;
    T* data;
    size_t capacity;
    size_t size_;

public:
    class Iterator {
    private:
        T* ptr;
    
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        Iterator(T* p) : ptr(p) {}
        
        reference operator*() const { return *ptr; }
        pointer operator->() { return ptr; }
        
        Iterator& operator++() {
            ++ptr;
            return *this;
        }
        
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++ptr;
            return tmp;
        }
        
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };
    
    DynamicArray(std::pmr::memory_resource* mr = std::pmr::get_default_resource()) 
        : allocator(mr), data(nullptr), capacity(0), size_(0) {}
    
    ~DynamicArray() {
        clear();
        if (data) {
            allocator.deallocate(data, capacity);
        }
    }
    
    void push_back(const T& value) {
        if (size_ >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        new (&data[size_]) T(value);
        ++size_;
    }
    
    void pop_back() {
        if (size_ > 0) {
            data[size_ - 1].~T();
            --size_;
        }
    }
    
    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }
    
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    
    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            data[i].~T();
        }
        size_ = 0;
    }
    
    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size_); }
    
private:
    void resize(size_t new_capacity) {
        T* new_data = allocator.allocate(new_capacity);
        
        for (size_t i = 0; i < size_; ++i) {
            new (&new_data[i]) T(std::move(data[i]));
            data[i].~T();
        }
        
        if (data) {
            allocator.deallocate(data, capacity);
        }
        
        data = new_data;
        capacity = new_capacity;
    }
};

#endif