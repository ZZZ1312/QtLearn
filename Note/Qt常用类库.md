# Qt 常用类

## QString

`QString` 是Qt实现的一个字符串类。相比于C++原生字符串类 `std::string` 更加易用且功能强大。

> `QString` 内部以 UTF-16 编码存储，每个字符通常占2字节。

### 基本信息获取

```cpp
str.length();    // 长度（QChar 数量）  
str.size();      // 同 length()  
str.isEmpty();   // 是否为空  
str.isNull();    // 是否为 null（未初始化）
```

区别：

- `isEmpty()`：长度为 0
- `isNull()`：未指向数据（很少用）

---

### 访问字符（QChar）

```
str.at(i);   // 安全访问（越界会断言）  
str[i];      // 可读写访问  
str.front(); // 第一个字符（Qt6）  
str.back();  // 最后一个字符（Qt6）
```

### 修改字符串

#### 添加

```
str.append("abc");  
str += "abc";  

str.prepend("abc");  // 前面添加
```

#### 插入 / 删除

```
str.insert(pos, "abc");  
str.remove(pos, len);  
str.remove("abc");        // 删除子串  
str.chop(n);              // 删除末尾 n 个字符  
str.clear();              // 清空
```

#### 替换

```
str.replace("old", "new");  
str.replace(pos, len, "new");
```

### 查找与判断（非常常用）

```
str.contains("abc");        // 是否包含  
str.startsWith("abc");      // 是否以...开头  
str.endsWith("abc");        // 是否以...结尾  

str.indexOf("abc");         // 第一次出现位置  
str.lastIndexOf("abc");     // 最后一次出现
```

### 截取字符串

```
str.left(n);        // 左 n 个  
str.right(n);       // 右 n 个  
str.mid(pos, len);  // 中间截取
```

### 分割与拼接（高频）

```
QStringList list = str.split(",");  // 分割  

QString s = list.join("-");         // 拼接
```

### 大小写与格式处理

```
str.toUpper();     // 转大写  
str.toLower();     // 转小写  

str.trimmed();     // 去两端空白  
str.simplified();  // 去多余空格（压缩）
```

### 数字转换（很常用）

#### QString → 数字

```cpp
int toInt(bool *ok = Q_NULLPTR, int base = 10);
long toLong(bool *ok = Q_NULLPTR, int base = 10);
short toShort(bool *ok = Q_NULLPTR, int base = 10);
uint toUInt(bool *ok = Q_NULLPTR, int base = 10);
ulong toULong(bool *ok = Q_NULL_PTR, int base = 10);
```

这些函数如果不设置参数，默认表示从十进制表示的字符串转换为整数，若指定整数，还可以直接将二进制、十进制字符串转换为整数。

```
int n = str.toInt();  
double d = str.toDouble();  
float f = str.toFloat();

带判断：

bool ok;  
int n = str.toInt(&ok);
```

#### 数字 → QString

```cpp
QString &setNum(int n, int base = 10);
static QString number(int n, int base = 10);
```

```cpp
QString s = QString::number(123);  
QString s2 = QString::number(3.14);

QString num1;
num1.setNum(1);
num2.setNum(3);
```

### 格式化字符串（重点）

```
QString s = QString("Hello %1").arg("World");
```

多个参数：

```
QString s = QString("%1 + %2 = %3")  
                .arg(1)  
                .arg(2)  
                .arg(3);
```

👉 特点：

- 类型安全
- 替代 printf

### 编码转换（很重要）

#### QString → QByteArray / char*

```
QByteArray ba = str.toUtf8();  
const char* cstr = ba.constData();
```

#### QByteArray / std::string → QString

```
QString s = QString::fromUtf8("你好");  
QString s2 = QString::fromStdString(stdStr);
```

### 比较操作

```
str == "abc";  
str != "abc";  

str.compare("abc");  // 返回 <0, =0, >0
```

👉 忽略大小写：

```
str.compare("abc", Qt::CaseInsensitive);
```

---

### 重复与填充

```
str.repeated(3);     // 重复 3 次  
str.fill('A', 5);    // 填充为 "AAAAA"
```

### 内存与性能相关（进阶）

```
str.reserve(100);    // 预分配空间  
str.capacity();      // 当前容量  
str.squeeze();       // 释放多余内存
```

### 遍历方式（推荐）

```
for (QChar ch : str) {  
    // 遍历字符  
}

 // 或：

for (int i = 0; i < str.size(); ++i) {  
    QChar ch = str[i];  
}
```

### 与 QChar 配合

```
str.append(QChar('A'));  
str.contains(QChar('A'));
```

### 常见易错点（重点）

#### 临时对象问题

```
const char* p = str.toUtf8().data(); // ❌

👉 正确：

QByteArray ba = str.toUtf8();  
const char* p = ba.data();
```

#### length ≠ 字符数（Unicode）

```
QString s = "😀";  
s.length();  // 2（不是1）
```

#### 拼接性能问题

```cpp
for (...) {  
    str += "abc";  // 可能慢  
}
```

👉 优化：

```cpp
str.reserve(1000);
```
