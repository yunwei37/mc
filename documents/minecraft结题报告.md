<center><font size='20' face='黑体'><strong>Minecraft组结题报告</strong></font></center> 
<center><font size='4' face='黑体'>周寒靖、尹浩霖、郑昱笙</font></center>

# 项目简介

### 项目描述

​		参考3D沙盒游戏minecraft（中文名：我的世界），做一个简易版minecraft。玩家根据第一视角可在生成的有限随机地图中随意移动，损毁方块或放置方块，搭建属于自己的方块世界。

版本库：[https://github.com/yunwei37/mc/](https://github.com/yunwei37/mc/)

### 操作规则

1、开启游戏：在游戏开始界面中按“Enter”键

2、位置移动：在当前视角方向下，“W”键向前、“S”键向后、“A”键向左，“D”键向右，“Q”键向上，“Z”键向下

3、第一视角移动：运用鼠标的移动可以改变玩家第一视角

4、方块放置与损毁：鼠标右键仿放置方块，鼠标左键销毁方块

5、放置方块转换：“1”键换soil，“2”键换stone，“3”键换stone brick，“4”键换sand，“5”键换bark，“6”键换cactus

# 项目需求

### 基本目标

1、实现基本地形生成

2、实现摄像机漫游

3、实现方块的放置和破坏

### 高级选项

1、实现无限地形、可重入的地形存储系统

2、丰富的方块类型

3、背包系统



# 项目开发

### 迭代计划

|      | 第一轮迭代                   | 第二轮迭代                                                   | 第三轮迭代                     |
| :--: | ---------------------------- | ------------------------------------------------------------ | ------------------------------ |
| 用时 | 4天                          | 3天                                                          | 4天                            |
| 成果 | 实现基本地形生成、摄像机漫游 | 扩增多种地形、增加植物群系、优化随机的地表高度（使其更符合自然地势） | 实现基本的的方块放置和破坏功能 |

### 开发技术和工具

|          |          工具           |
| -------- | :---------------------: |
| 编程语言 |          C++17          |
| 开发环境 |   visual studio 2019    |
| 开发系统 |         Windows         |
| 版本控制 |       Git，Github       |
| 持续集成 |         appveyor         |
| 相关库   | openGL、glm、freetype等 |
| 开发模式 |          MVVM           |
| 交流协作 |           QQ            |

### 小组分工

|                           | 第一轮迭代             | 第二轮迭代           | 第三轮迭代                 |
| :-----------------------: | ---------------------- | -------------------- | -------------------------- |
| 周寒靖（id: diaoshaoyou） | view层、文档、直播汇报 | 测试与集成、app层    | model层、viewmodel层、文档 |
|  郑昱笙（id：yunwei37）   | model层、viewmodel层   | view层、文档         | app层、测试与集成          |
|   尹浩霖（id：ycrisp）    | 测试与集成、app层      | model层、viewmodel层 | view层、直播汇报           |



# 项目成果

### 游戏效果图

1、封面

<table>
    <tr>
     <td><center>
        <img src="results\preface.png" height='350'/>
        </center>
        <center>
        图1 封面
        </center></td> 
    </tr>
</table>


2、不同地形各处风景

<table>
    <tr>
     <td><center>
        <img src="results\3.png" height='250'/>
        </center>
        <center>
        图2 斜坡与植物群
        </center></td> 
        <td><center>
        <img src="results\1.png" height='250'/>
        </center>
        <center>
        图3 森林与植物群
        </center></td> 
    </tr>
    <tr>
     <td><center>
        <img src="results\0.png" height='250'/>
        </center>
        <center>
        图4 仰视云朵
        </center></td> 
        <td><center>
        <img src="results\2.png" height='250'/>
        </center>
        <center>
        图5 海边风景
        </center></td> 
    </tr>
</table>


3、放置与损毁方块

<table>
    <tr>
     <td><center>
        <img src="results\add.png" height='300'/>
        </center>
        <center>
        图6 放置不同类型的方块
        </center></td> 
        <td><center>
        <img src="results\destroy.png" height='300'/>
        </center>
        <center>
        图7 销毁草地方块
        </center></td> 
    </tr>
</table>


### 代码框架

```mermaid
graph LR
Model---Block
Model---chunkGenerator
Model---plantGenerator
Model---PerlinNoise
Model---player
Model---StructureBuilder
View---Camera
View---Shader
View---Texture
View---Text
View---text_renderer
View---resource_manager
View---glad
View---stb_image
Viewmodel---Chunk
Viewmodel---Map
Viewmodel---viewmodel
App---app
```



# 项目总结

### 已实现的需求

1、基本随机地形生成

2、摄像机漫游

3、方块的放置和破坏

4、6种可放置的方块类型，且可相互更换

5、开始界面

### 优化空间探讨

1、无限地形渲染。过大的地形会影响项目运行速度，所以需要即时渲染，即只渲染用户看得见的区域。当用户移动时，已变成不可见区域的渲染内存应当回收，用于渲染新生成的可见区域。这样才能不断生成地形即实现无限地形，又不导致运行速度过慢/内存崩溃。这一块内容涉及内存管理，还有待优化提高。

2、背包系统。目前的项目中，玩家当前手持的方块类型由黑色的命令窗口输出，并未实现背包系统。背包系统要在当前界面中新增UI，需要更深层次的openGL图形学知识，所以暂未实现。

3、本项目除了代码逻辑外，一个难点是有关openGL库的图形学知识。如果直接使用游戏引擎如unity3D，可以省去图形学的基础代码，专注于游戏逻辑本身，也许能实现地更好。

### 感想与心得

总体心得：

这次课程给予各位组员全新的体验，以前的项目开发大都重视结果，不会特别在意过程中的协调和分工。但此次项目更重视MVVM模式下分工的合理性科学性，让全体组员对项目管理、设计模式有了一个良好的认识和初步的实践，包括用github进行版本控制、协作开发，软件的mvvm模式，敏捷开发流程、迭代等等，收获巨大。

郑昱笙：

​		这次项目起源于我在github上面发现的一个repo——在七天写一个简单的minecraft出来，得到组员的认可，于是着手开始尝试。开发过程中挑战和收获并存，由于能力有限，我们决定做一个简易版本，删减掉一些附加功能，整理了基础功能。由于对图形学背景知识不够熟悉，我也花费了不少时间在openGL的学习上面，但更重要的还是代码逻辑和分工协调，这影响团队项目进程和开发效率。这是我对MVVM模式开发的第一次尝试，在一轮轮迭代中获益匪浅。

尹浩霖：

​		这次project我们组做的是我的世界游戏的简略版本，首先我自学了opengl，这个过程中让我对opengl基础有了掌握，完成了计算机图形学的入门。在几轮迭代中，这些技能和知识的掌握越来越熟练。另外我对项目管理有了初步的认识，包括用github进行版本控制，与队友协作开发和软件的mvvm模式，这次的项目合作让我体会到了与以前小组合作完全不同的感受和效率，也提升了我的c++代码水平。

周寒靖：

​		在项目前期我狂补了openGL官方教程，终于补充了必备的图形学知识，为项目的打造奠定基础。之后，我们在经理最初分工的麻痹感染和混乱后，调整了协调分工模式，后面的工作都按照MVVM模式来进行，较大提高了团队效率。一次次迭代就是对知识和代码能力的一次次锤炼，我在这一过程中获益良多，看到自己和小伙伴们做出的游戏成品，有一种发自内心的自豪感。

# 参考资料

1、[https://learnopengl-cn.github.io/](https://learnopengl-cn.github.io/)

2、[https://github.com/Hopson97/MineCraft-One-Week-Challenge](https://github.com/Hopson97/MineCraft-One-Week-Challenge) 

3、[https://www.bilibili.com/video/BV1ux411H7ZE/?spm_id_from=333.788.videocard.1](https://www.bilibili.com/video/BV1ux411H7ZE/?spm_id_from=333.788.videocard.1)