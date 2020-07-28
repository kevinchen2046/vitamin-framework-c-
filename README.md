# vitamin-framework-cpp

## 环境配置
- 首先下载:  [mingw64](
https://nchc.dl.sourceforge.net/project/mingw-w64/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z)

- 配置你的环境变量，使用`g++ --help`测试是否安装成功
- 修改 ".vscode/launch.json" & ".vscode/task.json" g++ 路径. 如果成功你可以通过F5调试你的C++代码。
- 或者直接执行 "npm run start"编译并运行main.cpp.

## 文件编译

- 文件说明
  - `*.h` 头文件
    
    头文件主要是声明一些方法、类。类似于接口文件。同时可以逻辑也可以在头文件里面实现，但一般不这么做。

  - `*.cpp` c++文件
    
    通常是一些逻辑的实现，包括类的静态方法，等。

  - `*.o` 链接库文件

    通过命令`g++ -c`编译成链接库文件

- 单文件编译

执行 `g++ {cppfile} [-o {filename}]` 就可以编译出exe文件

- 多文件编译
    - 首先通过`g++ -c {cppfile} [-o {filename}]`将cpp文件编译成`*.o`的链接库文件
    - 然后通过`g++ {...*.o file} [-o {filename}]`编译成exe文件,同时注意顺序

- 例子
    ```shell
        > g++ -c src/core/helper.cpp -o src/core/helper.o
        > g++ -c main.cpp -o main.o
        > g++ main.o src/core/helper.o -o main

        > ./main.exe
        -------------------------------------------------
        > ...
    ```

## c++语法小结

- printf 需要提供占位符以确定后续参数.

  - %s 普通字符或字符串
  - %c 整数转成对应的 ASCII 字元。
  - %d 整数转成十进位。
  - %f 倍精确度数字转成浮点数。
  - %o 整数转成八进位。
  - %s 整数转成字符串。
  - %x 整数转成小写十六进位。
  - %X 整数转成大写十六进位。
  - %n sscanf(str, “%d%n”, &dig, &n)，%n表示一共转换了多少位的字符

    ```c++
    string a="my";
    int b=2;
    string b="bag";
    printf("this is %s %d %s .",a,b,c);
    ```
- class 类定义
  - 定义通常是在头文件中
  - 实现通常是在cpp文件中
  - 实例化不需要new
    ```c++
    Person person;

    person.age = 18;
    person.name = "X";
    person.sex = "M";
    person.say();
    ```
  - 使用`::`定义和调用静态方法

## 自动编译
`> gulp compile`
通过gulp扫码目录结构，并自动编译链接库。最终编译成exe。

----

## 例子
```c++
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <limits>
#include "person.h"
#include "core/helper.h"
#include "core/logger.h"
using namespace std;

enum Color
{
    red,
    green,
    blue
};

int main()
{
    //支持UTF8，防止中文乱码
    system("chcp 65001");
    Helper::logTypes();

    string str = "Hello";
    string megestr = str + "World!";
    Logger::info("> merge: %s , enum:%d", megestr.c_str(), Color::blue);
    //printf("> str: %s , length:%d %s", str.c_str(), str.length(), "\n");
    Logger::log("> str: %s , length:%d", str.c_str(), str.length());
    

    Person person;
    person.age = 20;
    person.name = "Kevin Chen";
    person.sex = "Men";
    person.say();

    system("pause");
    return 0;
}
```
```shell
[WAR] ---------------------------------------------------------------------
[INF] 类型               所占字节数             最大值          最小值
[WAR] ---------------------------------------------------------------------
[LOG] bool:              1                       1               0
[LOG] char:              1                       127             -128
[LOG] signed char:       1                       127             -128
[LOG] unsigned char:     1                       255             0
[LOG] wchar_t:           2                       65535           0
[LOG] short:             2                       32767           -32768
[LOG] int:               4                       2147483647      -2147483648
[LOG] unsigned:          4                       -1              0
[LOG] long:              4                       2147483647      -2147483648
[LOG] unsigned long:     4                       -1              0
[LOG] double:            8                       -1              0
[LOG] long double:       16                      6421760         6421744
[LOG] float:             4                       -536870912      0
[LOG] size_t:            8                       -1              0
[LOG] string:            32                      6421808         6421776
[WAR] ---------------------------------------------------------------------
[INF] > merge: HelloWorld! , enum:2
[LOG] > str: Hello , length:5
[LOG] > 构造Person...
[DEB] 我叫Kevin Chen, 性别 Men, 今年20岁.
Press any key to continue . . .
```
