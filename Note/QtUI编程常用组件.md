# Qt UI 编程常用组件基础

## QWidget

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

