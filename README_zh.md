# PL/0语法拓充

 ![platform: windows(shields.io)](https://img.shields.io/badge/platform-Windows-brightgreen)

对PL/0编译器（含中间代码解释器）进行语法拓充，包括`repeat`、`for`、`case`、`function`、`real`、`record`等内容。

## 内容

- `\src\PL` 包含PL编译器源代码；
- `\src\interpret` 包含中间代码解释器源代码；
- `src\PL`和`src\interpret`中包含`Makefile`;
- `\TestCases` 包含基础的测试用例（详见`PL编译测试用例说明.docx`）及运行脚本；
- `TestCases\run1`为运行脚本，包括编译PL编译器、编译解释器、测试特定用例等功能。

## 准备工作

1. 安装[GNU Make](https://www.gnu.org/software/make/)并确保添加路径至系统变量`PATH`中。

## 开始

### 使用`TestCases\run`的脚本

#### 脚本列表

1. `TestCases\run.ps1` 供Windows系统下 [`powershell`](https://github.com/powershell/powershell)使用的脚本

#### 使用方法

```sh
cd TestCases
# 直接运行脚本，默认编译运行test1.pls文件
.\run
# 运行脚本时指定文件，编译运行特定文件
.\run part1.pls
```

### 手动编译

源代码同目录中包含`Makefile`，可以直接通过`make`指令编译得到PL编译器或中间代码解释器。

## TODO

- [x] 拓充`repeat`语法
- [x] 拓充`for`语法
- [x] 拓充`case`语法
- [ ] 拓充`function`语法
- [x] 拓充`real`数据类型
- [ ] 拓充`record`数据类型

## 开源协议

[Apache 2.0](https://github.com/pisceskkk/EX-PL0/blob/main/LICENSE)