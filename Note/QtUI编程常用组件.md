# Qt UI 编程常用组件基础

## UI 设计介绍

Qt中常用的窗体基类是 `QWidget`、`QDialog` 和 `QMainWindow`。

`QWidget` 直接继承于 `QObject`，是 `QDialog` 和 `QMainWIndow` 的父类。另外还有一个 `QWindow`，它同时继承 `QObject` 和 `QSurface`。

![Qt几个窗体类的主要特点和用途](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260619233734896.png)

这些窗体类的主要特点和用途如下：

- `QWidget`：没有指定父容器时可作为独立的窗口，指定父容器后可以作为容器的内部组件。
- `QDialog`：用于设计对话框。
- `QMainWindow`：用于设计带有菜单栏、工具栏啊、状态栏的主窗口，一般以独立窗口显示。
- `QSplashScreen`：用于应用程序启动时的 splash 窗口，没有边框。
- `QMdiSubWindow`：用于为 `QMdiArea` 提供一个子窗体，用于 MDI（多文档）应用程序的设计。
- `QDesktopWindow`：具有多个显卡和多个显示器的系统具有多个桌面，该类提供用户桌面信息，如屏幕信息、每个屏幕的大小等。
- `QWindow`：通过底层的窗口系统表示一个窗口的类，一般作为一个父容器的嵌入式窗体，不作为独立窗体。

### Qt父子机制

父子机制是 Qt 对象管理的核心设计之一，它建立在 `QObject` 基础之上，用于实现：

- 对象层级管理
- 自动内存释放
- 事件传播
- 界面组件组织

几乎所有 Qt 控件都依赖这一机制。

#### 设置父子机制

在创建时，或调用 `setParent` 函数，可以形成父子关系。

```cpp
// 1. 第一种
QObject *parent = new QObject;
QObject *child = new QObjec(parent);

// 2. 第二种
QObject *parent = new QObject;
QObject *child = new QObject;

child->setParent(parent);
```

此时形成

```
QObject *parent = new QObject;
QObject *child = new QObject;

child->setParent(parent);
```

可以互相访问

```cpp
qDebug() << child->parent();

qDebug() << parent->children();
```

#### 自动内存管理

设置了父子关系后，在父对象析构时，会自动析构所有子对象。

析构顺序为先析构所有子对象，然后析构父对象。

**对象树**

Qt内部维护一颗对象树，例如：

```cpp
QMainWindow
 ├── QWidget
 │    ├── QPushButton
 │    └── QLabel
 │
 └── QStatusBar
```

如果删除根节点 `QMainWindow` ，那么整棵树会全部释放。

#### UI界面包含关系

如果给 `QWidget` 设置了父子机制。那么子组件会显示在父组件中。

子组件会跟随窗口移动、隐藏和销毁。

#### 信号槽与父子机制

如果子组件连接和父组件连接了信号，当子组件删除时，Qt会自动断开和父组件的连接。

#### 事件传播中的父子关系

例如鼠标事件：

```cpp
点击子控件
    ↓
子控件处理
    ↓
未处理
    ↓
父控件处理
```

## QWidget

### 创建右键菜单

每个从`QWidget` 继承的类都有信号 `customContextMenuRequested()` 这个信号在鼠标右键点击时发射。可以创建和运行右键快捷菜单。

```cpp
// 案例
void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
	Q_UNUSED(pos);
	QMenu *menuList = new QMenu(this); // 创建菜单
	// 添加 Actions 菜单项
	menuList->addAction(ui->actListIni);
	menuList->addAction(ui->actListClear);
	menuList->exec(QCursor::pos()); // 在鼠标光标位置显示右键快捷菜单
	delete menuList;
}
```

### 设置重要特性

#### `setAttribute` 函数

```cpp
void QWidget::setAttribute(Qt::WidgetAttribute attribute, bool on = true);
```

`Qt::WidgetAttribute` 定义了窗体的一些属性，可以打开或关闭这些属性。常用常量及意义如下。

| 常量                       | 意义                              |
| -------------------------- | --------------------------------- |
| `Qt::WA_AcceptDrops`       | 允许窗体接收拖放来的组件          |
| `Qt::WA_DeleteOnClose`     | 窗体关闭时删除自己，释放内存      |
| `Qt::WA_Hover`             | 鼠标进入或移出窗体时产生paint事件 |
| `Qt::WA_AcceptTouchEvents` | 窗体是否接受触屏事件              |

#### `setWindowFlags`函数

```cpp
void QWidget::setWindowFlags(Qt::WindowFlags type);
```

type 是枚举类型 `Qt::WindowType` 的值的组合，用于同时设置多个标记。常见常量值如下。

**表明窗体类型的常量**

| 常量               | 意义                                                         |
| ------------------ | ------------------------------------------------------------ |
| Qt::Widget         | 默认类型，如果有父窗体，就作为父窗体的子窗体，否则作为一个独立的窗口 |
| Qt::Window         | 表明这个窗体是一个窗口，通常具有窗口的边框、标题栏，而不管它是否有父窗体。 |
| Qt::Dialog         | 表明这个窗体是一个窗口，并且要显示为对话框（没有最小化最大化按钮），是 `QDialog` 类的默认类型。 |
| Qt::Popup          | 表明这个窗体是用作弹出式菜单的窗体。                         |
| `Qt::Tool`         | 表明这个窗体是 工具窗体，具有更小的标题栏和关闭按钮，通常作为工具栏的窗体。 |
| `Qt::ToolTip`      | 表明这是用于 ToolTip 消息提示的窗体                          |
| `Qt::SplashScreen` | 表明窗体是 splash 屏幕，是 `QSplashScreen` 类的默认类型      |
| `Qt::Desktop`      | 表明窗体是桌面，这是 `QDesktopWidget` 类的类型               |
| `Qt::SubWindow`    | 表明窗体是子窗体，                                           |

**控制窗体显示效果的常量**

| 常量                               | 意义                                                        |
| ---------------------------------- | ----------------------------------------------------------- |
| `Qt:::MSWindowFixedSizeDialogHint` | 在Windows平台上，使窗口具有更窄的边框，用于固定大小的对话框 |
| `Qt::FramelessWindowHint`          | 创建无边框窗口                                              |

**定制窗体外观的常量**

使用这些常量，需要先设置属性 `Qt::CustomizeWindowHint`。

| 常量                              | 意义                                                         |
| --------------------------------- | ------------------------------------------------------------ |
| `Qt::CustomizzeWindowHint`        | xxxxxxxxxx void QPerson::incAge(){    ++m_age;    emit ageChanged(m_age);}cpp |
| `Qt::WindowTitleHint`             | 窗口具有标题栏                                               |
| `Qt::WindowSystemMenuHint`        | 有窗口系统菜单                                               |
| `Qt::WindowMinimizeButtonHint`    | 有最小化按钮                                                 |
| `Qt::WindowMaximizeButtonHint`    | 有最大化按钮                                                 |
| `Qt::WindowMinMaxButtonsHint`     | 有最大化、最小化按钮                                         |
| `Qt::WindowCloseButtonHint`       | 有关闭按钮                                                   |
| `Qt::WindowContextHelpButtonHint` | 有上下文帮助按钮                                             |
| `Qt::WindowStaysOnTopHint`        | 窗口总是处于最上层                                           |
| `Qt::WindowStaysOnBottomHint`     | 窗口总是处于最下层                                           |
| `Qt::WindowTransparentForInput`   | 窗口只作为输出，不接受输入                                   |

```cpp
void QWidget::setWindowFlag(Qt::WindowFlag flag, bool on = true);
// 一次设置一个标记，可单独打开或关闭某个属性。
```

#### `setWindowState`函数

```cpp
void QWidget::setWindowState(Qt::WindowStates windowState)
```

`Qt::WindowState`  表示了窗体的状态。取值如下。

| 常量                   | 意义                                 |
| ---------------------- | ------------------------------------ |
| `Qt::WindowNoState`    | 正常状态                             |
| `Qt::WindowMinimized`  | 窗口最小化                           |
| `Qt::WindowMaximized`  | 窗口最大化                           |
| `Qt::WindowFullScreen` | 窗口填充整个屏幕，而且没有边框       |
| `Qt::WindowActive`     | 变为活动的窗口，例如可以接受键盘输入 |

#### `setWindowModality`函数

```cpp
void setWIndowModality(Qt::WindowModality windowModality);
```

`Qt::WindowModality` 是枚举值，取值如下。

| 常量                   | 意义                                           |
| ---------------------- | ---------------------------------------------- |
| `Qt::NonModal`         | 无模态，不会阻止其他窗口的输入                 |
| `Qt::WindowModal`      | 窗口对于其父窗口、所有的上级父窗口都是模态的   |
| `Qt::ApplicationModal` | 窗口对整个应用程序是模态的，阻止所有窗口的输入 |

#### `setWindowOpacity`函数

```cpp
void QWdiget::setWindowOpacity(qreal level);
```

