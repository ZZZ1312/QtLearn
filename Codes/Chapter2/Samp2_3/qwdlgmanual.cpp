#include "qwdlgmanual.h"
#include <QLayout>
QWDlgManual::QWDlgManual(QWidget *parent)
    : QDialog(parent)
{
    initUi();
    iniSignalSlots();
    setWindowTitle("Form created mannually");
    reflushUI();
}

QWDlgManual::~QWDlgManual()
{
    delete chkBoxBold;
    delete chkBoxItalic;
    delete chkBoxUnder;

    delete rBtnBlue;
    delete rBtnBlack;
    delete rBtnRed;

    delete btnOK;
    delete btnCancel;
    delete btnClose;

    delete txtEdit;
}


void QWDlgManual::initUi()
{
    // 创建Underline, Italic, Bold 3个 CheckBox,并水平布局
    chkBoxUnder = new QCheckBox(tr("Underline"));
    chkBoxItalic = new QCheckBox(tr("Italic"));
    chkBoxBold = new QCheckBox(tr("Bold"));
    QHBoxLayout *HLay1 = new QHBoxLayout();
    HLay1->addWidget(chkBoxUnder);
    HLay1->addWidget(chkBoxItalic);
    HLay1->addWidget(chkBoxBold);
    // 创建 Black,Red, Blue 3个 RadioButton 并水平布局
    rBtnBlack = new QRadioButton(tr("Black"));
    rBtnRed = new QRadioButton(tr("Red"));
    rBtnBlue = new QRadioButton(tr("Blue"));
    QHBoxLayout *HLay2 = new QHBoxLayout();
    HLay2->addWidget(rBtnBlack);
    HLay2->addWidget(rBtnRed);
    HLay2->addWidget(rBtnBlue);
    // 创建 确定,取消,退出3个PushButton,并水平布局
    btnOK = new QPushButton(tr("确定"));
    btnCancel = new QPushButton(tr("取消"));
    btnClose = new QPushButton(tr("退出"));
    QHBoxLayout *HLay3 = new QHBoxLayout();
    HLay3->addStretch(4);
    HLay3->addWidget(btnOK);
    HLay3->addWidget(btnCancel);
    HLay3->addStretch(1);
    HLay3->addWidget(btnClose);
    // 创建文本框,并设置初始字体
    txtEdit = new QPlainTextEdit();
    txtEdit->setPlainText("Hello world\n\nIt is my demo.");
    QFont font = txtEdit->font(); // 获取字体
    font.setPointSize(20); // 修改字体大小
    txtEdit->setFont(font); // 设置字体
    // 创建垂直布局,并设置为主布局
    QVBoxLayout *VLay = new QVBoxLayout();
    VLay->addLayout(HLay1);
    VLay->addLayout(HLay2);
    VLay->addWidget(txtEdit);
    VLay->addLayout(HLay3);
    setLayout(VLay);

    this->resize(617, 384);

    // 设置默认的组件状态
    rBtnBlack->setChecked(true);

}

void QWDlgManual::iniSignalSlots()
{
    // 三个颜色QRadioButton的clicked()信号与setTextFontColor()槽槽函数关联
    connect(rBtnBlack, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(rBtnBlue, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(rBtnRed, SIGNAL(clicked()), this, SLOT(setTextFontColor()));

    // 三个字体设置的QCheckBox的clicked(bool)信号与相应的槽函数关联
    connect(chkBoxUnder, SIGNAL(clicked(bool)), this, SLOT(on_chkBoxUnder(bool)));
    connect(chkBoxBold, SIGNAL(clicked(bool)), this, SLOT(on_chkBoxBold(bool)));
    connect(chkBoxItalic, SIGNAL(clicked(bool)),this, SLOT(on_chkBoxItalic(bool)));

    // 三个按钮的信号与窗体的槽函数关联
    connect(btnOK, SIGNAL(clicked()), this, SLOT(accept()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(close()));
}

void QWDlgManual::on_chkBoxUnder(bool checked)
{
    QFont font = txtEdit->font();
    font.setUnderline(checked);
    txtEdit->setFont(font);
}

void QWDlgManual::on_chkBoxItalic(bool checked)
{
    QFont font = txtEdit->font();
    font.setItalic(checked);
    txtEdit->setFont(font);
}

void QWDlgManual::on_chkBoxBold(bool checked)
{
    QFont font = txtEdit->font();
    font.setBold(checked);
    txtEdit->setFont(font);
}

void QWDlgManual::setTextFontColor()
{
    QPalette palette = txtEdit->palette();
    if (rBtnBlue->isChecked())
        palette.setColor(QPalette::Text, Qt::blue);
    else if (rBtnRed->isChecked())
        palette.setColor(QPalette::Text, Qt::red);
    else if (rBtnBlack->isChecked())
        palette.setColor(QPalette::Text, Qt::black);
    else
        palette.setColor(QPalette::Text, Qt::black);
    txtEdit->setPalette(palette);
}

void QWDlgManual::reflushUI()
{
    setTextFontColor();
    on_chkBoxBold(chkBoxBold->isChecked());
    on_chkBoxItalic(chkBoxItalic->isChecked());
    on_chkBoxUnder(chkBoxUnder->isChecked());
}


