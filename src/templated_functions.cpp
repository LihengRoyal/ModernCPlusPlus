/**
 * @file templated_functions.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for templated functions.
 */

// Includes std::cout (printing) for demo purposes.
#include <iostream>

//模板是 C++ 中的一种语言特性，允许你编写可以处理多种数据类型的代码，而无需实际指
//定这些类型。在 C++ 中，你可以创建模板函数和模板类。

//这是一个基本的模板函数，用于相加两个数字。语法说明：你会看到代码中既有 
//template<class T>，也有 template<typename T>。虽然这两个语句是等价的，
//但是 class 和 typename 关键字之间有一些区别。这篇博文涵盖了这种区别，
//但是对于这个课程来说你不需要了解这些：
template <typename T> T add(T a, T b) { return a + b; }

// It is possible to pass multiple type names via templates into functions.
// This function will print both of these values out.
template<typename T, typename U>
void print_two_values(T a, U b) {
  std::cout << a << " and " << b << std::endl;
}

// It is also possible to create specialized templated functions, that do
// different things for different types. Take the following contrived example,
// which prints the type if its a float type, but just prints hello world for
// all other types.
template <typename T> void print_msg() { std::cout << "Hello world!\n"; }

// Specialized templated function, specialized on the float type.
template <> void print_msg<float>() {
  std::cout << "print_msg called with float type!\n";
}

//最后，模板参数不一定非要是类。看这个基本的（虽然很牵强附会的）函数，它将一个布尔值
//作为模板参数，并根据布尔值参数执行不同的操作。
template <bool T> int add3(int a) {
  if (T) {
    return a + 3;
  }

  return a;
}

int main() {
  // First, let's see the add function called on both ints and floats.
  std::cout << "Printing add<int>(3, 5): " << add<int>(3, 5) << std::endl;
  std::cout << "Printing add<float>(2.8, 3.7): " << add<float>(2.8, 3.7)
            << std::endl;

  // It is also possible for a templated function to interpret the type of its
  // arguments, although if you're a beginner in modern C++, it's preferred you
  // don't do this because then you might not be sure of the types being passed
  // into your functions.
  std::cout << "Printing add(3, 5): " << add(3, 5) << std::endl;

  // Second, let's see the print_two_values function being called with two
  // different types.
  std::cout << "Printing print_two_values<int, float>(3, 3.2): ";
  print_two_values<int, float>(3, 3.2);

  // Let's see what happens when we called print_msg with and without the float
  // type being passed in. As expected, the first call to print_msg prints out
  // the general output, while the second one, with the float argument,
  // recognizes its type parameter and calls the specialized function.
  std::cout << "Calling print_msg<int>(): ";
  print_msg<int>();
  std::cout << "Calling print_msg<float>(): ";
  print_msg<float>();

  // add3 has the specified behavior for both a true and false templated
  // argument, as we can see here.
  std::cout << "Printing add3<true>(3): " << add3<true>(3) << std::endl;
  std::cout << "Printing add3<false>(3): " << add3<false>(3) << std::endl;
  
  //最后，重要的是要注意，大多数这些都是虚构的例子，而且可能可以编写一些这样的函数（例如，
  //将布尔值作为参数传递而不是模板参数）而不使用模板。然而，在这门课程中，你会在代码库中
  //看到类似这样的代码，所以理解这些上下文中的模板函数是很有好处的！

  return 0;
}