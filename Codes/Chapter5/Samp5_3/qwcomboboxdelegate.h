#ifndef QWCOMBOBOXDELEGATE_H
#define QWCOMBOBOXDELEGATE_H

#include <QStyledItemDelegate>

class QWComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit QWComboBoxDelegate(QObject *parent = nullptr);
public:
    // 自定义代理组件必须继承以下4个函数
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // QWCOMBOBOXDELEGATE_H
