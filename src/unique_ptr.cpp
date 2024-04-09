/**
 * @file unique_ptr.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for usage of a unique pointer.
 */

//智能指针是一种用于内存管理（有时也用于其他功能）的数据结构，在不具备内存管理功能
//的语言中使用（例如 C++）。具有垃圾回收功能的语言，如 Java 或 Python，是内置了
//内存管理功能的示例。现代 C++ 标准库中的两种智能指针（也是你在课程中将要使用的）
//是 std::unique_ptr 和 std::shared_ptr。std::unique_ptr 和 std::shared_ptr 
//都会自动处理内存分配和释放，并在内部包含原始指针。换句话说，它们是对原始指针的包装类。
//在本文件中，我们将讨论 std::unique_ptr。std::unique_ptr 是一种智能指针，它保留对象
//的唯一所有权。这意味着没有两个 std::unique_ptr 实例可以管理同一个对象。

// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes std::unique_ptr functionality.
#include <memory>
// String library for printing help for demo purposes.
#include <string>
// Including the utility header for std::move.
#include <utility>

// Basic point class. (Will use later)
class Point {
public:
  Point() : x_(0), y_(0) {}
  Point(int x, int y) : x_(x), y_(y) {}
  inline int GetX() { return x_; }
  inline int GetY() { return y_; }
  inline void SetX(int x) { x_ = x; }
  inline void SetY(int y) { y_ = y; }

private:
  int x_;
  int y_;
};

// Function that takes in a unique pointer reference and changes its x value to
// 445.
void SetXTo445(std::unique_ptr<Point> &ptr) { ptr->SetX(445); }

int main() {
  // This is how to initialize an empty unique pointer of type
  // std::unique_ptr<Point>.
  std::unique_ptr<Point> u1;
  // This is how to initialize a unique pointer with the default constructor.
  std::unique_ptr<Point> u2 = std::make_unique<Point>();
  // This is how to initialize a unique pointer with a custom constructor.
  std::unique_ptr<Point> u3 = std::make_unique<Point>(2, 3);

  // Here, for std::unique_ptr instance u, we use the statement (u ? "not empty"
  // : "empty") to determine if the pointer u contains managed data. The main
  // gist of this is that the std::unique_ptr class has a conversion function on
  // its objects to a boolean type, and so this function is called whenever we
  // treat the std::unique_ptr as a boolean. For instance, this can be used in
  // the following example.
  if (u1) {
    // This won't print because u1 is empty.
    std::cout << "u1's value of x is " << u1->GetX() << std::endl;
  }

  if (u2) {
    // This will print because u2 is not empty, and contains a managed Point
    // instance.
    std::cout << "u2's value of x is " << u2->GetX() << std::endl;
  }

  // Note that u1 is empty and u2 and u3 are not empty, since they were
  // initialized with a Point instance.
  std::cout << "Pointer u1 is " << (u1 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer u2 is " << (u2 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer u3 is " << (u3 ? "not empty" : "empty") << std::endl;

  // Since instances of std::unique_ptr can have only one owner, it has no copy
  // constructor. Therefore, this code won't compile. Uncomment it to try!
  // std::unique_ptr<Point> u4 = u3;

  // However, it's possible to transfer ownership of unique pointers via
  // std::move.
  std::unique_ptr<Point> u4 = std::move(u3);

  // Note that because u3 is an lvalue, it no longer contains any managed
  // object. It is an empty unique pointer. Let's retest for emptyness.
  std::cout << "Pointer u3 is " << (u3 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer u4 is " << (u4 ? "not empty" : "empty") << std::endl;
  
  //最后，让我们讨论一下如何将 std::unique_ptr 实例作为参数传递给函数。主要来说，
  //你应该将它作为引用传递，这样所有权就不会改变。你可以在函数 SetXTo445 中看到
  //这个示例（在文件中的第 41 行）。
  SetXTo445(u4);

  // Now, let's print the x value of u4 to confirm that the change occured, but
  // the ownership of the Point instance has been retained to u4.
  std::cout << "Pointer u4's x value is " << u4->GetX() << std::endl;

  return 0;
}