用于设置窗口的透明度。`level` 是从 1.0 (完全不透明) 到 0.0 (完全透明）之间，默认是 1.0。

### 事件

事件（event）是由窗口系统产生的某些操作触发的特殊函数，例如鼠标操作、键盘操作等，还有窗口显示、关闭、绘制等相关的事件。`QWidget` 继承的窗口部件常用事件函数有以下几种。

- `closeEvent()`：窗口关闭事件，可以在该处做一些处理，例如询问是否关闭窗口。
- `showEvent()`：窗口显示时触发的事件。
- `paintEvent()`：窗口绘制事件。
- `mouseMoveEvent()`：鼠标移动事件。
- `mousePressEvent()`：鼠标按下事件。
- `mouseReleaseEvent()`：鼠标释放事件。
- `keyPressEvent()`：键盘按下事件。
- `keyReleaseEvent()`：键盘按键释放事件。

## QMainWindow

### 常用函数

```cpp
void setCentralWidget(QWidget *widget = nullptr);
```

设置中央控件。

`QMainWindow` 具有自己的布局，使用该函数可以让控件处于中间最大的部分。

## QAction

## QMenu

## 标签QLabel

`QLabel` 是常用的标签组件，可以显示文字，也可以设置一个图片。

### buddy机制

QLabel 的 buddy 机制本质是：QLabel 可以从文本中识别“&字母”生成 Alt+字母快捷键，当用户按下这个快捷键时，Qt 会把输入焦点自动切换到 QLabel 通过 setBuddy 指定的那个控件上。也就是说 QLabel 负责定义快捷键，buddy 控件负责接收焦点。

使用时必须满足两个条件：第一，QLabel 的文本中必须包含 & 加字母，比如 Name(&N) 或 &Name，这样才会生成 Alt+N 的快捷键；第二，必须调用 setBuddy 绑定一个目标控件，比如输入框，否则快捷键不会执行焦点跳转。

需要注意的是 && 表示显示一个普通的 &，不会生成快捷键；如果 & 后面不是字母，或者快捷键冲突，可能不会生效；buddy 机制的作用仅仅是“快捷键触发后自动 setFocus 到目标控件”，不负责执行其他逻辑。

## 单行输入框QLineEdit

`QLineEdit` 是最常用的**单行**文本编辑器。

### 常用函数

1. 文本控制
   
   ```cpp
   lineEdit->text();              // 获取文本
   lineEdit->setText("abc");      // 设置文本
   lineEdit->clear();             // 清空
   ```

2. 插入、删除、修改
   
   ```cpp
   lineEdit->insert("abc");       // 光标处插入
   lineEdit->backspace();         // 删除前一个字符
   lineEdit->del();               // 删除后一个字符
   lineEdit->selectAll();         // 全选
   lineEdit->clear();             // 清空
   ```

3. 选中文本
   
   ```cpp
   lineEdit->insert("abc");       // 光标处插入
   lineEdit->backspace();         // 删除前一个字符
   lineEdit->del();               // 删除后一个字符
   lineEdit->selectAll();         // 全选
   lineEdit->clear();             // 清空
   ```

4. 显示模式
   
   ```cpp
   lineEdit->setEchoMode(QLineEdit::Password);
   ```
   
   - Normal（正常显示）
   - Password（隐藏）
   - NoEcho（不显示）
   - PasswordEchoOnEdit（编辑时显示）

5. 占位提示
   
   占位提示是在输入框中没有输入内容时，显示的内容
   
   ```cpp
   lineEdit->setPlaceholderText("请输入用户名");
   ```

6. 清除按钮
   
   输入框右侧出现 “X” 按钮
   
   ```cpp
   lineEdit->setPlaceholderText("请输入用户名");
   ```

### 常见信号

1. 文本变化类

```cpp
void textChanged(const QString &text); // 文本发生变化时触发（用户输入 + 代码 setText 都会触发）  
void textEdited(const QString &text); // 仅用户编辑时触发（不包括 setText 等代码修改）
```

2. 输入完成类  

```cpp
void editingFinished(); // 回车或失去焦点时触发（表示编辑结束）  
void returnPressed(); // 按下 Enter 键时触发（常用于搜索/提交）
```

3. 选择相关类  

```cpp
void selectionChanged(); // 文本选中状态发生变化时触发
```

4. 光标变化类  

```cpp
void cursorPositionChanged(int oldPos, int newPos); // 光标位置发生变化时触发
```

## 数字输入框QSpinBox

`QSpinBox` 用于整数的显示和输入，一般显示十进制数，也可以显示二进制、十六进制的数，还可以在显示框中增加前缀或后缀。

`QDoubleSpinBox` 用于浮点数的显示和输入，可以设置显示小数位数。

### 常用函数

1. 数值设置类  

```cpp
void setValue(int val); // 设置当前数值  
int value() const; // 获取当前数值  
void setRange(int min, int max); // 设置取值范围（最常用）  
void setMinimum(int min); // 设置最小值  
void setMaximum(int max); // 设置最大值
```

2. 步进控制类  

```cpp
void setSingleStep(int step); // 设置每次增减的步长  
int singleStep() const; // 获取步长
```

3. 显示与格式类  

```cpp
void setPrefix(const QString &prefix); // 设置前缀（如 "$"）  
void setSuffix(const QString &suffix); // 设置后缀（如 " kg"）
```

4. 编辑控制类  

```cpp
void setWrapping(bool on); // 是否允许循环（到最大回到最小）  
void setReadOnly(bool ro); // 是否只读
```

### 常用信号

1. 数值变化类  

```cpp
void valueChanged(int i); // 数值发生变化时触发（最常用）  
void textChanged(const QString &text); // 显示文本变化时触发（含前后缀）
```

2. 编辑完成类  

```cpp
void editingFinished(); // 用户编辑完成（回车或失焦时触发）
```

## 滑动条组件QAbstractSlider

滑动滚动条是标尺型组件，可以通过滑动来改变值。

`QAbstractSlider` 是 `QSlider`、`QScrollBar`、`Qdial` 都是从 `QAbstractSlider` 继承而来，有一些共有的属性。

`QAbstractSlider` 的主要属性包括以下几种：

- minimun、maximum：设置输入范围的最小值和最大值。

- singleStep：单步长，拖动标尺上的滑块，或按下左/右光标时的最小变化数值。

- pageStep：在Slider上输入焦点，按pgUp或PgDn键时变化的数值。

- value：组件当前的值，限定在minximum和maximum之间。

- sliderPosition：滑块的位置，若tracking属性设置为true，则sliderPoistion就等于value。

- tracking：sliderPosition是否等于value，如果tracking=true，改变value时也改变sliderPosition。

- orientation：Slider的方向，可以设置为水平或垂直。取值如下：
  
  - Qt::Horizontal：水平方向
  
  - Qt::Vetrial 垂直方向

- invertedAppearance：显示方向是否反向，当该属性为false时，水平的Slider由左向右数值增大，否则反过来（垂直的默认是上小下大）。

- invertControls：反向控制键，若该属性为true，则按PgUp或PgDn按键时，调整数值的反向相反。

### QSlider

`QSlider` 是滑动条，通过滑动来设置数值，可用于数值输入。

`QSlider` 的专有属性如下：

- tickPosition：标尺刻度的显示位置，类型为`QSlider::TickPosition`，取值如下：
  
  - `QSlider::NoTicks`：不显示刻度
  
  - `QSlider::TicksBothSides`：标尺两侧都显示刻度。
  
  - `QSlider::TicksAbove`：标尺上方显示刻度（水平标尺）
  
  - `QSlider::TicksBelow`：标尺下方显示刻度（水平标尺）
  
  - `QSlider::TicksLeft`：标尺左侧显示刻度（垂直标尺）
  
  - `QSlider::TocksRight`：标尺右侧显示刻度（垂直标尺）

- tickInterval：标尺刻度的间隔，若设置为0，会在singleStep和pageStep之间自动选择。

### QScrollBar

`QScrollBar` 从 `QAbstractSlider` 继承而来的，具有 `QAbstraceSlider` 的基本属性，没有专有属性。

### QDial

`QDial` 是仪表盘式的组件，通过旋转表盘获得输入值。

特有属性如下：

- notchesVisible：表盘的小刻度是否可见。

- notchTarget：表盘刻度间的间隔像素值。

### 常用函数

```cpp
void triggerAction(SliderAction action); // 触发一个滑动动作（如单步加减、页步等）  
void setSliderDown(bool down); // 设置滑块是否被按下（拖动状态）
```

### 常用信号

```cpp
void valueChanged(int value); // 当前值改变时触发（最常用）  
void sliderPressed(); // 按下滑块时触发  
void sliderReleased(); // 释放滑块时触发  
void sliderMoved(int position); // 拖动滑块时触发（仅拖动过程）  
void actionTriggered(int action); // 执行滑动动作时触发（如键盘、滚轮）  
void rangeChanged(int min, int max); // 范围变化时触发
```

## 进度条 QProgressBar

`QProgressBar` 的父类是 `QWidget`，一般用于进度显示。

### 常用属性

- minimum、maximum：最大值和最小值

- value：当前值，可以设定或读取当前值。

- textVisible：是否显示文字，文字一般是百分比表示的进度。

- orientation：可以设置为水平或垂直方向。

- fomat：显示文字的格式，可选项如下：
  
  - `%p%`：显示百分比
  
  - `%v`：显示当前值
  
  - `%m`：显示总步数
  
  默认为`%p%`。

## LCD显示数字组件QLCDNumber

`QLCDNumber` 是模拟LCD显示数字的组件，可以显示整数或小数。

主要属性如下：

- digitCount：显示数的位数，如果是小数，小数点也算一个数位。

- smallDecimalPoint：是否有小数点，如果有小数点，就可以显示小数

- mode：数的显示进制，通过调用函数`setDecMode()`、`sttBinMode()`、`setOctMode()`、`setHexMode()` 可以设置为十进制、二进制、八进制、十六进制。

- value：返回显示值，浮点数。若设置为显示整数，会自动四舍五入后得到整数设置为intValue的值，如果smallDecimalPoint=true，设置value时可以显示小数，但是数的位数不能超过digitCount。

- `intValue`：返回显示的整数值。

> 例如，若smallDecimalPoint=true，digitCount=3，设置value=2.36，则界面上LCDNumber显示为2.4，若设置value=1456.25，则LCDNumber组件上显示145。

## 时间编辑组件QTimeEdit

`QTimeEdit` 用于编辑和显示时间。

### 常用函数

1. 时间设置类  

```cpp
void setTime(const QTime &time); // 设置当前时间  
void setMinimumTime(const QTime &min); // 设置最小时间  
void setMaximumTime(const QTime &max); // 设置最大时间  
void setTimeRange(const QTime &min, const QTime &max); // 设置时间范围  
void setDisplayFormat(const QString &format); // 设置显示格式（如 "HH:mm:ss"）  
void setCalendarPopup(bool enable); // 是否启用日历弹出（对 QDateTimeEdit 更常用）
```

2. 状态获取类  

```cpp
QTime time() const; // 获取当前时间  
QTime minimumTime() const; // 获取最小时间  
QTime maximumTime() const; // 获取最大时间  
QString displayFormat() const; // 获取显示格式
```

3. 步进控制类  

```cpp
void setSingleStep(const QTime &step); // 设置步进值（如每次增加1分钟）  
QTime singleStep() const; // 获取步进值
```

4. 编辑相关类  

```cpp
void setReadOnly(bool enable); // 设置是否只读  
void setButtonSymbols(QAbstractSpinBox::ButtonSymbols bs); // 设置按钮样式（上下箭头等）  
void setAccelerated(bool on); // 是否启用加速（长按加快变化）  
void setWrapping(bool on); // 是否允许循环（如23:59 → 00:00）
```

### 常用信号

```cpp
void timeChanged(const QTime &time); // 时间变化时触发（最常用）  
void editingFinished(); // 编辑完成（失去焦点或按回车）  
void userTimeChanged(const QTime &time); // 用户修改时间时触发（Qt6 引入，更精确区分用户操作）
```

>  补充说明  
> QTimeEdit 继承自 QDateTimeEdit，本质是“只显示时间”的日期时间编辑器  
> // 支持格式示例：  
> // "HH:mm" → 23:59  
> // "hh:mm AP" → 11:59 PM  
> // "HH:mm:ss" → 23:59:59

## 日期编辑组件QDateEdit

`QDateEdit` 用于编辑和显示日期。

### 常用函数

1. 日期设置类  

```cpp
void setDate(const QDate &date); // 设置当前日期  
void setMinimumDate(const QDate &min); // 设置最小日期  
void setMaximumDate(const QDate &max); // 设置最大日期  
void setDateRange(const QDate &min, const QDate &max); // 同时设置最小和最大日期  
void setDisplayFormat(const QString &format); // 设置显示格式（如 "yyyy-MM-dd"）  
void setCalendarPopup(bool enable); // 是否启用日历弹出选择
```

2. 状态获取类  

```cpp
QDate date() const; // 获取当前日期  
QDate minimumDate() const; // 获取最小日期  
QDate maximumDate() const; // 获取最大日期  
QString displayFormat() const; // 获取显示格式  
bool calendarPopup() const; // 是否启用了日历弹出
```

3. 步进控制类  

```cpp
void setSingleStep(int days); // 设置步进（单位：天）  
int singleStep() const; // 获取步进天数
```

4. 编辑控制类  

```cpp
void setReadOnly(bool enable); // 设置是否只读  
void setButtonSymbols(QAbstractSpinBox::ButtonSymbols bs); // 设置按钮样式  
void setAccelerated(bool on); // 是否启用加速（长按加速变化）  
void setWrapping(bool on); // 是否允许循环（如月底→月初）
```

### 常用信号

```cpp
void dateChanged(const QDate &date); // 日期变化时触发（最常用）  
void userDateChanged(const QDate &date); // 用户手动修改日期时触发（Qt6）  
void editingFinished(); // 编辑完成（失去焦点或按回车）
```

> 补充说明  
> // QDateEdit 继承自 QDateTimeEdit，本质是“只处理日期”的编辑控件  
> // 常见格式示例：  
> // "yyyy-MM-dd" → 2026-04-17  
> // "dd/MM/yyyy" → 17/04/2026  
> // "yyyy年MM月dd日" → 2026年04月17日

## QDateTimeEdit

### 常用函数

1. 日期时间设置类  

```cpp
void setDateTime(const QDateTime &dt); // 设置当前日期时间  
void setDate(const QDate &date); // 设置日期部分  
void setTime(const QTime &time); // 设置时间部分  
void setMinimumDateTime(const QDateTime &min); // 设置最小日期时间  
void setMaximumDateTime(const QDateTime &max); // 设置最大日期时间  
void setDateTimeRange(const QDateTime &min, const QDateTime &max); // 设置日期时间范围  
void setDisplayFormat(const QString &format); // 设置显示格式（如 "yyyy-MM-dd HH:mm:ss"）  
void setCalendarPopup(bool enable); // 是否启用日历弹出选择
```

2. 状态获取类

```cpp
QDateTime dateTime() const; // 获取当前日期时间  
QDate date() const; // 获取日期部分  
QTime time() const; // 获取时间部分  
QDateTime minimumDateTime() const; // 获取最小日期时间  
QDateTime maximumDateTime() const; // 获取最大日期时间  
QString displayFormat() const; // 获取显示格式  
bool calendarPopup() const; // 是否启用了日历弹出
```

3. 步进控制类  

```cpp
void setSingleStep(const QTime &step); // 设置步进（时间部分，如每次+1分钟）  
QTime singleStep() const; // 获取步进值
```

4. 编辑控制类

```cpp
void setReadOnly(bool enable); // 设置是否只读  
void setButtonSymbols(QAbstractSpinBox::ButtonSymbols bs); // 设置按钮样式  
void setAccelerated(bool on); // 是否启用加速（长按加速变化）  
void setWrapping(bool on); // 是否允许循环（如时间到23:59→00:00）
```

### 常用信号

```cpp
void dateTimeChanged(const QDateTime &datetime); // 日期时间变化时触发（最常用）  
void dateChanged(const QDate &date); // 日期部分变化时触发  
void timeChanged(const QTime &time); // 时间部分变化时触发  
void editingFinished(); // 编辑完成（失去焦点或按回车）
```

> 补充说明  
> // QDateTimeEdit 是 QDateEdit 和 QTimeEdit 的基类，支持同时编辑日期 + 时间  
> // 常见格式示例：  
> // "yyyy-MM-dd HH:mm:ss" → 2026-04-17 18:30:00  
> // "dd/MM/yyyy hh:mm AP" → 17/04/2026 06:30 PM  
> // "yyyy年MM月dd日 HH时mm分" → 2026年04月17日 18时30分、

## QComboBox

`QComboBox` 时下拉列表框组件，提供一个下拉列表共用户选择，也可以当作一个`QLineEdit` 用作用户输入。

除了显示可下拉列表外，每个项（Item，或称列表项）还可以关联一个`QVariant`类型的变量，用于存储一些不可见的数据。

可以在Qt Designer中双击`QComboBox`，会出现列表项编辑器，可以在该编辑器中给`QComboBox`添加简单项，还可以为每一项设置简单图标。

### 用法

1. 添加简单项

```cpp
// 添加带图标的简单项
QIcon icon;
icon.addFile(":/images/icons/aim.icon");
comboBox->clear(); // 清空列表
comboBox->addItem(icon, QString::asprintf("Item 1"));
```

```cpp
// 添加纯文字的项
QStringList strList;
strList << "北京" << "上海" << "天津" << "河北省" << "山东省";
comboBox->addItems(strList);
```

2. 添加具有用户数据的
   
   `QComboBox::addItem()` 函数的两种参数的原型定义如下，不论是哪个`addItem()`函数，都有一个可选的`QVariant`类型的参数userData，这个变量存储用户定义数据。

```cpp
void addItem(const QString &test, const QVariant &userData = QVariant());
void addItem(const Icon &icon, const QString &text, const QVariant &userData = Qvariant());
```

3. 访问列表项
   
   `QComboBox` 存储的项是一个列表，可以通过索引访问某个项。访问项的一些函数主要有以下几种。
   
   - `int currentIndex()`：返回当前项的序号，第一个项的序号为0。
   
   - `QString currentText()`：返回当前项的文字。
   
   - `QVariant currentData(int role = Qt::UserRole)`：返回当前项的关联数据，数据的缺省角色为`role = Qt::UserRole`。
   
   - `QString itemText(int index)`：返回指定索引号的项的文字
   
   - `QVariant itemData(int index, int role = Qt::UserRole)`：返回指定索引号的项的关联数据。
   
   - `int count()`：返回项的个数。

### 常用信号

`QComboBox` 组件上选择项发生变化时，会发射如下两个信号。

```cpp
void currentIndexChanged(int index);
void currentIndexChanged(const QString &text);
```

如果`QComboBox`可以输入时，用户输入了内容后，会发射以下的信号：

```cpp
void editTextChanged(const QString &text);
```

## QPlainText

`QPlainText` 是一个多行文本编辑器，用于显示和编辑多行简单文本。

### 常用函数

1. 添加一行字符串

```cpp
void appendPlainText(const QString &text);
```

2. 将全部文字内容输出为一个字符串

```cpp
QString QPlainTextEdit::toPlainText() const;
```

3. 逐行读取文字内容
   
   `QPlainTextEdit` 的文字内容以`QTextDocument`类型存储，函数`document()` 返回这个对象的指针。
   
   `QTextDocument` 是内存中的文本对象，以文本块的方式存储，一个文本块就是一个段落以回车符结束。
   
   `QTextDocument` 提供以下函数实现对文本内容的存取：
   
   - `int blockCount()`：获取文本块数。
   
   - `QTextBlock findBlockByNumber(int blockNumber)`：读取某一个文本块，序号从0开始，到`blockCount() - 1`结束。
   
   一个document有多个`QTextBlock`，从document中读取出的一个文本快类型为`QTextBlock`，通过`QTextBlock::text()`函数可以获取其纯文本文字。

## QToolButton

`QToolButton` 有一个 `setDefaultAction()` h桉树，可以使其与一个 Action 关联。按钮的文字、图标、ToolTip 都将自动设置为与其关联的 Action 一直。

> 单击一个 `QToolButton` 就是执行 Action 的槽函数，与工具栏上的按钮一样。

`QToolButton` 有一个 `setMenu()` 函数，可以为其设置一个下拉式菜单。

### 常用函数

1. 关联`QAction`

   原型函数：

   ```c++
   void QToolButton::setDefaultAction(QAction *actiono);
   ```

   使用改函数设置一个Action后，将自动获取Action的文字、图标、ToolTip等属性。

2. 设计下拉菜单

   可以为`QToolButton`设置一个下拉菜单。

   用到了以下函数:

   ```c++
   void QToolButton::setPopupMode(QToolButton::MenuButtonPopup);
   ```

   参数为一个枚举量，可选项如下：

   - `QToolButton::DelayedPopup`：**延时弹出**，按住按钮一会儿才会弹出菜单。
   - `QToolButton::MenuButtonPopup`：**菜单按钮**，按钮右侧显示一个小箭头，点击箭头弹出菜单，点击按钮触发常规点击。
   - `QToolButton::InstantPopup`：**立即弹出**，点击按钮的任何地方都会直接弹出菜单，不触发普通的 `clicked()` 信号。

   ```c++
   void QToolButton::setMenu(QMenu *menu);
   ```

   为按钮创建下拉菜单对象

   ```c++
   // 案例
   QMenu *menu = new QMenu(this);
   menu->addAction(ui->actionSelALL);
   menu->addAction(ui->actionSelNone);
   menu->addAction(ui->actSelNone);
   
   ui->tBtnSelectItem->setMenu(menu);
   ```

3. 设置按钮样式

   ```c++
   void QToolButton::setToolButtonStyle(Qt::ToolButtonBesideIcon);
   ```

   可选项如下：

   - `Qt::ToolButtonIconOnly`：仅显示图标。这是默认值，不显示文字，即使设置了`setText`。
   - `Qt::ToolButtonTextOnly`：仅显示文字。
   - `Qt::ToolButtonTextBesideIcon`：文字在图标旁边（水平排列）。通常图标在左，文字在右。
   - `Qt::ToolButtonTextUnderIcon`：文字在图标下方。
   - `Qt::ToolButtonFollowStyle`：跟随系统风格，根据当前操作系统桌面环境的默认设置来设定。

# Qt UI 编程常用容器组件

## QToolBox

`QToolBox` 是一个多组工具箱，可以有多个组。每个组相当于一个页面。可以理解为一个 **带折叠页的多页面组件**。特点如下：

- 多个页面（page）

- 每个页面有一个标题

- 一次只显示一个页面内容。

- 点击标题可切换页面

- 可以防止任何界面组件，并设置布局

> 在页面中，需要注意布局的排列方式，如果使用了水平布局（Horizontal Layout），则所有的按键会自动向左靠齐，使用网格布局（Grid Layout），自动居中

### 常用函数

#### 页面管理

1. 添加一个页面。

```cpp
int addItem(QWidget *widget, const QString &text);
```

2. 指定位置插入页面

```cpp
int insertItem(int index, QWidget *widget, const QString &text);
```

3. 删除页面

```cpp
void removeItem(int index);
```

#### 页面访问

1. 获取某个页面

```cpp
QWidget *widget(int index);
```

> 页面索引从 0 开始。

2. 获取页面索引

```cpp
int indexOf(QWidget *widget);
```

3. 页面数量

```cpp
int count() const;
```

#### 当前页面控制

1. 设置当前页面为第几个页面

```cpp
void setCurrentIndex(int index);
```

2. 当前页面的索引

```cpp
int currentIndex() const;
```

#### 页面控制

1. 设置/获取页面标题

```cpp
void setItemText(int index, const QString &text);

QString itemText(int index) const;
```

2. 设置页面标题

```cpp
void currentChanged(int index);
```

### 常用信号

1. 当前页面改变

```cpp
void currentChanged(int index);
```

## QTabWidget

`QTabWidget` 是一个多页面容器，效果类似浏览器的标签页。是多页面容器+标签栏。

标签索引从 0 开始。

### 常用函数

#### 页面管理

1. 添加页面

```cpp
int addTab(QWidget *widget, const QString &label);
```

2. 插入页面

```cpp
int insertTabt(int index, QWidget *widget, const QString &label);
```

3. 删除页面

```cpp
void removeTab(int index);
```

#### 页面访问

1. 获取页面

```cpp
QWidget *widget(int index) const;
```

2. 获取指定页面的索引

```cpp
int indexOf(QWidget *widget) const;
```

> 如果不存在返回 -1

3. 页面数量

```cpp
int count() const;
```

#### 当前页面控制

1. 切换当前显示的页面

```cpp
void setCurrentIndex(int index);
```

2. 获取当前的页面

```cpp
QWidget *currentWidget() const;
```

#### 标签设置

1. 设置标签文本

```cpp
void setTabText(int index, const QString &text);
```

2. 设置标签图标

```cpp
void setTabIcon(int index, const QIcon &icon);
```

3. 设置标签提示

```cpp
void setTabToolTip(int index, const QString &tip);
```

#### 外观控制

1. 设置标签位置

```cpp
void setTabPosition(QTabWidget::TabPosition position);
```

可选参数：

- `QTabWidget::North`（上）

- `QTabWidget::South`（下）

- `QTabWidget::West`（左）

- `QTabWidget::East`（右）
2. 是否可关闭标签

```cpp
void setTabClosable(bool closable);
```

3. 是否可移动biaoqian

```cpp
void setMovable(bool movable);
```

### 常用信号

1. 当前页面改变

```cpp
void currentChanged(int index);
```

2. 标签关闭请求

```cpp
void tabCloseRequested(int index);
```

> 点击标签的关闭按钮时触发（需要开启 closabel)

