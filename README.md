# farmjiTong
基于Cocos2d-x-3.17.2开发的类星露谷游戏项目. (2024年同济大学程序设计范式课程项目)
该项目是一个基于 Cocos2d-x 3.17.2 开发的类星露谷游戏，灵感来自于《星露谷物语》。游戏拥有丰富的基础功能，如具有独具一格的初始和设置界面、背景音效、多种行为及社交系统、战斗、探险、钓鱼等，为玩家带来更加丰富和沉浸式的游戏体验。
## 成员分工

| 姓名 | 学号 | 分工 |
| :---: | :---: | :---: |
| 罗力 (组长) | 2353250 | **整体项目及人物运动工作统筹** <br> 完善所有的人物动画 <br> 代码审查 <br> 项目框架搭建 <br> 实现对话框类 <br> 社交系统 <br> 战斗系统 <br> 金融系统 <br> 人物阴影 <br> 提供资源文件|
| 潘越 | 2353788 | **项目测试及场景工作统筹** <br> 实现碰撞检测 <br> 优化移动逻辑 <br> 实现视角移动 <br> 上传瓦片地图文件及材质 <br> 配套更新地图工具类函数 <br> 添加回家接口，优化切换场景接口内部实现逻辑 <br> 派生可互动对象类及传送点类 <br> 图像元素绘制 <br> 实现地图之间传送|
| 齐震罡 | 2457054 | **项目后端统筹** <br> `Corral_system` 类 <br> `Farm_system` 类 <br> `Land_system` 类 <br> `Livestock_farm_system` 类 <br> `Time_system` 类 <br> `basic_plant_and_animal_class` 类 <br> `map_system` 类 | 
| 毛韩宇 | 2353731 | **项目前端工作统筹** <br> `AudioPlayer` 类 <br> `BackpackLayer` 类 <br> `BackpackManager` 类 <br> `BagScene` 类 <br> `CoopScene` 类 <br> `EntrustScene` 类 <br> `HoverButton` 类 <br> 部分素材绘制 <br> `InitialScene` 类 <br> `Item` 类 <br> `MenuScene` 类 <br> `SettingsScene` 类 <br> `SkillScene` 类 <br> `StartupScene` 类 <br> 项目答辩 PPT 制作 |

## 成员贡献

| 姓名 | 学号 | 代码行数 | 工作量 |
| :---: | :---: | :---: | :---: |
| 罗力 (组长) | 2353250 | ** | *% |
| 潘越 | 2353788 | ** | *% |
| 齐震罡 | 2457054 | ** | *% |
| 毛韩宇 | 2353731 | ** | *% |

## 项目组成

* `/src`
项目源代码

  * `/Classes`
  类定义与类实现

  * `/Resources`
  资源文件

  * `/cocos2d`
  依赖文件

  * `/proj.win32`
  游戏程序

* `Documentation.md`
项目实现功能与项目技术细节文档

* `Project.pptx`
项目答辩汇报

## 项目开发日志

### 2024/11/20

* 确认选题
* 初步确定团队成员分工

### 2024/11/21

* Python 2.7.16 环境配置
* Cocos2d-x 3.17.2 环境配置

### 2024/11/22

* 明确团队项目代码规范
* Markdown 语言掌握
* 项目托管 GitHub [仓库]([https://github.com/linkryl/farmjiTong])

### 2024/11/23

* 学习 Cocos2d-x

### 2024/12/1

* git 工具掌握
* GitHub Desktop 工具掌握
* 明确项目 git 提交规范
* 放弃 Cocos2d-x 4.0 环境，配置 Cocos2d-x 3.17.2 环境
* 编译 Cocos2d-x 3.17.2 测试项目

### 2024/12/2

* 明确项目仓库组成
* 初步搭建项目框架

### 2024/11/22-2024/12/22
* 实现 `AppDelegate` 类
* 实现 `HoverButton` 类
* 绘制图标
* 初步实现商店功能
* 完善初始场景背景图与细节
* 实现鼠标和键盘事件监听功能
* 完善项目框架
* 初步实现 `Land_system` 类
* 初步实现 `Corral_system` 类
* 初步实现 `Livestock_farm_system` 类
* 初步实现 `Farm_system` 类
* 实现 `InitialScene` 类与交互细节
* 实现 `Time_system` 类
* 调整 `Resources 文件夹`
* 调整 `basic_plant_and_animal_class` 类
* 调整 `LocationMap` 类
* 实现 `StartupScene` 类与交互细节
* 实现 `MenuScene` 类与交互细节
* 初步实现 `map_system` 类
* 初步实现 `Player` 类
* 确定角色属性参数
* 完成角色绘制
* 初步实现 `BackpackLayer` 类
* 实现 `BackpackManager` 类
* 实现 `AudioPlayer` 类
* 绘制商店相关按钮
* 基本实现 `BagScene` 类
* 基本实现 `SettingsScene` 类与交互细节
* 实现金币系统
* 调整命名空间
* 实现 `CoopScene` 类与交互细节
* 实现 `EntrustScene` 类
* 实现 `Champion` 类
* 实现 `InitialScene` 类
* 实现 `Item` 类
* 实现 `SkillScene` 类
* 工作对接与项目仓库整合
* 实现 `SocialInfo` 类
* 实现动画效果
* 完善游戏功能性与平衡性
* 项目收尾工作

### 2024/12/21

* 完善项目自述文档 `README.md`
* [Project](Project.pptx) 制作

### 2024/12/23

* 答辩验收

## 集成开发环境

* Microsoft Visual Studio 2022

## 编译运行环境

* 本项目仅适用于x86架构

## 免责声明

本仓库包含的代码和资料仅用于个人学习和研究目的，不得用于任何商业用途。请其他用户在下载或参考本仓库内容时，严格遵守**学术诚信原则**，不得将这些资料用于任何形式的作业提交或其他可能违反学术诚信的行为。本人对因不恰当使用仓库内容导致的任何直接或间接后果不承担责任。请在使用前务必确保您的行为符合所在学校或机构的规定，以及适用的法律法规。如有任何问题，请通过[电子邮件](3167937401@qq.com)与我联系。

## 文档更新日期

2024年12月22日
