#  Qt基础类和常用函数

## Qt全局定义

`<QtGlobal>`头文件中包含了Qt类库的一些全局定义，包括基础数据类型、函数和宏。

> 一般的Qt类的头文件都会包含该文件。

### 数据类型

Qt为常见数据类型定义了符号，确保在各平台上有统一的长度

| Qt数据类型 | 对应C++中的类型        | 字节数 |
| ---------- | ---------------------- | ------ |
| qint8      | singned char           | 1      |
| qint16     | signed short           | 2      |
| qint32     | singed int             | 4      |
| qint64     | long long int          | 8      |
| qlonglong  | long long int          | 8      |
| quint8     | usigned char           | 1      |
| quint16    | unsigned short         | 2      |
| quint32    | unsigned int           | 4      |
| quint64    | unsigned long long int | 8      |
| qulonglong | usigned long long int  | 8      |
| uchar      | unsigned char          | 1      |
| ushort     | unsigned short         | 2      |
| uint       | unsigned int           | 4      |
| ulong      | unsigned long          | 8      |
| qreal      | double                 | 8      |
| qfloat16   | 无                     | 2      |

默认情况下`qreal`是8字节的`double`类型，如果Qt编译时使用了`-qreal float`进行配置，就是4字节`float`类型浮点数。

`qfloat16`是从`Qt 5.9.0`中新增的一个类，用于表示16位的浮点数，要使用`qfloat16`，需要包含头文件`<QFloat16>`。

### 函数

`<QtGlobal`头文件中包含一些常用函数的定义，这些函数多以模板类型作为参数，返回相应的模板类型，模板类型可以用任何其他类型替换。如果以`double`或`float`类型数作为参数的，一般有两个参数版本的同名函数。

| 函数                                                         | 功能                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `T qAbs(const T& value)`                                     | 返回变量 value 的绝对值                                      |
| `const T &qBound(const T &min, const T &value, const T&max)` | 返回 value 限定在 min 至 max 范围之内的值（ value 在 min 和 max 之间，返回 value；否则，当 value 小于 min ，返回 min；value 大于 max，返回 max。） |
| `bool qFuzzy(double p1, double p2)`                          | 若 p1 和 p2 近似相等，返回 true                              |
| `bool qFuzzyIsNull(double d)`                                | 如果参数 d 约等于 0， 返回 true                              |
| `double qInf()`                                              | 返回无穷大的数                                               |
| `bool qIsFinite(double d)`                                   | 若 d 是一个有限的数，返回 true                               |
| `bool qIsInf(double d)`                                      | 若 d 是一个无限大的数，返回 true                             |
| `bool qIsNan(double d)`                                      | 若 d 不是一个数，返回 true                                   |
| `const T &qMax(const T &value1, const T &value2)`            | 返回 value1 和 value2 中较大的值                             |
| `const T &qMin(const T &value1, const  T &value2)`           | 返回 value1 和 value2 中较小的值                             |
| `qint64 qRound64(double value)`                              | 将 value 近似为最接近的 qint64 整数                          |
| `int qRound(double value)`                                   | 将 value 近似为最接近的 int 整数                             |
| `int qrand()`                                                | 标准 C++ 中 `rand()` 函数的线程安全型版本，返回 0 值 RAND_MAX 之间的伪随机数 |
| `void qsrand(uint seed)`                                     | 标准 C++ 中 `srand()` 函数的线程安全型版本，使用种子 seed 对伪随机数序列初始化 |

### 宏定义

`<QtGlobal` 头文件中定义了很多宏，以下是一些比较常用的。

- `QT_VERSION`：表示 Qt 编译器版本，展开为数值形式 0xMMNNPP（MM = major，NN = minor，PP = patch）。常用于条件编译。

  > 例如 Qt 编译器版本为 Qt 5.9.1，则 QT_VERSION 为 0x050901。

- `QT_VERSION_CHECK`：这个宏接收3个整数，并将其转换为与 `QT_VERSION` 相同格式的整数。

  ```c++
  #if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
  // ....
  #else
  //...
  #endif
  ```

- `QT_VERSION_STR`：宏展开为 Qt 版本号的字符串，如“5.9.0”

- `Q_BYTE_ORDER`、`Q_BIG_ENDIAN`、`Q_LITTLE_ENDIAN`

  `Q_BYTE_ORDER`代表当前系统的大小端顺序，跟`Q_BIG_ENDIAN`、`Q_LITTLE_ENDIAN`进行比较，确定当前机器的大小端顺序。

- `Q_DECL_IMPORT`、`Q_DECL_EXPORT`：在使用或设计共享库库时，用于导入或导出库的内容。

- `Q_DECL_OVERRIDE`：类定义中，用于生命重载一个虚函数。使用该宏后，如果重载的虚函数没有进行任何重载操作，编译器将会报错。

- `Q_DECL_FINAL`：将虚函数定义为最终级别，不能再被重载；或定义一个类不能再被继承。

- `Q_UNUSED(name)`：用于定义在函数中不被使用的参数，使用该宏后，编译器将不再产生警告。

- `foeach(variable, container)`：用于遍历容器类。

- `forever{...}`：用于构造一个无限循环。

## QCoreApplication

`QCoreApplication` 是 Qt 框架中国非GUI应用程序的核心。它是整个应用程序的生命周期管理者和事件驱动源头。

### 职责

- **事件循环（Event Loop）**：它是 Qt 事件驱动机制的发动机。没有它，Qt 的定时器（QTimer）、网络请求（QNetworkAccessManager）以及信号与槽（Signals and Slots）的跨线程投递都无法工作。