## QDockWidget

`QDockWidget` 是一个可停靠/可浮动的工具面板。通常配合 `QMainWindow` 使用。实现：

- 停靠在主窗口四周（上下左右）

- 拖动重新停靠位置

- 脱离主窗口变成独立浮动窗口

- 显示/隐藏

### 常用函数

1. 内容设置

```cpp
void setWidget(QWidget *widget); // 设置内部组件，widget：要放入 Dock 中的实际内容组件

QWidget *widget() const; // 获取内容
```

2. 停靠区域控制

```cpp
void setAllowedAreas(Qt::DockWidgetAreas areas); // 设置允许停靠的位置。
/*
 areas 可选项如下：
 Qt::LeftDockWidgetArea 左侧停靠
 Qt::RightDockWidgetArea 右侧停靠
 Qt::TopDockWidgetArea 上侧停靠
 Qt::BottomDockWidgetArea 下侧停靠

 areas 是 flag类型，可以通过 | 组合。例如：Qt::LeftDockWigetArea | Qt::RightDockWidgetArea 代表只允许左右停靠

 Qt::AllDockWidgetArea 允许停靠在任意位置，默认值
 Qt::NoDockWidgetArea 不允许停靠在任何位置
 以上两个不要与上下左右选项混合使用
*/


void setFloatin(bool floating); // 设置是否浮动

void isFloating(); // 判断当前是否正在浮动
```

3. 标题与显示

```cpp
void setWindowTitle(const QString &title); // 设置标题

void setFeatures(QDockWidget::DockWidgetFeatures features); // 设置是否可关闭/移动
/*
 features 可选项如下：
 QDockWidget::DockWidgetClosable
 QDockWidget::DockWidgetMovable
 QDockWidget::DockWidgetFloatable
*/

void show(); // 显示

void hide(); // 隐藏
```

### 常用信号

```cpp
void topLevelChanged(bool topLevel); // 浮动状态改变,topLevel 为 true 代表变为浮动窗口

void visibilityChanged(bool visible); // 可见性发生变化

void dockLocationChanged(Qt::DockWidgetArea area); // 停靠区域发生变化
```

# 常用简化容器类

## QListWidget

`QListWidget` 是 Qt 中一个基于项的列表控件，用于以列表形式展示一组数据。

> `QListWidget` 是对 `QListView` + `QAbstractItemModel` 的封装。适合中小规模数据展示

特点：

- 每个元素是一个 `QListWidgetItem`

- 组件负责管理数据（不需要自己写Model）

- 支持文本、图标、自定义组件等

### 常用函数

1. 项目管理

```cpp
void addItem(const QString &label); // 添加一个只有文字的项目

void addItem(QListWidgetItem *item); // 添加一个ListWidget Item

void insertItem(int row, const QString &label); // 插入一个简单的只有文字的项目


QListWidgetItem *takeItem(int row); // 从列表中删除项目
/* 只会从列表中移除该项，不会自动 delete，需要自己释放 */

QListWidgetItem *item(int row) const; // 获取项目

int count() const; // 获取到所有Item的数量

void clear(); // 清空列表
```

2. 当前项操作

```cpp
QListWidgetItem *currentItem() const; // 获取到当前选中的 Item

void setCurrentItem(QListItemItem *item); // 设置当前选中的 Item

int currentRow() const; // 当前选中的 Item 的行数

void setCurrentRow(int row); // 设置当前选中的 item 的行数
```

3. 查找

```cpp
QList<QListWidgetItem*> findItems(const QString &text, Qt::MatchFlags flags); 
// 根据 text 找到对应的 Item
/*
   Qt::MatchFlags 是设置匹配模式，可选项如下：

*/
```

4. 排序

```cpp
void sortItems(Qt::SortOrder order = Qt::AccendingOrder); // 按照指定的方式对 Items 进行排序
/*
   Qt::SortOrder 是排序规则，可选项如下：

*/
```

5. 选择模式

```cpp
void setSelectionMode(QAbstractItemView::SelectionMode mode);
/*
   选择模式：
   - SingleSelection ： 单选
   - MultiSelection ：多选
   - ExtendedSelection : Shift/Ctrl 多选
*/
```

### 常用信号

```cpp
void itemClicked(QListWidgetItem *item); // 单击项
void itemDoubleClicked(QListWidgetItem *item); // 双击项

void currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous); // 当前项变化，
void currentRowChanged(int currentRow); // 当前项变化，但是信号传递的是行数

void itemSelectioinChanged(); // 选择变化

void itemChanged(QListWIdgetItem *item); // 项的内容发生变化
```

### QListWidgetItem 介绍

`QListWidgetItem` 是 Qt 中配合 `QListWidget` 使用的 **列表项对象**，代表列表中的“每一行”。

> 可以理解为：`QListWidget` 中每个元素的数据 + 显示属性的载体

每个 item 可以包含：

- 文本

- 图标

- 数据（隐藏数据）

- 状态（选中/勾选/禁用等）

`QListWidgetItem` 最重要的属性是 flags，该属性控制着该Item的很多功能，如是否可选中、是否可编辑、是否可拖动、是否可勾选等等。

#### 常用函数

1. 构造函数

```cpp
QListWidgetItem();

QListWidgetItem(const QString &text); // 传入显示的文本

QListWidgetItem(const QIcon &icon, const QString &text); // 传入图标和文本

QListWidgetItem(QListWidget *parent); // 设置默认父List

QListWidgetItem(const QString &text, QListWidget *parent);
```

2. 其他函数

```cpp
void setText(const QString &text);  // 设置/获取文本
QString text() const;

void setIcon(const QIcon &icon);  // 设置/获取图标
QIcon icon() const;

void setData(int role, const QVariant &value); // 设置/获取数据
QVariant data(int role) const;

void setFont(const QFont &font); // 设置/获取字体
QFont font(); 

void setForeground(const QBrush &brush);  // 设置/获取字体颜色
QBrush foreground();

void setBackground(const QBrush &brush); // 设置/获取字体颜色
void background(); 

void setSizeHint(const QSize &size); // 自定义 Item 高度

void setHidden(bool hide); // 设置隐藏/显示
bool isHidden() const; // 获取是否隐藏
```

3. 设置编辑数据的控件

默认情况下，`QListWidgetItem` 设置了支持编辑后，双击会触发一个编辑行为，默认的编辑控件为 `LineEdit` 功能比较简单。

可以在 Item 中放置一个编辑控件，自定义编辑时展示的控件样式。

```cpp
// 案例

QListWidgetItem *item = new QListWidgetItem(listWidget);

QWidget *widget = new QWidget();

QHBoxLayout *layout = new QHBoxLayout(widget);
layout->setContentsMarins(5, 5, 5, 5);

QLineEdit *edit = new QLineEdit;
QPushButton *btn = new QPushButton("OK");

layout->addWidget(edit);
layout->addWidget(btn);

item->setSizeHint(widget->sizeHint()); // 一定要设置尺寸，否则UI会显示不正常

listWidget->addItem(item);
listWidget->setItemWidget(item, widget);

// 添加完成后，需要自己处理数据的同步
connect(edit, &QLineEdit::textChanged, listWidget, [item](const QString &text){
   item->setData(Qt::UserRole, text);
})
```

4. 行为控制

   `QListWidgetItem` 的 `flags` 属性用来控制每个 item 的行为能力，比如：

   - 能否选中

   - 能否编辑

   - 能否拖拽

   - 能否勾选

   基本用法：

   ```cpp
   Qt::ItemFlags flags(); // 获取 flags
   void setFlags(QtItemFlags);
   /*  
   flags 是枚举值，可以组合使用，例如：
   Qt::ItemIsSelectable | Qt::ItemIsEnabled
   */
   ```

   常用 `flags` 如下：

   - `Qt::ItemIsSelectable`：可以选择

   - `Qt::ItemIsEnabled`：是否启用（不启用则显示灰色）

   - `Qt::ItemIsEditable`：可以编辑

   - `Qt::ItemIsUserCheckable`：允许显示复选框

     设置该选项后，可以通过 `CheckState` 来获取到选中状态

   - `Qt::itemIsDragEnabled`：可以拖动

   - `Qt::ItemIsDropEnabled`：可以作为放置目标

   - `Qt::ItemIsAutoTristate`：常用于树结构

5. Role 用于描述一个 item 的不同“维度的数据”。每个Role对应一个 `QVariant`。

   > Qt内部的实现相当于：`QMap<int, QVariant>`

   最常用的 role 如下：

   - `Qt::DisplayRole`：显示的文本

   - `Qt::DecorationRole`：图标

   - `Qt::EditRole`：编辑数据（通常和 DisplayRole 显示的数据一样）

   - `Qt::CheckStateRole`：复选框

   - `Qt::ToolTipRole`：提示文字

   - `Qt::ForegroundRole`：字体颜色

   - `Qt::BackgroundRole`：背景

   - `Qt::UserRole`：用户数据，用来存自己的业务数据。

   ```cpp
   // 使用方式
   item->setData(Qt::UserRole, 1001); // ID
   item->setData(Qt::UserRole + 1, "type");
   ```

## QTreeWidget

`QTreeWidget` 是 Qt 中一个基于项（Item-Based）的树形控件，用于以层级结构（父节点 / 子节点）展示数据。

> `QTreeWidget` 是对 `QTreeView` + `QAbstractItemModel` 的封装，适合中小规模树状数据展示。

特点：

- 每个节点是一个 `QTreeWidgetItem`
- 支持无限层级的父子结构
- 支持多列显示
- 支持图标、复选框、自定义组件等
- 不需要自己实现 Model

典型应用场景：

- 文件目录树
- 工程资源管理器
- 配置树
- 组织架构图

------

### 常用函数

#### 1. 节点管理

```
void addTopLevelItem(QTreeWidgetItem *item); 
// 添加顶层节点

void insertTopLevelItem(int index, QTreeWidgetItem *item);
// 插入顶层节点

QTreeWidgetItem *takeTopLevelItem(int index);
// 移除顶层节点（不会自动 delete）

QTreeWidgetItem *topLevelItem(int index) const;
// 获取顶层节点

int topLevelItemCount() const;
// 获取顶层节点数量

void clear();
// 清空整个树
```

------

#### 2. 当前节点操作

```
QTreeWidgetItem *currentItem() const;
// 获取当前选中的节点

void setCurrentItem(QTreeWidgetItem *item);
// 设置当前选中的节点

void setCurrentItem(QTreeWidgetItem *item, int column);
// 设置当前选中的节点及列

QTreeWidgetItem *itemAt(const QPoint &p) const;
// 获取指定位置对应的节点
```

------

#### 3. 展开与折叠

```
void expandItem(QTreeWidgetItem *item);
// 展开节点

void collapseItem(QTreeWidgetItem *item);
// 折叠节点

void expandAll();
// 展开所有节点

void collapseAll();
// 折叠所有节点

bool isItemExpanded(QTreeWidgetItem *item) const;
// 判断节点是否展开
```

------

#### 4. 列管理

```
void setColumnCount(int columns);
// 设置列数

int columnCount() const;
// 获取列数

void setHeaderLabel(const QString &label);
// 设置单列表头

void setHeaderLabels(const QStringList &labels);
// 设置多列表头
```

