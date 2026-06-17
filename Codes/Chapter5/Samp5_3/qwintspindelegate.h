#ifndef QWINTSPINDELEGATE_H
#define QWINTSPINDELEGATE_H

#include <QStyledItemDelegate>

class QWIntSpinDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    QWIntSpinDelegate();

public:
    // 自定义代理组件必须继承以下4个函数
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // QWINTSPINDELEGATE_H
