# awtk-mvvm-c-hello

## 1.介绍

* [AWTK](https://github.com/zlgopen/awtk)  全称 Toolkit AnyWhere，是 ZLG 开发的开源 GUI 引擎，旨在为嵌入式系统、WEB、各种小程序、手机和 PC 打造的通用 GUI 引擎，为用户提供一个功能强大、高效可靠、简单易用、可轻松做出炫酷效果的 GUI 引擎。

* [AWTK-MVVM](https://github.com/zlgopen/awtk-mvvm) 是一套为 AWTK 用 C 语言开发，并支持各种脚本语言的 MVVM 框架，实现了数据绑定、命令绑定和窗口导航等基本功能，使用 AWTK-MVVM 开发应用程序，无需学习 AWTK 本身的 API，只需学习绑定规则和 Model 的实现方式即可。

AWTK-MVVM 提供的 demo 功能单一，适合查看特定功能的实现方法。但是在开发实际项目时，有的同学看了那些 demo 之后，可能仍然不知从何着手。[AWTK-MVVM-C-HELLO](https://github.com/zlgopen/awtk-mvvm-c-hello) 提供一个完整的项目，演示 AWTK-MVVM 的基本用法，可以作为一个模板项目来使用。本项目提供以下功能的演示：

* 数据绑定。
* 命令绑定。
* 窗口导航。
* 数据格式转换器。
* 数据有效验证器。
* 窗口之间的数据传递。
* 多视图共享 ViewModel。
* 数据存储及 Repository 模式的使用。
* 列表视图及数组 ViewModel 的使用。
* 数据的增删改查操作。
* 排序和过滤 (TODO)。

在开发 AWTK-MVVM 应用程序时，建议采用如下目录结构：

```
├─assets            资源
│  └─default        缺省主题
├─docs              文档
├─scripts           脚本工具
├─src               源码
│  ├─common         公共的代码
│  ├─idls           用于产生代码的idl定义
│  └─view_models    ViewModel的实现
└─tests             测试程序
```

## 2.准备

1. 获取 awtk 并编译

```
git clone https://github.com/zlgopen/awtk.git
cd awtk; scons; cd -
```

2. 获取 awtk-mvvm 并编译
```
git clone https://github.com/zlgopen/awtk-mvvm.git
git clone https://github.com/jerryscript-project/jerryscript.git awtk-mvvm/3rd/jerryscript
cd awtk-mvvm; scons
```

2. 获取 awtk-mvvm-c-hello 并编译
```
git clone https://github.com/zlgopen/awtk-mvvm-c-hello.git
cd awtk-mvvm-c-hello; scons
```

## 3.运行

```
./bin/awtk_mvvm_app
```

> 本文以 Linux/MacOS 为例，Windows 可能会微妙差异，请酌情处理。
