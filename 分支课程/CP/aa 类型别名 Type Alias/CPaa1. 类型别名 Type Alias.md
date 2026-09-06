---
aliases:
  - using
  - typedef
tags:
  - 分支
  - 受审状态/请求
  - 知识类型/cpp
前置知识-最低: 基本数据类型（int , char, double, bool ....）
前置知识-推荐: 基本数据类型，指针，函数指针，模板，STL 容器
---
# 类型别名 Type Alias

## 1. 类型别名的基本概念

**类型别名**就是给已有的类型**起一个“外号”**。它不会创建新的类型，只是让一个已有的类型多一个名字，用来提高代码的可读性和可维护性。

例如：

```cpp
// 给 int 类型起个别名 MyInt
using MyInt = int;

// 现在 MyInt 和 int 完全等价
MyInt a = 10;      // 等价于 int a = 10;
int b = 20;        // MyInt 和 int 可以混用
a = b;             // 完全兼容
```

C++ 中有两种方式定义类型别名：

| 语法                | 示例                   | 引入版本  |
| ----------------- | -------------------- | ----- |
| `typedef`（C 语言遗留） | `typedef int MyInt;` | C++98 |
| `using`（现代 C++）   | `using MyInt = int;` | C++11 |

| 对比维度     | `typedef`                  | `using`                   |
| -------- | -------------------------- | ------------------------- |
| 语法直观性    | ❌ 较晦涩（`typedef int MyInt`） | ✅ 直观（`using MyInt = int`） |
| 函数指针可读性  | ❌ 容易看晕                     | ✅ 更清晰                     |
| **模板别名** | ❌ **不支持**                  | ✅ **支持**                  |
| 可读性      | 一般                         | 更好                        |
| 引入版本     | C++98                      | C++11                     |

> [!TIP] **提示**：推荐使用 `using`
> **推荐使用 `using`**，原因：
> 
> 1. **语法更直观**：`T = U` 更像赋值，容易理解。
> 2. **模板别名**：`using` 支持模板，`typedef` 不支持（见下文）。
> 3. **可读性更好**：特别是复杂类型（如函数指针），`using` 更清晰。

---

## 2. using

### 2.1 基本类型别名

`using` 最基础的用法是为简单类型起别名：

```cpp
using MyInt = int;
using MyDouble = double;
using MyString = std::string;
MyInt age = 25;                    // int
MyString name = "Closure";         // std::string
```

### 2.2 复杂类型别名

类型别名最经典的用途之一，是简化那些“写起来很长的类型”，比如函数指针、容器嵌套等。

1. 简化**函数指针**：

```cpp
// 原始写法：定义一个函数指针类型
void (*funcPtr)(int, double);
// 用 using 起别名
using Callback = void(*)(int, double);
// 现在可以直接用 Callback 声明变量
Callback cb = SomeFunction;
```

2. 简化**嵌套容器**类型：

```cpp
// 一个存储学生姓名和成绩的 map，它的类型写起来很长
std::map<std::string, std::vector<int>> scoreMap;
// 用 using 起别名
using ScoreMap = std::map<std::string, std::vector<int>>;
// 现在可以直接使用
ScoreMap classScores;
classScores["Tom"].push_back(95);
```

3. 简化**迭代器**类型：

```cpp
std::vector<std::string>::iterator it = vec.begin();
// 起别名后
using StringIterator = std::vector<std::string>::iterator;
StringIterator it2 = vec.begin();
```

### 2.3 模板别名 Template Alias

`typedef` **不能**定义模板别名，而 `using` **可以**。这是 `using` 相对于 `typedef` 最重要的增强。

```cpp
// 需求：定义一个 Vec，它总是 std::vector<T> 的别名
template<typename T>
using Vec = std::vector<T>;
// 使用
Vec<int> numbers;          // std::vector<int>
Vec<std::string> names;    // std::vector<std::string>
```

**用 `typedef` 做不到这一点**，这也是现代 C++ 推荐 `using` 的核心原因之一。

**更复杂的模板别名示例**：

```cpp
// 定义一个固定容量为 10 的数组别名
template<typename T>
using Array10 = std::array<T, 10>;
Array10<int> scores;        // std::array<int, 10>
Array10<std::string> words; // std::array<std::string, 10>
```

### 2.4 模板别名 + 嵌套类型

模板别名也可以用于简化嵌套在模板内的类型：

```cpp
template<typename T>
using Iterator = typename std::vector<T>::iterator;
// 使用
Iterator<int> it = vec.begin();
```

> [!WARNING] **注意**：
> 这里需要 `typename` 关键字，因为 `std::vector<T>::iterator` 是一个“依赖类型”（dependent type），编译器在解析模板时不知道它是什么，`typename` 告诉编译器“这是一个类型”。

---

## 3. typedef

`typedef` 是 C++98 之前引入的语法，功能与 `using` 类似，但语法较**晦涩**。在现代 C++ 中，除了一些特殊场景（比如兼容非常老的代码），通常使用 `using`。

基本用法：

```cpp
// 基本类型别名
typedef int MyInt;

// 函数指针
typedef void (*Callback)(int, double);

// 容器类型
typedef std::map<std::string, std::vector<int>> ScoreMap;
```

---

## 4. 注意事项

### 4.1 类型别名不是新类型

`using MyInt = int;` 只是给 `int` 起了一个“外号”。在函数重载中，`void Func(int)` 和 `void Func(MyInt)` 是**同一个函数**，会编译报错：
 
```cpp
using MyInt = int;
void Func(int x) {}
void Func(MyInt x) {}   // ❌ 重复定义
```
 
 如果你**确实需要**创建新类型（比如防止混淆 `int` 和 `Score`），应该使用 `enum class` 或 `struct` 包装。