- **命令行参数处理**：它在初始化时接管了 `main` 函数传入的 `argc` 和 `argv`。

- **语言本地化**：通过加载翻译文件（`.qm`），控制整个程序的语言切换。

- **应用级元数据**：存储应用程序的名称、版本、组织机构等信息（很多配置文件或注册表会自动读取这些信息）。

### 常用函数

**生命周期和事件循环**

```cpp
// 启动主事件循环，阻塞直到调用 quit()。返回值通常作为 main() 的返回码。
static int exec();

// 告诉应用程序退出事件循环，返回码为 0（代表正常退出）。
static void quit();

// 告诉应用程序带着指定的返回码退出事件循环。
static void exit(int returnCode = 0);

// 强制处理当前事件队列中所有积压的事件，直到没有事件可处理。
static void processEvents(QEventLoop::ProcessEventsFlags flags = QEventLoop::AllEvents);

// 强制处理当前事件队列中的事件，最多处理 maxtime 毫秒。
static void processEvents(QEventLoop::ProcessEventsFlags flags, int maxtime);
```

**应用程序元数据**

```cpp
// 设置/获取 组织名称（用于 QSettings 等类自动定位路径）
static void setOrganizationName(const QString &orgName);
static QString organizationName();

// 设置/获取 组织域名
static void setOrganizationDomain(const QString &orgDomain);
static QString organizationDomain();

// 设置/获取 应用程序名称
static void setApplicationName(const QString &application);
static QString applicationName();

// 设置/获取 应用程序版本
static void setApplicationVersion(const QString &version);
static QString applicationVersion();

// 获取当前正在运行的应用程序实例指针
static QCoreApplication *instance();
```

**文件路径与系统环境**

```cpp
// 获取当前应用程序可执行文件所在的目录（绝对路径，末尾不含斜杠）
static QString applicationDirPath();

// 获取当前应用程序可执行文件的完整绝对路径（包含文件名）
static QString applicationFilePath();

// 获取运行程序时传入的命令行参数列表
static QStringList arguments();

// 库文件的搜索路径管理
static QStringList libraryPaths();
static void setLibraryPaths(const QStringList &paths);
static void addLibraryPath(const QString &path);
static void removeLibraryPath(const QString &path);
```

**事件发送与管理**

```cpp
// 同步发送事件：直接调用 receiver 的 event() 函数，处理完才返回。
static bool sendEvent(QObject *receiver, QEvent *event);

// 异步投递事件：将事件放入 receiver 的事件队列中，立即返回，事件所有权移交 Qt。
static void postEvent(QObject *receiver, QEvent *event, int priority = Qt::NormalEventPriority);

// 从事件队列中移除指定接收者和特定类型的事件
static void removePostedEvents(QObject *receiver, int eventType = 0);

// 全局事件过滤器管理
void installNativeEventFilter(QAbstractNativeEventFilter *filterObj);
void removeNativeEventFilter(QAbstractNativeEventFilter *filterObj);
```

### 常用信号

```cpp
// 在事件循环即将退出（例如调用 quit() 或关闭最后一个主窗口）时触发
void aboutToQuit(QPrivateSignal);

// 当应用程序名称发生改变时触发
void applicationNameChanged();

// 当应用程序版本发生改变时触发
void applicationVersionChanged();

// 当组织名称发生改变时触发
void organizationNameChanged();

// 当组织域名发生改变时触发
void organizationDomainChanged();
```

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

## 容器类

### 顺序容器类

Qt 常用顺序容器有：`QList`、`QLinkedList`、`QVector`、`QStack` 和 `QQueue`。

#### `QList` 是最常用的容器

是以数组列表（array-list）的形式实现的。

提供下标索引方式（即方括号`[]`）来访问数据，也提供了`at()`函数。

可以通过`<<`向顺序容器中添加数据。如下：

```c++
QList<QString> list;
list << "one" << "two" << "three";
```

`isEmpty()`在数据项为空时返回true。

#### `QLinkedList` 

`QLinkedList` 是链式列表，数据项使用链表的方式存放，基于迭代器访问数据项。

该容器类没有通过下标索引访问数据项的方式。

#### `QVector` 

`QVector` 是动态数组，提供与`QList`完全一样的接口。

> 实际上，在Qt6中，这两个容器类已经几乎一样了。

#### `QStack` 

`QStack` 是栈，先入后出，主要操作函数是`push()`和`pop()`。

#### `QQueue`

`QQueue` 是队列，提供先入先出的功能，主要操作函数是 `enqueue()`和`dequeue()`。

### 关联容器类

Qt中的关联容器类型有：`QMap`、`QMultiMap`、`QHash`、`QMultiHash`和`QSet`。

以 `QMulti` 开头的容器，支持一个键关联多个值，`xxHash`系列的类使用哈希函数进行查找，速度更快。

#### `QSet`

`QSet` 是使用hash函数实现的集合类，内部用 `QHash` 实现。

#### `QMap` 

`QMap` 提供一个字典（关联数组），一个键对应一个值。

> `QMap` 存储数据是按照键的顺序的。如果不在乎顺序，使用`QHash`会更快。

```
// 使用QMap的案例
QMap<QString, int> map;
map["one"] = 1;
map["two"] = 2;
map["three"] = 3;

// 插入也可以使用insert函数
map.insert("four", 4);

// 移除一个键，使用remove
map.remove("two");

// 查找一个值，使用 [] 或 value() 函数
int num1 = map["one"];
int num2 = map.value("two");
// 如果QMap中没有要查找的键对应的值，那么就会返回一个默认值，如果值是字符串，则会返回一个空的字符串；如果使用value() 函数，还可以传入一个默认的返回值，在没找到时就会返回该值。
int num3 = map.value("three", 30);
```

