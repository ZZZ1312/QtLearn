#ifndef QWFLOATSPINDELEGATE_H
#define QWFLOATSPINDELEGATE_H

#include <QStyledItemDelegate>

class QWFloatSpinDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit QWFloatSpinDelegate(QObject *parent = nullptr);

    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // QWFLOATSPINDELEGATE_H
