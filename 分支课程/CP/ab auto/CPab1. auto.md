---
aliases:
  - 类型推导说明符
tags:
  - 分支
  - 知识类型/cpp
  - 受审状态/请求
前置知识-最低: 基本数据类型（int , char, double, bool ....）
前置知识-推荐: 基本数据类型，范围 for 循环，指针，模板，迭代器，STL 容器
---
# auto

## 1. auto 的基本概念

`auto` 是 C++ 中的**类型推导说明符（type specifier）**，它的作用是：**让编译器根据初始化表达式自动推导变量的类型**。

简单来说：**你告诉编译器“帮我猜类型”，编译器根据右操作数的值来“猜”**。

```cpp
auto x = 10;          // x 的类型是 int
auto y = 3.14;        // y 的类型是 double
auto z = "hello";     // z 的类型是 const char*
auto p = &x;          // p 的类型是 int*
```

`auto` 的**作用**：

| 作用          | 说明                         | 示例                                      |
| ----------- | -------------------------- | --------------------------------------- |
| **简化长类型**   | 避免写出冗长、重复的复杂类型名            | `auto it = vec.begin();`                |
| **保证类型一致性** | 自动匹配右侧表达式的精确类型，避免写错        | `auto len = vec.size();`（`size_t`）      |
| **存储匿名类型**  | Lambda 等匿名类型只能通过 `auto` 存储 | `auto func = [](int x){ return x*2; };` |

`auto` 的**使用场景**：

| 场景                  | 推荐    | 说明                                      |
| ------------------- | ----- | --------------------------------------- |
| **迭代器类型**           | ✅ 推荐  | `auto it = vec.begin();`                |
| **Lambda 表达式**      | ✅ 必须用 | `auto func = [](int x){ return x*2; };` |
| **模板中复杂类型**         | ✅ 推荐  | `auto result = SomeComplexFunction();`  |
| **类型很明显时**          | ✅ 推荐  | `auto count = 10;`（明显是 `int`）           |
| **需要精确控制类型**        | ❌ 不推荐 | 比如需要 `long long`，用 `auto` 可能推导为 `int`   |
| **`auto` 的推导不符合预期** | ❌ 不推荐 | 如需要 `const` 引用时用 `auto` 会丢掉 `const`     |

`auto` 在 C++98 时期就存在，但当时它只是一个“自动存储期”的占位符（几乎没人用）。C++11 赋予了它“类型推导”的新含义，从此成为 C++ 中最常用的关键字之一。

---

## 2. auto 的推导规则

### 2.1 `auto` 与 `const` / 引用

`auto` 会**丢弃** `const` 和引用，除非显式加上：

```cpp
const int x = 10;
const int& ref = x;
auto a = x;        // a 是 int（const 被丢弃）
auto b = ref;      // b 是 int（引用和 const 都被丢弃）
auto& c = ref;     // c 是 const int&（保留引用和 const）
const auto d = x;  // d 是 const int
```

### 2.2 `auto` 与数组

`auto` 推导数组时会退化为指针：

```cpp
int arr[] = {1, 2, 3};
auto p = arr;      // p 是 int*（数组退化为指针）
auto& ref = arr;   // ref 是 int(&)[3]（数组引用，保留大小信息）
```

### 2.3 `auto` 与 `{}` 初始化

`auto` 推导 `{}` 初始化时有一个特殊规则：

|写法|C++11 推导结果|C++17 推导结果|
|---|---|---|
|`auto a = {1};`|`std::initializer_list<int>`|`std::initializer_list<int>`|
|`auto a{1};`|`std::initializer_list<int>`|**`int`**（C++17 起）|
|`auto a{1, 2};`|`std::initializer_list<int>`|**编译报错**（C++17 起）|

---

## 3. auto 的使用场景

### 3.1 auto 在函数中的使用

#### 3.1.1 返回类型推导（C++14）

```cpp
auto Add(int a, int b) {
    return a + b;      // 推导返回类型为 int
}
auto GetValue() {
    return 3.14;       // 推导返回类型为 double
}
```

#### 3.1.2 尾置返回类型 Trailing Return Type

对于返回类型复杂的函数（比如返回一个迭代器），可以用尾置返回类型让代码更清晰：

```cpp
// 声明一个返回 std::vector<int>::iterator 的函数
auto FindValue(std::vector<int>& vec, int value) -> std::vector<int>::iterator {
    // ...
}
```

C++14 之后，如果返回类型可以从 `return` 语句推导，可以省略尾置类型：

```cpp
auto FindValue(std::vector<int>& vec, int value) {
    // ...
    return it; // 编译器推导返回类型为 std::vector<int>::iterator
}
```

#### 3.1.3 auto 作为参数类型（C++20）

C++20 允许在普通函数参数中使用 `auto`，这是一种简化的模板：

```cpp
// C++20，等价于 template<typename T> void Print(T value)
void Print(auto value) {
    std::cout << value;
}
```

这称为**缩写函数模板（abbreviated function template）**。

### 3.2 auto 与范围 for 循环

范围 for 循环是 `auto` 最经典的搭档：

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
// 只读遍历
for (auto x : v) {
    std::cout << x << " ";
}
// 修改元素
for (auto& x : v) {
    x *= 2;
}
// 只读且避免拷贝（性能优化）
for (const auto& x : v) {
    std::cout << x << " ";
}
```

### 3.3 auto 与函数指针

`auto` 可以自动推导函数指针的类型，让声明变得极其简单：

```cpp
void PrintMessage(int level, double value) {
    std::cout << "Level: " << level << ", Value: " << value << std::endl;
}

// 传统写法
void (*func1)(int, double) = PrintMessage;

// auto 写法（简洁）
auto func2 = PrintMessage;   // 自动推导为 void(*)(int, double)

// 调用方式完全一样
func2(3, 3.14);
```

### 3.4 auto 与成员函数指针

`auto` 可以自动推导成员函数指针的类型，彻底简化声明：

```cpp
class Calculator {
public:
    int Add(int a, int b) { return a + b; }
    int Multiply(int a, int b) { return a * b; }
};

// auto 自动推导
auto memFuncPtr = &Calculator::Add; // 类型：int (Calculator::*)(int, int)

// 调用时需要用 .* 或 ->*
Calculator calc;
int result = (calc.*memFuncPtr)(3, 5); // 调用 Calculator::Add(3, 5)
```