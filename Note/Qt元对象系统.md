# Qt元对象系统

Qt的元对象系统（Meta-Object System）提供了对象之间通信的**信号与槽机制**、**运行时类型信息**和**动态属性系统**。

## 基础组成

- `QObject`类：所有元对象系统类的基类。

- `Q_OBJECT`宏：在类的`private`部分声明，使类可以使用元对象特性，如动态属性、信号与槽。

- `MOC`（元对象编译器）：为每个`QObject`的子类提供必要的代码来实现元对象的特性。

> 构建项目时，有以下流程：
> 
> 1. MOC读取C++源码文件，如有`Q_OBJECT`宏，就会为这个类生成另一个包含有元对象支持代码的C++代码，生成的源文件连同类的实现文件一起被编译和连接。

## 元对象系统基础功能

### 获取元对象

`QObject::metaObject()`函数返回关联的元对象。

#### 元对象类

元对象的类为`QMetaObject`。该类包含了访问元对象的一些接口函数。

- `className()`：运行时返回类的名称字符串。

- `newInstance()`：从`QMetaObject`创建一个类的新实例，但是只能调用无参数构造函数。

### 判断继承关系

`QObject::inherits(const char* className)`判断一个对象实例是否时名称为class的类或`QObject`的子类的实例。

```cpp
// 例如
QTimer *timer = new QTimer();    // QTimer 是 QObject 的子类
timer->inherits("QTimer");        // 返回 true
timer->inherits("QObject");        // 返回 true
tiemr->inherits("QAbstractButton"); // 返回 false
```

### 字符串翻译

`QObject::tr()`和`QObject::trUtf8()`函数用于翻译字符串。

### 类型转换

`QObject`及其子类使用`qobject_cast<T>()`进行动态转换。

如果转换失败，返回`nullptr`。

### 动态属性

`QObject::setProperty()`和`QObject::property()``函数通过属性名称，实现给类实例动态添加属性和获取属性值的功能。

> 可以认为，可以在运行时给一个类添加、获取和修改成员变量的功能。

#### 遍历属性

遍历元对象中的属性时，需要用到一下函数：

- `propertyOffset()`：返回类的第一个属性的序号，第一个属性的序号不一定是0。

- `propertyCount()`：返回类的属性个数。

- `QMetaProperty property(int index)`：返回序号为index的属性对象。返回值`QMetaProperty`是类型，它封装了对属性的更多特征查询功能，以及属性值的读写功能。

## 属性系统

### 属性定义

`Q_PROPERTY()`宏用于定义属性，使用格式如下：

```cpp
Q_PROPERTY(type name
           (READ getFunction [WRITE setFunction] |
            MEMBER memberName [(READ getFunction | WRITE setFunction)])
            [RESET resetFunction]
            [NOTIFY notifySignal]
            [REVISION int]
            [DESIGNABLE bool]
            [SCRIPTABLE bool]
            [STORED bool]
            [USER bool]
            [CONSTANT]
            [FINAL] )
