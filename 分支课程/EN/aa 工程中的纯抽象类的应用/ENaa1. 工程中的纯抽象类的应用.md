## 6. 工程中的纯抽象类

### 6.1 抽象与具体实现

### 6.2 依赖与耦合

### 6.3 依赖倒置原则与解耦



纯抽象类在工程中的最大价值，就是它能够定义一种**契约**，让调用者依赖接口而不依赖具体实现。这种思想在架构设计中非常核心，常见的应用场景包括：

| 应用场景         | 说明                                        | 典型例子                   |
| ------------ | ----------------------------------------- | ---------------------- |
| **插件系统**     | 插件只暴露接口，主程序通过接口加载和调用插件                    | `PluginInterface`      |
| **UI 与业务分离** | UI 层依赖接口，更换 UI 框架时业务层不需改动                 | `UiInterface`          |
| **日志系统**     | 业务层只写日志接口，具体写文件/网络/控制台由实现决定               | `LoggerInterface`      |
| **数据库访问**    | 业务层通过接口操作数据库，切换 DB（MySQL→PostgreSQL）不影响上层 | `DatabaseInterface`    |
| **测试与 Mock** | 测试时用 Mock 对象替换真实对象，隔离外部依赖                 | `MockNetworkInterface` |

> [!NOTE] **概念**：依赖 Dependency
> 在软件工程中，**依赖** 指的是 **一个模块（或类、函数）在运行或编译时，需要另一个模块（或类、函数）提供某种服务或数据**。
> 
> 简单来说：**如果 A 必须要有 B 才能正常工作，那么 A 就依赖于 B。**
> 
> ```cpp
> // 邮件发送器
> class EmailSender {
> public:
> 	// 发送邮件
>     void SendEmail(const std::string& to, const std::string& content) {
>         // 真实的发邮件逻辑
>     }
> };
> 
> // 用户服务
> class UserService {
> public:
> 	// 注册用户
>     void RegisterUser(const std::string& email) {
>         // ...
>         EmailSender sender;          // UserService 依赖 EmailSender
>         sender.SendEmail(email, "欢迎注册！");
>     }
> };
> ```
> 
> 在这里，`UserService` 依赖于 `EmailSender`。如果 `EmailSender` 的实现发生变化（比如换成短信通知），`UserService` 就必须修改代码。

> [!NOTE] **概念**：依赖倒置原则
