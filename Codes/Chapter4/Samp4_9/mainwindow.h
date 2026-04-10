#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    // 自定义单元格Type的类型，在创建单元格的Item时使用
    enum CellType{ctName=1000, ctSex, ctBrith, ctNation, ctPartyM, ctScore};
    // 各字段在表格中的列号
    enum FieldColNum{colName=0, colSex, colBrith, colNation,colScore,colPartM};

    QLabel *labCellIndex; // 状态栏上用于显示单元格的行号、列号
    QLabel *labCellType; // 状态栏上用于显示单元格的type
    QLabel *labStudID; // 状态栏上用于显示学号

private:
    void createItemARow(int rowNo, const QString &name, const QString& sex, const QDate& brith,
                        const QString &nation, bool isPM, int score = 90); // 为某一行创建items
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_btnSetHeader_clicked();

    void on_btnInitTableData_clicked();

    void on_btnSetRow_clicked();

    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_btnInsert_clicked();

    void on_btnAppend_clicked();

    void on_btnDelete_clicked();

    void on_chkEditable_toggled(bool checked);
    void on_chkRowHeader_clicked(bool checked);

    void on_chkColumnHeader_clicked(bool checked);

    void on_chkDiffLine_clicked(bool checked);

    void on_rBtnRowSelectable_clicked();

    void on_rBtnColumnSelectable_clicked();

    void on_btnTableToText_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