```

该语句定义一个返回值类型为type，名称为name的属性。可以用READ、WRITE关键字定义属性的读取、写入函数。

属性的类型可以是`QVariant`支持的的任何类型，也可以是用户自定义类型。

主要关键字意义如下：

- `READ`：指定一个读取属性值的函数，没有`MEMBER`关键字时必须设置`READ`。

- `WRITE`：指定一个设定属性值的函数，只读属性没有`WRITE`关键字。

- `MEMBER`：指定一个成员变量与属性关联，成为可读可写的属性，无需再设置`READ`和`WRITE`。

- `RESET`：可选，用于指定一个设置属性默认值的函数。

- `NOTIFY`：可选，用于设置一个信号，当属性值变化时发射此信号。

- `DESIGNABLE`：表示属性是否在Qt Designer中可见，默认为true。

- `CONSTANT`：表示属性值是一个常数，有该关键字的属性不能有`WRITE`和`NOTIFY`关键字。具有该关键字的类，其实例返回的值为常数，但是不同实例可以返回的值可以不一样。

- `FINAL`：表示改属性不能被子类重载。

> 定义属性的一些例子如下：
> 
> ```cpp
> Q_PROPERTY(bool focus READ hasFocus)
> Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabeled)
> Q_PROPERTY(QCursor cursor READ cursor WRITE setCursor RESET unsetCursor)
> ```

### 属性的使用

1. 不管是否通过`READ`或`WRITE`定义了接口函数，只要知道名称，就可以通过`QObject::property()`读取属性值，并通过`QObject::setProperty()`设置属性值。

```cpp
QPushButton *button = new QPushButton();
QObject *object = button;
object->setProperty("flat", true);
bool isFlat = object->property("flat");
```

2. 动态属性。`setProperty`函数可以在程序运行时给类定义一个新的属性，称之为动态属性。动态属性是针对类的实例定义的。
   动态属性可以使用`property()`函数查询。

3. 类的附加信息。属性系统提供了`Q_CLASSINFO()`宏，可以为类的元对象定义“名称——值”信息，信息名称和值都必须是字符串字面量。定义后可以使用`QMetaObject::classInfo(int index)`函数来获取到类的附加信息，返回值是`QMetaClassInfo`类型，有`name()`和`value()`两个函数，例如：
   
   ```cpp
   class QMyClass : public QObject
   {
    Q_OBJECT
    Q_CLASSINFO("author", "Wang")
    Q_CLASSINFO("company", "UPC")
    ...
   }
   
   // 获取
   QMetaObject *meta = Object->metaObject();
   // 遍历ClassInfo的方式
   for (int i = meta->classInfoOffset(); i < meta->classInfoCount(); ++i)
   {
       QMetaClassInfo classInfo = meta->classInfo();
       QString name = classInfo.name();
       QString value = classInfo.value();
   }
   ```

## 信号与槽

信号（Signal）是在特定情况下被发射的事件。

槽（Slot）是对信号进行响应的函数，与一般的C++函数一样的可以定义在类的任何部分（private、public或protected）。可以有任何参数，也可以被直接调用。槽函数可以与一个信号关联，当有该信号发送时，关联的槽函数被自动执行。

> GUI程序设计的主要内容就是对界面上各组件的信号的响应。只要知道什么情况下发射那些信号，合理地去响应和处理这些信号就可以了。

### 信号与槽的关联

使用`QObject::connect()`函数实现信号和槽的关联。

函数原型有多种形式，最常用的函数原型为：

```cpp
QMetaObject::Connection QObject::connect(const QObejct* sender, const char *signal,
const QObject* receiver, const char* method, Qt::ConnectionType type = Qt::AutoConnection);
```

> 上面的形式一般的调用形式为：
> 
> ```cpp
> connection(ui->button, SIGNAL(clicked()), this, SLOT(on_clicked());nection(ui->button, SIGNAL(clicked()), this, SLOT(on_clicked());
> ```

如果信号函数和槽函数满足： 没有重载。还可以使用第二种形式：

```cpp
QMetaObject::Connection QObejct::connect(const QObject *sender, const QMetaMethod &signal,
const QObject *receiver, const QMetaMethod &method, Qt::ConnectionType type = Qt::AutoConnection);  )
```

> 上面的形式的参数调用案例为：
> 
> ```cpp
> connect(lineEdit, &QLineEdit::textChanged, this, &widget::on_textChanged);
> ```
> 
> 参数会自动一一对应。

### 注意事项

1. 如果信号或槽函数有参数，则需要写明参数
   
   ```cpp
   connect(spinNum, SIGNAL(valueChanged(int)), this, SLOT(slot(int));
   ```
   
   **需要注意，一般信号的参数需要和槽的参数个数匹配，至少信号的参数个数不能少于槽的参数个数，否则会出编译错误。**

2. 一个信号可以连接到多个槽。

3. 多个信号可以连接到一个槽。

4. 一个信号可以连接到另一个信号，这样当信号发送时，与其连接的信号也会发送。

5. 如果使用信号与槽机制，必须在类中添加`Q_OBJECT`宏。

### 连接类型

`connect()`函数最后的参数是连接类型，表示了信号与槽之间的连接方式。

- `Qt::AutoConnection`：默认的连接方式，如果信号的接收者与发射者在同一个线程，就使用`Qt::DirectConnection`的方式，否则使用`Qt::QueueConnection`方式，在信号发射时自动确定关联方式。

- `Qt::DirectConnection`：信号被发射时槽函数立即执行，要求槽函数与信号在同一个线程，此时类似于函数调用。

- `Qt::QueuedConnection`：事件循环回到接收者线程后执行槽函数，要求槽函数与信号在不同线程。

- `Qt::BlockingQueuedConnection`：与`Qt::QueuedConnection`相似，只是信号线程会阻塞直到槽函数执行完毕，**槽和信号在同一个线程中时绝对不能使用这种方式，否则会造成死锁。**

### 获取信号发射者

在信号内部，调用`sender()`函数，可以获取到信号发射者的指针。

### 自定义信号并发射

在定义类时，使用关键字`signals`自定义信号 。**使用该关键字时，不必刻意控制private、public或protected。**

```cpp
class Person : public QObject
{
    Q_OBJECT
private: 
    int m_age = 10;
public:
    void incAge();
signals:
    void ageChanged(int value);
}
```

使用`emit`关键字发射信号

```cpp
void QPerson::incAge()
{
    ++m_age;
    emit ageChanged(m_age);
}
```
