# 南邮软件设计
————一个从千禧年就没变过题目的软件设计

## 使用方式

请在类Unix平台使用（Linux/MacOS），Windows没测过（樂）
windows的话也得用MinGW工具链编译运行
可惜没上Ninja（主打一个杀鸡用牛刀）

### 1.克隆仓库
```shell
git clone https://github.com/msuadOf/PJ.git
```
或者国内网络不好的话使用ssh
```shell
git clone git@github.com:msuadOf/PJ.git
```

### 2.运行代码
工程目录下使用makefile编写了运行脚本，可以在根目录很方便的进行运行
推荐方式：先全部编译一遍，再逐个运行
```shell
make all -j `nproc`

make run_a1
...
make run_a2
```

### 3.一键回归测试
输入内容都在每个文件夹的test_$.txt中，会从文本中读入作为输入
```shell
make test
```
