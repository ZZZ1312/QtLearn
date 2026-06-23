# 对话框

## 标准对话框

Qt提供了一些标准的对话框供使用。

### `QFileDialog` 文件对话框

| 常用静态函数名称                  | 函数功能                             |
| --------------------------------- | ------------------------------------ |
| `QString  getOpenFileName()`      | 选择打开一个文件                     |
| `QStringList getOpenFileName()`   | 选择打开多个文件                     |
| `QString getSaveFileName()`       | 选择保存一个文件                     |
| `QString getExistinggDirectory()` | 选择一个已有的目录                   |
| `QUrl getOpenFileUrl()`           | 选择打开一个文件，可选择远程网络文件 |

### `QColorDialog` 颜色对话框

| 常用静态函数名称    | 函数功能 |
| ------------------- | -------- |
| `QColor getColor()` | 选择颜色 |

### `QFontDialog` 字体对话框

| 常用静态函数名称  | 函数功能 |
| ----------------- | -------- |
| `QFont getFont()` | 选择字体 |

### `QInputDialog` 输入对话框

| 常用静态函数名称             | 函数功能                   |
| ---------------------------- | -------------------------- |
| `QString getText()`          | 输入单行文字               |
| `int getInt()`               | 输入整数                   |
| `double getDouble()`         | 输入浮点数                 |
| `QString getItem()`          | 从一个下拉列表框中选择输入 |
| `QString getMultiLineText()` | 输入多行字符串             |

`QMessageBox` 消息框

| 常用静态函数名称               | 函数功能                   |
| ------------------------------ | -------------------------- |
| `StandardButton information()` | 信息提示对话框             |
| `StandardButton question()`    | 询问并获取是否确认的对话框 |
| `StandardButton warning()`     | 警告信息提示对话框         |
| `StandardBUtton cirtical()`    | 错误信息提示对话框         |
| `void about()`                 | 设置自定义信息的关于对话框 |
| `void aboutQt()`               | 关于Qt的对话框             |

`StandardBUtton` 类型是各种按钮的定义，是一个枚举值，常用的如下：

- `StandardButton:Ok`
- `StandardButton::Yes`
- `StandardButton::Cancel`
- `StandardButton::Close`

## 自定义对话框

自定义的对话框一般从 `QDialog` 继承。

> 对话框调用一般包括如下过程：
>
> 1. 创建对话框
> 2. 传递数据给对话框
> 3. 显示对话框并获取输入
> 4. 判断对话框单击按钮的返回类型
> 5. 获取对话框输入数据

### 对话框的调用方式

Qt中的对话框主要有两种调用方式：模态和非模态。

**模态**指的是，当对话框出现后，用户是否还能否操作其他窗口。

> 模态的概念和阻塞的概念是不一样的，注意区分。

#### 模态（Modal）对话框

对应函数是 `exec()`。

模态对话框的调用流程如下：

```
当前函数暂停
↓
进入对话框事件循环
↓
用户关闭对话框
↓
exec() 返回
↓
后续代码继续执行
```

> 这种调用方式会阻塞当前主线程的代码。

> 这种方式还会再创建一个属于对话框的事件循环。

#### 非模态对话框

对应函数是 `show()`。

调用流程如下：

```
show()
↓
立即返回
↓
后面的代码继续执行
↓
用户可以随时操作对话框
```

> 这种方式不会阻塞主窗口，但也无法获得返回值。

#### 特殊对话框调用

Qt中还提供了一个比较特殊的方式，对应函数是 `open()`。

这种方式会打开一个模态的对话框，但不会阻塞代码执行。

同样无法获取到返回值。

### 对话框的关闭

关闭对话框后，对话框只是被隐藏了，并没有从内存中删除。有两种方式处理。

1. **手动删除对话框的指针**

   通过 `delete` 关键字，可以手动删除掉对话框。

2. **设置对话框的属性**

   可以通过 `setAttribute` 函数，给对话框设置一个 `Qt::WA_DeleteOnClose` 属性，这样在对话框关闭后，会自动删除掉对话框。

   > 设置这个属性后，只能通过非模态方式显示对话框。

#### 非模态对话框的关闭