例如：

```
treeWidget->setColumnCount(3);

treeWidget->setHeaderLabels({
    "名称",
    "类型",
    "大小"
});
```

------

#### 5. 查找

```
QList<QTreeWidgetItem *> findItems(
    const QString &text,
    Qt::MatchFlags flags,
    int column = 0
);
// 查找符合条件的节点
```

例如：

```
auto items = treeWidget->findItems(
    "Qt",
    Qt::MatchContains | Qt::MatchRecursive
);
```

常用匹配模式：

```
Qt::MatchExactly
Qt::MatchContains
Qt::MatchStartsWith
Qt::MatchEndsWith
Qt::MatchRecursive
```

------

#### 6. 选择模式

```
void setSelectionMode(
    QAbstractItemView::SelectionMode mode
);
```

常见模式：

```
SingleSelection
MultiSelection
ExtendedSelection
NoSelection
```

------

#### 常用信号

```
void itemClicked(
    QTreeWidgetItem *item,
    int column
);
// 单击节点

void itemDoubleClicked(
    QTreeWidgetItem *item,
    int column
);
// 双击节点

void itemChanged(
    QTreeWidgetItem *item,
    int column
);
// 节点数据变化

void currentItemChanged(
    QTreeWidgetItem *current,
    QTreeWidgetItem *previous
);
// 当前节点变化

void itemExpanded(
    QTreeWidgetItem *item
);
// 节点展开

void itemCollapsed(
    QTreeWidgetItem *item
);
// 节点折叠

void itemSelectionChanged();
// 选择变化
```

------

### QTreeWidgetItem 介绍

`QTreeWidgetItem` 是 Qt 中配合 `QTreeWidget` 使用的树节点对象。

> 可以理解为：树中的每一个节点（Node）。

每个节点可以包含：

- 文本
- 图标
- 多列数据
- 用户数据
- 勾选状态
- 父子节点关系

例如：

```
Root
├── Child1
│   ├── Child1_1
│   └── Child1_2
└── Child2
```

其中每个节点都是一个 `QTreeWidgetItem`。

------

#### 常用函数

##### 1. 构造函数

```
QTreeWidgetItem();

QTreeWidgetItem(QTreeWidget *parent);
// 顶层节点

QTreeWidgetItem(QTreeWidgetItem *parent);
// 子节点

QTreeWidgetItem(
    const QStringList &strings
);
// 多列文本

QTreeWidgetItem(
    QTreeWidgetItem *parent,
    const QStringList &strings
);
```

例如：

```
QTreeWidgetItem *root =
    new QTreeWidgetItem(treeWidget);

root->setText(0, "Root");

QTreeWidgetItem *child =
    new QTreeWidgetItem(root);

child->setText(0, "Child");
```

------

##### 2. 文本与图标

```
void setText(int column, const QString &text);
QString text(int column) const;

void setIcon(int column, const QIcon &icon);
QIcon icon(int column) const;
```

例如：

```
item->setText(0, "main.cpp");
item->setText(1, "CPP File");
```

------

##### 3. 数据存储

```
void setData(
    int column,
    int role,
    const QVariant &value
);

QVariant data(
    int column,
    int role
) const;
```

例如：

```
item->setData(
    0,
    Qt::UserRole,
    1001
);
```

------

##### 4. 父子节点管理

```
void addChild(QTreeWidgetItem *child);
// 添加子节点

void insertChild(
    int index,
    QTreeWidgetItem *child
);

QTreeWidgetItem *child(int index) const;
// 获取子节点

int childCount() const;
// 子节点数量

QTreeWidgetItem *parent() const;
// 获取父节点

QTreeWidgetItem *takeChild(int index);
// 移除子节点
```

例如：

```
QTreeWidgetItem *root =
    new QTreeWidgetItem();

QTreeWidgetItem *child =
    new QTreeWidgetItem();

root->addChild(child);
```

------

##### 5. 展开状态

```
void setExpanded(bool expand);

bool isExpanded() const;
```

例如：

```
root->setExpanded(true);
```

------

##### 6. 勾选框

```
void setCheckState(
    int column,
    Qt::CheckState state
);

Qt::CheckState checkState(
    int column
) const;
```

例如：

```
item->setCheckState(
    0,
    Qt::Checked
);
```

------

##### 7. 外观控制

```
void setFont(
    int column,
    const QFont &font
);

void setForeground(
    int column,
    const QBrush &brush
);

void setBackground(
    int column,
    const QBrush &brush
);

void setHidden(bool hide);

bool isHidden() const;
```

------

#### 设置自定义控件

和 `QListWidget` 类似，可以给某个节点放置一个自定义 Widget。

```
QTreeWidgetItem *item =
    new QTreeWidgetItem(treeWidget);

item->setText(0, "Name");

QLineEdit *edit =
    new QLineEdit;

treeWidget->setItemWidget(
    item,
    1,
    edit
);
```

参数说明：

```
void setItemWidget(
    QTreeWidgetItem *item,
    int column,
    QWidget *widget
);
```

即：

- 第一个参数：节点
- 第二个参数：列号
- 第三个参数：控件

例如：

```
名称          值
----------------------
用户名      [QLineEdit]
密码        [QLineEdit]
```

这种配置界面非常常见。

------

#### 行为控制（flags）

和 `QListWidgetItem` 完全一致：

```
Qt::ItemFlags flags() const;

void setFlags(Qt::ItemFlags flags);
```

常用选项：

```
Qt::ItemIsSelectable
Qt::ItemIsEnabled
Qt::ItemIsEditable
Qt::ItemIsUserCheckable
Qt::ItemIsDragEnabled
Qt::ItemIsDropEnabled
Qt::ItemIsAutoTristate
```

特别说明：

#### Qt::ItemIsAutoTristate

这是树控件中特别常用的一个 Flag。

```
item->setFlags(
    item->flags()
    | Qt::ItemIsAutoTristate
    | Qt::ItemIsUserCheckable
);
```

效果：

```
☑ Root
 ├─ ☑ Child1
 └─ ☐ Child2
```

父节点状态会根据子节点自动变为：

```
☑ 已全部选中
☐ 全部未选中
◩ 部分选中
```

这也是文件选择树最常见的实现方式。

------

#### Role 数据

与 `QListWidgetItem` 完全一致。

Qt 内部维护：

```
QMap<int, QVariant>
```

常用 Role：

```cpp
Qt::DisplayRole
Qt::DecorationRole
Qt::EditRole
Qt::CheckStateRole
Qt::ToolTipRole
Qt::ForegroundRole
Qt::BackgroundRole

Qt::UserRole
Qt::UserRole + 1
Qt::UserRole + 2
...
```

例如：

```cpp
item->setData(
    0,
    Qt::UserRole,
    1001
); // ID

item->setData(
    0,
    Qt::UserRole + 1,
    "Folder"
); // 类型
```

## QTableWidget

`QTableWidget` 是 Qt 中的表格组件类，支持行表头、列表头。除了行列表头之外的表格区域是内容区，每个网格单元有一个行号、列号，每一个单元格是一个 `QTableWidgetItem` 对象，可以设置文字内容、字体、前景色、背景色、图标，也可以设置编辑和显示标记，每个单元格还可以存储一个 `QVariant` 数据，用于设置用户自定义数据。

###  常用函数

```cpp
/* 行列管理 */
int columnCount(); // 获取总列数
void setColumnCount(int columns); // 设置总列数

void setRowCount(int rows); // 设置总行数
int rowCount(); // 获取总行数

void insertRow(int row); // 在指定行插入一行（原行在新行下方）

void insertColumn(int column); // 在指定列插入一列（原列在新列后方）

void removeRow(int row); // 删除指定行

void removeColumn(int column); // 删除指定列
```

```cpp
/* 单元格数据管理 */
// 设置单元格项
void setItem(int row, int column, QTableWidgetItem *item);

// 获取单元格项，若没有该项，则返回nullptr
QTableWidgetItem *item(int row, int column) const; 

// 删除所有单元格数据，保留行列结构和表头
void clearCountents(); 

// 清空整个表格，包括单元格数据和表头数据，但保留行列数量。
void clear();
```

```cpp
/* 表头管理 */
// 设置水平表头，只设置所有的表头文字内容
void setHorizontalHeaderLabels(const QStringList &labels);

// 设置垂直表头，只设置所有的表头文字内容
void setVerticalHeaderLabels(const QStringList &labels);

// 获取水平表头对象
QHeaderView *horizontalHeader() const;

// 获取垂直表头对象
QHeaderView *verticalHeader() const;
```

```cpp
/* 当前单元格管理（需要单元格可选中，且为单元格选中模式） */
// 设置当前选中的单元格
void setCurrentCell(int row, int column);

// 获取当前行
int currentRow() const;

// 获取当前列
int currentColumn() const;

// 获取当前单元项
QTableWidgetItem *currentItem() const;
```

```cpp
/* 选中项管理 */
// 获取所有选中项
QList<QTableWidgetItem *> selectedItems() const;

// 获取所有选中的区域
QList<QTableWidgetSelectionRange> selectedRanges() const;

// 选择某个单元格
void setRangeSelected(const QTableWidgetSelectionRange &range, bool select);

// 清除选择
void clearSelection();
```

```cpp
/* 编辑功能 */
// 设置编辑模式,该项属于视图层的选项,与 QTableWidgetItem 的 falgs 共同决定是否可以编辑
void setEidtTriggeers(EditTriggers editTriggers);
/* EditTriggers是QAbstractItemView中的一个枚举类型，可选项如下：
	- NoEditTirggers 禁止编辑
	- CurrentChanged 当前项发生变化时（键盘上下移动，鼠标点击其他单元格）进行编辑
	- DoubleClicked 双击单元格进入编辑（最常见）
	- SelectedClicked 如果当前项已经被选中，再次单击时进入编辑（常与DoubleClicked同时使用）
	- EditKeyPressed 按编辑键进入编辑（通常是F2，一些平台还支持 Enger、Return）
	- AnyKeyPressed 按任意字符立即开始编辑，并替换为按下的字符
	- AllEditTriggers 开启所有编辑触发方式（除了NoEditTriggers）
*/

// 打开指定单元格编辑器
void editItem(QTableWidgetItem *item);
```

```cpp
/* 排序功能 */
// 启用排序，启用后点击表头即可排序
void setSortingEnabled(bool enable);

// 按指定列排序
void sortItems(int column Qt::SortOrder order);
/* SortOrder 是 Qt 类中的一个枚举类型，可选项如下：
	- AscendingOrder：升序排序
	- DescendingOrder：降序排序
*/
```

```cpp
/* 外观设置 */
// 设置列宽
void setColumnWidth(int column , int width);

// 设置行高
void setRowHeight(int row, int height);

// 自动调整列宽
void resizeColumnsToContents(); 

// 自动调整行高
void resizeRowsToContents();

// 隐藏列
void setColumnHiddend(int column, bool hide);

// 隐藏行
void setRowHidded(int row, bool hide);
```

### 常用信号

```cpp
// 当前单元格变化
void currentCellChanged(int currentRow, int currnetColumn, 
						int previousRow, int previousColumn);
```

```cpp
// 单元格点击
void cellClicked(int row, int column);
```

```cpp
// 单元格双击
void cellPressed(int row, int column);
```

```cpp
// 单元格进入
void cellEntered(int row, int column);
// 前提是，需要开启鼠标跟踪
void setMouseTracking(bool enable);
```

```cpp
// 单元格内容变化
void cellChanged(int row, int column);
```

```cpp
// 单元格激活
void cellActivated(int row, int column);
// 通常由：双击、回车、键盘导航触发
```

```cpp
// 项对象变化
void itemChanged(QTableWidgetItem *item);
// 相比于 cellChanged()，能够直接获得对应的 QTableWidgetItem 对象
```



# Model/View 架构

Model/View （模型/视图）结构是 Qt 中用界面中显示与编辑数据的一种结构，视图（View）用于显示和编辑组件，模型（Model）是视图与原始数据之间的接口。该架构的典型应用是在数据库应用程序中。

## 基本原理

将界面组件与所编辑的数据分离开来，又通过数据源的方式连接起来，是处理界面与数据的一种较好方式。Qt使用 Model/View 结构来处理这种关系，基本结构图如下所示。

![image-20260616102114965](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260616102114965.png)

- 数据是实际的数据。

- 视图或视图组件是屏幕上的界面组件，视图从数据模型获取每个数据项的模型索引（model index），通过模型索引获取数据，然后为界面组件提供显示数据。

  Qt提供了一些现成的数据视图组件，如 QListView、QTreeView 和 QTableView 等。

- 模型或数据模型与实际数据通信，并为视图组件提供数据结构，它从原始数据提取需要的内容，用于视图组件进行显示和编辑。

  Qt 中有一些预定义的数据模型，如 QStringListModel 可作为 StringList 的数据模型，QSqlTableModel 可以作为数据库中一个数据表的数据模型。

> 由于数据源与显示界面通过 Model/View 结构分离开来，因此可以将一个数据模型在不同的视图中显示，也可以在不修改数据模型的情况下，设置特殊的视图组件。

在 Model/View 架构中，还提供了代理（Delegate）功能，该功能可以让用户定制数据的界面显示和编辑方式。在标准的视图组件中，代理功能显示一个数据，当数据被编辑时，代理通过模型索引与数据模型通信，并为编辑提供一个编辑器，一般是一个 QLineEdit 组件。

模型、视图和代理之间使用信号和槽通信。

> 实际上，每个视图组件不仅有一个数据模型（Model），还有一个选择模型（Selection Model），选择模型中保存的是当前选中的哪些数据。

### 数据模型

所以基于项数据（item data）的数据模型（Model）都是基于 QAbstractItemModel 类的，该类定义了视图组件和代理存取数据的接口。

数据无需存放在数据模型中，可以是其他类、文件、数据库或任何数据源。

![Qt中模型类的层次结构](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260616105430178.png)



QAbstractItemModel 不能直接使用，Qt 提供了一些模型类用于项数据处理，常见的如下表。

| Model类                    | 用途                                                       |
| -------------------------- | ---------------------------------------------------------- |
| `QStringListModel`         | 用于处理字符串列表数据                                     |
| `QSstandardItemModel`      | 标准的基于项数据的数据模型类，每个项数据可以是任何数据类型 |
| `QFileSystemModel`         | 计算机上文件系统的数据模型类                               |
| `QSortFilterProxyModel`    | 与其他数据模型结构，提供排序和过滤功能的数据模型类         |
| `QSqlQueryModel`           | 用于数据库 SQL 查询结构的数据模型类                        |
| `QSqlTableModel`           | 用于数据库的一个数据表的数据模型类                         |
| `QSqlRelationalTableModel` | 用于关系型数据表的数据模型类                               |

### 视图组件

Qt 提供的视图组件如下。

- `QListView`：用于显示单列的列表数据，适用于一维数据的操作。
- `QTreeView`：用于显示树状结构数据，适用于树状结构数据的操作。
- `QTableView`：用于显示表格状数据，适用于二维表格型数据的操作。
- `QColumnView`：用多个 QListView 显示树状层次结构，树状结构的一层用一个 `QListView` 显示。
- `QHeaderView`：提供行表头或列表头的视图组件，如 `QTableView` 的行表头和列表头。

