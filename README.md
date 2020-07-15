# our Craft 

简易版 Minecraft 实现计划 - 浙江大学短学期C++工程实践课程项目 

组员：

- 周寒靖
- 郑昱笙
- 尹浩霖

## 项目描述

## 总体目标：

本项目希望基于 openGL 实现一个 类似于 `MineCraft` 创造模式的沙盒游戏项目；

## 基本目标：

- 实现基本地形生成与存储；
- 实现摄像机漫游；
- 实现方块的放置与破坏；
- 实现方块的切换功能

## 可选高级选项：

- 实现碰撞检测；
- 实现可重入的地形存储系统；
- 丰富的方块；
- 背包系统；

## 迭代计划：

### 第一轮迭代计划：

- 用时：四天
- 实现基本地形生成；
- 实现摄像机漫游；

## 开发工具与项目管理

- 版本控制	Git, GitHub
- 开发环境：visual studio 2019
- 编程语言	C++ 17
- 持续集成	Jenkins\
- 交流协作	钉钉
- 文档编辑	Markdown

## 具体实现

尝试采用MVVM结构进行开发；

## 参考资料

### 原版

- github:

[https://github.com/Hopson97/MineCraft-One-Week-**Challenge**](https://github.com/Hopson97/MineCraft-One-Week-Challenge)

- b站搬运视频（感觉不错：

[https://www.bilibili.com/video/BV1ux411H7ZE/?spm_id_from=333.788.videocard.1](https://www.bilibili.com/video/BV1ux411H7ZE/?spm_id_from=333.788.videocard.1)

可以参考一下他每次迭代的进度，开发过程；

(感觉今天第一个周期可以先尝试把方块系统做出来，能生成很多个叠在一起方块那样？对应于视频两天的进度什么的...)

可以参考这个部分的OpenGL教程？（入门那一块的教程挺完整的，差不多就是显示方块加贴图的部分了）

[https://learnopengl-cn.github.io/](https://learnopengl-cn.github.io/)

### 极限编程方法论

可以蛮看看？（虽然我也不太懂）

### 技术选型

（感觉可以不要现成的游戏引擎轮子，这样可以有理由说做的不完善也没关系）

openGL的窗口显示也可以采用QT相关；

可能还需要一点数学和物理的相关库；

### 参考资料：

- 学长的图形学作业

[https://github.com/Clapeysron/Mycraft](https://github.com/Clapeysron/Mycraft)

- 一个用纯c写的，素材有很多可以拿过来现成的用

[https://github.com/fogleman/Craft](https://github.com/fogleman/Craft)

- 这里也有人写了

[https://ryuzhihao123.blog.csdn.net/article/details/88079736](https://ryuzhihao123.blog.csdn.net/article/details/88079736)