以非模态方式打开对话框，如果想要在对话框关闭之后，对主窗口做一些操作（例如传递一些参数），可以通过重写对话框的 `closeEvent` 事件函数，来对调用窗口做一些操作。

# MDI 应用程序设计

## 简介

MDI指多文档界面（Multi-document Interface，MDI）应用程序，通常是一个窗口，窗口中有多个小文档窗口。

### `QMdiArea` 组件

`QMdiArea` 是一个容纳多文档的组件。类似于 `QTabWidget`。

一个主窗口内部可以包含多个可独立移动、缩放、关闭的子窗口的界面。

#### 创建

通常作为主窗口的中央区域

```cpp
QMdiArea *mdiArea = new QMdiArea(this);

setCentralWidget(mdiArea);
```

#### 常用函数

**子窗口管理**

```cpp
// 添加子窗口
QMdiSubWindow *addSubWindow(QWidget *widget, Qt::WindowFlags flags = Qt::WindowFlags());
// 删除子窗口
void removeSubWindow(QWidget *widget);

// 获取所有子窗口
QList<QMdiSubWindow *> subWindowList(WindowOrder order = CreationOrder) const
/* 可以设置获取的顺序
	- CreationOrder：创建顺序。
	- StackingOrder：Z轴顺序（也就是根据在屏幕上显示的层级关系）
	- ActivationHistoryOrder：历史的激活顺序
*/

// 获取当前活动窗口
QMdiSubWindow *activeSubWindow() const;

// 设置活动窗口
void setActiveSubWindow(QMdiSubWindow *window);
```

**窗口排列**

```cpp
// 平铺
void tileSubWindows();

// 层叠
void cascadeSubWindows();

// 关闭所有窗口
void closeAllSubWindows();

// 激活下一个窗口
void activeNextSubWindow(); 

// 激活上一个窗口
void activePreviousSubWindow();
```

**显示模式**

```cpp
// 设置显示模式
void setViewMode(QMdiArea::ViewMode viewMode)
/* 支持两种模式
	- SubWindowView：多个窗口自由排列
	- TabbedView：标签页模式，类似于浏览器标签页.
*/

// 获取视图模式
ViewMode viewMode() const;
```

**标签页模式设置**

```cpp
// 允许关闭标签页
void setTabsClosable(bool closable);

// 允许移动标签页
void setTabsMovable(bool movable);

// 文档模式（更贴近浏览器标签风格）
void setDocumentMode(bool enabled);
```

**背景设置**

```cpp
// 设置背景画刷
void setBackground(const QBrush &background);

// 获取背景
QBrush background() const;
```

#### 常用信号

**当前活动窗口变化**

```cpp
void subWindowActivated(QMdiSubWindow *window);
```

#### `QMdiSubWindow` 

`QMdiSubWindow` 是 Qt 中用于实现 **MDI（Multiple Document Interface，多文档界面）子窗口** 的控件类。它通常作为 `QMdiArea` 的子窗口存在，用于在一个主窗口内部管理多个可独立操作的窗口。

`QMdiSubWindow` 本质上是一个特殊的 `QWidget`，具有独立窗口的特性，例如标题栏、边框、最小化按钮、最大化按钮和关闭按钮等。用户可以在 `QMdiArea` 中自由移动、调整大小、最大化、最小化或关闭这些子窗口。

在实际开发中，`QMdiSubWindow` 很少单独使用，通常是将一个普通的 `QWidget`（例如编辑器、表格、图像查看器等）嵌入到 `QMdiSubWindow` 中，然后交由 `QMdiArea` 统一管理。

# Splash与登录窗口

Splash 窗口指的就是应用程序在启动时显示的启动画面。有无边框、显示一个图片和软件的信息。

Splash 窗口显示时，程序在后台做一些比较耗时的启动准备工作，Splash窗口显示一段时间后自动关闭，然后软件的主窗口显示出来。

## `QSplashScreen`

Qt 中提供了 `QSplashScreen` ，可以实现无边框的功能。

还可以通过设置 `WindowFlag`，启用 `Qt::SplashScreen` 也可以实现相同的效果。

> 也可以将 `WindowFlag` 设置 `Qt::FramelessWindowHint` ，这样的窗口，没有边框，但是会在任务栏中显示标题。