> 视图组件在显示数据时，只需调用视图类的 `setModel()` 函数，为视图组件设置一个数据模型就可以实现视图组件与数据模型之间的关联，在视图组件上的修改自动保存到关联的数据模型里，一个数据模型可以同时在多个视图组件里显示数据。

### 代理

代理就是在视图组件上为编辑数据提供编辑器，如在表格组件中编辑一个单元格的数据时，默认是一个 `QLineEdit` 编辑框。

代理负责从数据模型获取相应的数据，然后显示在编辑器里，修改数据后哦，又将其保存到数据模型中。

`QAbstractItemDelegate` 是所有代理类的基类，不能直接使用。它的一个子类 `QStyleItemDelegate` 是视图组件默认使用的代理类。

### 一些基本概念

#### 基本结构

不管底层数据是如何组织数据的，`QAbstractItemMoodel` 的子类都以表格的层次结构表示数据。

数据模型常见的 3 中表现形式如下。

![image-20260616110710695](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260616110710695.png)

数据模型中存储数据的基本单元都是项（Item），每个项有一个行号、一个列号，还有一个父项（parent item）。

- 列表和表格：有一个相同的顶层项（root item）；
- 树状结构：行号代表一个节点下第几个，列号代表节点的第几个数据，父项代表节点的父项。

#### 模型索引

引入了模型索引（model index）来保证数据的表现与数据存取方式隔离。

数据模型中的每个数据都有一个数据索引，视图组件和代理都通过模型索引来存取数据。

`QModelIndex` 表示模型索引的类。模型索引提供数据存取的一个临时指针。如果需要使用持久性的模型索引，则需要使用 `QPersistentModelIndex` 类。

#### 行号和列号

要获取一个模型索引，必须提供3个参数：行号、列号、父项的模型索引。

例如：

```cpp
QModelIndex indexA = model->index(0, 0, QModelIndex());
```

对于列表和表格模式的数据模型，顶层节点总是用 `QModelIndex()` 表示。

#### 父项

数据模型是列表或表格时，所有数据项的父项就是顶层项，使用 `QModelIndex()` 表示。

数据模型是树状结构时，情况比较复杂，一个节点可以有父节点，也可以是其他节点的父节点。对于顶层节点，获取模型索引的代码是：

```cpp
QModelIndex indexA = model->index(0, 0, QModelIndex());
QModelIndex indexC = model->index(2, 1, QModelIndex());
```

节点B的父节点是节点A，节点B的模型索引由下面的代码生成：

```cpp
QModelIndex indexB = model->index(1, 0, indexA);
```

#### 项的 Role

为数据模型的一个项设置数据时，可以赋予其不同项的角色（item role）的数据。例如，数据模型类 `QStandardItemModel` 的项数据类是 `QStandardItem`，其设置数据的函数如下。

```cpp
void QStandardItem::setData(const QVariant &value, int role = Qt::UserRole + 1);
```

其中：

- value：需要设置的数据。

- role：设置数据的角色，一个项可以有不同角色的数据，用于不同的场合。role 是 `Qt::ItemDataRole` 枚举类型，有多种取值，例如：

  - `Qt::DisplayRole`：显示的字符串。
  - `Qt::ToolTipRole`：鼠标悬浮时，显示的提示信息。
  - `Qt::UserRole`：自定义的数据。

  标准角色是 `Qt::UserRole`。

获取一个项的数据时也需要指定角色，以获取不同角色的数据。

```cpp
QVariant QStandardItem::data(int role = Qt::UserRoel + 1) const;
```

## 内置常用Model

### QFileSystemModel

`QFileSystemModel` 提供了用于访问本机文件系统的数据模型。和视图组件 `QTreeView` 结合使用，用目录树的形式显示本机上的文件系统。

#### 常用函数

**路径管理**

```cpp
// 设置根目录
QModelIndex setRootPath(const QString  &newPath);

// 获取根目录
QString rootPath() const;

// 根据路径获取索引
QModelIndex index(const QString &path, int column = 0) const;

// 根据索引获取路径
QString filePath(const QModelIndex &index) const;
```

**文件信息获取**

```cpp
// 获取文件名
QString fileName(const QModelIndex &index) const;

// 获取文件信息
QFileInfo fileInfo(const QModelIndex &index) const;
/* QFileInfo 是一个非常使用且常用的类，可以获取到文件的名称、路径、大小、修改日期、访问权限等信息。*/

// 判断是否目录
bool isDir(const QModelIndex &index) const;

// 获取文件大小
qint64 size(const QModelIndex &index) const;

// 获取文件类型
QString type(const QModelIndex &index) const;
/* 该函数返回的是一个由底层操作系统或Qt根据文件后缀/类型生成的、用于项用户战士的"文件类型描述文本"，最好不要使用该函数来判断文件的类型。而是使用 QFileInfo 的函数来判断类型 */

// 获取权限
QFile::Permissions permissions(const QModelIndex &index) const;
```

**文件过滤**

```cpp
// 设置过滤条件
void setFilter(QDir::Filters filters);
/* 常见过滤项如下所示：
	- QDir::Files
	- QDir::Dirs
	- QDir::AllDirs
	- QDir::NoDotAndDotDot
	- QDir::Hidden
	- QDir::Readable
	- QDir::Writable
*/

// 获取过滤条件
QDir::Filters filter() const;

// 设置名称过滤器
void setNameFilters(const QStringList &filters);
/* 参数可以是一个后缀列表，例如： {"*.cpp", "*.h", "*.ui"} */

// 是否禁用不匹配文件
void setNameFilterDisable(bool enable);
/* 
	- true：不匹配文件变灰
	- false：不匹配文件直接隐藏
*/
```

**文件修改**

```cpp
// 创建目录
QModelIndex mkdir(
	const QModelIndex &parent,
	const QString &name);

// 删除文件
bool remove(const QModelIndex &index);

// 删除目录，但只能删除空目录
bool rmdir(const QModelIndex &index);

// 重命名
bool setData(const QModelIndex &index,
            const QVariant &value,
            int role = Qt::EditRole);
```

**图标与只读属性**

```cpp
// 设置只读模式
void setReadOnly(bool enable);

// 获取是否只读
bool isReadOnly() const;

// 设置图标提供器，用于自定义文件图标
void setIconProvider(QFileIconProvider *provider);

// 获取图标提供其
QFileIconProvider *iconProvider() const;
```

**排序**

```cpp
// 排序
void sort(
	int column,
	Qt::SortOrder order = Qt::AscendingOrder);
/* column 的含义：
	- 0 名称
	- 1 大小
	- 2 类型
	- 3 修改时间
*/
```

#### 常用信号

**路径加载类**

```cpp
// 根目录加载完成，当根目录发生变化时触发
void rootPathChanged(const QString &newPath); 

// 目录加载完成，目录内容异步加载完成时触发
void directoryLoaded(const QString &path);
```

**文件重命名类**

```cpp
// 文件重命名完成，当文件或目录重命名成功后触发
void fileRenamed(const QString &path, const QString &oldName, const QString &newName);
```

### QStringListModel

`QStringListModel` 是用于处理字符串列表的数据模型，可以作为 `QListView` 的数据模型，在界面上显示和编辑字符串列表。

#### 常用函数

**数据管理**

```cpp
// 设置整个字符串列表
void setStringList(const QStringList &strings);

// 获取字符串列表
QStringList stringList() const;

// 获取指定索引的数据
QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

// 修改指定项的数据
bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
```

**行操作**

```cpp
// 插入多行,默认是从顶层节点开始插入
bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
// 插入单行
bool insertRow(int row, const QModelIndex &parent = QModelIndex()) override;

// 删除多行
bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
// 删除单行
bool removeRow(int row, const QModelIndex &parent = QModelIndex()) override;

// 获取行数
int rowCount(const QModelIndex &parent = QModelIndex()) const override;
```

**索引相关**

```cpp
// 获取模型索引
QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override;

// 获取父索引，但是始终返回无效索引
QModelIndex parent(const QModelIndex &clild) const override;
```

**模型属性**

```cpp
// 获取支持的 Item Flags
Qt::ItemFlags flags(const QModelIndex &index) const override;
```

**排序**

```cpp
void sort(int column Qt::SortOrder order = Qt::AscendingOrder) override;
```

#### 常用信号

**数据变化类**

```cpp
// 数据发生变化
void dataChanged(const QModelIndex &topLeft,
				const QModelIndex &bottomRight,
				const QList<int> &roles = QList<int>());
```

**行变化类**

```cpp
// 即将插入行
void rowAboutToBeInserted(
	const QModelIndex &parent,
	int first,
	int last);

// 行插入完成
void rowsInserted(
	const QModelIndex &parent,
	int first, 
	int last);

// 即将删除行
void rowsAboutToBeRemoved(
	const QModelIndex &parent,
	int first,
	int last);

// 行删除完成
void rowsRemoved(
	const QModelIndex &parent,
	int first,
	int last);
```

**模型重置类**

```cpp
// 即将重置模型
void modelAboutToBeReset();

// 模型重置完成
void modelReset();
```

**布局变化类**

```cpp
// 布局即将变化
void latyoutAboutToBeChanged();

// 布局变化完成, 常见于排序
void layoutChanged();
```

### QStandardItemModel

`QStandardItemModel` 是标准的以项数据（item data）为基础的标准数据模型类，通常与 `QTableView` 组合成 Model/View，实现通用的二维数据的管理功能。

`QStandardItemModel` 的数据管理的基本单元是 `QStandardItem`。

> 也可以直接与 `QTreeView`、`QListView`、`QListView` 等配合使用。

#### 常用函数

**模型结构管理**

```cpp
// 设置行数
void setRowCount(int rows);
// 获取行数
int rowCount(const QModelIndex &parent = QModelIndex()) const;

// 设置列数
void setColumnCount(int columns);
// 获取列数
int columnCount(const QModelIndex &parent = QModelIndex()) const;

// 清空模型，删除所有数据和表头
void clear();
```

**Item管理**

```cpp
// 设置 Item
void setItem(int row, int column, QStandardItem *item); 

// 获取 Item
QStandardItem *item(int row, int column = 0) const;

// 根据索引获取 Item
QStandardItem *itemFromIndex(const QModelIndex &index) const;

// 获取索引
QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
```

**行列操作**

```cpp
// 添加一行
void appendRow(QStandardItem *item);

// 添加多列行
void appendRow(const QList<QStandardItem *> &items)
    
// 插入行
void insertRow(int row, const QList<QStandardItem *> &items);

// 删除行
void removeRow(int row);

// 删除列
void removeColumn(int column);
```

**表头管理**

```cpp
// 设置水平表头的文字
void setHorizontalHeaderLabels(const QStringList &labels);

// 设置垂直表头
void setVerticalHeaderLabels(const QStringList &labels);

// 设置表头 Item
void setHorizontalHeaderItem(int column, QStandardItem *item);
void setVerticalHeaderItem(int row, QStandardItem *item);
```

**数据操作**

```cpp
// 设置数据
bool setData(
	const QModelIndex &index, 
	const QVariant &value,
	int role = Qt::EditRole);
	
// 获取数据
QVariant data(
	const QModelIndex &index,
	int role = Qt::DisplayRole);
	
// 查找 item
QList<QStandardItem *> findItems(
	const QString &text,
	Qt::MatchFlags flags = Qt::MatchExactly,
	int column = 0);
```

**排序**

```cpp
// 排序
void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);
```

#### 常用信号

**数据变化类**

```cpp
// 数据发生变化
void dataChanged(
	const QModelIndex &topLeft,
	const QModelIndex &bottomRight,
	const QList<int> &roles = QList<int>());
	
// Item 内容变化
void itemChanged(QStandaradItem *item);
```

## 自定义代理

Qt中代理的几个类的层次结构如下图。

![image-20260617124521808](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260617124521808.png)

- `QAbstractItemDelegate`：是所有代理类的抽象基类。
- `QStyledItemDelegate`：是视图组件使用的缺省的代理类。
- `QItemDelegate`：也是类似功能的类。

> `QStyledItemDelegate` 与 `QItemDelegate` 的差别：
>
> `QStyledItemDelegate` 可以使用当前的样式表设置来绘制组件，因此建议使用 `QStyledItemDelegate` 作为自定义代理组件的基类。

### 实现

不管从 `QStyledItemDelegate` 还是 `QItemDelegate` 继承设计自定义代理组件，都必须实现如下的4个函数：

```cpp
createEdit();
// 创建用于编辑模型数据的 widget 组件，如一个 QSpinBox 组件，或一个 QComboBox组件
```

```cpp
setEditorData()
// 从数据模型获取数据，供 widget 组件进行编辑
```

```
setModelData()
// 将 widget 上的数据更新到数据模型
```

```cpp
updateEditorGeometry()
// 用于 widget 组件设置一个合适的大小
```

**案例**

```cpp
QWidget *QWIntSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // 创建代理编辑组件
    QSpinBox *editor = new QSpinBox(parent);
    editor->setFrame(false); // 设置为无边框
    editor->setMinimum(0);
    editor->setMaximum(100000);
    return editor; // 返回此编辑器
}

void QWIntSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    // 从数据模型获取数据，显示到代理组件中
    int value = index.model()->data(index, Qt::EditRole).toInt();
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->setValue(value);
}

void QWIntSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    // 将代理组件的数据保存到数据模型中
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->interpretText();
    int value = spinBox->value();
    model->setData(index, value, Qt::EditRole);
}

void QWIntSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // 设置组件大小
    editor->setGeometry(option.rect);
}
```

# 绘图

Qt的二维绘图基本功能是使用 `QPainter` 在绘图设备（例如 `QWidget`、`QPixmap`）上进行绘制基本的点、线、圆等基本形状组合成自己需要的图形。

> 得到的图形是不可交互操作的图形。

Qt 还提供了 Graphics View 架构，可以在场景中绘制图件，并且每个图件都是可选择、可交互的。

## QPainter

### 介绍

1. `QPainter` 和 `QPaintDevice`

   绘图系统基于 `QPainter`、`QPaintDevice`和`QPaintEngine`类。`QPainter` 是用来进行绘图操作的类，`QPaintDevice` 是一个可以使用 `QPainter` 进行绘图的抽象二维界面。`QPaintEngine` 给 `QPainter` 提供在不同设备上绘图的接口。`QPaintEnging` 类由 `QPainter` 和 `QPaintDevice` 内部使用。

2. paintEvent 事件和绘图区

   最常用的绘图设备是 `QWidget` 类。从 `QWidget` 类继承的类都有 `paintEvent()` 事件，要在设备上绘图，只需要重定义此事件并编写响应代码。创建一个 `QPainter` 对象获取绘图设备的接口，然后就可以在绘图设备的“画布”上绘图了。

   在 `paintEvent()` 事件里绘图的基本程序结构是：

   ```cpp
   void Widget::paintEvent(QPaintEvent *event)
   {
   	QPainter painter(this); // 创建于绘图设备关联的 QPainter 对象
   	// ... 绘图代码
   }
   ```

3. 坐标系统

   `QWidget` 的绘图区就是其窗口内部区域。其坐标系统如下图所示。

   ![QWidget 的坐标系统](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260622112357690.png)

   **坐标系统的单位是像素**

   > 该坐标系统是绘图区的局部物理坐标，称为视口（viewport）坐标。
   >
   > 还有一个逻辑坐标，称为窗口（window）坐标。

