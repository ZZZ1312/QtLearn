#include "qwfloatspindelegate.h"
#include <QDoubleSpinBox>

QWFloatSpinDelegate::QWFloatSpinDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}


QWidget *QWFloatSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDoubleSpinBox *spinBox = new QDoubleSpinBox(parent);
    // spinBox->setFrame(false);
    spinBox->setDecimals(2);
    return spinBox;
}



void QWFloatSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index, Qt::EditRole).toDouble();
    QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    spinBox->setValue(value);
}



void QWFloatSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    spinBox->interpretText();
    double value = spinBox->value();
    model->setData(index, value,Qt::EditRole);
}



void QWFloatSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

