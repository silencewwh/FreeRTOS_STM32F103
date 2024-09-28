创建template文件夹，在该目录下创建doc driver library listing output project startup user目录

| 文件夹     | 主要存放的文件                       |
| ------- | ----------------------------- |
| driver  | 驱动文件                          |
| library | ST官方库文件                       |
| startup | ST 官方提供的库相关的核心代码, 包括引导启动的汇编代码 |
| user    | 上层应用程序代码相关文件, main 函数入口文件     |
| output  | 编译的输出文件，不用git管理               |
| Project | 工程配置文件，保存工程相关配置               |
| listing | 链接的中间文件，不用git管理               |
| doc     | 相关的说明文档，学习笔记                  |


可以使用git bash创建
```
mkdir  01Driver 02Library 03Startup 04User 05Output 06Project 07Listing 08Doc
```

#### keil添加文件结构如下
```
Project
   |--- 01Driver
   |       |--- systick                         /* 使用滴答定时器进行精确延时 */
   |       |        |--- bsp_systick.h          // 此驱动由 mz8023yt 提供
   |       |        |--- bsp_systick.c          // 此驱动由 mz8023yt 提供
   |       |--- usart                           /* 串口实现 printf 打印调试功能 */
   |       |        |--- bsp_usart.h            // 此驱动由 mz8023yt 提供
   |       |        |--- bsp_usart.c            // 此驱动由 mz8023yt 提供
   |--- 02Library
   |       |--- inc                             /* st 库文件头文件 */
   |       |        |--- misc.h                 // stm32 中断核心文件
   |       |        |--- stm32f10x_gpio.h       // stm32 通用输入输出引脚库文件
   |       |        |--- stm32f10x_rcc.h        // stm32 系统时钟配置文件
   |       |        |--- stm32f10x_usart.h      // stm32 串口相关库文件
   |       |--- src                             /* st 库文件源文件 */
   |       |        |--- misc.c
   |       |        |--- stm32f10x_gpio.c
   |       |        |--- stm32f10x_rcc.c
   |       |        |--- stm32f10x_usart.c
   |--- 03Startup                                 /* stm32 库核心代码 */
   |       |--- core_cm3.h
   |       |--- core_cm3.c
   |       |--- startup_stm32f10x_hd.s          // 汇编启动代码, 根据 STM32 flash 容量分为 ld md 和 hd
   |       |--- stm32f10x.h
   |       |--- system_stm32f10x.h
   |       |--- system_stm32f10x.c
   |--- 04User
           |--- stm32f10x_conf.h                // 工程配置头文件
           |--- stm32f10x_it.h                  // 中断控制头文件
           |--- stm32f10x_it.c                  // 中断控制源文件
           |--- stm32f10x_main.c
```
#### 使用 keil 新建工程，工程文件保存在刚刚创建的 project 目录下
 keil 打开新建立的工程, 点击"品"字型按钮, 配置工程内部文件组织结构, 以及添加对应的文件到工程中, 这里只需要添加 c 文件和 s 文件.
#### 设置链接和编译输出文件路径
#### 指定头文件查找路径
#### 设置默认开启的宏定义：STM32F10X_HD, USE_STDPERIPH_DRIVER
#### 修改 stm32f10x_conf.h 文件，只需要包含使用到的头文件
#### 新增 stm32f10x_main.c 文件，实现主函数
#### 编译工程，工程可以编译通过
#### 设置 DAP/J-LINK 下载配置，需要配置两个地方：Debug、Utilite

.gitignore里文件
```
# 这是 Git 的忽略文件

  

# 忽略 listing 下所有文件


/07listing/*


# 忽略 output 下所有文件


/05output/*

  

# 忽略doc目录下所有文件

/08Doc/*


# 忽略 project 目录下除 *.uvopt 和 *.uvproj 格式的其他文件
 

/06project/*

  

!/06project/*.uvoptx

  

!/06project/*.uvprojx
```

# 或者直接git获取

```
git clone https://github.com/silencewwh/stm32f103.project.template.git
```


---
### 使用工程
#### 添加ST官方外设文件
1. 在*library*目录下加入外设文件
2. 点击品字按钮，添加刚刚追加的文件到工程目录树中，只需要添加c文件
### 添加自己的驱动文件
1. 在*driver*目录下创建文件夹，比如电机就添加motor文件夹
2. 点击品字按钮，添加刚刚追加的文件到工程目录树中，只需要添加c文件
3. 点击魔术棒按钮，进入C/C++选项卡，将../driver/motor目录添加到编译器的查找路径中

