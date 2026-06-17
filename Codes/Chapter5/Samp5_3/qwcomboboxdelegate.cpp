#include "qwcomboboxdelegate.h"
#include <QComboBox>
#include <QStringList>

QWComboBoxDelegate::QWComboBoxDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}

QWidget *QWComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    QStringList elements;
    elements << "优" << "普" << "劣";
    editor->addItems(elements);
    return editor;
}

void QWComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString content = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setEditText(content);
}

void QWComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString content = comboBox->currentText();
    model->setData(index, content, Qt::EditRole);
}

void QWComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
