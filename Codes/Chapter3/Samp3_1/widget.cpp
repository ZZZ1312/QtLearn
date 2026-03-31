#include "widget.h"
#include "./ui_widget.h"
#include "cperson.h"

#include <QMetaProperty>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , boy(new CPerson("王小明"))
    , girl(new CPerson("张小丽"))
{
    ui->setupUi(this);
    boy->setProperty("score", 95);
    boy->setProperty("age", 10);
    boy->setProperty("sex", "Boy"); // 动态属性

    girl->setProperty("score", 81);
    girl->setProperty("age", 20);
    girl->setProperty("sex", "Girl"); // 动态属性

    ui->spinBoy->setProperty("isBoy", true);
    ui->spinGirl->setProperty("isBoy", false);

    ui->spinBoy->setValue(boy->property("age").toInt());
    ui->spinGirl->setValue(girl->property("age").toInt());

    connect(boy.get(), &CPerson::ageChanged, this, &Widget::on_ageChanged);
    connect(girl.get(), &CPerson::ageChanged, this, &Widget::on_ageChanged);

    connect(boy.get(), &CPerson::ageChanged, ui->spinBoy, &QSpinBox::setValue);
    connect(girl.get(), &CPerson::ageChanged, ui->spinGirl, &QSpinBox::setValue);

    connect(ui->spinGirl, SIGNAL(valueChanged(int)),
            this, SLOT(on_spin_valueChanged(int)));
    connect(ui->spinBoy, SIGNAL(valueChanged(int)),
            this, SLOT(on_spin_valueChanged(int)));


}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_ageChanged(int value)
{
    // 响应 CPerson 的 ageChanged() 信号
    Q_UNUSED(value);
    CPerson *aPerson = qobject_cast<CPerson*> (sender()); // 类型转换
    QString hisName = aPerson->property("name").toString(); // 姓名
    QString hisSex = aPerson->property("sex").toString(); // 动态属性
    int hisAge = aPerson->age(); // 通过接口函数获取年龄
    // int hisAge = aPerson->property("age").toInt(); // 通过属性获得年龄
    ui->txtEdit->appendPlainText(hisName + "," + hisSex + QString::asprintf(", 年龄=%d", hisAge));
}

void Widget::on_spin_valueChanged(int arg1)
{
    // 响应界面上spinBox的valueChanged(int)信号

    QSpinBox *spinBox = qobject_cast<QSpinBox*>(sender());
    if (!spinBox) return;
    CPerson *person = spinBox->property("isBoy").toBool() ? boy.get() : girl.get();

    int age = person->age();
    if (age != arg1)
        person->setAge(spinBox->value());
}

void Widget::on_btnClear_clicked()
{
    ui->txtEdit->clear();
}

void Widget::on_btnBoyInc_clicked()
{
    boy->incAge();
}

void Widget::on_btnGirlInc_clicked()
{
    girl->incAge();
}


void Widget::on_btnClassInfo_clicked()
{
    // "类的元对象信息" 按钮
    const QMetaObject *meta = boy->metaObject();
    ui->txtEdit->clear();
    ui->txtEdit->appendPlainText("==元对象信息==\n");
    ui->txtEdit->appendPlainText(QString("类名称: %1\n").arg(meta->className()));
    ui->txtEdit->appendPlainText("property");
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i)
    {
        QMetaProperty prop = meta->property(i);
        const char* propName = prop.name();
        QString propValue = boy->property(propName).toString();
        ui->txtEdit->appendPlainText(QString("属性名称=%1, 属性值=%2").arg(propName).arg(propValue));
    }

    ui->txtEdit->appendPlainText("");
    ui->txtEdit->appendPlainText("classInfo");
    for (int i = meta->classInfoOffset(); i < meta->classInfoCount(); ++i)
    {
        QMetaClassInfo classInfo = meta->classInfo(i);
        ui->txtEdit->appendPlainText(QString("Name=%1, Value=%2").arg(classInfo.name()).arg(classInfo.value()));
    }
}


