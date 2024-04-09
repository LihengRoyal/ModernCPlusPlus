/**
 * @file move_constructors.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for move constructors and move assignment operators.
 */

// Move constructors and move assignment operators are methods implemented
// inside of classes to effectively move resources from one object to the
// other, typically using std::move. These class methods take in another
// object of the same type, and move its resources to the instance
// where the method is called. In this file, we will explore implementing
// and using move constructors and move assignment operators.

// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes the utility header for std::move.
#include <utility>
// Includes the C++ string library.
#include <string>
// Includes the header for uint32_t.
#include <cstdint>
// Includes the header for std::vector. We'll cover vectors more in
// containers.cpp, but what suffices to know for now is that vectors are
// essentially dynamic arrays, and the type std::vector<std::string> is an array
// of strings. Mainly, vectors take up a non-negligible amount of memory, and
// are here to show the performance benefits of using std::move.
#include <vector>

//基本的人员（Person）类，其中实现了移动构造函数和移动赋值运算符，并且删除了复制
//构造函数和复制赋值运算符。这意味着一旦实例化了 Person 对象，就不能再进行复制。
//它必须从一个左值移动到另一个左值。没有复制运算符的类在必须只有一个定义的类实例
//时非常有用。例如，如果一个类管理一个动态分配的内存块，那么在没有适当处理的情况下，
//创建多个该类的实例可能会导致双重删除或内存泄漏。
class Person {
public:
  Person() : age_(0), nicknames_({}), valid_(true) {}

  //请记住，此构造函数接受一个 std::vector<std::string> 的右值。这使得构造函数更
  //高效，因为在构造 Person 对象时不会对 vefctor 实例进行深拷贝。
  Person(uint32_t age, std::vector<std::string> &&nicknames)
      : age_(age), nicknames_(std::move(nicknames)), valid_(true) {}

  //Person 类的移动构造函数。它接受一个类型为 Person 的右值，并将传入的右值的内容
  //移动到此 Person 对象实例中。请注意使用了 std::move。为了确保对象 person 中的
  //昵称被移动，而不是深拷贝，我们使用了 std::move。std::move 将左值 person.nicknames_ 
  //转换为右值，表示值本身。还请注意，我没有在 age_ 字段上调用 std::move。
  //因为它是一个整数类型，复制的成本太小。通常情况下，对于数值类型，复制它们是可以接受的，
  //但对于其他类型，例如字符串和对象类型，除非必要，否则应该移动类实例。
  Person(Person &&person)
      : age_(person.age_), nicknames_(std::move(person.nicknames_)),
        valid_(true) {
    std::cout << "Calling the move constructor for class Person.\n";
    // The moved object's validity tag is set to false.
    person.valid_ = false;
  }

  // Move assignment operator for class Person.
  Person &operator=(Person &&other) {
    std::cout << "Calling the move assignment operator for class Person.\n";
    age_ = other.age_;
    nicknames_ = std::move(other.nicknames_);
    valid_ = true;

    // The moved object's validity tag is set to false.
    other.valid_ = false;
    return *this;
  }

  // We delete the copy constructor and the copy assignment operator,
  // so this class cannot be copy-constructed.
  Person(const Person &) = delete;
  Person &operator=(const Person &) = delete;

  uint32_t GetAge() { return age_; }
  
  //这个返回类型中的 ampersand（&）表示我们返回了 nicknames_[i] 中字符串的
  //引用。这也意味着我们没有复制返回的字符串，而且在底层返回的内存地址实际上是
  //指向 nicknames_ 向量内存的地址。
  std::string &GetNicknameAtI(size_t i) { return nicknames_[i]; }

  void PrintValid() {
    if (valid_) {
      std::cout << "Object is valid." << std::endl;
    } else {
      std::cout << "Object is invalid." << std::endl;
    }
  }

private:
  uint32_t age_;
  std::vector<std::string> nicknames_;
  // Keeping track of whether an object's data is valid, i.e. whether
  // all of its data has been moved to another instance.
  bool valid_;
};

int main() {
  // Let's see how move constructors and move assignment operators can be
  // implemented and used in a class. First, we create an instance of the class
  // Person. Note that the object andy is a valid object.
  Person andy(15445, {"andy", "pavlo"});
  std::cout << "Printing andy's validity: ";
  andy.PrintValid();

  // To move the contents of the andy object to another object, we can use
  // std::move in a couple ways. This method calls the move assignment operator.
  Person andy1;
  andy1 = std::move(andy);

  // Note that andy1 is valid, while andy is not a valid object.
  std::cout << "Printing andy1's validity: ";
  andy1.PrintValid();
  std::cout << "Printing andy's validity: ";
  andy.PrintValid();

  // This method calls the move constructor. After this operation, the contents
  // of the original andy object have moved to andy1, then moved to andy2. The
  // andy and andy1 lvalues are effectively defunct (and should not be used,
  // unless they are re-initialized).
  Person andy2(std::move(andy1));

  // Note that andy2 is valid, while andy1 is not a valid object.
  std::cout << "Printing andy2's validity: ";
  andy2.PrintValid();
  std::cout << "Printing andy1's validity: ";
  andy1.PrintValid();

  // However, note that because the copy assignment operator is deleted, this code 
  // will not compile. The first line of this code constructs a new object via the
  // default constructor, and the second line invokes the copy assignment operator
  // to re-initialize andy3 with the deep-copied contents of andy2. Try uncommenting
  // these lines of code to see the resulting compiler errors.
  // Person andy3;
  // andy3 = andy2;

  // Because the copy constructor is deleted, this code will not compile. Try
  // uncommenting this code to see the resulting compiler errors.
  // Person andy4(andy2);

  return 0;
}