#### `QMultiMap`

`QMultiMap`是`QMap`的子类，`QMap`的大多数函数都可以在`QMultiMap`中使用，但是在`QMultiMap`中的`replace()`函数相当于`QMap`中的`insert()`。

```
// QMultiMap 使用案例
QMultiMap<QString, int> map1, map2, map3;
map1.insert("plenty", 100);
map1.insert("plenty", 2000);
map2.insert("pletny", 5000);
map3 = map1 + map2;
```

`QMultiMap`中不提供`[]`操作符，`value()`函数返回的是最新插入的键的单个值。

使用`values()`函数获取到键对应的所有值，返回值是`QList<T>`类型。

```
QList<int> values = map.values("plenty");
for (int i = 0; i < values.size(); ++i)
	count << values.at(i) << endl;
```

#### `QHash` 和 `QMultiHash` 

`QHash` 是基于哈希函数来实现字典功能的容器类。

`QHash` 与 `QMap` 用法类似。`QMultiHash` 与 `QMultiMap` 用法相似。

### 容器类迭代

Qt中的容器类支持Java风格的迭代器和STL风格的迭代器。

Java风格迭代器更易于使用，且提供一些高级功能；STL类型迭代器效率更高，且可以使用STL中的算法。

Qt中提供了一个关键字foreach（实际上是`<QtGlobal>`中定义的一个宏，用于方便地访问容器里地的所有数据项。

#### Java风格迭代器

每个容器类，有两个Java类型迭代器，一个用于只读，另一个用于读写。

| 容器类                                | 只读迭代器               | 读写迭代器                        |
| ------------------------------------- | ------------------------ | --------------------------------- |
| `QList<T>`、`QQueue<T>`               | `QListIterator<T>`       | `QMultableListIterator<T>`        |
| `QLinkedList<T>`                      | `QLinkedListIterator<T>` | `QMultiableLinkedListIterator<T>` |
| `QVector<T>`、`QStack<T>`             | `QVectorIterator<T>`     | `QMutableVectorIterator<T>`       |
| `QSet<T>`                             | `QSetIterator<T>`        | `QMutableSetIterator<T>`          |
| `QMap<T>`、`QMuultiMap<Key, T>`       | `QMapIterator<T>`        | `QMutableMapIterator<T>`          |
| `QHash<Key, T>`、`QMultiHash<Key, T>` | `QHashIterator<T>`       | `QMutableHashIterator<T>`         |

##### 迭代器常用函数

Java风格迭代器常用函数如下：

| 容器类                  | 功能                                      |
| ----------------------- | ----------------------------------------- |
| void toFont()           | 迭代器移动到列表最前端                    |
| void toBack()           | 迭代器移动到列表最后端                    |
| bool hasNext()          | 如果迭代器不是位于列表最后位置，返回 true |
| const T &next()         | 返回下一个数据项，并且迭代器后移一个位置  |
| const T& peekNext()     | 返回下一个数据项，但是不移动迭代器位置    |
| bool hasPrevious()      | 如果迭代器不是位于列表最前面，返回 true   |
| const T& previous()     | 返回前一个数据项，并且迭代器前移一个位置  |
| const T& peekPrevious() | 返回前一个数据项，但是不移动迭代器指针    |

```c++
// 案例一，遍历迭代器
QList<QString> list;
list << "A" << "B" << "C" << "D";
QListIterator<QString> i(list);
while (i.hasNext())
	qDebug() << i.next();
```

```c++
// 案例二：反向遍历
QListIterator<QString> i(list);
i.toBack();
while (i.hasPrevious())
	qDebug() << i.previous();
```

```c++
// 案例三：从容器中移除数据
QList<int> list;
list << 1 << 2 << 3 << 4;
QMutableListIterator<int> i(list);
while (i.hasNext())
{
	if (i.next() % 2 != 0)
		i.remove();
}
```

> 关联容器的迭代器多了`key()`和`value()`两个函数，用于获取键和值

```c++
// 案例四：关联容器迭代器使用
QMap<QString, QString> map;
map.insert("Paris", "France");
map.insert("New York", "USA");
map.insert("Mexico City", "USA");
map.insert("Moscow", "Russia");

QMutableMapIterator<QString, QString> i(map);
while (i.hasNext())
{
	if (i.next().key().endsWith("City"))
		i.remove();
}
```

```c++
// 案例五：多值容器里的便利，使用findNext()或findPrevious()查找下一个或上一个值
QMutableMapIterator<QString, QString> i(map);
while (i.findNext("USA"))
	i.remove();
```

#### STL风格迭代器

STL风格迭代器与Qt和STL原生算法兼容，并且进行了速度优化。

每一个容器类，都有两个STL类型迭代器，一个用于只读访问，一个用于读写访问。

> 无需修改数据时，一定要使用只读迭代器，速度更快

| 容器类                                | 只读迭代器                       | 读写迭代器                 |
| ------------------------------------- | -------------------------------- | -------------------------- |
| `QList<T>`、`QQueue<T>`               | `QList<T>:::const_iterator`      | `QList<T>::iterator`       |
| `QLinkedList<T>`                      | `QLinkedList<T>::const_iterator` | `QLinkedList<T>::iterator` |
| `QVector<T>`、`QStack<T>`             | `QVector<T>::const_iterator`     | `QVector<T>::iterator>`    |
| `QMap<Key, T>`、`QMultiMap<Key, T>`   | `QMap<Key, T>::const_iterator`   | `QMap<Key, T>::iterator`   |
| `QHash<Key, T>`、`QMultiHash<Key, T>` | `QHash<Key, T>::const_iterator`  | `QHash<Key, T>::iterator`  |

