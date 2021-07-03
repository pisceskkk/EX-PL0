# EX-PL0

![GitHub](https://img.shields.io/github/license/pisceskkk/EX-PL0)
![platform: windows(shields.io)](https://img.shields.io/badge/platform-Windows-brightgreen)
![GitHub last commit](https://img.shields.io/github/last-commit/pisceskkk/EX-PL0)

![GitHub watchers](https://img.shields.io/github/watchers/pisceskkk/EX-PL0?style=social)
![GitHub Repo stars](https://img.shields.io/github/stars/pisceskkk/EX-PL0?style=social)
![GitHub forks](https://img.shields.io/github/forks/pisceskkk/EX-PL0?style=social)

PL/0 Compiler Extension(including `repeat`, `for`, `case`, `function`, `real`, `record` and so on)

## Structure

- [`src/PL`](https://github.com/pisceskkk/EX-PL0/tree/master/src/PL) source code of PL compiler;
- [`src/interpret`](https://github.com/pisceskkk/EX-PL0/tree/master/src/interpret) source code of interpret for intermediate code;
- There are `Makefile`s in both `src/PL` and `src/interpret`;
- [`TestCases`](https://github.com/pisceskkk/EX-PL0/tree/master/TestCases) basic test case files and `run` script;
- `TestCases/run` script for compiling PL compiler and interpret, test some case and so on.

## Prerequisites

1. Install [GNU Make](https://www.gnu.org/software/make/) and ensure that the path is addedd to the system variable `PATH`.

## Start

### Use `TestCases/run` script

#### List of scripts

1. [`TestCases/run.ps1`](https://github.com/pisceskkk/EX-PL0/blob/master/TestCases/run.ps1) for [`powershell`](https://github.com/powershell/powershell) in Windows.

#### Usage

```sh
cd TestCases
# run script directly(compile and run test1.pls by default)
./run
# run script with specific .pls file
./run part1.pls
```

### Manual

There is `Makefile` in source dir. And you can just run `make` to compile PL compiler or interpret.

## TODO

- [x] expand `repeat` statement
- [x] expand `for` statement
- [x] expand `case` statement
- [ ] expand `function` statement
- [x] expand `real` structure
- [ ] implicit conversion from `int` to `real`
- [ ] expand `record` structure
- [x] `run` script for `powershell`
- [ ] `run` script for `bash`
- [ ] batch script for test cases

## LICENSE

[Apache 2.0](https://github.com/pisceskkk/EX-PL0/blob/matser/LICENSE)