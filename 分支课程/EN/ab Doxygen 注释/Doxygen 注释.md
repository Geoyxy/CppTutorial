---
tags:
  - 分支
  - 知识类型/工程实践
  - 受审状态/拒绝
前置知识-最低:
  - 注释
updated: 2026-09-09
---
# Doxygen 注释概述

Doxygen 是一个从源代码注释中自动生成文档的工具，支持 C++、C、Java 等多种语言。通过在注释块中添加特殊标记，可以将代码注释转化为结构化的 HTML、PDF 或 CHM 文档。

```cpp
#include <iostream>
```

> [!NOTE]
> Doxygen 注释块本质是在 C/C++ 注释块的基础上添加额外标识，让 Doxygen 识别并组织到生成的文档中。

---

# 速查表

## 注释风格

| 风格         | 格式           | 适用场景   |
| ---------- | ------------ | ------ |
| JavaDoc 风格 | `/** ... */` | 最常用，推荐 |
| Qt 风格      | `/*! ... */` | 实现文件   |
| 单行风格       | `/// ...`    | 简短说明   |
| 后置注释       | `///< ...`   | 成员变量后  |

## 常用指令

| 指令                   | 说明     | 示例                             |
| -------------------- | ------ | ------------------------------ |
| `@file`              | 文件名称   | `@file module.c`               |
| `@brief`             | 简要描述   | `@brief 计算最大值`                 |
| `@author`            | 作者     | `@author 张三`                   |
| `@date`              | 日期     | `@date 2025-06-08`             |
| `@version`           | 版本号    | `@version 1.0`                 |
| `@param`             | 参数说明   | `@param[in] a 第一个整数`           |
| `@return`            | 返回值说明  | `@return 返回较大的整数`              |
| `@retval`            | 具体返回值  | `@retval 0 成功`                 |
| `@see` / `@sa`       | 相关参考   | `@see MyClass`                 |
| `@note`              | 注意事项   | `@note 非线程安全`                  |
| `@warning`           | 警告信息   | `@warning 可能溢出`                |
| `@todo`              | 待办事项   | `@todo 添加错误处理`                 |
| `@bug`               | 已知 Bug | `@bug 内存泄漏`                    |
| `@code` / `@endcode` | 代码块    | `@code int x = 0; @endcode`    |
| `@deprecated`        | 弃用说明   | `@deprecated 请使用 newAPI`       |
| `@copyright`         | 版权信息   | `@copyright (c) 2025`          |
| `@details`           | 详细描述   | `@details 实现细节...`             |
| `@throw`             | 异常     | `@throw <异常类型> [异常描述]`         |
| `@pre`               | 前提条件   | `@pre grid1 和 grid2 必须具有相同的维度` |
| `@tparam`            | 模板参数   | `@tparam T 元素类型，必须可默认构造和赋值`    |

## 参数方向标识

| 标识 | 含义 |
|------|------|
| `@param[in]` | 输入参数 |
| `@param[out]` | 输出参数 |
| `@param[in,out]` | 输入输出参数 |

---

# 注释风格

## 1. JavaDoc 风格（推荐）

```cpp
/**
 * 简要描述（brief description）
 * 
 * 详细描述（detailed description）
 * 可以包含多行。
 */
int max(int a, int b);
```

## 2. Qt 风格

```cpp
/*!
 * 简要描述
 * 
 * 详细描述
 */
int max(int a, int b);
```

## 3. 单行风格

```cpp
/// 单行简要描述
int max(int a, int b);
```

## 4. 后置注释

```cpp
struct Point {
    int x; ///< X 坐标
    int y; ///< Y 坐标
};
```

---

# 常用注释场景

## 1. 文件注释

每个 `.h` 和 `.cpp` 文件顶部应包含文件级注释。

```cpp
/**
 * @file    worker_manager.cpp
 * @brief   职工管理模块实现
 * @author  张三
 * @date    2025-06-08
 * @version 1.0
 * @copyright (c) 2025 项目名称
 */
```

## 2. 函数注释

函数的注释应包含功能描述、参数说明和返回值说明。

```cpp
/**
 * @brief 计算两个整数的最大值
 * @details 使用条件运算符进行比较，时间复杂度 O(1)
 * @param[in] a 第一个整数
 * @param[in] b 第二个整数
 * @return 返回较大的那个整数
 * @note 如果两个数相等，返回该值
 * @see std::max
 */
int max(int a, int b) {
    return a > b ? a : b;
}
```

