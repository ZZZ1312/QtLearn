# Qt基础类和常用函数

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

