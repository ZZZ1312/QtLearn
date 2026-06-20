#ifndef QFORMTABLE_H
#define QFORMTABLE_H

#include <QMainWindow>

namespace Ui {
class QFormTable;
}

class QFormTable : public QMainWindow
{
    Q_OBJECT

public:
    explicit QFormTable(QWidget *parent = nullptr);
    ~QFormTable();

private:
    Ui::QFormTable *ui;
};

#endif // QFORMTABLE_H