```c++
// 案例1：顺序容器迭代器遍历
QList<QString> list;
list << "A" << "B" << "C" << "D";
QList<QString>::const_iteraator i;
for (i = list.constBegin(); i != list.constEnd(); ++i)
{
	qDebug() << *i;
}
```

```c++
// 案例2：反向迭代器遍历容器
QList<QString> list;
list << "A" << "B" << "C" << "D";
QList<QString>::reverse_iterator i;
for (i = lilst.rbegin(); i != list.rend(); ++i)
{
	qDebug() << *i;
}
```

```c++
// 案例3：关联容器遍历
// 对于关联容器，使用 * 会获取到数据项的值，如果要获取到键，使用key()函数，对应的，使用value()函数返回一个项的值
QMap<int, int> map;
// ...
QMap<int, int>::const_iterator i;
for (i = map.constBegin(); i != map.constEnd(); ++i)
{
	qDebug() << i.key() << ":" << i.value();
}
```

# Qt文件系统相关类

## `QFile` 

`QFile` 是 Qt 中专门用来操作文件的类。

继承自 `QFileDevice`，并进一步继承自 `QIODevice`。

### 常用函数

**文件生命周期与状态控制**

```cpp
// 构造函数，直接关联一个文件路径，可以是绝对路径或相对路径。
QFile(const QString &name);

// 修改关联的文件路径
void setFileName(const QString &name);

// 获取当前关联的文件名
QString fileName() const;
```

**打开、关闭与状态控制**

```cpp
// 打开文件。参数为打开模式标志位
bool open(QIODevice::OpenModeFlag mode) override;
/* 
枚举类型，主要取值如下
	- QIODevice::ReadOnly：以只读方式和打开文件
	- QIODevice::WriteOnly：以只写发那个是打开文件，该属性也隐含了 QIODevice::Truncate 选项
	- QIODevice::ReadWrite：以读写方式打开
	- QIODevice::Append：以追加模式打开，新数据添加到文件尾部
	- QIODevice::Truncate：以截取方式打开文件，原有文件内容全部被删除
	- QIODevice::Text 以文本方式打开文件，读取时换行符被自动替换为系统平台的编码。
*/

// 关闭文件
void close() override;

// 判断文件是否已经打开
bool isOpen() const;

// 强行将缓冲区的数据写入物理磁盘
bool flush();

// 获取当前发生的错误类型的枚举
QFileDevice::FileError error() const;

// 获取人类可读的错误原因字符串
QString errorString() const;
```

**数据读取操作**

```cpp
// 一次性读取文件中的所有数据
QByteArray readAll();

// 读取一行数据，遇到遇到换行符或达到 maxSize 时停止（maxSize为0代表不限制单行最大长度）
QByteArray readLine(qint64 maxSize = 0);

// 读取最多 maxSize 字节的数据，并存入用户自定义的 char 缓冲区中
qint64 read(char * data, qint64 maxSize);

// 读取最多 maxSize 字节的数据，并以 QByteArray 形式返回
QByteArray read(qint64 maxSize);
```

**数据写入操作**

```cpp
// 将 QByteArray 中的字节数据写入文件
qint64 write(const QByteArray &byteArray);

// 将 C 风格字符串（以 \0 结尾）写入文件
qint64 write(const char * data);

// 将自定义缓冲区 data 中指定长度 len 的二进制数据写入文件
qint64 write(const char *data, qint64 len);
```

**文件定位指针**

```cpp
// 获取当前读写光标在文件中的位置（字节偏移量）
qint64 pos() const override;

// 移动读写光标到指定的位置 pos
bool seek(qint64 pos) override;

// 判断当前光标是否已经到达文件末尾（End of File）
bool atEnd() const override;
```

**文件系统物理操作**

```cpp
// 获取当前文件的字节大小
qint64 size() const override;

// 检查文件在硬盘上是否存在
bool exists() const;
static bool QFile::exists(const QString &fileName); // 静态工具函数

// 从硬盘上彻底删除文件
bool remove();
static bool QFile::remove(const QString &fileName); // 静态工具函数

// 重命名或移动文件。成功返回 true
bool rename(const QString &newName);
static bool QFile::rename(const QString &oldNamee, const QString &newName); // 静态工具函数

// 复制文件到新路径（新路径文件已存在会失败，不会自动覆盖）
bool copy(const QString &newName);
static bool QFile::copy(const QString &fileName, cosnt QString &newName); // 静态工具函数
```

### 常用信号

```cpp
// 当有新数据从文件中“准备好被读取”时产生（在普通本地QFile中很少触发，主要在网络/管道通信中非常频繁）
void readRead();

// 当有一批数据写入到物理文件后产生，参数表示实际写入的字节数据，常用于文件传输进度条
void bytesWritten(qint64 bytes);

// 当文件通道关闭，或文件发生错误被强制阻断时发射（常用于多线程排查故障）
void aboutToClose();
```

> 提示：在通过 `connect` 连接 `readRead` 或 `bytesWritten` 时，因为它们是父类 `QIODevice` 的信号，如果编译器提示找不到信号，可以在连接时将发送端显式生命或转换为其他父类
>
> ```cpp
> connect(&file, &QIODevice::bytesWritten, this, [](qint64 bytes){
> 	qDebug() << "成功写入了" << bytes << "字节数据";
> })
> ```