4. 绘图的主要属性

   控制绘图的元素特性的是 `QPainter` 的 3 个属性。

   - pen 属性：是一个 `QPen` 对象，用于控制线条的颜色、宽度、线型等。
   - brush 属性：是一个 `QBrush` 对象，用于设置一个区域的填充特性，可以设置填充颜色、填充方式、渐变特性等，还可以采用图片做填充。
   - font 属性：是一个 `QFont` 对象，用于绘制文字时，设置文字的字体样式、大小等属性.

### 常用函数

**抗锯齿**

```
// 1. 设置或关闭单个渲染提示（最常用）
// hint: 渲染提示枚举值；on: true 代表开启，false 代表关闭
void setRenderHint(QPainter::RenderHint hint, bool on = true);

// 2. 批量设置多个渲染提示
// hints: 可以通过按位或（|）组合多个枚举值
void setRenderHints(QPainter::RenderHints hints, bool on = true);

// 3. 配套的 Getter 函数：判断当前是否开启了某个提示
bool testRenderHint(QPainter::RenderHint hint) const;
```

1. `QPainter::Antialiasing`（核心：抗锯齿）

- **作用**：对直线、圆弧、多边形等几何图形的边缘进行平滑处理。
- **原理**：当图形边界落在非整数像素点（或斜线区域）时，绘图引擎会通过色彩混合算法，在边缘产生半透明的过渡像素（亚像素渲染），从而消除“视觉毛刺”。
- **视觉对比例子**：

2. `QPainter::TextAntialiasing`（文本抗锯齿）

- **作用**：专门用于文字绘制（`drawText`）的平滑开关。
- **注意**：通常情况下，Qt 会默认跟随系统的字体平滑设置（如 Windows 的 ClearType）。但如果你在自定义控件里绘制倾斜文字、特效文字，手动开启它可以确保字体边缘绝对丝滑。

3. `QPainter::SmoothPixmapTransform`（图片平滑变换）

- **作用**：专门针对图片（`QPixmap` / `QImage`）在进行**放大、缩小或旋转**时的图像优化。
- **原理**：默认情况下，图片缩放采用的是“最近邻插值”算法，速度极快但缩放后会有强烈的马赛克和锯齿。开启此项后，会启用**双线性过滤算法（Bilinear Filtering）**，让缩放后的图片依然平滑清晰。

**绘图函数**

`QPainter` 支持绘制多种简单图案，例如点、线、矩形、圆形、三角形等等。具体细节查看 Qt 官方文档。

**坐标变化**

`QPainter` 默认提供的坐标系统是右上角为原点（0，0）。X轴水平向右、Y轴水平向下的直角坐标系。`QPainter` 提供了一些坐标变换的功能。

```cpp
// 坐标系统平移一定的偏移量，坐标原点平移到新的点
void translate(qreal x, qreal y);
```

表示将坐标系统水平方向平移 x 个单位，垂直方向平移 y 个单位。

> 将坐标原点变换到窗口中心在绘制某些图形时非常方便。

```cpp
// 坐标系统顺时针旋转一个角度
void rotate(qreal angle);
```

表示将坐标系统绕坐标原点旋转 angle 角度，单位是度。angle 是正数时顺时针旋转。为负数时是逆时针旋转。

```cpp
// 坐标系统缩放
void scale(qreal sx, qreal sy);
```

sx，sy分别为横向和纵向的缩放比例，大于1 是放大，小于1是缩小。

```cpp
// 坐标系统做扭转变换
void shear(qreal sh, qreal sv);

// 保存painter当前的状态，方式是将当前状态压栈
void save();

// 恢复上一次的状态
void restore();

// 复位所有的坐标变换
void resetTransform();
```

**视口和窗口**

在 Qt 的二维绘图系统中，`QPainter` 的**视口（Viewport）\**和\**窗口（Window）\**是实现\**坐标系转换、图形自动缩放与自适应布局**的核心机制。

**窗口（Window）**：是面向开发者的“逻辑坐标系”（你希望在多大的画布上画图）。

**视口（Viewport）**：是面向设备的“物理坐标系”（图形最终要渲染到屏幕上多大的像素区域）。

`QPainter` 内部维护了一个从“窗口”到“视口”的**线性映射矩阵**。

当你调用 `painter.drawRect(x, y, w, h)` 绘图时，你传入的参数属于**窗口坐标（逻辑坐标）**。Qt 在真正把图形画到屏幕上之前，会自动根据窗口和视口的比例关系，将其等比缩放并平移到视口坐标（物理坐标）上。

在默认情况下，窗口和视口是**完全重合**的：

- 它们的左上角都是 `(0, 0)`。
- 它们的大小都等于绘图设备（如 `QWidget`）的物理像素大小。
- 此时，1个逻辑单位就等于1个屏幕像素。

```cpp
// ==========================================
// 1. 窗口（Window）相关函数 - 逻辑坐标
// ==========================================
// 设置窗口（逻辑画布）的矩形区域
void setWindow(const QRect &rect);
void setWindow(int x, int y, int width, int height);

// 获取当前窗口的矩形区域
QRect window() const;

// ==========================================
// 2. 视口（Viewport）相关函数 - 物理坐标
// ==========================================
// 设置视口（物理渲染目标）的矩形区域
void setViewport(const QRect &rect);
void setViewport(int x, int y, int width, int height);

// 获取当前视口的矩形区域
QRect viewport() const;
```

**叠加规则**

定了**新绘制的图形（源图像 Source）与画布上已经存在的图形（目标图像 Destination）以何种“像素混合规则”进行叠加。**

```cpp
// 设置当前的图像合成/混合模式
void setCompositionMode(QPainter::CompositionMode mode);

// 获取当前的图像合成模式
QPainter::CompositionMode compositionMode() const;
```

1. 基础不透明度类（最常用）

- **`CompositionMode_SourceOver` (默认值)**：最符合直觉的模式。新画的图形在旧图形**上方**。如果新图形有 Alpha 半透明通道，会自然渗透并看到底下的旧图形。
- **`CompositionMode_DestinationOver`**：颠倒过来，新画的图形被“塞”到了旧图形的**下方**。

2. 擦除与裁剪类（特效利器）

- **`CompositionMode_Clear`**：清除画布。无论你画什么（哪怕画一个红色的圆），只要处于这个模式，它划过的区域对应的**画布像素会彻底变成完全透明（Alpha=0）**。
- **`CompositionMode_SourceOut`**：只保留新图形中**没有与旧图形重叠**的部分，重叠部分变透明。
- **`CompositionMode_DestinationIn`**：**（极为常用）** 类似 Photoshop 的剪切蒙版。只保留旧图形与新图形**相交**的部分，其余变透明。可以用来把任意图片裁剪成文字形状或猫咪形状。

3. 高级光影融合类（数字图像处理）

- **`CompositionMode_Multiply` (正片叠底)**：将新旧像素颜色相乘。颜色会变暗，常用于给物体画环境阴影。
- **`CompositionMode_Screen` (滤色)**：将新旧像素颜色的反色相乘。颜色会变亮，常用于制作发光、霓虹灯、激光、手电筒光晕特效。
- **`CompositionMode_Xor` (异或)**：新旧图形重叠的地方会被“扣空”变透明。常用于老式画图软件中拖动鼠标画矩形选框（再画一次就能恢复）。

> 一共有四十多种的枚举值，可以查看 Qt 文档。

### 绘图流程

```cpp
// 一般使用 QPainter 进行绘图的流程如下
void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    int W = this->rect().width();
    int H = this->rect().height();
 
    // 画一个矩形
    QRect targetRect{W/4, H/4, W/2, H/2};
	painter.drawRect(targetRect);
}
```

## QPen

`QPen` 用于绘图时对线条进行设置，主要包括线宽、颜色、线型等

### 常用函数

**构造函数**

```cpp
// 1. 默认构造函数（创建一个黑色、宽度为0、实线的画笔）
QPen();

// 2. 指定线型的构造函数（颜色默认为黑色，宽度为0）
QPen(Qt::PenStyle style);

// 3. 指定颜色、宽度、线型、线帽和连接点的完整构造函数
QPen(const QColor &color, qreal width = 0, Qt::PenStyle style = Qt::SolidLine, Qt::PenCapStyle cap = Qt::SquareCap, Qt::PenJoinStyle join = Qt::BevelJoin);

// 4. 使用 QBrush（画刷）作为线条填充色的构造函数（允许线条带有渐变色或纹理）
QPen(const QBrush &brush, qreal width, Qt::PenStyle style = Qt::SolidLine, Qt::PenCapStyle cap = Qt::SquareCap, Qt::PenJoinStyle join = Qt::BevelJoin);

// 5. 拷贝构造函数
QPen(const QPen &pen);
```

**颜色与画刷**

除了基础的 `QColor`，`QPen` 还可以使用 `QBrush`，这意味着你可以画出带有渐变色（Gradient）或图片纹理（Texture）的线条。

```cpp
// 获取/设置画笔颜色
QColor color() const;
void setColor(const QColor &color);

// 获取/设置画笔画刷（用于高级填充，如渐变线）
QBrush brush() const;
void setBrush(const QBrush &brush);
```

**宽度与粗细**

```cpp
// 获取/设置画笔宽度（返回 qreal 即 double，支持浮点数精度的线条）
qreal widthF() const;
void setWidthF(qreal width);

// 获取/设置画笔宽度（整型版本，内部会自动转换为 qreal）
int width() const;
void setWidth(int width);

// 获取/设置是否为化妆笔（若为 true，即使 QPainter 缩放，线条宽度也保持设备像素不变）
bool isCosmetic() const;
void setCosmetic(bool cosmetic);
```

**线型样式**

```cpp
// 获取/设置线型样式
Qt::PenStyle style() const;
void setStyle(Qt::PenStyle style);

// 自定义虚线模式（当 style 为 Qt::CustomDashLine 时使用）
// 传入的 QVector<qreal> 轮流代表“实线长度”和“空白长度”
QList<qreal> dashPattern() const; // 注：在旧版本中返回 QVector，Qt6 中统一为 QList
void setDashPattern(const QList<qreal> &pattern);

// 获取/设置虚线偏移量（改变虚线滚动的起始位置，常用于制作蚂蚁线动画）
qreal dashOffset() const;
void setDashOffset(const qreal offset);
```

线条样式：

![各种样式的线条样式](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260622164141675.png)

**线帽与连接点样式**

```cpp
// 获取/设置线帽样式（端点形状：FlatCap平头, SquareCap方头, RoundCap圆头）
Qt::PenCapStyle capStyle() const;
void setCapStyle(Qt::PenCapStyle capStyle);

// 获取/设置连接点样式（相交形状：MiterJoin尖角, BevelJoin斜角, RoundJoin圆角）
Qt::PenJoinStyle joinStyle() const;
void setJoinStyle(Qt::PenJoinStyle joinStyle);

// 获取/设置尖角限制（当 joinStyle 为 MiterJoin 时，限制尖角突出的最大长度，防止角度过小时尖角无限延长）
qreal miterLimit() const;
void setMiterLimit(qreal limit);
```

线条端点（线帽）样式

![image-20260622164224880](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260622164224880.png)

线条连接样式

![image-20260622164315766](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260622164315766.png)

**比较与常用操作符**

```cpp
// 判断画笔是否是不透明的
bool isSolid() const;

// 赋值操作符
QPen &operator=(const QPen &pen);

// 比较操作符
bool operator==(const QPen &pen) const;
bool operator!=(const QPen &pen) const;
```

## QBrush

`QBrush` 与 `QPen` 配合使用，`QBrush` 负责填充图形的内部区域。

### 常用函数

**构造函数**

```cpp
// 1. 默认构造函数（创建一个默认的、不进行任何填充的画刷，样式为 Qt::NoBrush）
QBrush();

// 2. 指定颜色和填充样式的构造函数（样式默认为实心纯色 Qt::SolidPattern）
QBrush(const QColor &color, Qt::BrushStyle style = Qt::SolidPattern);
QBrush(Qt::GlobalColor color, Qt::BrushStyle style = Qt::SolidPattern);

// 3. 指定颜色和内置纹理图片（QPixmap）的构造函数
QBrush(const QColor &color, const QPixmap &pixmap);

// 4. 自定义图片纹理构造函数（直接将一张图片作为填充纹理，样式自动变为 Qt::TexturePattern）
QBrush(const QPixmap &pixmap);
QBrush(const QImage &image);

// 5. 渐变填充构造函数（传入一个 QGradient 及其子类对象）
QBrush(const QGradient &gradient);

// 6. 拷贝构造函数
QBrush(const QBrush &other);
```

**样式与颜色控制**

```cpp
// 获取/设置画刷的填充样式（如纯色、各种阴影线、渐变、纹理等）
Qt::BrushStyle style() const;
void setStyle(Qt::BrushStyle style);

// 获取/设置画刷的颜色（如果是渐变或未知纹理，可能返回不确定颜色）
const QColor &color() const;
void setColor(const QColor &color);
void setColor(Qt::GlobalColor color);
```

`Qt::BrushStyle` 的几个主要常量

| 枚举常量                   | 描述                                                         |
| -------------------------- | ------------------------------------------------------------ |
| Qt::NoBrush                | 不填充                                                       |
| Qt::SolidPattern           | 单一颜色填充                                                 |
| Qt::HorPattern             | 水平线填充                                                   |
| Qt::VerPattern             | 垂直线填充                                                   |
| Qt::LinearGradienPattern   | 线性渐变，需要使用 QLinearGradient 类对象作为Brush           |
| Qt::RedialGradientPattern  | 辐射渐变，需要使用QRadialGradient 类对象作为Brush            |
| Qt::ConicalGradientPattern | 圆锥型渐变，需要使用 QConicalGradientPattern 类对象作为 Brush |
| Qt::TexturePattern         | 材质填充，需要指定 texture 或 textureImage 图片              |

填充样式

![image-20260622165249703](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260622165249703.png)

渐变填充样式

- `QLinearGradient`：是线性渐变，指定一个起点和颜色，终点和颜色，还可以指定中间某个点的颜色，起点和终点之间的颜色会自动计算（插值计算）。

  ![image-20260622181455914](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260622181455914.png)

- `QRadialGrandient`：辐射渐变，有两种方式：简单辐射渐变和扩展辐射渐变两种方式。简单辐射渐变是在一个圆内的一个焦点和一个端点之间生成渐变色。扩展辐射渐变是在一个焦点圆和一个中心圆之间生成渐变色。

  ![image-20260622181439851](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260622181439851.png)

  

- `QConicalGradient`：圆锥形渐变，围绕一个中心逆时针生成渐变色。

  ![image-20260622181511639](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260622181511639.png)

扩展方式

扩展方式是在填充完成之后，剩余部分应该怎样填充。有 3 种可取值。

- `PadSpread`：用结束点的颜色填充外部区域。
- `RepeatSpread`：重复使用渐变方式填充外部区域。
- `ReflectSpread`：反射式重复使用渐变方式填充外部区域。

例如，填充颜色是：红->绿->蓝。三种不同的选项效果如下：

- `PadSpread`：红->绿->蓝->蓝->蓝->...。

  ![image-20260622182016937](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260622182016937.png)

- `RepadSpread`：红->绿->蓝->红->绿->蓝->...。

  ![image-20260622182041376](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260622182041376.png)

