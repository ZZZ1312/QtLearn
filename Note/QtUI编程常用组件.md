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

## 常用函数

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

## 常用信号

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

# QDateTimeEdit

## 常用函数

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

## 常用信号

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

# QComboBox

`QComboBox` 时下拉列表框组件，提供一个下拉列表共用户选择，也可以当作一个`QLineEdit` 用作用户输入。

除了显示可下拉列表外，每个项（Item，或称列表项）还可以关联一个`QVariant`类型的变量，用于存储一些不可见的数据。

可以在Qt Designer中双击`QComboBox`，会出现列表项编辑器，可以在该编辑器中给`QComboBox`添加简单项，还可以为每一项设置简单图标。

## 用法

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

## 常用信号

`QComboBox` 组件上选择项发生变化时，会发射如下两个信号。

```cpp
void currentIndexChanged(int index);
void currentIndexChanged(const QString &text);
```

如果`QComboBox`可以输入时，用户输入了内容后，会发射以下的信号：

```cpp
void editTextChanged(const QString &text);
```

# QPlainText

`QPlainText` 是一个多行文本编辑器，用于显示和编辑多行简单文本。

## 常用函数

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

# QToolButton

`QToolButton` 有一个 `setDefaultAction()` h桉树，可以使其与一个 Action 关联。按钮的文字、图标、ToolTip 都将自动设置为与其关联的 Action 一直。

> 单击一个 `QToolButton` 就是执行 Action 的槽函数，与工具栏上的按钮一样。

`QToolButton` 有一个 `setMenu()` 函数，可以为其设置一个下拉式菜单。