## `QFileInfo`

`QFileInfo` 是 Qt 框架中专门用来**获取文件或目录属性**的工具类。它本身**不具备**读写文件内容的能力。

通过 `QFileInfo`，你可以轻松获取文件的绝对路径、纯文件名、文件大小、创建与修改时间、判断它是文件还是文件夹、是否有读写权限等。

> `QFileInfo` 的底层设计非常注重性能。当你第一次查询文件信息时，它会通过操作系统内核读取文件属性，并把这些信息**缓存**在类内部。
>
> **好处**：后续你连续调用 `size()`、`suffix()`、`isDir()` 时，它直接从内存缓存中读取，速度极快。
>
> **注意点**：如果你的程序在运行期间，别的进程（或者你的 `QFile`）修改了该文件的物理大小或删除了它，你需要手动调用 `fileInfo.refresh()` 刷新缓存，否则拿到的依然是旧数据。

### 常用函数

**构造与路径绑定**

```cpp
// 默认构造函数（未绑定任何路径，此时 exists() 返回 false）
QFileInfo::QFileInfo();

// 最常用：直接绑定一个文件或目录的路径
QFileInfo::QFileInfo(const QString &file);

// 传入已经打开或存在的 QFile 对象，获取其余关联的属性
QFileInfo::QFileInfo(const QFileDevice &file);

// 传入一个目录对象和相对其中的文件名
QFileInfo::QFileInfo(const QDir &dir, const QString &file);

// 拷贝构造函数
QFileInfo::QFileInfo(const QFileInfo &fileinfo);

// 中途修改或重新绑定路径
void QFileInfo::setFile(const QString &file);
void QFileInfo::setFile(const QFileDevice &file);
```

**路径与名字切分**

```cpp
// 获取去掉文件名后的纯目录路径。返回: "/A/B"
QString QFileInfo::absolutePath() const;
QString QFileInfo::path() const; // 相对路径复读机，通常建议用上面那个

// 获取完整的绝对路径（含文件名）。返回: "/A/B/C.tar.gz"
QString QFileInfo::absoluteFilePath() const;
QString QFileInfo::filePath() const;

// 获取带完整后缀的文件名。返回: "C.tar.gz"
QString QFileInfo::fileName() const;

// 获取文件的基础名字（碰到第一个点 '.' 就截止）。返回: "C"
QString QFileInfo::baseName() const;

// 获取文件的完整基础名字（碰到最后一个点 '.' 才截止）。返回: "C.tar"
QString QFileInfo::completeBaseName() const;

// 获取文件的后缀名（从最后一个点 '.' 开始算）。返回: "gz"
QString QFileInfo::suffix() const;

// 获取文件的完整后缀名（从第一个点 '.' 开始算）。返回: "tar.gz"
QString QFileInfo::completeSuffix() const;
```

**类型与状态判断**

```cpp
// 检查该路径在硬盘上是否真实存在
bool QFileInfo::exists() const;
static bool QFileInfo::exists(const QString &file); // 静态版本，无需实例化直接用

// 判断是否是一个常规文件
bool QFileInfo::isFile() const;

// 判断是否是一个目录（文件夹）
bool QFileInfo::isDir() const;

// 判断是否是一个快捷方式/符号链接（Link）
bool QFileInfo::isSymLink() const;

// 获取文件的物理大小（单位：字节 Byte）。如果是文件夹，返回值取决于操作系统
qint64 QFileInfo::size() const;

// 清空内部缓存，强行从硬盘重新读取最新属性
void QFileInfo::refresh();
```

**权限与时间戳**

```cpp
// 判断当前程序对该文件是否可读、可写、可执行
bool QFileInfo::isReadable() const;
bool QFileInfo::isWritable() const;
bool QFileInfo::isExecutable() const;

// 获取文件权限的完整枚举标志位
QFile::Permissions QFileInfo::permissions() const;

// 获取文件的时间戳（返回 QDateTime 对象）
QDateTime QFileInfo::birthTime() const;    // 创建时间（某些旧 Linux 内核可能不支持）
QDateTime QFileInfo::metadataChangeTime() const; // 元数据（如权限、拥有者）修改时间
QDateTime QFileInfo::lastModified() const; // 内容最后一次被修改的时间
QDateTime QFileInfo::lastRead() const;     // 最后一次被读取/访问的时间
```

### 常用信号

`QFileInfo` 没有任何信号。

## `QDir`

`QDir` 是 Qt 框架中专门用来操作和遍历目录（文件夹）的核心工具类。

在 Windows 下，路径分隔符默认是反斜杠 `\`（如 `C:\Windows`）；而在 Linux 和 macOS 下是正斜杠 `/`（如 `/usr/bin`）。 `QDir` 内部**一律采用正斜杠 `/` 作为统一的分隔符**。

### 常用函数

**构造与路径切换**

```cpp
// 默认构造函数（指向程序当前的工作目录）
QDir::QDir();

// 最常用：直接指定指向某一个目录的路径
QDir::QDir(const QString &path);

// 拷贝构造函数
QDir::QDir(const QDir &dir);

// 修改当前 QDir 对象指向的路径
void QDir::setPath(const QString &path);

// 获取当前指向的目录路径字符串（可能是相对路径）
QString QDir::path() const;

// 获取当前目录的绝对物理路径（会自动化简掉其中的 "." 和 "..")
QString QDir::absolutePath() const;