## 3. 类/结构体注释

```cpp
/**
 * @brief 表示一个二维点
 * @details 包含 x 和 y 坐标，支持基本运算
 */
struct Point {
    double x; ///< X 坐标
    double y; ///< Y 坐标
};
```

## 4. 枚举注释

```cpp
/**
 * @brief 错误码类型
 */
enum class ErrorCode {
    kSuccess = 0,     ///< 操作成功
    kTimeout,         ///< 超时错误
    kOverflow,        ///< 溢出错误
    kNotFound         ///< 未找到
};
```

## 5. 成员变量注释

```cpp
class Worker {
private:
    std::string name_;  ///< 职工姓名
    int id_;            ///< 职工编号
    double salary_;     ///< 月薪
};
```

## 6. 宏定义注释

```cpp
/**
 * @brief 定义圆周率的近似值
 * @note 精度为 10 位小数
 */
#define PI 3.1415926535
```

## 7. 命名空间注释

```cpp
/**
 * @namespace network
 * @brief 网络通信相关函数和类
 */
namespace network {
    // ...
}
```

---

# 特殊功能指令

## 1. 代码块示例

```cpp
/**
 * @brief 使用示例
 * @code
 * int result = max(10, 20);
 * std::cout << result << std::endl;
 * @endcode
 */
int max(int a, int b);
```

## 2. 交叉引用 `@see`

```cpp
/**
 * @brief 打开文件
 * @see open() 函数
 * @see FileReader 类
 */
void openFile();
```

## 3. 待办事项 `@todo`

```cpp
/**
 * @brief 处理用户输入
 * @todo 添加输入验证
 * @todo 支持 Unicode
 */
void processInput();
```

## 4. 弃用标记 `@deprecated`

```cpp
/**
 * @brief 旧版接口
 * @deprecated 请使用 newProcess() 替代
 */
void oldProcess();
```

## 5. 组分组 `@defgroup`

```cpp
/**
 * @defgroup math_utils 数学工具
 * @brief 常用数学函数集合
 */
// 组内的函数会自动归入
```

---

# 详细注释与简要注释

Doxygen 为每个代码项提供两种描述：

| 描述类型 | 说明 | 触发方式 |
|---------|------|---------|
| **简要描述 (brief)** | 简短的一行描述，显示在概述中 | `@brief` 命令或 `JAVADOC_AUTOBRIEF=YES` 时第一个句号 |
| **详细描述 (detailed)** | 更长的详细说明，在详情页面 | 简要描述后的空行之后的内容 |

```cpp
/**
 * @brief 简要描述，显示在概述中
 * 
 * 详细描述从这里开始，显示在详情页面。
 * 可以包含多行内容。
 */
void func();
```

> [!TIP]
> 如果设置 `JAVADOC_AUTOBRIEF = YES`，JavaDoc 风格的注释块会自动以第一个句号`.`作为简要描述和详细描述的分隔。

---

# 实践建议

## ✅ 推荐做法

1. **在头文件中放接口注释**，实现文件中放实现细节注释
2. **每个函数都应有 `@brief` 和必要的 `@param`、`@return`**
3. **后置注释用 `///<` 或 `/**<`** 标记
4. **使用 `@see` 建立引用关系**，方便导航
5. **保持注释与代码同步更新**

## ❌ 避免做法

1. **不要在注释中重复代码本身**（如 `@return 返回 a+b` 对加法函数无意义）
2. **避免过长的单行注释**，用多行拆分
3. **避免空洞的注释**，应提供有价值信息
4. **不要遗漏文件注释**，否则全局函数、typedef 等可能无法被文档收录

---

# 生成文档

```bash
# 1. 生成配置文件
doxygen -g

# 2. 编辑 Doxyfile
# 设置 PROJECT_NAME, INPUT, OUTPUT_DIRECTORY 等

# 3. 运行 Doxygen
doxygen Doxyfile
```

---

# 总结

| 问题 | 答案 |
|------|------|
| Doxygen 是什么？ | 从注释自动生成文档的工具 |
| 常用注释风格？ | `/** ... */`（推荐）、`/*! ... */`、`///` |
| 核心指令？ | `@brief`、`@param`、`@return` |
| 如何标记后置注释？ | `///<` 或 `/**<` |
| 文档放在哪里？ | 接口注释在头文件，实现注释在源文件 |
| 文件注释是否必须？ | 是，否则全局对象可能无法生成文档 |