- `ReflectSpread`：红->绿->蓝->绿->红->绿->蓝->...。

  ![image-20260622182059484](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260622182059484.png)

**高级填充：渐变与纹理**

```cpp
// 获取当前画刷绑定的渐变对象（只有在 style() 为渐变类型时才有效）
const QGradient *gradient() const;

// 获取/设置自定义纹理图片
QPixmap texture() const;
void setTexture(const QPixmap &pixmap);

// 获取自定义的纹理图片（Qt5.15+ / Qt6 推荐，返回 QImage 性能在某些平台更好）
QImage textureImage() const;
void setTextureImage(const QImage &image);
```

 **空间变换**

你可以让画刷填充的图案进行旋转、缩放或平移。例如，让填充的密点纹理旋转 45 度。

```cpp
// 获取/设置画刷的局部变换矩阵（Qt6 使用 QTransform，旧版本可能使用 QMatrix）
QTransform transform() const;
void setTransform(const QTransform &matrix);
```

**状态判断与操作符**

```cpp
// 判断画刷是否是不透明的（纯色且 Alpha 通道为 255）
bool isOpaque() const;

// 赋值与比较操作符
QBrush &operator=(const QBrush &brush);
bool operator==(const QBrush &brush) const;
bool operator!=(const QBrush &brush) const;
```

## QPainterPath

`QPainterPath` 是一个容器，充当了一个画图轨迹记录器。

1. **复用性强**：路径只需创建并配置一次，就可以在 `paintEvent` 中被多次重复绘制，或者进行平移、旋转、缩放。

2. **高级几何运算**：支持**交集、并集、差集**等布尔运算（例如：从一个矩形中“挖掉”一个圆形）。

3. **完美的封闭填充**：无论路径多复杂，它都能根据特定规则（如奇偶规则）完美计算并填充内部区域。

### 常用函数

```cpp
// 1. 默认构造函数（创建一个空的、没有任何轨迹的点）
QPainterPath();

// 2. 指定起始点（画笔落笔位置）的构造函数
QPainterPath(const QPointF &startPoint);

// 3. 拷贝构造函数
QPainterPath(const QPainterPath &other);
```

**轨迹移动与直线**

```cpp
// 将当前画笔“提起”并移动到指定点（不留下划线痕迹，作为新一段轨迹的起点）
void moveTo(const QPointF &point);
void moveTo(qreal x, qreal y);

// 从当前画笔位置，画一条直线到指定点（画笔位置更新为指定点）
void lineTo(const QPointF &point);
void lineTo(qreal x, qreal y);
```

**添加基础几何图形 **

```cpp
// 添加矩形
void addRect(const QRectF &rect);
void addRect(qreal x, qreal y, qreal width, qreal height);

// 添加椭圆 / 正圆
void addEllipse(const QRectF &rect);
void addEllipse(const QPointF &center, qreal rx, qreal ry);

// 添加圆角矩形
void addRoundedRect(const QRectF &rect, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize);

// 添加多边形
void addPolygon(const QPolygonF &polygon);

// 添加另一个已有的路径
void addPath(const QPainterPath &path);
```

**曲线与弧线 **

```cpp
// 绘制一段圆弧（起始角和跨越角的单位依旧是 1/16 度）
void addArc(const QRectF &rect, qreal startAngle, qreal sweepLength);

// 二次贝塞尔曲线：从当前位置，通过控制点(cpx, cpy) 画一条曲线到终点(endPoint)
void quadTo(const QPointF &ctrlPoint, const QPointF &endPoint);
void quadTo(qreal cpx, qreal cpy, qreal endX, qreal endY);

// 三次贝塞尔曲线：使用两个控制点(c1, c2) 画一条平滑曲线到终点(endPoint)
void cubicTo(const QPointF &c1, const QPointF &c2, const QPointF &endPoint);
void cubicTo(qreal c1x, qreal c1y, qreal c2x, qreal c2y, qreal endX, qreal endY);
```

**路径控制与闭合**

```cpp
// 自动闭合路径：从当前画笔位置画一条直线连接到本段轨迹的起点(moveTo的点)，形成封闭图形
void closeSubpath();

// 强制清空路径里的所有轨迹数据，将其重置为空路径
void clear();

// 获取路径中当前画笔所处的坐标位置
QPointF currentPosition() const;
```

**几何布尔运算**

利用两个路径计算出新的路径形态（注意：这些是**非成员函数**，或者通过重载运算符使用）。

```cpp
// 返回两个路径的相交部分（交集）
QPainterPath intersected(const QPainterPath &other) const;

// 返回两个路径合并后的部分（并集）
QPainterPath united(const QPainterPath &other) const;

// 返回从当前路径中扣除 other 路径后的部分（差集/相减）
QPainterPath subtracted(const QPainterPath &other) const;
```

**填充规则**

当路径中的线条互相交错（比如画一个五角星）时，Qt 需要知道哪些区域算“内部”（需要涂色），哪些算“外部”（保持透明）。你可以通过 `path.setFillRule(Qt::FillRule)` 来设置。

```cpp
void setFillRule(Qt::FillRule rule);
```

- `Qt::OddEvenFill`（**奇偶规则，默认**）：从该区域向外引一条射线，如果与路径交叉了奇数次，就是内部；偶数次就是外部。

- `Qt::WindingFill`（**非零环绕规则**）：根据路径线条的方向（顺时针/逆时针）来计算环绕数，通常用于需要完全填满交错图形的场景。

## 集合核心类

| **类名**         | **核心职责 (它是什么)**                         | **整数版 / 浮点版**            | **核心常用成员函数**                                 | **典型应用场景**                                     |
| ---------------- | ----------------------------------------------- | ------------------------------ | ---------------------------------------------------- | ---------------------------------------------------- |
| **`QPoint`**     | 描述二维空间中的**一个坐标点** $(x, y)$         | `QPoint` `QPointF`             | `x()`, `y()`, `setX()`, `setY()`                     | 捕捉鼠标点击位置、定义图形的起点或中心点。           |
| **`QSize`**      | 描述物体的**尺寸大小**（宽度和高度）            | `QSize` `QSizeF`               | `width()`, `height()`, `scale()`, `isValid()`        | 设置控件的最小/最大尺寸、定义图片的缩放分辨率。      |
| **`QRect`**      | 描述一个**矩形区域**（位置 + 大小）             | `QRect` `QRectF`               | `center()`, `contains()`, `intersects()`, `moveTo()` | 控件在屏幕上的布局范围、按钮点击区域、圆形的外切框。 |
| **`QLine`**      | 描述空间中的一条**物理线段**（起点 $\to$ 终点） | `QLine` `QLineF`               | `p1()`, `p2()`, `length()`, `angle()`, `intersect()` | 绘制雷达扫描线、时钟指针、图表折线、线段碰撞检测。   |
| **`QPolygon`**   | 描述由多个点顺次连接组成的**多边形**            | `QPolygon` `QPolygonF`         | `boundingRect()`, `containsPoint()`, `translated()`  | 绘制三角形箭头、五角星、不规则多边形按键。           |
| **`QRegion`**    | 描述屏幕上不规则的**像素区域集合**              | 仅 `QRegion` *(无浮点版)*      | `intersected()`, `united()`, `subtracted()`          | 窗口异形裁剪（遮罩）、局部区域精确刷新、点击穿透。   |
| **`QTransform`** | 描述 3x3 的**空间仿射变换矩阵**                 | 仅 `QTransform` *(内部全浮点)* | `translate()`, `rotate()`, `scale()`, `map()`        | 让图形或画布整体实现平移、旋转、缩放或镜像翻转。     |

## Graphics View绘图架构

通过 `QPainter` ，只能绘制位图，不能实现图件的选择、编辑、拖放和修改等功能。

Graphics View 绘图架构是一种基于图形项（Graphics Item）的模型/视图模型，与 Model/View 模式类似，使用该架构可以绘制复杂的有几万个基本图形元件的图形，并且每个图形元件是**可选择、可拖放和修改的**。

Graphics View 架构由 3 个部分组成，即场景、视图和图形项。

![image-20260622221932097](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260622221932097.png)

### 场景

`QGraphicsScene` 类提供绘图场景（Scene）。场景是不可见的，可以向场景添加图形项或获取场景中的某个图形项

#### 功能

- 提供管理大量图形项的快速接口
- 将事件传播给每个图形项
- 管理每个图形项的状态，例如选择、焦点等
- 管理未经变换的渲染功能，主要用于打印

还有背景层和前景层，通常由 `QBrush` 指定。也可以通过重新实现 `drawBackground()` 和 `drawForeground()` 函数来实现自定义的背景和前景。

### 视图

`QGraphicsView` 提供绘图的视图（View）组件，用于显示场景的内容。

一个场景可以设置几个视图，用于对同一个数据集提供不同的视图窗口。

视图接受键盘和鼠标输入并转换为场景事件，进行坐标转换后传送给可视场景。

### 图形项

`QGraphicsItem` 就是一些基本的图形元件。

Qt 提供了一些基本的图形项，如绘制椭圆的 `QGraphicsEllipseItem` 、绘制矩形的 `QGraphicsRectItem`、绘制文字的 `QGraphicsTextItem` 等。

支持如下操作

- 支持鼠标事件响应
- 支持键盘输入，按键事件
- 支持拖放操作
- 支持组合，可以是父子项关系组合，也可以是通过 `QGraphicsItemGroup` 类进行组合。

### 坐标系统

Graphics View 系统有 3 个有效的坐标系。

![image-20260623102413687](C:\Users\KKKK\Works\QtLearn\Note\QtUI编程常用组件.assets\image-20260623102413687.png)

- 图形项坐标

  图形项使用自己的局部坐标（Item Coordinates），通常以其中心为原点（0，0）。

  图形项的鼠标事件的坐标是用局部坐标表示的。

  创建自定义图形项，绘制图形项时只需要考虑其局部坐标，`QGraphicsScene` 和 `QGraphicsView` 会自动进行坐标转换。

  图形项的位置是其中心点在父坐标系中的坐标（如果没有父图形项的，其位置就是在场景中的坐标）

  如果一个图形项还是其他图形项的父项，父项进行坐标变换时，子项也做相同的坐标变换。

- 视图坐标

  视图坐标（View Coordinates）就是窗口界面（QWidget）的物理坐标，单位是像素。视口的左上角坐标总是（0，0）。

  所有的鼠标事件、拖放事件的坐标首先是视图坐标定义的，然后用户需要将这些坐标映射为场景坐标，以便和图形项交互。
  
- 场景坐标

  场景坐标（Scene Coordinates）描述了每个顶层图形项的位置。

  创建场景时可以自定义场景矩形区的坐标范围。例如：`scene = new QGraphicsScene(-400, -300, 800, 600);`。

  单位也是像素。

  每个图形项在场景中都有一个位置坐标，由函数 `QGraphicsItem::scenePos()` 给出。还有一个图形项边界矩形，由 `QGraphicsItem::sceneBoundingRect()` 函数给出。边界矩形可以使 `QGraphicsScene` 知道场景的哪个矩形发生了变化。场景变化时会发射 `QGraphicsScene::changed()` 信号，参数是一个场景的矩形列表，表示发生变化的矩形区。

- 坐标映射

  在 `QGraphicsView` 的视口上单击鼠标，通过函数 `QGraphicsView::mapToScene()` 可以将视图坐标映射为场景坐标，然后用 `QGraphicsScene::itemAt()` 函数可以获取场景中鼠标光标处的图形项。

### QGraphicsView视窗

`QGraphicsView` 是 Qt 图形视图框架（Graphics View Framework）的核心组件之一。它扮演着“视图窗口（View）”**的角色，专门用于可视化显示**“图形场景（QGraphicsScene）”中的内容，并允许用户通过鼠标、键盘与场景中的图形项（QGraphicsItem）进行交互。

#### 常用函数

**构造函数**

```cpp
// 构造一个没有场景的视图
QGraphicsView::QGraphicsView(QWidget *parent = nullptr);

// 构造一个视图，并自动将其与指定的场景(scene)关联
QGraphicsView::QGraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
```

**场景关联与基础设置**

```cpp
// 设置当前视图需要显示的场景
void QGraphicsView::setScene(QGraphicsScene *scene);

// 获取当前视图关联的场景指针，如果没有关联则返回 nullptr
QGraphicsScene *QGraphicsView::scene() const;

// 设置视图在场景中的可视区域（场景矩形）
void QGraphicsView::setSceneRect(const QRectF &rect);
void QGraphicsView::setSceneRect(qreal x, qreal y, qreal w, qreal h);

// 获取当前视图的可视区域矩形
QRectF QGraphicsView::sceneRect() const;
```

**视图变换（缩放、旋转、平移）**

```cpp
// 缩放视图。sx 和 sy 分别是横向和纵向的缩放倍数（例如：1.2 表示放大 20%）
void QGraphicsView::scale(qreal sx, qreal sy);

// 旋转视图。angle 是旋转角度（顺时针为正数，逆时针为负数）
void QGraphicsView::rotate(qreal angle);

// 平移视图。dx 和 dy 是在屏幕坐标系下的平移像素距离
void QGraphicsView::translate(qreal dx, qreal dy);

// 彻底重置视图的所有变换（恢复到没有放大、缩小、旋转的初始状态）
void QGraphicsView::resetTransform();

// 直接设置自定义的变换矩阵
void QGraphicsView::setTransform(const QTransform &matrix, bool combine = false);

// 获取当前视图的变换矩阵
QTransform QGraphicsView::transform() const;

// 确保指定的矩形区域或图形项在视图中完全可见（必要时会自动平移或缩放视图）
void QGraphicsView::ensureVisible(const QRectF &rect, int xmargin = 50, int ymargin = 50);
void QGraphicsView::ensureVisible(qreal x, qreal y, qreal w, qreal h, int xmargin = 50, int ymargin = 50);
void QGraphicsView::ensureVisible(const QGraphicsItem *item, int xmargin = 50, int ymargin = 50);

// 缩放并平移视图，使得指定的矩形区域或整个场景完美填充当前的视图窗口
void QGraphicsView::fitInView(const QRectF &rect, Qt::AspectRatioMode aspectRadioMode = Qt::IgnoreAspectRatio);
void QGraphicsView::fitInView(qreal x, qreal y, qreal w, qreal h, Qt::AspectRatioMode aspectRadioMode = Qt::IgnoreAspectRatio);
void QGraphicsView::fitInView(const QGraphicsItem *item, Qt::AspectRatioMode aspectRadioMode = Qt::IgnoreAspectRatio);
```

**坐标转换（Mapping）**

```cpp
// 将视图（局部）坐标转换成场景坐标
QPointF QGraphicsView::mapToScene(const QPoint &point) const;
QRectF QGraphicsView::mapToScene(const QRect &rect) const;
QPolygonF QGraphicsView::mapToScene(const QPolygon &polygon) const;
QPainterPath QGraphicsView::mapToScene(const QPainterPath &path) const;

// 将场景坐标转换成视图（局部）坐标
QPoint QGraphicsView::mapFromScene(const QPointF &point) const;
QRect QGraphicsView::mapFromScene(const QRectF &rect) const;
QPolygon QGraphicsView::mapFromScene(const QPolygonF &polygon) const;
QPainterPath QGraphicsView::mapFromScene(const QPainterPath &path) const;
```

