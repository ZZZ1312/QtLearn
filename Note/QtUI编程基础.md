# Qt UI 编程基础

## 项目文件结构

一个Qt项目中，通常包括以下文件：

- `*.ui`文件：用XML格式存储的窗体界面文件。

- `.h`、`.cpp`文件：代码文件。

- `CMakeLists.txt`或`.pro`文件：是项目管理文件，`CMakeLists.txt`是CMake的项目文件，`.pro`是qmake的项目管理文件。

  > Qt 6 及以上已经全面转向CMake

### 窗体相关文件

假如有一个窗体，名为Widget，一般有以下文件：

- widget.ui

  该文件是一个XML文件。

- widget.h

  ```c++
  #ifndef WIDGET_H
  #define WIDGET_H
  
  #include <QWidget>
  
  namespace Ui {
  class widget;
  }
  
  class widget : public QWidget
  {
      Q_OBJECT
  
  public:
      explicit widget(QWidget *parent = nullptr);
      ~widget();
  
  private:
      Ui::widget *ui;
  };
  
  #endif // WIDGET_H
  ```

- widget.cpp

  ```c++
  #include "widget.h"
  #include "ui_widget.h"
  
  widget::widget(QWidget *parent)
      : QWidget(parent)
      , ui(new Ui::widget)
  {
      ui->setupUi(this);
  }
  
  widget::~widget()
  {
      delete ui;
  }
  ```

`.ui`文件用于Qt Designer这个Qt窗体设计工具。在Qt Creator中双击`.ui`文件，就可以以可视化的方式设计窗口结构。

在编译时，Qt会首先调用UIC工具，将xxx.ui文件转换成ui_xxx.h文件。xxx.cpp文件会包含该头文件。以widget.ui为例，生成的ui_widget.h文件内容为：

```c++
#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget
{
public:

    void setupUi(QWidget *widget)
    {
        if (widget->objectName().isEmpty())
            widget->setObjectName("widget");
        widget->resize(400, 300);

        retranslateUi(widget);

        QMetaObject::connectSlotsByName(widget);
    } // setupUi

    void retranslateUi(QWidget *widget)
    {
        widget->setWindowTitle(QCoreApplication::translate("widget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget: public Ui_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
```

ui_widget.h文件中，会自动生成一个`Ui_widget`类，并会自动定义一个命名空间`Ui`，使用时通过`Ui::widget`来使用Ui类。

`Ui_wdiget`类中提供两个函数：

- `setUi()`：创建各个界面组件，并设置其位置、大小、文字内容和字体等属性，设置信号与槽的关联。
- `retranslateUi()`：用于多语言翻译。

## UI设计相关

### 界面组件布局

所谓布局，就是界面上的组件如何分布。Qt中有以下布局：

| 布局组件          | 功能                                                         | 组件类名    |
| ----------------- | ------------------------------------------------------------ | ----------- |
| Vertical Layout   | 垂直方向布局，组件自动在垂直方向上分布                       | QVBoxLayout |
| Horizontal Layout | 水平方向布局，组件自动在水平方向上分布                       | QHBoxLayout |
| Grid Layout       | 网格状布局，网状布局大小改变时，每个网格的大小都改变         | QGridLayout |
| Form Layout       | 窗体布局，与网状布局类似，但是只有最右侧的一列网格会改变大小 | QFormLayout |

```c++
// 案例
QWidget window;

// 创建控件
QPushButton *button = new QPushButton("按钮");
QLabel *label = new QLabel("这是一个标签");
// 创建水平布局
QHBoxLayout *layout = new QHBoxLayout;

// 把控件加入布局
layout->addWidget(button);
layout->addWidget(label);

// 设置窗口布局
window.setLayout(layout);
```

一个窗口只能有一个布局，但是布局中可以嵌套布局

### 空格组件

空格就像一个“弹簧”，中间空白会自动“撑开”，把控件推到两边。

```c++
QWidget window;
// 创建控件
QPushButton *btnLeft = new QPushButton("左按钮");
QPushButton *btnRight = new QPushButton("右按钮");
// 创建水平布局
QHBoxLayout *layout = new QHBoxLayout;
// 添加左侧按钮
layout->addWidget(btnLeft);
//Spacer
QSpacerItem *spacer = new QSpacerItem(
    40, 20,
    QSizePolicy::Expanding, 
    QSizePolicy::Minimum
);
layout->addItem(spacer);
// 添加右侧按钮
layout->addWidget(btnRight);
```

`QSpacerItem`就是一个弹簧组件，它的构造函数有四个参，依次是：宽、高、水平扩展策略、垂直扩展策略。

其中，水平/垂直扩展策略一般使用以下选项：

- `QSizePolicy::Expanding`：向外扩展，尽可能占据更多的空间。
- `QSizePolicy::Minimum`：最小，尽量保持原始尺寸。

### 伙伴关系

伙伴关系（Buddy）是指界面上一个Label和一个组件的关联。

Label和一个组件设置了伙伴关系后，可以将Label的内容设置为`XXX(&N)`，其中`(&N)`是重点，`&`是一个标识，用来将其后的一个字母指定为快捷键，并不会显示，按Alt + 字母就会循序将焦点切换到与Label有伙伴关系的组件。

`QLabel`的`setBuddy()`函数用来设置伙伴关系，参数为一个控件的指针。

### Tab顺序

一个窗口程序可以通过按Tab来切换窗口中的焦点，Qt中也有该功能。

Qt中设计Tab顺序的方式是使用`QWidget::setTabOrder(QWidget *, QWidget *)`函数来设置。

```c++
// 案例：三个按钮组件btn1、btn2、btn3，设置顺序为: 1. btn1, 2. btn2, 3. btn3.
QWidget::setTabOrder(btn1, btn2);
QWidget::setTabOrder(btn2, btn3);
QWidget::setTabOrder(btn2, btn3);
// 第一次调用过setTabOrder时，第一个参数顺序为1，然后依次向下编号。
```