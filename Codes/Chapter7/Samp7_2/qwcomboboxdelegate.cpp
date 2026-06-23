#include "qwcomboboxdelegate.h"
#include <QComboBox>
#include <QStringList>

QWComboBoxDelegate::QWComboBoxDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}


QWidget *QWComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *comboBox = new QComboBox(parent);
    QStringList items{"优", "良", "不合格"};
    comboBox->setFrame(false);
    comboBox->addItems(items);
    comboBox->setEditable(false);
    return comboBox;
}



void QWComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString item = index.model()->data(index).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentText(item);
}



void QWComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString text = comboBox->currentText();
    model->setData(index, text);
}



void QWComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

