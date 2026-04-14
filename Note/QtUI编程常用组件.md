# Qt UI 编程常用组件基础

## QWidget



## QLabel

`QLabel` 是常用的标签组件，可以显示文字，也可以设置一个图片。

### buddy机制

QLabel 的 buddy 机制本质是：QLabel 可以从文本中识别“&字母”生成 Alt+字母快捷键，当用户按下这个快捷键时，Qt 会把输入焦点自动切换到 QLabel 通过 setBuddy 指定的那个控件上。也就是说 QLabel 负责定义快捷键，buddy 控件负责接收焦点。

使用时必须满足两个条件：第一，QLabel 的文本中必须包含 & 加字母，比如 Name(&N) 或 &Name，这样才会生成 Alt+N 的快捷键；第二，必须调用 setBuddy 绑定一个目标控件，比如输入框，否则快捷键不会执行焦点跳转。

需要注意的是 && 表示显示一个普通的 &，不会生成快捷键；如果 & 后面不是字母，或者快捷键冲突，可能不会生效；buddy 机制的作用仅仅是“快捷键触发后自动 setFocus 到目标控件”，不负责执行其他逻辑。

## QLineEdit

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

## QSpinBox

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


