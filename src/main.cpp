#include <iostream>
#include "../include/CustomAllocator.h"
#include "../include/DynamicArray.h"

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

int main() {
    CustomMemoryResource custom_mr;
    
    DynamicArray<int> int_array(&custom_mr);
    
    std::cout << "=== Testing with int ===" << std::endl;
    
    for (int i = 0; i < 5; ++i) {
        int_array.push_back(i * 10);
    }
    
    std::cout << "Int array: ";
    for (auto it = int_array.begin(); it != int_array.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Range-based for: ";
    for (const auto& val : int_array) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\n=== Testing with Point ===" << std::endl;
    
    DynamicArray<Point> point_array(&custom_mr);
    
    point_array.push_back(Point(1, 2));
    point_array.push_back(Point(3, 4));
    point_array.push_back(Point(5, 6));
    
    std::cout << "Point array: ";
    for (const auto& point : point_array) {
        std::cout << point << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\n=== Memory information ===" << std::endl;
    custom_mr.print_allocated_blocks();
    
    std::cout << "\n=== Cleaning up ===" << std::endl;
    
    return 0;
}