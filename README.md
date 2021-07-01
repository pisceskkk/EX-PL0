# EX-PL0

 ![platform: windows(shields.io)](https://img.shields.io/badge/platform-Windows-brightgreen)

PL/0 Compiler Extension(including `repeat`, `for`, `case`, `function`, `real`, `record` and so on)

## Structure

- `\src\PL` source code of PL compiler;
- `\src\interpret` source code of interpret for intermediate code;
- There are `Makefile`s in both `src\PL` and `src\interpret`;
- `\TestCases` basic test case files and `run` script;
- `TestCases\run` script for compiling PL compiler and interpret, test some case and so on.

## Prerequisites

1. Install [GNU Make](https://www.gnu.org/software/make/) and ensure that the path is addedd to the system variable `PATH`.

## Start

### Use `TestCases\run` script

#### List of scripts

1. `TestCases\run.ps1` for [`powershell`](https://github.com/powershell/powershell) in Windows.

#### Usage

```sh
cd TestCases
# run script directly(compile and run test1.pls by default)
.\run
# run script with specific .pls file
.\run part1.pls
```

### Manual

There is `Makefile` in source dir. And you can just run `make` to compile PL compiler or interpret.

## TODO

- [x] expand `repeat` statement
- [x] expand `for` statement
- [x] expand `case` statement
- [ ] expand `function` statement
- [x] expand `real` structure
- [ ] expand `record` structure

## 开源协议

[Apache 2.0](https://github.com/pisceskkk/EX-PL0/blob/main/LICENSE)