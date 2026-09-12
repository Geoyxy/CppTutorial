---
tags:
  - 分支
  - 知识类型/数据结构与算法
  - 受审状态/拒绝
前置知识-最低:
  - "[[DAaa1. 数据结构与算法的基础概念|DAaa1]]"
前置知识-推荐:
  - "[[ENab1. Doxygen 注释]]"
  - "[[14. 析构、拷贝构造、RAII、转换构造、this、运算符重载#6. 运算符重载 Operator Overloading|14-6. 运算符重载]]"
  - 断言
  - 异常
updated: 2026-09-12
---
# 线性结构、线性表

## 1. 线性结构 Linear Structure

在 [[DAaa1. 数据结构与算法的基础概念#2.1 逻辑结构|DAaa1-2.1 逻辑结构]] 中我们提到过“线性结构”这种逻辑结构。

![[DAaa1. 数据结构与算法的基础概念#^LinearStructure]]

观察图示，我们能发现线性结构有以下特点：

1. 存在且仅存在一个“**首元素**”。
2. 存在且仅存在一个“**尾元素**”。
3. 除了首元素外，结构中的每个数据元素均只有一个“**前驱**”。
4. 除了尾元素外，结构中的每个数据元素均只有一个“**后继**”。

| 中文     | 英文              | 含义                     |
| ------ | --------------- | ---------------------- |
| **前驱** | **predecessor** | 在序列中，某元素**前面**紧挨着的那个元素 |
| **后继** | **successor**   | 在序列中，某元素**后面**紧挨着的那个元素 |

属于线性结构的**数据类型**（或 ADT）包括：

- 线性表
- 栈
- 队列
- 数组
- 串

等，你应该能察觉到，之前我们使用的数组、`std::vector` 等都属于线性结构。接下来的本系列课程将首先围绕线性结构展开。

---

## 2. 线性表 Linear List

### 2.1 线性表的基本概念

**线性表**（Linear List）是由 $n$ 个**相同类型**的数据元素构成的**有限序列**，通常记为：

$$
(a_1, a_2, \dots, a_n)
$$

其中：

- $n$ 称为线性表的**长度**（$n\geq0$）。
- 当 $n=0$ 时，称为**空表**。
- $a_i$ 是线性表中第 $i$ 个元素，$i$ 称为该元素的**位序**。

在逻辑结构上，线性表是一种线性结构，满足线性结构的一切特征。

在存储结构上，线性表有两种基本的存储方式：

|存储方式|名称|特点|
|---|---|---|
|**顺序存储**|顺序表|用一组**连续**的内存单元依次存储元素，逻辑相邻即物理相邻|
|**链式存储**|链表|用一组**任意**的存储单元存储元素，通过**指针**链接，逻辑相邻不一定物理相邻|

接下来我们会学习这两种线性表。

### 2.2 线性表的 ADT 定义

> [!TIP] **提示**：学习建议
> 若不熟悉 ADT 的概念，请回顾 [[DAaa1. 数据结构与算法的基础概念#3. 抽象数据类型|DAaa1-3. 抽象数据类型]] 。

```
ADT List {
    数据对象: D = { aᵢ | aᵢ ∈ ElemSet, i = 1, 2, ⋯, n, n ≥ 0 }

    数据关系: R = { <aᵢ₋₁, aᵢ> | aᵢ₋₁, aᵢ ∈ D, i = 2, ⋯, n }

    基本操作:
        InitList(&L)
            操作结果: 构造空线性表 L。

        DestroyList(&L)
            初始条件: L 已存在。
            操作结果: 销毁 L。

        ClearList(&L)
            初始条件: L 已存在。
            操作结果: 将 L 重置为空表。

        ListEmpty(L)
            初始条件: L 已存在。
            操作结果: 若 L 为空表返回 true，否则返回 false。

        ListLength(L)
            初始条件: L 已存在。
            操作结果: 返回 L 中数据元素个数。

        GetElem(L, i, &e)
            初始条件: L 已存在，1 ≤ i ≤ ListLength(L)。
            操作结果: 用 e 返回 L 中第 i 个数据元素的值。

        LocateElem(L, e)
            初始条件: L 已存在。
            操作结果: 返回 L 中第 1 个值与 e 相同的元素的位置；若不存在，返回 0。

        PriorElem(L, cur_e, &pre_e)
            初始条件: L 已存在。
            操作结果: 若 cur_e 是 L 的数据元素且不是第一个，用 pre_e 返回其前驱；否则操作失败。

        NextElem(L, cur_e, &next_e)
            初始条件: L 已存在。
            操作结果: 若 cur_e 是 L 的数据元素且不是最后一个，用 next_e 返回其后继；否则操作失败。

        ListInsert(&L, i, e)
            初始条件: L 已存在，1 ≤ i ≤ ListLength(L) + 1。
            操作结果: 在 L 中第 i 个位置之前插入新元素 e，L 的长度加 1。

        ListDelete(&L, i)
            初始条件: L 已存在且非空，1 ≤ i ≤ ListLength(L)。
            操作结果: 删除 L 的第 i 个数据元素，L 的长度减 1。

        TraverseList(L)
            初始条件: L 已存在。
            操作结果: 遍历 L，对每个结点访问一次。
} ADT List
```

|部分|说明|
|---|---|
|**数据对象**|元素的集合，`ElemSet` 表示元素类型（可以是 int、char、结构体等）|
|**数据关系**|用序对 `<a_{i-1}, a_i>` 表示前驱-后继关系|
|**基本操作**|分为四类：初始化/销毁、查询属性、访问元素、修改结构|
|**`&` 的含义**|表示引用参数（C++ 风格），即该参数会被修改并带回结果|
|**`i` 的范围**|插入时 `1 ≤ i ≤ n+1`（可插到末尾），删除时 `1 ≤ i ≤ n`|

**操作的分类**：

| 类别         | 操作                                            | 是否改变表 |
| ---------- | --------------------------------------------- | :---: |
| **初始化/销毁** | `InitList`、`DestroyList`                      |   ✅   |
| **属性查询**   | `ListEmpty`、`ListLength`                      |   ❌   |
| **元素访问**   | `GetElem`、`LocateElem`、`PriorElem`、`NextElem` |   ❌   |
| **结构修改**   | `ListInsert`、`ListDelete`                     |   ✅   |
| **遍历**     | `ListTraverse`                                |   ❌   |

### 2.3 顺序表和链表的特征及区别

#### 2.3.1 对比

> [!TIP] **提示**：学习建议
> 本章节是对以下的 [[#3. 顺序表 Sequential List]] 和 [[占位]] 的总结。 #issue

| 对比项          | 顺序表          | 链表            |
| ------------ | ------------ | ------------- |
| **存储结构**     | 顺序存储         | 链式存储          |
| **内存布局**     | 连续的一块内存      | 离散的节点，靠指针连接   |
| **逻辑关系表示**   | 靠物理位置相邻      | 靠指针指向         |
| **是否支持随机访问** | ✅ 支持（下标直接访问） | ❌ 不支持（必须从头遍历） |

| 操作          | 顺序表          | 链表            |
| ----------- | ------------ | ------------- |
| 随机访问        | $O(1)$       | $O(n)$        |
| 查找          | $O(n)$       | $O(n)$        |
| 插入（头部）      | $O(n)$       | $O(1)$        |
| 插入（尾部）      | $O(1)$（若不扩容） | $O(1)$（维护尾指针） |
| 插入（中间，已知位置） | $O(n)$       | $O(1)$        |
| 删除（已知位置）    | $O(n)$       | $O(1)$        |

| 场景          | 推荐      |
| ----------- | ------- |
| 频繁随机访问      | **顺序表** |
| 频繁插入/删除     | **链表**  |
| 数据量已知且固定    | **顺序表** |
| 数据量变化大、不可预测 | **链表**  |
| 对缓存友好性要求高   | **顺序表** |
| 需要频繁在中间操作   | **链表**  |

#### 2.3.2 顺序表的优缺点

| 优点        | 说明                    |
| --------- | --------------------- |
| **随机访问快** | 通过下标直接访问，时间复杂度 $O(1)$ |
| **存储密度高** | 不需要额外指针域，空间利用率高       |
| **缓存友好**  | 连续内存，CPU 缓存命中率高，遍历速度快 |
| **实现简单**  | 底层就是数组，操作直观           |
| **尾插高效**  | 若无需扩容，尾部插入为 $O(1)$    |

| 缺点         | 说明                         |
| ---------- | -------------------------- |
| **插入/删除慢** | 中间或头部插入删除需移动大量元素，平均 $O(n)$ |
| **扩容代价高**  | 容量不足时需重新分配内存并复制全部数据        |
| **空间可能浪费** | 预分配空间，可能预留过多或不足            |
| **需要连续内存** | 内存碎片多时可能无法分配大块连续空间         |

#### 2.3.3 链表的优缺点

| 优点         | 说明                 |
| ---------- | ------------------ |
| **插入/删除快** | 已知位置时只需修改指针，$O(1)$ |
| **动态扩容**   | 按需分配节点，不需要预先估计容量   |
| **内存灵活**   | 不要求连续内存，可利用零散空间    |
| **无预留浪费**  | 用多少分配多少，不会预留过多空间   |

| 缺点        | 说明                       |
| --------- | ------------------------ |
| **随机访问慢** | 必须从头遍历，访问第 i 个元素为 $O(n)$ |
| **存储开销大** | 每个节点需额外存储指针，存储密度低        |
| **缓存不友好** | 节点离散分布，CPU 缓存命中率低        |
| **实现复杂**  | 指针操作易出错（如内存泄漏、野指针）       |
| **不支持下标** | 无法像数组一样用 `a[i]` 直接访问     |

---

## 3. 顺序表 Sequential List

### 3.1 顺序表的基本概念

**顺序表**（Sequential List）是线性表的**顺序存储**实现：用一组**地址连续**的存储单元依次存放线性表中的数据元素。在这一点上，顺序表和数组很像，但是需要注意顺序表和数组属于不同的数据结构。

![[顺序表的内存布局.png]]

由上图可以发现：

设顺序表的起始地址为 $LOC(a_1​)$，每个元素占 $c$ 个存储单元，则 $a_i$ 的起始地址 $LOC(a_i)$ 为：

$$
LOC(a_i) = LOC(a_1) + (i - 1) \times c
$$

顺序表的内存的**连续性**，使其可以**高效地随机访问**。但也由于内存的连续性，导致它每次只能分配固定大小的内存，造成可能的**空间浪费**。可以说，**顺序表的绝大多数优缺点均是由于内存的连续性而产生的**。

### 3.2 顺序表的实现

#### 3.2.1 准备

##### C 版本

```c
#include <stdlib.h>
#include <stddef.h>

#define MAX_SIZE 10000 // 线性表的最大长度（容量）

typedef 类型名 ElementPack; // 将需要存储的类型声明别名为 ElementPack

// 操作状态 
typedef enum {
	OK = 1,       // 成功 
	ERROR = 0,    // 通用错误 
	OVERFLOW = -2 // 申请堆内存失败 
} Status;

// 顺序表 
typedef struct {
	ElementPack* elements; // 列表
	int length;            // 当前长度 
} SqList; 

// 注意，此函数仅作示范，实际需根据“类型名”的具体数据成员来实现比较操作的逻辑
// 比较两个元素包装的内容是否相等 
int ElementPackEquiv(ElementPack element, ElementPack* element_p) {
	// 参数是否非法
	if (!element_p) return 0; 
	return (element.name == element_p->name) && (element.id == element_p->id);
}
```

##### C++ 版本

```cpp
#include <cstddef>
#include <cassert>
#include <stdexcept>

/**
* @brief 顺序表 
* @details 顺序存储结构，无扩容机制
* @tparam T 元素类型，必须支持==运算符
*/
template <typename T>
class SqList {
private:
	const std::size_t max_length_; ///< 顺序表的最大长度（容量）
	T* elements_ = nullptr;        ///< 指向顺序表的头元素
	std::size_t length_ = 0;       ///< 顺序表的当前长度
public:
	/**
	* @brief 构造长度为 max_length 的顺序表
	* @param max_length 顺序表的元素数量
	* @throw std::bad_alloc 如果分配内存失败
	*/
	explicit SqList(std::size_t max_length = 100);

	// 数据成员中存在资源，需要深拷贝
	/**
	* @brief 拷贝 list 构造顺序表
	* @param list 被拷贝的顺序表
	*/
	SqList(const SqList& list);

	/** 
	* @brief 通过索引访问元素
	* @param 被访问元素的索引
	* @return 返回元素本身
	* @warning 不保证越界访问的安全性
	*/
	T& operator[](std::size_t pos);

	/**
	* @brief 通过索引访问元素
	* @param pos 被访问元素的索引
	* @return 返回元素本身
	* @warning 不保证越界访问的安全性
	*/
	const T& operator[](std::size_t pos) const;

	/**
	* @brief 通过索引访问元素
	* @param pos 被访问元素的索引
	* @return 返回元素本身
	* @throw std::out_of_range 当 pos >= length_
	*/
	T& At(std::size_t pos);

	/** 
	* @brief 根据元素对象查找，返回元素在顺序表中的索引
	* @param element 查找时对比的元素
	* @return 若找到，返回与 element 的值相同的元素的索引；否则返回 std::size_t(-1)
	*/
	std::size_t Find(const T& element);

	/**
	* @brief 在索引为pos的元素前插入element
	* @param pos 要插入的位置
	* @param element 要插入的元素
	* @throw std::runtime_error 当 length_ > max_length_ 时
	*/
	void Insert(std::size_t pos, const T& element);

	/**
	* @brief 删除索引为pos的元素
	* @param brief 要删除的元素的索引
	*/
	void Erase(std::size_t pos);

	// 遵守三法则
	/**
	* @warning 当 list.length_ > 本表的容量时会截断
	* @param list 被拷贝的顺序表 
	*/
	SqList& operator=(const SqList& list);

	// 实现RAII
	~SqList();
};
```

#### 3.2.2 初始化 `InitList(&L)`

##### C 版本

**功能**：为顺序表分配存储空间，并将其初始化为空表。

**步骤**：

1. **参数合法性检查**：判断传入的指针 `list` 是否为 `NULL`。若为空指针，说明调用者未提供有效的顺序表地址，直接返回 `ERROR`。
2. **分配内存**：调用 `malloc` 申请 `MAX_SIZE * sizeof(ElementPack)` 字节的连续内存空间，将首地址赋给 `list->elements`。
3. **分配失败检查**：若 `malloc` 返回 `NULL`，说明内存不足，返回 `OVERFLOW`。
4. **初始化长度**：将 `list->length` 置为 `0`，表示当前为空表。
5. **返回成功**：返回 `OK`。

**要点**：

- 使用 `malloc` 进行**动态内存分配**，使顺序表容量在运行时确定。
- 必须检查 `malloc` 的返回值，避免对空指针解引用。
- 初始化后，顺序表逻辑上为空，但物理上已具备 `MAX_SIZE` 的容量。

```c
// 初始化列表 
// 参数 list：存储列表地址的指针 
Status InitList(SqList* list) {
	// 判断列表是否无效 
	if (list == NULL) return ERROR;
	
	list->elements = (ElementPack*)malloc(MAX_SIZE * sizeof(ElementPack));
	if (list->elements == NULL) return OVERFLOW;
	list->length = 0;
	return OK;
}
```

##### C++ 版本

**功能**：通过构造函数为顺序表分配存储空间并完成初始化，同时提供深拷贝语义以保证资源安全。

**构造函数（默认构造 + 带参构造）**：

1. **参数默认值**：`max_length` 默认为 `100`，允许调用者指定容量。
2. **成员初始化列表**：按声明顺序初始化三个数据成员：
    - `max_length_`：记录顺序表最大容量。
    - `elements_`：用 `new T[max_length_]` 分配类型为 `T` 的连续数组。
    - `length_`：置为 `0`，表示空表。
3. **异常安全**：若 `new` 分配失败，会抛出 `std::bad_alloc`，由调用者处理。

**拷贝构造函数**：

1. **复制容量**：将 `list.max_length_` 复制给当前对象的 `max_length_`。
2. **重新分配内存**：用 `new T[max_length_]` 为当前对象分配**独立**的内存空间（这是深拷贝的关键）。
3. **复制长度**：将 `list.length_` 复制给当前对象的 `length_`。
4. **逐元素复制**：循环将源顺序表的每个元素复制到当前对象中。

**要点**：

- **深拷贝**：由于数据成员 `elements_` 持有动态资源，默认的浅拷贝会导致两个对象共享同一块内存，引发双重释放等问题。因此必须自定义拷贝构造函数，重新分配内存并复制元素。
- **`explicit` 关键字**：阻止隐式类型转换（如 `SqList<int> s = 100;` 非法），避免意外构造。
- **异常安全**：若 `new` 抛出异常，对象构造失败，不会产生半成品对象。
- **模板化**：通过模板 `typename T` 支持任意元素类型，提高复用性。

```cpp
/**
* @brief 构造长度为 max_length 的顺序表
* @param max_length 顺序表的元素数量，默认值 100
* @throw std::bad_alloc 如果分配内存失败
*/
// explicit SqList(std::size_t max_length = 100);
template <typename T>
SqList<T>::SqList(std::size_t max_length)
	: max_length_(max_length),
	elements_(new T[max_length_]),
	length_(0) {}
	
// 数据成员中存在资源，需要深拷贝
/**
* @brief 拷贝 list 构造顺序表
* @param list 被拷贝的顺序表
* @throw std::bad_alloc 如果分配内存失败
*/
// SqList(const SqList& list);
template <typename T>
SqList<T>::SqList(const SqList& list)
	: max_length_(list.max_length_),
	elements_(new T[max_length_]),
	length_(list.length_) {
	for (std::size_t i = 0; i < length_; ++i) {
		this->elements_[i] = list[i];
	}
}
```

#### 3.2.3 取值 `GetElem(L, i, &e)`

##### C 版本

**功能**：按位序读取顺序表中第 $i$ 个元素，并通过指针参数返回。

**步骤**：

1. **参数合法性检查**：判断 `list` 和 `element` 是否为 `NULL`。若任一为空指针，说明参数无效，返回 `ERROR`。
2. **越界检查**：判断位序 $i$ 是否合法。合法范围为 $1\leq i\leq$`length`。若不满足，返回 `ERROR`。
3. **取值**：将 `list->elements[i - 1]` 赋给 `*element`。
4. **返回成功**：返回 `OK`。

**要点**：

- **位序从 1 开始**：用户传入的 $i$ 是逻辑位序（1-based），而数组下标从 0 开始，因此访问时需用 `i - 1`。
- **越界检查必不可少**：C 语言不提供数组越界保护，必须手动检查 $i$ 的范围。
- **通过指针返回结果**：由于 C 不支持引用，使用 `ElementPack*` 参数将结果“带回”给调用者。
- **时间复杂度**：$O(1)$，这是顺序表随机访问的直接体现。

```c
// 获取元素
// 参数 list：要操作的顺序表
// 参数 i：要获取的元素的位序（位序从1开始）
// 参数 element：获取到的元素 
Status GetElement(SqList* list, int i, ElementPack* element) {
	// 判断列表是否无效 
	if (list == NULL || element == NULL) return ERROR;
	
	// 检查访问是否越界 
	if (i < 1 || i > list->length) return ERROR;
	
	*element = list->elements[i - 1];
	return OK;
}
```

##### C++ 版本

**功能**：提供两种按索引访问元素的方式——`operator[]`（不检查越界，高性能）和 `At`（检查越界，抛异常，更安全），同时支持 const 和非 const 两个版本。

**`operator[]`（非 const 版本）**：

1. 使用 `assert(pos < length_)` 在 Debug 模式下检查越界。
2. 返回 `elements_[pos]` 的引用，允许调用者修改元素。
3. **Release 模式下 `assert` 被移除**，不保证越界安全，追求性能。

**`operator[]`（const 版本）**：

1. 同样使用 `assert` 检查越界。
2. 返回 `const T&`，防止通过 const 对象修改元素。
3. 使 const 对象也能使用下标访问。

**`At` 方法**：

1. 显式检查 `pos >= length_`。
2. 若越界，抛出 `std::out_of_range` 异常，携带错误信息。
3. 返回元素引用，允许修改。
4. **无论 Release 模式还是 Debug 模式都会检查**，安全性更高。

**要点**：

- **索引从 0 开始**：C++ 版本采用 0-based 索引，与 C 版本的 1-based 位序不同，更符合工程习惯。
- **`operator[]` vs `At`**：
    - `operator[]` 不抛异常，性能高，适合已知索引合法的场景。
    - `At` 抛异常，安全性高，适合索引可能越界的场景。
- **const 重载**：为非 const 对象返回可修改引用，为 const 对象返回只读引用，保证 const 正确性。
- **`assert` 的局限性**：`assert` 在 Release 模式下会被禁用，因此 `operator[]` 在 Release 模式下不具备越界保护能力。
- **时间复杂度**：两种方式均为 $O(1)$。

> [!WARNING] **注意**：`At` 的 `const` 版本的重载
> 这里的 `At` 函数实际上还需要 `const` 版本的重载，但因为已经演示了 `operator[]` 的 `const` 版本的重载，所以 `At` 的 `const` 版本的重载不再演示。

```cpp
/** 
* @brief 通过索引访问元素
* @param 被访问元素的索引
* @return 返回元素本身
* @warning 不保证越界访问的安全性
*/
// T& operator[](std::size_t pos);
template <typename T>
T& SqList<T>::operator[](std::size_t pos) {
	assert(pos < length_); // 访问越界时报错
	return elements_[pos];
}

/**
* @brief 通过索引访问元素
* @param pos 被访问元素的索引
* @return 返回元素本身
* @warning 不保证越界访问的安全性
*/
// const T& operator[](std::size_t pos) const;	
template <typename T>
const T& SqList<T>::operator[](std::size_t pos) const {
	assert(pos < length_); // 访问越界时报错
	return elements_[pos];
}

/**
* @brief 通过索引访问元素
* @param pos 被访问元素的索引
* @return 返回元素本身
* @throw std::out_of_range 当 pos >= length_
*/
// T& At(std::size_t pos);
template <typename T>
T& SqList<T>::At(std::size_t pos) {
	// 检查是否越界
	if (pos >= length_) {
		throw std::out_of_range("访问越界");
	}
	return elements_[pos];
}
```

#### 3.2.4 查找 `LocateElem(L, e)`

##### C 版本

**功能**：在顺序表中查找与给定元素值相同的元素，返回其位序；若未找到或表为空，返回 0。

**步骤**：

1. **参数合法性检查**：判断 `list` 和 `element` 是否为 `NULL`。若任一为空指针，返回 0。
2. **遍历查找**：从 `i = 0` 开始遍历到 `list->length - 1`，逐一比较 `list->elements[i]` 与 `*element` 是否相等。
3. **找到返回位序**：若 `ElementPackEquiv` 返回真，说明找到，返回位序 `i + 1`（转换为 1-based 位序）。
4. **未找到返回 0**：循环结束仍未找到，返回 0。

**要点**：

- **返回值为位序（1-based）**：找到时返回 `i + 1`，与顺序表位序约定一致。
- **用 0 表示失败**：由于合法位序从 1 开始，0 可以安全地作为“未找到”的标志。
- **`ElementPackEquiv` 比较函数**：元素相等性判断被封装为独立函数，便于适配复杂类型（如结构体）。
- **空表处理**：若 `length == 0`，循环不执行，直接返回 0，无需额外判断。
- **时间复杂度**：$O(n)$，最坏情况需比较所有元素。

```c
// 获取要查找到元素的位序  
// 参数 list：要操作的顺序表
// 参数 element：要匹配的元素 
// 返回：若 list 为空则返回0,；若找到与 element 的值相同的元素，则返回其位序；否则返回0 
int LocateElement(SqList* list, ElementPack* element) {
	// 判断列表是否无效 
	if (list == NULL || element == NULL) return 0;
	
	for (int i = 0; i < list->length; ++i) {
		if (ElementPackEquiv(list->elements[i], element)) return i + 1;
	}
	return 0;
}
```

**平均时间复杂度**：

在计算 $O(n)$ 前，我们需要先了解**平均查找长度（Average Search Length, ASL）**，它描述的是：在查找过程中，为了找到目标元素，平均需要比较多少次，它的定义式为：
$$
ASL = \sum_{i=1}^{n} p_i C_i
$$

| 符号     | 含义                     | 说明                                                       |
| ------ | ---------------------- | -------------------------------------------------------- |
| $n$    | 元素总数                   | 表中有 $n$ 个元素                                              |
| $i$    | 元素编号                   | 从 $1$ 到 $n$                                              |
| $p_i$​ | 查找第 $i$ 个元素的**概率**     | $\displaystyle\sum_{i=1}^n p_i = 1$，顺序表中通常 $p_i = 1 / n$ |
| $C_i$​ | 找到第 $i$ 个元素所需的**比较次数** | 取决于查找算法和元素位置，顺序表中通常 $C_i = 1$                            |
| $\sum$ | 求和                     | 对所有元素的“概率 × 比较次数”求和                                      |

> [!EXAMPLE] **示例**：ASL 的计算
> 例如，对于一个顺序表 `[10, 20, 30, 40, 50]`，用顺序表查找目标元素：
>
>|  元素  | 位置 $i$ | 比较次数 $C_i$​ | 查找概率 $p_i$​（等概率） |
>| :--: | :----: | :---------: | :--------------: |
>| `10` |   1    |      1      |      $1/5$       |
>| `20` |   2    |      2      |      $1/5$       |
>| `30` |   3    |      3      |      $1/5$       |
>| `40` |   4    |      4      |      $1/5$       |
>| `50` |   5    |      5      |      $1/5$       |
>
> 代入公式得：
>$$
>\begin{aligned}
>&ASL=\frac{1}{5}​\times1+\frac{1}{5}\times2+\frac{1}{5}​\times3+\frac{1}{5}\times4+\frac{1}{5}​\times5 \\
>&ASL=\frac{1+2+3+4+5}{5}​=\frac{15}{5}​=3
>\end{aligned}
>$$
>**结论**：顺序查找成功时，平均比较 3 次。

在顺序表中 $p_i = \frac{1}{n},\ C_i = 1$，于是 ASL 的定义式可以简化为：
$$
ASL = \frac{1}{n}\sum_{i=1}^{n}i
$$
于是其**渐近时间复杂度**为：
$$
\frac{1}{n}\sum_{i=1}^{n}i=\frac{1+2+3+\dots+n}{n}=\frac{\frac{(1+n)n}{2}}{n}=\frac{(1+n)}{2}=\frac{1}{2}n+\frac{1}{2}=O(n)
$$
即该顺序表的查找算法的**平均时间复杂度**为 $O(n)$。

> [!QUESTION] **问题**：为什么 ASL 可以推导出 $O(n)$
> 
> |对比项|ASL（平均查找长度）|O(n)（时间复杂度）|
> |---|---|---|
> |**全称**|Average Search Length|Big O Notation|
> |**含义**|查找过程中平均比较次数的**精确值**|算法执行时间随问题规模增长的**趋势**|
> |**是否带系数**|✅ 带系数（如 `1/2`、`1`）|❌ 忽略系数|
> |**是否带低阶项**|✅ 带低阶项（如 `+1/2`）|❌ 忽略低阶项|
> |**是否带概率**|✅ 带概率 pipi​|❌ 不带概率|
> |**数学性质**|一个**数**或**函数**|一个**集合**（所有同阶函数的集合）|
> |**例子**|$ASL=2n+1$​|$O(n)$|
> 
> 因为 **ASL 本身就是一个关于 `n` 的函数**，而 O(n) 就是这个函数的渐近上界。也就是说，$O(n)$ 就是关于 $n$ 的函数，取最高阶项、忽略系数后的值。

##### C++ 版本

**功能**：在顺序表中查找与给定元素值相同的元素，返回其索引；若未找到，返回 `std::size_t(-1)`。

**步骤**：

1. **遍历查找**：从 `i = 0` 开始遍历到 `length_ - 1`，逐一比较 `elements_[i] == element`。
2. **找到返回索引**：若相等，返回当前索引 `i`（0-based）。
3. **未找到返回哨兵值**：循环结束仍未找到，返回 `std::size_t(-1)`。

> [!NOTE] **概念**：哨兵值 Sentinel Value
> **哨兵值**是一个**特殊的、约定好的值**，用于**标记“结束”或“无效”**，让程序知道“到此为止”或“这里没有有效数据”。
> 
> 在遍历或处理数据时，我们往往需要知道“什么时候停下来”或“什么时候数据无效”。哨兵值就是用来做这件事的——它本身不是有效数据，而是**一个标记**。
> 
> 哨兵值的常见使用场景：
> 
> |场景|哨兵值|说明|
> |---|---|---|
> |**C 风格字符串**|`'\0'`|字符串末尾的终止符，标记字符串结束|
> |**链表尾节点**|`nullptr`|尾节点的 `next` 指针为 `nullptr`，标记链表结束|
> |**查找失败**|`std::string::npos`|`find()` 找不到时返回 `npos`（通常是 `-1`）|
> |**循环输入结束**|`-1`|输入 `-1` 表示不再输入|
> |**文件读取结束**|`EOF`|文件末尾标记（值为 `-1`）|
> |**红黑树/NIL 节点**|特殊的 NIL 节点|标记叶子节点的结束|

**要点**：

- **索引从 0 开始**：C++ 版本返回 0-based 索引，与 C 版本的 1-based 位序不同。
- **用 `std::size_t(-1)` 表示失败**：这是 `std::size_t` 能表示的最大值（通常是 `18446744073709551615`），相当于“无符号版本的 -1”。
- **`==` 运算符比较**：依赖元素类型 `T` 的 `==` 运算符，要求 `T` 支持相等性比较。
- **与 STL 风格一致**：返回 `std::size_t` 而非 `int`，符合 C++ 标准库（如 `std::string::find`）的习惯。
- **时间复杂度**：$O(n)$。

```cpp
/** 
* @brief 根据元素对象查找，返回元素在顺序表中的索引
* @param element 查找时对比的元素
* @return 若找到，返回与 element 的值相同的元素的索引；否则返回 std::size_t(-1)
*/
// std::size_t Find(const T& element);
template <typename T>
std::size_t SqList<T>::Find(const T& element) {
	for (std::size_t i = 0; i < length_; ++i) {
		if (elements_[i] == element) return i;
	}
	return std::size_t(-1); // 返回一个size_t能表示的最大值
}
```

#### 3.2.5 插入 `ListInsert(&L, i, e)`

##### C 版本

**功能**：在顺序表第 $i$ 个位置（位序从 1 开始）插入元素 `element`，插入后表长加 1。

**步骤**：

1. **参数合法性检查**：判断 `list` 是否为 `NULL`。若为空指针，返回 `ERROR`。
2. **越界检查**：判断位序 $i$ 是否合法。合法范围为 $1\leq i\leq$`length`$+1\leq i\leq$`length`$+1$。注意允许 $i=$`length`$+1$，表示在表尾追加。
3. **空间检查**：判断 `list->length == MAX_SIZE`。若已满，无法插入，返回 `ERROR`。
4. **元素后移**：从表尾 `j = length - 1` 开始，向前遍历到 `j = i - 1`，将每个元素 `elements[j]` 后移到 `elements[j + 1]`。这样为第 $i$ 个位置腾出空间。
5. **插入元素**：将 `element` 放入 `elements[i - 1]`。
6. **更新长度**：`++list->length`。
7. **返回成功**：返回 `OK`。

**要点**：

- **位序从 1 开始**：用户传入的 $i$ 是 1-based，数组下标需用 $i−1$。
- **允许表尾插入**：$i=$`length`$+1$ 是合法的，此时循环不执行，直接追加。
- **从后往前移动**：必须从表尾开始后移，否则会覆盖未移动的元素。   
- **先检查空间再移动**：若表已满，直接返回，避免无效操作。    
- **时间复杂度**：$O(n)$，最坏情况（表头插入）需移动 $n$ 个元素。

```c
// 将 element 插入位序为 i 的元素前 
// 参数 list：要操作的顺序表
// 参数 i：要插入到的位序
// 参数 element：要插入的元素 
Status ListInsert(SqList* list, int i, ElementPack element) {
	// 判断列表是否无效 
	if (list == NULL) return ERROR;
	
	// 检查访问是否越界（这里允许访问 length+1 以在列表末尾插入）
	if (i < 1 || i > list->length + 1) return ERROR;
	
	// 检查存储空间是否已满
	if (list->length == MAX_SIZE) return ERROR; 
	
	// 将位序为 i 及其以后的元素后移一位 
	for (int j = list->length - 1; j >= i - 1; --j) {
		list->elements[j + 1] = list->elements[j];
	}
	
	// 插入
	list->elements[i - 1] = element;
	++list->length;
	return OK; 
}
```

**平均时间复杂度计算**：

可以发现，插入操作的时间大多耗费在移动元素上，即移动元素的语句为基本语句，我们以此来计算平均时间复杂度。

假设在长度为 $n$ 顺序表中任何位置插入元素的概率都是相等的，即 $p_i=\frac{1}{n+1}$ ，其中 $p_i$ 为在第 $i$ 个元素前插入的概率（$p_{n+1}$ 表示在末尾插入），则插入一个元素所需移动元素次数的期望值（平均值）$E_{ins}$ 为：
$$
\begin{aligned}
E_{ins}&=p_1 \times n + p_2 \times (n-1) + p_3 \times (n-2) + \dots + p_n \times 1 + p_{n+1} \times 0 \\
&= \sum_{i=1}^{n+1}p_i(n-i+1) \\
&=\frac{1}{n+1}\sum_{i=1}^{n+1}(n-i+1) \\
&=\frac{(n)+(n-1)+(n-2)+\dots+(1)+(0)}{n+1} \\
&=\frac{\frac{(n+0)(n+1)}{2}}{n+1} \\
&=\frac{n}{2}
\end{aligned}
$$
对于关于 $n$ 的函数 $E_{ins} = \frac{1}{2}n$ ，忽略系数，于是平均时间复杂度为：
$$
O(n) 
$$

##### C++ 版本

**功能**：在顺序表索引 `pos`（0-based）处插入元素 `element`，插入后长度加 1。

**步骤**：

1. **越界检查**：使用 `assert(pos <= length_)` 在 Debug 模式下检查 `pos` 是否合法。允许 `pos == length_`，表示在尾部插入。    
2. **空间检查**：判断 `length_ >= max_length_`。若已满，抛出 `std::runtime_error("列表已满")`。    
3. **元素后移**：从 `i = length_` 开始，向前遍历到 `i > pos`，将 `elements_[i - 1]` 后移到 `elements_[i]`。    
4. **插入元素**：将 `element` 放入 `elements_[pos]`。    
5. **更新长度**：`++length_`。    

**要点**：

- **索引从 0 开始**：`pos` 是 0-based，与 C 版本的 1-based 位序不同。    
- **允许尾部插入**：`pos == length_` 合法，循环不执行，直接追加。    
- **`assert` 的局限性**：在 Release 模式下 `assert` 被禁用，越界检查失效。若需 Release 模式下的安全检查，应改用 `if` 判断并抛异常。    
- **空间不足抛异常**：与 C 版本返回 `ERROR` 不同，C++ 版本通过异常传递错误信息，更符合现代 C++ 风格。    
- **从后往前移动**：与 C 版本相同，必须从尾部开始后移，防止元素被覆盖。    
- **时间复杂度**：$O(n)$。

```cpp
/**
* @brief 在索引为pos的元素前插入element
* @param pos 要插入的位置
* @param element 要插入的元素
* @throw std::runtime_error 当 length_ > max_length_ 时
*/
// void Insert(std::size_t pos, const T& element);
template <typename T>
void SqList<T>::Insert(std::size_t pos, const T& element) {
	// 索引越界时报错，这里允许索引取到length_处，以允许在尾部插入元素
	assert(pos <= length_);
	// 检查列表是否已满
	if (length_ >= max_length_) throw std::runtime_error("列表已满");
	// 将插入处及其以后的元素后移一位
	for (std::size_t i = length_; i > pos; --i) {
		elements_[i] = elements_[i - 1];
	}
	elements_[pos] = element;
	++length_;
}
```

#### 3.2.6 删除 `ListDelete(&L, i)`

##### C 版本

**功能**：删除顺序表中位序为 $i$ 的元素，删除后表长减 1。

**步骤**：

1. **参数合法性检查**：判断 `list` 是否为 `NULL`。若为空指针，返回 `ERROR`。    
2. **越界检查**：判断位序 $i$ 是否合法。合法范围为 $1≤i≤$`length`$1≤i≤$`length`。注意删除时 $i$ 不能取 `length`$+1$，因为不存在第 `length`$+1$ 个元素。    
3. **元素前移**：从 $j=i$ 开始遍历到 $j=$`length`$−1$，将 `elements[j]` 前移到 `elements[j-1]`，覆盖被删除的元素。    
4. **更新长度**：`--list->length`。    
5. **返回成功**：返回 `OK`。    

**要点**：

- **位序从 1 开始**：用户传入的 $i$ 是 1-based，数组下标需转换为 $i−1$。    
- **删除范围限制**：$1≤i≤$`length`，不能删除表尾之后的空位。    
- **从前向后移动**：必须从被删位置的下一个元素开始，依次前移，否则会覆盖未移动的元素。    
- **不返回被删元素**：该版本仅删除，不保留（即返回）被删元素的值。    
- **时间复杂度**：$O(n)$，最坏情况（删除表头）需移动 $n−1$ 个元素。

```c
// 删除位序为 i 的元素 
// 参数 list：要操作的顺序表
// 参数 i：要删除的元素的位序 
Status ListDelete(SqList* list, int i) {
	// 判断列表是否无效 
	if (list == NULL) return ERROR;
	
	// 检查访问是否越界 
	if (i < 1 || i > list->length) return ERROR;
	
	// 将位序为 i+1 及其以后的元素前移一位 
	for (int j = i; j < list->length; ++j) {
		list->elements[j-1] = list->elements[j]; 
	} 
	--list->length;
	return OK;
}
```

**平均时间复杂度计算**：

可以发现，删除操作的时间大多耗费在移动元素上，即移动元素的语句为基本语句，我们以此来计算平均时间复杂度。

假设 $p_i$ 为删除第 $i$  个元素的概率，$E_{del}$ 为在长度为 $n$ 顺序表中删除一个元素所需移动元素次数的期望值（平均值），假设在顺序表中 $p_i=\frac{1}{n}$，于是有：
$$
\begin{aligned}
E_{del}&=p_1\times(n-1)+p_2\times(n-2)+p_3\times(n-3)+\dots+p_{n-1}\times(1)+p_n\times(0) \\
&=\sum_{i=1}^{n}p_i(n-i) \\
&=\frac{1}{n}\sum_{i=1}^{n}(n-i) \\
&=\frac{(n-1)+(n-2)+(n-3)+\dots+(1)+(0)}{n} \\
&=\frac{\frac{(n-1)n}{2}}{n} \\
&=\frac{n-1}{2}
\end{aligned}
$$
对于关于 $n$ 的函数 $E_{del} = \frac{1}{2}n-\frac{1}{2}$ ，忽略系数和常数项，于是平均时间复杂度为：
$$
O(n)
$$

##### C++ 版本

**功能**：删除顺序表中索引为 `pos`（0-based）的元素，删除后长度减 1。

**步骤**：

1. **越界检查**：使用 `assert(pos < length_)` 在 Debug 模式下检查 `pos` 是否合法。删除时 `pos` 必须严格小于 `length_`。    
2. **元素前移**：从 `i = pos` 开始遍历到 `i < length_ - 1`，将 `elements_[i + 1]` 前移到 `elements_[i]`。    
3. **更新长度**：`--length_`。    

**要点**：

- **索引从 0 开始**：`pos` 是 0-based，与 C 版本的 1-based 位序不同。    
- **删除范围限制**：`pos < length_`，不能删除不存在的元素。    
- **`assert` 的局限性**：在 Release 模式下 `assert` 被禁用，越界检查失效。若需 Release 模式下的安全检查，应改用 `if` 判断并抛异常。    
- **从前向后移动**：与 C 版本相同，必须从被删位置开始依次前移。    
- **时间复杂度**：$O(n)$。

```cpp
/**
* @brief 删除索引为pos的元素
* @param brief 要删除的元素的索引
*/
// void Erase(std::size_t pos);
template <typename T>
void SqList<T>::Erase(std::size_t pos) {
	assert(pos < length_); // 索引越界时报错
	// 将删除处及其以后的元素前移一位
	for (std::size_t i = pos; i < length_ - 1; ++i) {
		elements_[i] = elements_[i + 1];
	}
	--length_;
}
```

#### 3.2.7 销毁 `DestroyList(&L)`

##### C 版本

**功能**：释放顺序表占用的动态内存，并将顺序表重置为空状态。

**步骤**：

1. **参数合法性检查**：判断 `list` 是否为 `NULL`。若为空指针，返回 `ERROR`。    
2. **释放内存**：调用 `free(list->elements)` 释放 `malloc` 分配的数组空间。    
3. **置空指针**：将 `list->elements` 置为 `NULL`，避免悬空指针。    
4. **重置长度**：将 `list->length` 置为 `0`，表示空表。    
5. **返回成功**：返回 `OK`。    

**要点**：

- **`free` 与 `malloc` 配对**：`elements` 是由 `malloc` 分配的，必须用 `free` 释放，不能与 `new`/`delete` 混用。    
- **置空指针防悬空**：释放后将指针置为 `NULL`，防止后续误用已释放的内存。    
- **不释放 `list` 本身**：`list` 指向的顺序表结构体通常由调用者分配（如栈上变量），此函数只释放内部动态数组。    
- **重复销毁安全**：由于释放后指针置为 `NULL`，再次调用时 `free(NULL)` 是安全的（C 标准规定 `free(NULL)` 无操作）。

```c
// 销毁列表
// 参数 list： 要操作的列表 
Status DestroyList(SqList* list) {
	// 判断列表是否无效 
	if (list == NULL) return ERROR;
	
	free(list->elements);
	list->elements = NULL;
	list->length = 0;
	return OK;
}
```

##### C++ 版本

**功能**：析构函数，在对象生命周期结束时自动释放动态数组，实现 **RAII**（Resource Acquisition Is Initialization，资源获取即初始化）。

**步骤**：

1. 调用 `delete[] elements_` 释放 `new T[]` 分配的数组。    
2. 析构函数结束后，对象占用的内存随之被回收。    

**要点**：

- **RAII 思想**：资源（此处是动态数组）的生命周期与对象绑定。对象构造时获取资源，对象析构时自动释放资源，无需手动调用释放函数。    
- **`delete[]` 与 `new[]` 配对**：`elements_` 由 `new T[]` 分配，必须用 `delete[]` 释放（不是 `delete`），否则行为未定义。    
- **自动调用**：析构函数在对象离开作用域、被 `delete` 或程序结束时自动调用，无需显式调用。   
- **异常安全**：即使构造过程中抛出异常，已构造完成的成员也会被正确析构（C++ 保证）。    
- **无需手动置空**：对象销毁后，其成员本身也不复存在，不存在悬空指针问题。

```cpp
// 实现RAII
// ~SqList();
template <typename T>
SqList<T>::~SqList() {
	delete[] elements_;
}
```

#### 3.2.8 其他

##### C++ 版本

**功能**：重载拷贝赋值运算符，采用 **copy-and-swap（拷贝并交换）** 惯用法，保证强异常安全与自赋值安全，遵守三法则。

> [!TIP] **提示**：学习建议
> 若不熟悉“**三法则**”，请回顾 [[14. 析构、拷贝构造、RAII、转换构造、this、运算符重载#^RuleofThree|14^三法则]]

**步骤**：

1. **拷贝构造临时副本**：调用拷贝构造函数创建 `temp`，它是源表 `list` 的一份独立副本。    
    - 若此步抛出异常（如内存分配失败），`*this` 完全不受影响，对象保持原状。        
2. **交换资源**：通过 `std::swap` 依次交换三个数据成员：    
    - `max_length_` 与 `temp.max_length_`        
    - `elements_` 与 `temp.elements_`        
    - `length_` 与 `temp.length_`    
    交换后，`*this` 获得了源表的内容，`temp` 持有 `*this` 原来的旧资源。    
3. **临时对象析构**：函数返回时，`temp` 离开作用域被析构，自动释放 `*this` 原来的旧资源。    

**要点**：

- **强异常安全**：整个赋值过程要么完全成功，要么对象保持原状，绝不会出现“部分修改”的中间状态。这是通过“先拷贝构造临时副本，再交换”实现的——任何可能失败的操作（内存分配）都发生在修改 `*this` 之前。    
- **自赋值安全：当 `list` 就是 `*this` 时，拷贝构造 `temp(list)` 会创建一份自身的副本，随后交换资源。虽然多了一次拷贝，但结果是正确的，不会出现“先释放自身再复制”的问题。无需显式的 `this == &list` 检查。    
- **自动释放旧资源**：`temp` 析构时释放 `*this` 的原内存，无需手动 `delete[]`。    
- **代码简洁**：无需显式检查自赋值、无需手动释放旧内存、无需处理截断，逻辑清晰。

```cpp
// 遵守三法则
/**
* @brief 拷贝赋值运算符
* @param list 被拷贝的顺序表
* @return 返回自身引用，支持链式赋值
* @note 采用 copy-and-swap 惯用法，保证强异常安全与自赋值安全
*/
// SqList& operator=(const SqList& list);
template <typename T>
SqList<T>& SqList<T>::operator=(const SqList& list) {
	// 1. 拷贝构造临时副本（若抛异常，*this 不受影响）
	SqList<T> temp(list);
	// 2. 与临时副本交换资源
	std::swap(max_length_, temp.max_length_);
	std::swap(elements_, temp.elements_);
	std::swap(length_, temp.length_);
	// 3. temp 析构时释放原 *this 的旧资源
	return *this;
}
```

### 3.3 顺序表的特点

由以上实现代码可以看出：

| 优点         | 原因                                |
| ---------- | --------------------------------- |
| **支持随机访问** | 内存连续，第 $i$ 个元素地址可直接计算，按位查找 $O(1)$ |
| **存储密度高**  | 只存数据元素本身，无需额外指针域                  |
| **缓存友好**   | 元素连续存放，CPU 可整块加载，局部性好，遍历效率高       |
| **实现简单**   | 底层直接借助数组，地址计算和操作逻辑直观              |

| 缺点             | 原因                              |
| -------------- | ------------------------------- |
| **插入和删除慢**     | 必须保持内存连续，插入/删除需移动大量元素，平均 $O(n)$ |
| **容量固定或扩容成本高** | 静态分配容量固定；动态扩容需重新申请连续内存并复制原有元素   |
| **需要预分配连续内存**  | 要求一整块连续空间，元素较多时可能因内存碎片而分配失败     |
| **空间可能浪费**     | 预分配容量若大于实际需求，多余空间闲置             |

> [!SUMMARY] **总结**
> 顺序表的优缺点几乎都源于“**内存连续性**”这一**根本特征**：
> 
> - 连续性带来了**随机访问**、**高存储密度**和**缓存友好**，
> - 也带来了**插入删除慢**、**扩容困难**和**内存要求高**。
