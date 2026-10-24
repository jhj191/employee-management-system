# 职工管理系统（Employee Management System）

用 C++ 写的一个控制台职工管理小程序。练习点是**继承与多态**、**动态数组**、**文件读写**。

Windows + Visual Studio 2026 编译运行。

## 功能

运行后是一个命令行菜单，输入 0~7 选择操作：

| 编号 | 功能 | 说明 |
|---|---|---|
| 0 | 退出 | 关闭程序 |
| 1 | 增加职工 | 可以一次添加多个，每位输入编号、姓名、部门 |
| 2 | 显示职工 | 列出当前所有职工 |
| 3 | 删除职工 | 按编号删除 |
| 4 | 修改职工 | 按编号找到后重新录入信息 |
| 5 | 查找职工 | 支持按编号查、按姓名查 |
| 6 | 排序 | 按编号升序或降序排列 |
| 7 | 清空 | 确认后删掉全部数据 |

部门分三种：1 = 员工，2 = 经理，3 = 老板。

所有改动都会写到 `file.txt`，下次启动自动读回来。

## 文件结构

| 文件 | 负责什么 |
|---|---|
| `main.cpp` | 程序入口，循环显示菜单、分发操作 |
| `workerManager.h` / `.cpp` | 职工管理的全部逻辑：增删改查、排序、读写文件 |
| `worker.h` | 抽象基类，声明 `showInfo()`、`getdepName()` 两个纯虚函数 |
| `employee.h` / `.cpp` | 普通员工 |
| `manager.h` / `.cpp` | 经理 |
| `boss.h` / `.cpp` | 老板 |
| `file.txt` | 数据文件，程序运行时生成 |
| `zhigong.slnx` / `zhigong.vcxproj` | Visual Studio 工程文件 |

`workerManager` 里的职工数组是 `worker**`，即“指向基类指针的指针”。存进去的其实是 `employee` / `manager` / `boss` 对象，靠虚函数在调用时决定执行哪个版本的 `showInfo()`。

## 怎么编译

### 用 Visual Studio

1. 双击 `zhigong.slnx` 打开工程
2. `Ctrl + Shift + B` 生成
3. `F5` 运行

生成的 exe 在 `x64\Debug\zhigong.exe`。

注意事项：工程的 `C/C++ → 命令行 → 其他选项` 里必须带 `/utf-8`，否则源码里的中文会被 MSVC 按 GBK 解析，个别汉字会丢。

### 用 MSVC 命令行

在 “x64 Native Tools Command Prompt for VS” 里，进入项目目录：

```cmd
cl /nologo /EHsc /std:c++20 /utf-8 main.cpp workerManager.cpp employee.cpp manager.cpp boss.cpp /Fe:zhigong.exe
```

### 用 g++（MinGW）

```cmd
g++ -std=c++17 -Wall -Wextra main.cpp workerManager.cpp employee.cpp manager.cpp boss.cpp -o zhigong.exe
```

## 中文显示的设置

`main.cpp` 开头有两行：

```cpp
SetConsoleOutputCP(CP_UTF8);   // 输出用 UTF-8
SetConsoleCP(CP_UTF8);         // 输入也用 UTF-8
```

这两行必须成对出现。只设输出的话，你在控制台输入的姓名会按 GBK 存进去、按 UTF-8 打印出来，屏幕上显示成问号。

## 数据文件

`file.txt` 每行一条记录，用空格分隔：

```
101   张三   1
102   李四   2
```

格式是 `编号 姓名 部门`。删掉这个文件就等于清空数据，程序下次启动会当成空数据。

## 这套代码涉及的知识点

| 知识点 | 用在哪 |
|---|---|
| 继承 + 虚函数 + 多态 | `worker` 是抽象基类，三个子类各自实现 `showInfo()` |
| 虚析构函数 | `worker` 里 `virtual ~worker()`，保证 `delete` 基类指针时子类析构也执行 |
| 动态数组扩容 | `addWorker()` 里开新数组、搬旧指针、释放旧数组 |
| 指针数组 | `worker** m_arr` |
| 文件读写 | `saveFile()` 写、构造函数和 `init_emp()` 读 |
| `std::sort` + 比较函数 | `sortEmp()` 里按编号排序 |

## 已知的限制

- 输入校验不完整。菜单和部门编号输错会提示重输，但数量、编号这些地方如果输入字母，可能卡住需要重启程序。
- 每次启动都重新从文件读，没有做增量保存。
- 姓名不能带空格（用 `cin >>` 读的，遇空格就截断）。