// 切进子目录（支持相对路径如 "images" 或 "../config"）。成功返回 true
bool QDir::cd(const QString &dirName);

// 切回到上一级父目录。相当于 cd("..")
bool QDir::cdUp();
```

**物理目录操作**

```cpp
// 检查该目录在硬盘上是否存在
bool QDir::exists() const;
static bool QDir::exists(const QString &path); // 静态工具版本

// 创建一个子文件夹。要求父级目录必须存在，否则创建失败
bool QDir::mkdir(const QString &dirName) const;

// 常用：递归创建多级子文件夹（比如路径里有 /A/B/C，哪怕 A 和 B 都不存在，也会一并全部创建）
bool QDir::mkpath(const QString &dirPath) const;

// 删除一个**空**的子文件夹。如果里面有文件，会删除失败
bool QDir::rmdir(const QString &dirName) const;

// 常用：递归删除整个文件夹（包括里面所有的子文件和子文件夹，极度危险且高效）
bool QDir::rmpath(const QString &dirPath) const;

// 重命名当前目录下的某个文件或子文件夹
bool QDir::rename(const QString &oldName, const QString &newName);

// 删除当前目录下的某个文件
bool QDir::remove(const QString &fileName);
```

**遍历目录与文件过滤**

```cpp
// 1. 设置全局文件名通配符过滤器（比如 "*.txt", "*.png"）
void QDir::setNameFilters(const QStringList &nameFilters);

// 2. 抓取当前目录下所有符合条件的【文件名和子文件夹名】列表
QStringList QDir::entryList(QDir::Filters filters = NoFilter, QDir::SortFlags sort = NoSort) const;
// 静态包装版，可以直接传入通配符
QStringList QDir::entryList(const QStringList &nameFilters, QDir::Filters filters = NoFilter, QDir::SortFlags sort = NoSort) const;

// 3. 抓取当前目录下所有符合条件的【QFileInfo 属性对象】列表（更方便后续直接获取大小、时间）
QFileInfoList QDir::entryInfoList(QDir::Filters filters = NoFilter, QDir::SortFlags sort = NoSort) const;
QFileInfoList QDir::entryInfoList(const QStringList &nameFilters, QDir::Filters filters = NoFilter, QDir::SortFlags sort = NoSort) const;

/*
 常用的过滤标志（QDir::Filter）：

- QDir::Files：只列出常规文件。
- QDir::Dirs：只列出文件夹。
- QDir::NoDotAndDotDot：非常重要！排除掉每个目录下默认自带的 .（当前目录）和 ..（上级目录）。如果不加这个，遍历时会陷入死循环。

常用的排序标志（QDir::SortFlag）：

- QDir::Name：按字母顺序排序。
- QDir::Time：按修改时间排序（常用于找最新的日志）。
- QDir::Size：按文件大小排序。
- QDir::IgnoreCase：不区分大小写。
*/
```

**快捷获取系统特殊路径（静态工具函数）**

```cpp
// 获取当前程序启动时、在操作系统内被激活的工作目录
static QDir QDir::current();
static QString QDir::currentPath();

// 获取当前登录用户的家目录（Windows通常是 C:/Users/用户名，Linux是 /home/用户名）
static QDir QDir::home();
static QString QDir::homePath();

// 获取当前操作系统的根目录（Windows下通常返回 "C:/"）
static QDir QDir::root();
static QString QDir::rootPath();

// 获取系统的临时文件夹路径（适合临时存放缓存解压包）
static QDir QDir::temp();
static QString QDir::tempPath();
```

### 常用信号

没有任何信号。

## `QTextStream`

`QTextStream` 是 Qt 框架中专门用来读写纯文本数据（Text Data）的流式包装器类。它本身并不直接负责在硬盘上存储数据，而是作为一个高效率的“转换器”，包裹在 `QFile`、`QTcpSocket` 或 `QString` 等基础 I/O 设备的外层。

`QTextStream` 的核心价值在于以下三点：

1. **极其优雅的读写语法**：它借鉴了标准 C++ 的 `<iostream>` 风格。你可以使用 **`<<`（流插入运算符）** 方便地写入数据，使用 **`>>`（流提取运算符）** 方便地解析提取数据。
2. **完美的字符编码转换**：它内置了字符集编码转换器。你可以一行代码将流指定为 `UTF-8`、`GBK` 或 `UTF-16`。它会自动将复杂的编码转换为 Qt 内部标准的 Unicode（`QString`），彻底告别文本乱码。
3. **智能的换行符翻译**：在 Windows、Linux 和 macOS 平台之间，换行符的表示方法各不相同（`\r\n` 与 `\n`）。`QTextStream` 会自动将平台的差异抚平，提供统一的统一跨平台文本体验。

由于它是一个高效率的工具类，**没有继承自 `QObject`**。

### 常用函数

**构造与绑定**

```cpp
// 默认构造函数（未绑定任何设备，通常后续通过 setDevice() 绑定）
QTextStream::QTextStream();

// 最常用：用一个已有的 I/O 设备（如已经打开的 QFile）来初始化流
QTextStream::QTextStream(QIODevice *device);

// 高级写法：直接绑定一个内存中的 QString，数据读写会直接改变这个字符串
QTextStream::QTextStream(QString *string, QIODevice::OpenMode openMode = QIODevice::ReadWrite);

// 绑定只读的 QByteArray 原始数据块
QTextStream::QTextStream(const QByteArray &array, QIODevice::OpenMode openMode = QIODevice::ReadOnly);

// 销毁流（销毁流不会导致它包裹的 QFile 被关闭，底层的 file.close() 仍需手动或在文件析构时调用）
QTextStream::~QTextStream();