**行为与交互模式配置**

```cpp
// 设置拖拽模式。可选值：
// QGraphicsView::NoDrag (什么都不做)
// QGraphicsView::MinimalViewportUpdate (框选模式，鼠标拖动会拉出选择框)
// QGraphicsView::ScrollHandDrag (手势拖拽模式，鼠标变成小手，按住可以拖动整个视口)
void QGraphicsView::setDragMode(QGraphicsView::DragMode mode);
QGraphicsView::DragMode QGraphicsView::dragMode() const;

// 设置视口更新模式（用于性能优化，决定画面如何重绘）
void QGraphicsView::setViewportUpdateMode(QGraphicsView::ViewportUpdateMode mode);
QGraphicsView::ViewportUpdateMode QGraphicsView::viewportUpdateMode() const;

// 设置当缩放或平移时，视图的锚点位置（例如：以鼠标所在位置为中心缩放，还是以视图中心缩放）
void QGraphicsView::setResizeAnchor(QGraphicsView::ViewportAnchor anchor);
QGraphicsView::ViewportAnchor QGraphicsView::resizeAnchor() const;

void QGraphicsView::setTransformationAnchor(QGraphicsView::ViewportAnchor anchor);
QGraphicsView::ViewportAnchor QGraphicsView::transformationAnchor() const;

// 设置背景刷和前景刷（通常直接调用 scene 的，但 view 也可以独立设置覆盖）
void QGraphicsView::setBackgroundBrush(const QBrush &brush);
QBrush QGraphicsView::backgroundBrush() const;

void QGraphicsView::setForegroundBrush(const QBrush &brush);
QBrush QGraphicsView::foregroundBrush() const;

// 设置或获取用来渲染的底层视口部件（例如：可以传入 QOpenGLWidget 以开启硬件加速）
void QGraphicsView::setViewport(QWidget *widget);
QWidget *QGraphicsView::viewport() const;
```

#### 常用信号

```cpp
// 当用户的橡胶圈（Rubber Band）选择框所圈定的区域发生改变时触发
// 比如在 DragMode 为 RubberBandDrag 时，鼠标拖出的蓝色选择框大小变化时
void QGraphicsView::rubberBandChanged(QRect viewportRect, QPointF fromScenePoint, QPointF toScenePoint);
```

> 如果你想在 `QGraphicsView` 中捕获“鼠标点击了哪里”、“双击了哪个物体”这类信号，通常有三种正确途径，而不是在 View 中找 Signal：
>
> 1. **使用 `QGraphicsScene` 的信号：** `QGraphicsScene` 提供了丰富的交互信号，通常直接连接场景的信号更方便。
> 2. **重写（Override）事件虚函数：** 如果你需要定制复杂的鼠标滚轮缩放、鼠标右键菜单，应该创建一个继承自 `QGraphicsView` 的自定义类，并重写它的事件处理器：

### QGraphicsScene场景

`QGraphicsScene` 是 Qt 图形视图框架（Graphics View Framework）的**核心管理中心**。它扮演着“三维世界里的舞台”或“画布（Canvas）”的角色。

`QGraphicsScene` 本身是**不可见**的，它只负责在内存中维护和管理所有的图形项（`QGraphicsItem`），处理它们的位置、碰撞检测、状态选中以及事件分发。要把它显示出来，必须将其关联到一个或多个 `QGraphicsView`（视口）上。

#### 常用函数

**构造函数**

```cpp
// 构造一个空的图形场景
QGraphicsScene::QGraphicsScene(QObject *parent = nullptr);

// 构造一个指定大小和坐标系范围的图形场景
QGraphicsScene::QGraphicsScene(const QRectF &sceneRect, QObject *parent = nullptr);
QGraphicsScene::QGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);
```

**场景尺寸（SceneRect）**

```cpp
// 设置场景的边界矩形（定义了场景的逻辑坐标系范围）
void QGraphicsScene::setSceneRect(const QRectF &rect);
void QGraphicsScene::setSceneRect(qreal x, qreal y, qreal w, qreal h);

// 获取当前场景的边界矩形
QRectF QGraphicsScene::sceneRect() const;

// 这是一个极其有用的函数：根据当前场景中所有 Item 的边界，自动计算并返回一个刚能包裹住它们的矩形
QRectF QGraphicsScene::itemsBoundingRect() const;
```

**图形项（Item）的管理（添加与删除）**

```cpp
// 将一个已有的 QGraphicsItem（或其派生类）添加到场景中
void QGraphicsScene::addItem(QGraphicsItem *item);
```

**添加 Qt 内置的基础快捷图形项**

为了方便开发，场景提供了直接创建并添加基础图形的方法，它们会返回创建好的对象指针：

```cpp
// 添加椭圆/圆
QGraphicsEllipseItem *QGraphicsScene::addEllipse(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());
QGraphicsEllipseItem *QGraphicsScene::addEllipse(qreal x, qreal y, qreal w, qreal h, const QPen &pen = QPen(), const QBrush &brush = QBrush());

// 添加直线
QGraphicsLineItem *QGraphicsScene::addLine(const QLineF &line, const QPen &pen = QPen());
QGraphicsLineItem *QGraphicsScene::addLine(qreal x1, qreal y1, qreal x2, qreal y2, const QPen &pen = QPen());

// 添加矩形
QGraphicsRectItem *QGraphicsScene::addRect(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());
QGraphicsRectItem *QGraphicsScene::addRect(qreal x, qreal y, qreal w, qreal h, const QPen &pen = QPen(), const QBrush &brush = QBrush());

// 添加多边形
QGraphicsPolygonItem *QGraphicsScene::addPolygon(const QPolygonF &polygon, const QPen &pen = QPen(), const QBrush &brush = QBrush());

// 添加文本（支持纯文本和 HTML 富文本）
QGraphicsTextItem *QGraphicsScene::addText(const QString &text, const QFont &font = QFont());
QGraphicsSimpleTextItem *QGraphicsScene::addSimpleText(const QString &text, const QFont &font = QFont());

// 添加图片（像素图）
QGraphicsPixmapItem *QGraphicsScene::addPixmap(const QPixmap &pixmap);

// 嵌入标准的 QWidget 控件（如 QPushButton、QLineEdit 等）
QGraphicsProxyWidget *QGraphicsScene::addWidget(QWidget *widget, Qt::WindowFlags wFlags = Qt::WindowFlags());
```

**移除与清空 Item **

```cpp
// 将 Item 从场景中移除（注意：此函数只将 Item 从场景剥离，不会 delete 释放内存，需手动销毁）
void QGraphicsScene::removeItem(QGraphicsItem *item);

// 从场景中移除并销毁（delete）所有的 Item，彻底清空整个画布
void QGraphicsScene::clear();
```

**图形项的检索与碰撞检测**

```cpp
// 获取当前场景中所有的 Item 列表（默认按照 Z 轴从高到低排序）
QList<QGraphicsItem *> QGraphicsScene::items(Qt::SortOrder order = Qt::DescendingOrder) const;

// 获取与指定点、矩形、多边形或路径相交/包含的所有 Item
QList<QGraphicsItem *> QGraphicsScene::items(const QPointF &pos, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape, Qt::SortOrder order = Qt::DescendingOrder) const;
QList<QGraphicsItem *> QGraphicsScene::items(const QRectF &rect, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape, Qt::SortOrder order = Qt::DescendingOrder) const;

// 获取在指定场景坐标 (x, y) 处最顶层的那个 Item，如果没有则返回 nullptr（极常用）
QGraphicsItem *QGraphicsScene::itemAt(const QPointF &position, const QTransform &deviceTransform) const;
QGraphicsItem *QGraphicsScene::itemAt(qreal x, qreal y, const QTransform &deviceTransform) const;

// 获取当前被用户选中的所有 Item 的列表（Item 需开启 QGraphicsItem::ItemIsSelectable 属性）
QList<QGraphicsItem *> QGraphicsScene::selectedItems() const;
```

**工具函数**

```cpp
// 设置/获取场景的背景画刷（可以用颜色，也可以用纹理图片填充背景）
void QGraphicsScene::setBackgroundBrush(const QBrush &brush);
QBrush QGraphicsScene::backgroundBrush() const;

// 设置/获取场景的前景画刷（通常用来在最上层绘制网格线、坐标轴等）
void QGraphicsScene::setForegroundBrush(const QBrush &brush);
QBrush QGraphicsScene::foregroundBrush() const;

// 获取当前正在显示这个场景的所有 QGraphicsView 视图列表（一个场景可以同时在多个视图显示）
QList<QGraphicsView *> QGraphicsScene::views() const;

// 手动强制触发更新、重绘整个场景
void QGraphicsScene::update(const QRectF &rect = QRectF());
```

#### 常用信号

```cpp
// 核心信号：当场景中的某一块区域发生改变（如 Item 移动、重绘、删除）时触发
// 参数 region 包含了所有发生重绘的矩形区域
void QGraphicsScene::changed(const QList<QRectF> &region);

// 当场景的边界矩形（sceneRect）发生改变时触发
void QGraphicsScene::sceneRectChanged(const QRectF &rect);

// 极常用：当场景中物体的“选中状态”发生改变时触发。可以通过 selectedItems() 获取当前最新被选中的项
void QGraphicsScene::selectionChanged();

// 当场景中获取键盘焦点的 Item 发生切换时触发
void QGraphicsScene::focusItemChanged(QGraphicsItem *newFocusItem, QGraphicsItem *oldFocusItem, Qt::FocusReason reason);
```

### QGraphicsItem基本图形项 

`QGraphicsItem` 是 Qt 图形视图框架（Graphics View Framework）中所有**图形项的基类**。

**`QGraphicsItem` 并不是 `QObject` 的子类，因此它本身【没有】任何 Qt 信号（Signals）！**

如果你需要让一个自定义的 Item 支持信号槽（比如被点击时发导一个自定义信号），你通常有两种解决方案：

1. **多重继承：** 让你的自定义类同时继承 `QObject` 和 `QGraphicsItem`（注意 `QObject` 必须写在前面）。
2. **继承 `QGraphicsObject`：** Qt 提供了一个官方封装类 `QGraphicsObject`，它已经帮你把 `QObject` 和 `QGraphicsItem` 组合好了，自带信号槽功能。

####  常用的核心内置子类

Qt 已经为你准备好了很多开箱即用的标准图形项：

| **派生类名称**                | **用途说明**                                                 |
| ----------------------------- | ------------------------------------------------------------ |
| **`QGraphicsRectItem`**       | 矩形项                                                       |
| **`QGraphicsEllipseItem`**    | 椭圆 / 圆形项                                                |
| **`QGraphicsLineItem`**       | 直线段项                                                     |
| **`QGraphicsPolygonItem`**    | 多边形项                                                     |
| **`QGraphicsPixmapItem`**     | 图片 / 像素图项                                              |
| **`QGraphicsTextItem`**       | 支持 HTML 富文本的文本项（可编辑、可选择）                   |
| **`QGraphicsSimpleTextItem`** | 简单的单行纯文本项（性能比 TextItem 更好）                   |
| **`QGraphicsProxyWidget`**    | 极其强大，可以将任意 `QWidget`（如 QPushButton）嵌入到场景中 |

#### 常用函数

**基础状态与特性开关（Flags）**

```cpp
// 设置图形项的功能特性
void setFlag(GraphicsItemFlag flag, bool enabled = true);
void setFlags(GraphicsItemFlags flags);

// 🔍 极其常用的标志位（Flags）：
// QGraphicsItem::ItemIsMovable        -> 允许鼠标拖动该物体
// QGraphicsItem::ItemIsSelectable     -> 允许鼠标点击选中该物体
// QGraphicsItem::ItemIsFocusable      -> 允许接受键盘输入焦点
// QGraphicsItem::ItemSendsGeometryChanges -> 当物体坐标改变时发送通知（常用于连线跟随）
```

**位置与坐标控制（Geometry）**

```cpp
// 设置该 Item 在场景（或父 Item）坐标系中的位置
void setPos(const QPointF &pos);
void setPos(qreal x, qreal y);

// 获取当前的坐标位置
QPointF pos() const;
qreal x() const;
qreal y() const;

// 移动相对距离（在当前位置基础上累加 dx, dy）
void moveBy(qreal dx, qreal dy);

// 每一个自定义 Item 都必须实现的纯虚函数：返回物体的几何外包矩形（用于刷新和碰撞检测）
virtual QRectF boundingRect() const = 0;
```

**图形变换（旋转、缩放）**

```cpp
// 设置物体的旋转角度（单位度，顺时针为正。注意：会覆盖之前的角度）
void setRotation(qreal angle);
qreal rotation() const;

// 设置物体的缩放比例（1.0 为原大小，2.0 为放大一倍）
void setScale(qreal factor);
qreal scale() const;

// 关键函数：设置旋转和缩放的“中心基准点”（如果不设置，默认以物体局部坐标的 0,0 为中心旋转）
void setTransformOriginPoint(const QPointF &origin);
void setTransformOriginPoint(qreal x, qreal y);
QPointF transformOriginPoint() const;

// 重置物体的变换矩阵（注意：正如你之前遇到的，它不重置独立属性 rotation 和 scale）
void resetTransform();
```

**层级与父子关系**

```cpp
// 设置堆叠顺序（Z轴）。Z值越大的物体，显示在越上层，会遮挡Z值小的物体
void setZValue(qreal z);
qreal zValue() const;

// 设置父图形项。子 Item 会随着父 Item 一起移动、旋转、缩放
void setParentItem(QGraphicsItem *parent);
QGraphicsItem *parentItem() const;

// 获取当前 Item 的所有子图形项列表
QList<QGraphicsItem *> childItems() const;
```

**显示状态与数据绑定**

```cpp
// 控制显示与隐藏
void setVisible(bool visible);
bool isVisible() const;

// 控制是否接收鼠标事件（如果设为 false，鼠标会直接穿透该物体）
void setAcceptedMouseButtons(Qt::MouseButtons buttons);

// 绑定自定义数据。相当于给 Item 挂载一个键值对字典，非常适合用来存放业务 ID 或业务对象
void setData(int key, const QVariant &value);
QVariant data(int key) const;
```

#### 常用信号

由于 `QGraphicsItem` 没有信号，如果你想在它身上玩出花样（比如**鼠标悬停变色、双击弹出窗口、自定义绘制精美图案**），你就必须通过子类化它，并重写（Override）它的虚函数：

```cpp
class MyItem : public QGraphicsItem {
public:
    // 1. 必须重写：定义物体的边界
    QRectF boundingRect() const override {
        return QRectF(-25, -25, 50, 50); // 以中心为原点的 50x50 正方形
    }

    // 2. 必须重写：实现精美的具体绘制
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        painter->setPen(Qt::black);
        painter->setBrush(Qt::red);
        painter->drawRect(boundingRect()); // 画一个红色的正方形
    }

protected:
    // 3. 可选重写：捕获鼠标按下事件
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        // 当被点击时，可以做逻辑处理
        qDebug() << "我被点击了！";
        
        // 如果想让 Item 继续保持“能被拖动”的特性，必须调用基类的事件处理
        QGraphicsItem::mousePressEvent(event);
    }
    
    // 4. 可选重写：捕获鼠标悬停（需要先调用 setAcceptHoverEvents(true)）
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override {
        qDebug() << "鼠标进来了";
    }
};
```

