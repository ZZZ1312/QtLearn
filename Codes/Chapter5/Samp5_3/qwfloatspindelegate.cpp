#include "qwfloatspindelegate.h"
#include <QDoubleSpinBox>

QWFloatSpinDelegate::QWFloatSpinDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}

QWidget *QWFloatSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setDecimals(2);
    editor->setSingleStep(0.01);
    editor->setMinimum(0);
    editor->setMaximum(10000.0);
    return editor;
}

void QWFloatSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index, Qt::EditRole).toDouble();
    QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(editor);
    doubleSpinBox->setValue(value);
}

void QWFloatSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(editor);
    doubleSpinBox->interpretText();
    double value = doubleSpinBox->value();
    model->setData(index, value, Qt::EditRole);
}

void QWFloatSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // 设置组件大小
    editor->setGeometry(option.rect);
}