// 中途更改或重新获取绑定的底层设备
void QTextStream::setDevice(QIODevice *device);
QIODevice *QTextStream::device() const;
```

**文本读取函数**

```cpp
// 一次性读取从当前光标位置到文本末尾（EOF）的所有内容
QString QTextStream::readAll();

// 读取完整的一行文本（不包含末尾的换行符 '\n' 或 '\r\n'）
QString QTextStream::readLine(qint64 maxlen = 0);

// 读取指定长度 maxlen 的字符组成的字符串
QString QTextStream::read(qint64 maxlen);

// 检查光标是否已经到达流的末尾。如果读完了返回 true
bool QTextStream::atEnd() const;

// 移动读写光标或手动跳转位置（注意：这里的 pos 指的是字节偏移量，若涉及多字节编码需谨慎计算）
bool QTextStream::seek(qint64 pos);
```

**字符编码与格式控制**

```cpp
// 【Qt 6 新增】：设置文本流的编码格式（例如：QStringConverter::Utf8）
void QTextStream::setEncoding(QStringConverter::Encoding encoding);
QStringConverter::Encoding QTextStream::encoding() const;

/* 【Qt 5 历史保留，Qt 6 仍兼容】：
void QTextStream::setCodec(const char *codecName); 
void QTextStream::setCodec(QTextCodec *codec); */

// 强行把当前留在流缓冲区内的零散数据立刻刷入底层的物理设备（如硬盘）
void QTextStream::flush();

// 设置输出数字时的字段宽度。如果实际数字偏小，会自动用空格或指定字符补齐
void QTextStream::setFieldWidth(int width);
int QTextStream::fieldWidth() const;

// 设置补齐字段宽度时使用的填充字符（默认是空格 ' '）
void QTextStream::setPadChar(QChar ch);

// 设置实数（float/double）输出时的浮点数精度
void QTextStream::setRealNumberPrecision(int precision);
```

### 常用信号

没有信号。

## `QDataStream`

`QDataStream` 是 Qt 框架中专门用来读写二进制数据（Binary Data）的流式包装器类。

核心价值在于实现了 **C++ 对象的序列化（Serialization）与反序列化**：

1. **一键读写复杂类型**：它不仅能读写基础的 `int`、`float`、`char`，还能直接利用 `<<` 和 `>>` 操作符将 Qt 特有的复杂数据结构（如 `QString`、`QList`、`QMap`、`QImage` 甚至 `QVariant`）直接打包存入硬盘，或者从硬盘还原。
2. **绝对的跨平台兼容性（核心王牌）**：不同的计算机 CPU（如 Intel 的 x86 与手机的 ARM）在底层存储多字节数字时，字节顺序是不同的（即大端字节序 Big-Endian 和小端字节序 Little-Endian）。如果直接把内存里的 `int` 存入文件，换台电脑读出来就会变成天文数字。`QDataStream` 默认**将所有数据转换为统一的大端字节序**进行传输和存储，确保了数据在 Windows、Linux、macOS、Android 之间完全通用。

`QDataStream` 同样没有继承自 `QObject`（不支持信号与槽），是一个专注于执行效率和数据紧凑性的轻量级实用工具。

### 常用函数

**构造与设备绑定**

```cpp
// 默认构造函数
QDataStream::QDataStream();

// 最常用：绑定一个已经打开的输入/输出设备（如 QFile、QTcpSocket）
QDataStream::QDataStream(QIODevice *d);

// 绑定一个动态字节数组，所有写入的数据会直接追加到这个 QByteArray 内存块中
QDataStream::QDataStream(QByteArray *a, QIODevice::OpenMode mode);

// 绑定一个只读的静态字节数组，用于从内存数据块中反序列化解析变量
QDataStream::QDataStream(const QByteArray &a);

// 析构函数
QDataStream::~QDataStream();

// 中途更改或获取绑定的底层 I/O 设备
void QDataStream::setDevice(QIODevice *d);
QIODevice *QDataStream::device() const;

// 检查流当前的光标是否已经读到了最末尾
bool QDataStream::atEnd() const;
```

**字节序与版本控制（跨平台生存核心）**

```cpp
// 设置/获取字节序规则。默认是 QDataStream::BigEndian（大端）
void QDataStream::setByteOrder(QDataStream::ByteOrder bo);
QDataStream::ByteOrder QDataStream::byteOrder() const;

// 设置/获取浮点数的精准度规则（如 QDataStream::DoublePrecision 代表双精度）
void QDataStream::setFloatingPointPrecision(QDataStream::FloatingPointPrecision v);
QDataStream::FloatingPointPrecision QDataStream::floatingPointPrecision() const;

// 【极其重要】：设置/获取 Qt 数据结构的序列化版本号。
// 随着 Qt 版本的升级，某些类（如 QMap）的底层打包结构可能会变。
// 为了保证稳定性，必须指定一个固定的版本号（如 QDataStream::Qt_6_0）
void QDataStream::setVersion(int v);
int QDataStream::version() const;
```

**原始裸数据读写（不带类型标记的纯字节流）**

```cpp
// 写入指定长度 len 的原始内存数据到流中
int QDataStream::writeRawData(const char *s, int len);

// 从流中读取最多 len 字节的原始数据到预先分配好的缓冲区 s 中
int QDataStream::readRawData(char *s, int len);

