#include <gtest/gtest.h>
#include "../include/CustomAllocator.h"
#include "../include/DynamicArray.h"

TEST(CustomAllocatorTest, BasicAllocation) {
    CustomMemoryResource mr(false);
    
    void* ptr1 = mr.allocate(100);
    void* ptr2 = mr.allocate(200);
    
    EXPECT_EQ(mr.get_allocated_count(), 2);
    
    mr.deallocate(ptr1, 100);
    EXPECT_EQ(mr.get_allocated_count(), 1);
    
    mr.deallocate(ptr2, 200);
    EXPECT_EQ(mr.get_allocated_count(), 0);
}

TEST(CustomAllocatorTest, MemoryReuse) {
    CustomMemoryResource mr(false);
    
    void* ptr1 = mr.allocate(50);
    mr.deallocate(ptr1, 50);
    
    void* ptr2 = mr.allocate(50);
    mr.deallocate(ptr2, 50);
    
    EXPECT_EQ(mr.get_allocated_count(), 0);
}

TEST(DynamicArrayTest, ComplexTypeWithCustomAllocator) {
    CustomMemoryResource mr(false);
    
    struct TestStruct {
        int a, b, c;
        TestStruct(int a, int b, int c) : a(a), b(b), c(c) {}
    };
    
    DynamicArray<TestStruct> arr(&mr);
    
    arr.push_back(TestStruct(1, 2, 3));
    arr.push_back(TestStruct(4, 5, 6));
    arr.push_back(TestStruct(7, 8, 9));
    
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0].a, 1);
    EXPECT_EQ(arr[1].b, 5);
    EXPECT_EQ(arr[2].c, 9);
    
    int sum = 0;
    for (const auto& item : arr) {
        sum += item.a + item.b + item.c;
    }
    EXPECT_EQ(sum, 45);
}

TEST(DynamicArrayTest, BasicOperations) {
    DynamicArray<int> arr;
    
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.size(), 0);
    
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    EXPECT_FALSE(arr.empty());
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    
    arr.pop_back();
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[1], 2);
}

TEST(DynamicArrayTest, IteratorOperations) {
    DynamicArray<int> arr;
    
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    
    auto it = arr.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    it++;
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(it, arr.end());
    
    int sum = 0;
    for (const auto& val : arr) {
        sum += val;
    }
    EXPECT_EQ(sum, 60);
}

TEST(DynamicArrayTest, ResizeOperation) {
    DynamicArray<int> arr;
    
    for (int i = 0; i < 10; ++i) {
        arr.push_back(i * 10);
    }
    
    EXPECT_EQ(arr.size(), 10);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[5], 50);
    EXPECT_EQ(arr[9], 90);
}

TEST(DynamicArrayTest, ClearOperation) {
    DynamicArray<int> arr;
    
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    EXPECT_EQ(arr.size(), 3);
    
    arr.clear();
    EXPECT_EQ(arr.size(), 0);
    EXPECT_TRUE(arr.empty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}