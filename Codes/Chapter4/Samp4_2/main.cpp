#include <QDebug>
#include <QLoggingCategory>
#include <QString>

void test1() {
    QString str1 = "卖", str2 = "拐";
    QString str3 = str1;
    str1.append(str2);
    str3.prepend(str2);
    qDebug() << "str1:" << str1;
    qDebug() << "str3:" << str3;
}

void test2() {
    QString str1 = "Hello, World", str2;
    qDebug() << "original:" << str1;
    str2 = str1.toUpper();
    qDebug() << "upper:" << str2;
    str2 = str1.toLower();
    qDebug() << "lower:" << str2;
}

void test3() {
    QString str1 = "NI好";
    qDebug() << "count:" << str1.count();
    qDebug() << "size:" << str1.size();
    qDebug() << "length:" << str1.length();
}

void test4() {
    QString str1 = "    Are    you   OK?   ";
    qDebug() << "tirmmed:" << str1.trimmed();
    qDebug() << "simplified:" << str1.simplified();
}

void test5() {
    QString str1 = R"(G:\Qt5Book\Qt5.9Study\qw.cpp)";
    qDebug() << "string:" << str1;
    qDebug() << R"(index of  "5.9":)" << str1.indexOf("5.9");
    qDebug() << R"(last index of "\")" << str1.lastIndexOf(R"(\)");
}

void test6() {
    QString str1, str2 = "";
    qDebug() << "str1 is Null?" << str1.isNull();
    qDebug() << "str2 is Null?" << str2.isNull();
    qDebug() << "str1 is Empty?" << str1.isEmpty();
    qDebug() << "str2 is Empty?" << str2.isEmpty();

    // isNull 代表未赋值，isEmpty代表空字符串
}

void test7() {
    QString str1 = R"(G:\Qt5Book\QT5.9Study\qw.cpp)";
    qDebug() << "string is contains \".cpp\"?"
             << str1.contains(".cpp", Qt::CaseInsensitive);
    qDebug() << "string is contains \".CPP\"?"
             << str1.contains(".CPP", Qt::CaseSensitive);
}

void test8() {
    QString str1 = R"(G:\Qt5Book\QT5.9Study\qw.cpp)";
    qDebug() << str1.endsWith(".cpp", Qt::CaseInsensitive);
    qDebug() << str1.endsWith(".CPP", Qt::CaseInsensitive);
    qDebug() << str1.startsWith("g: ");
}

void test9() {
    QString str1 = "学生姓名, 男, 1985-3-4, 汉族, 山东", str2;
    int N = str1.indexOf(",");
    qDebug() << R"(第一个","出现的位置:)" << N;
    qDebug() << R"(left(N):)" << str1.left(N);
    N = str1.lastIndexOf(",");
    qDebug() << R"(最后一个","出现的位置)" << N;
    qDebug() << R"(right(str1.size() -N -1):)" << str1.right(str1.size() - N - 2);
}

void test10() {
    QString str1 = "学生姓名, 男, 1984-3-4, 汉族, 山东", str2;
    qDebug() << str1.section(", ", 0, 0);
    qDebug() << str1.section(", ", 1, 1);
    qDebug() << str1.section(", ", 0, 1);
    qDebug() << str1.section(", ", 4, 4);
}
int main(int argc, char *argv[]) {
    // QLoggingCategory::setFilterRules("*.debug=false");

    qSetMessagePattern("[%{time yyyy-MM-dd hh:mm:ss.zzz t}] "
                       "[%{type}] "
                       "%{message}"); // 设置日志格式

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    return 0;
}