// 跳过流中接下来的 len 字节数据不读取
int QDataStream::skipRawData(int len);
```

### 常用信号

没有任何信号.

## `QTemporaryDir`

`QTemporaryDir` 是 Qt 框架中专门用来**安全创建和自动管理临时文件夹**的工具类。

`QTemporaryDir` 不是 `QObject` 的子类（它是一个轻量级的普通 C++ 类），所以它**没有信号（Signals）和槽（Slots）**。

### 常用函数

**析构与构造**

```cpp
// 默认构造函数。在系统临时目录下创建一个名为 "qt_temp.XXXXXX" 的唯一文件夹
QTemporaryDir();

// 自定义模板构造函数。例如传入 "myApp_XXXXXX"，生成的文件夹名可能为 "myApp_a1B2c3"
explicit QTemporaryDir(const QString &templateName);

// 析构函数。如果 autoRemove 属性为 true（默认值），此时会递归删除该文件夹及内部所有内容
~QTemporaryDir();
```

**状态与路径检查状态与路径检查**

```
// 检查临时文件夹是否成功创建（如果磁盘满了或无写入权限，会返回 false）
bool isValid() const;

// 如果文件夹创建失败，返回具体的错误原因文本（Qt 6 新增）
QString errorString() const;

// 返回创建好的临时文件夹的绝对路径
QString path() const;

// 快捷函数：返回临时文件夹内部某个文件的绝对路径（Qt 5.15 新增）
QString filePath(const QString &fileName) const;
```

**控制开关 **

```
// 获取/设置 是否在析构时自动删除磁盘文件夹（默认为 true）
bool autoRemove() const;
void setAutoRemove(bool b);

// 提前手动删除该文件夹及其所有内容（不需要等到析构时）
bool remove();
```

## `QTemporaryFile`

`QTemporaryFile` 是 Qt 框架中专门用来**安全、创建和管理临时文件**的类。

### 常用函数

**析构与构造**

```cpp
// 默认构造函数。在系统临时目录下创建一个名为 "qt_temp.XXXXXX" 的唯一文件
QTemporaryFile();

// 自定义模板构造函数。例如传入 "myApp_XXXXXX"，生成的文件名可能为 "myApp_a1B2c3"
explicit QTemporaryFile(const QString &templateName);

// 带有父对象的自定义模板构造函数
QTemporaryFile(const QString &templateName, QObject *parent);

// 析构函数。如果 autoRemove 属性为 true（默认值），此时会从磁盘自动删除该文件
~QTemporaryFile();
```

**静态便捷函数**

```cpp
// 【极常用】静态快捷函数。直接在磁盘上创建一个临时文件，写入数据，并返回该文件对象指针
// 它的生命周期由传入的 parent 管理
static QTemporaryFile *createNativeFile(QFile &file);
static QTemporaryFile *createNativeFile(const QString &fileName);
```

**属性与状态控制**

```cpp
// 获取/设置 是否在析构时自动删除磁盘文件（默认为 true）
bool autoRemove() const;
void setAutoRemove(bool b);

// 返回该临时文件在磁盘上的完整绝对路径（在调用 open() 之前，该函数返回空字符串）
QString fileName() const override;

// 获取/设置 文件名模板
QString fileTemplate() const;
void setFileTemplate(const QString &name);
```

**核心重写函数**

```cpp
// 打开临时文件。Qt 会在此阶段真正去磁盘创建文件并随机命名。
// 默认会以 QIODevice::ReadWrite (读写模式) 打开
bool open() override;
```

## `QFileSystemWatcher`

`QFileSystemWatcher` 是 Qt 框架中专门用来**监控文件和目录（文件夹）状态变化**的实用工具类。

> 它通过监听操作系统底层的通知机制（例如 Linux 的 `inotify`、Windows 的 `ReadDirectoryChangesW`、macOS 的 `FSEvents`），在指定的路径发生修改、创建、删除等操作时，以信号（Signals）的方式实时通知程序。这在需要实现“配置文件热加载”、“日志实时监控”或“文件同步”功能时非常有用。

> **局限性（需注意）**：`QFileSystemWatcher` **不支持递归监控**。如果你监控了 `/path` 文件夹，它只能感知该层级下的变化，如果 `/path/sub_folder/file.txt` 发生了改变，它是无法自动感知的（需要手动将子文件夹也加入监控列表）。

### 常用函数

**构造与析构**

```cpp
// 默认构造函数
explicit QFileSystemWatcher(QObject *parent = nullptr);

// 构造的同时，直接将路径列表加入监控
QFileSystemWatcher(const QStringList &paths, QObject *parent = nullptr);

// 析构函数
~QFileSystemWatcher();
```

**动态添加/移除监控路径**

```cpp
// 【常用】添加单个监控路径（可以是文件，也可以是文件夹）
// 如果路径已存在或无效，返回 false
bool addPath(const QString &path);

// 【常用】批量添加监控路径
// 返回添加失败的路径列表（全部成功则返回空列表）
QStringList addPaths(const QStringList &paths);

// 移除单个监控路径
bool removePath(const QString &path);

// 批量移除监控路径
QStringList removePaths(const QStringList &paths);
```

**状态查询**

```cpp
// 获取当前正在监控的所有【文件】路径列表
QStringList files() const;

// 获取当前正在监控的所有【文件夹】路径列表
QStringList directories() const;
```

### 常用信号

```cpp
// 当被监控的【文件】被修改、重命名或删除时，发射此信号
// 参数 path 为该文件的绝对路径
void fileChanged(const QString &path);

// 当被监控的【文件夹】内部的内容（如新建文件、删除文件）发生改变时，发射此信号
// 参数 path 为该文件夹的绝对路径
void directoryChanged(const QString &path);
```

