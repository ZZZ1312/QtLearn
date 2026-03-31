#include <QtGlobal>
#include <QDebug>
#include <QLoggingCategory>
#include <QStack>
#include <QQueue>
#include <QMultiMap>
#include <QMultiHash>

int main(int argc, char *argv[])
{

    qSetMessagePattern(
        "[%{time yyyy-MM-dd hh:mm:ss.zzz t}] "
        "[%{type}] "
        "[tid:%{threadid}]$ "
        "%{message}"
        ); // 设置日志格式


    int value1 = -3;
    qDebug() << "|value|=" << qAbs(value1);

    int value2 = 10;
    qDebug() << "(5,9)" << qBound(5, value2, 9);
    qDebug() << "(5, 15)" << qBound(5, value2, 15);
    qDebug() << "(11, 15)" << qBound(11, value2, 15);

    double value3 = 1.1111111;
    double value4 = 1.1111112;
    qDebug() << value3 << "and" << value4
             << "is fuzzy Compare?" << qFuzzyCompare(value3, value4);


    double value5 = 0.00000001;
    qDebug() << value5 << "is Fuzzy null?" << qFuzzyIsNull(value5);

    double value6 = qInf();
    qDebug() << "infinity:" << value6;

    double value7 = 1;
    qDebug() << value7 << "is Finite?" << qIsFinite(value7);
    qDebug() << value6 << "is Finite?" << qIsFinite(value6);

    qDebug() << value7 << "is Infinity?" << qIsInf(value7);
    qDebug() << value6 << "is Infinity?" << qIsInf(value6);

    double value8 = qQNaN();
    qDebug() << value8 << "is NaN?" << qIsNaN(value8);

    qDebug() << "max in (2, 8):" << qMax(2, 8);
    qDebug() << "min in (2, 8):" << qMin(2, 8);

    double value9 = 10.234;
    double value10 = 10.993;
    qDebug() << "qRound(" << value9 << "):" << qRound(value9);
    qDebug() << "qRound(" << value10 << "):" << qRound(value10);

    qDebug() << "RAND_MAX:" << RAND_MAX;

    qDebug() << "QT_VERSION:" << QT_VERSION;
    int a = QT_VERSION_CHECK(6,11,0);
    qDebug() << a;
    qDebug() << QT_VERSION_STR;

    qDebug() << Q_BYTE_ORDER;
    qDebug() << Q_LITTLE_ENDIAN;
    qDebug() << Q_BIG_ENDIAN;
    QStringList words;
    words << "a" << "b" << "c";
    foreach(const QString& word, words)
    {
        qDebug() << word;
    }

    int count = 0;
    forever{
        ++count;
        if (count > 10)
            break;
        qDebug() << "cycle times:" << count;
    }

    // QList
    QList<QString> list;
    list << "one" << "two" << "three";
    QString str1 = list[1];
    QString str0 = list.at(0);

    foreach(const QString &word, list)
    {
        qDebug() << word;
    }

    QVector<QString> vector;
    vector << "one1" << "two2" << "three3";
    foreach(const QString &word, vector)
    {
        qDebug() << word;
    }

    QStack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    while (!stack.isEmpty())
    {
        qDebug() << stack.pop();
    }

    QQueue<int> queue;
    queue.enqueue(11);
    queue.enqueue(21);
    queue.enqueue(31);
    while (!queue.isEmpty())
    {
        qDebug() << queue.dequeue();
    }

    QSet<QString> set;
    set << "dog" << "cat" << "tigger";
    qDebug() << set;
    if (!set.contains("cat"))
        qDebug() << "set do not contains 'cat'.";
    else
        qDebug() << "set contains 'cat'";

    QMap<QString, int> map;
    map["one"] = 1;
    map["two"] = 2;
    map["three"] = 3;
    map.insert("four", 4 );
    qDebug() << map;
    map.remove("two");
    qDebug() << map;
    int num1 = map["one"];
    qDebug() << num1;
    int num2 = map.value("two");
    qDebug() << num2;

    QHash<QString, int> hash;
    hash["one"] = 1;
    hash["two"] = 2;
    hash["three"] = 3;
    qDebug() << hash;
    int num3 = hash["one"];
    qDebug() << num3;
    int num4 = hash["four"];
    qDebug() << num4;

    QMultiMap<QString, int> multimap;
    multimap.insert("plenty", 100);
    multimap.insert("plenty", 2000);
    multimap.insert("plenty", 5000);

    qDebug() << multimap;
    qDebug() << multimap.value("plenty");
    qDebug() << multimap.values("plenty");


    QList<QString> list2;
    list2 << "A" << "B" << "C" << "D";
    QListIterator<QString> i(list2);
    while(i.hasNext())
    {
        const QString& word = i.next();
        qDebug() << word;
    }

    QListIterator<QString> i2(list2);
    i.toBack();
    while(i.hasPrevious())
    {
        qDebug() << i.previous();
    }

    QList<int> nums;
    nums << 1 << 2 << 3 << 4;
    qDebug() << nums;
    QMutableListIterator<int> ni(nums);
    while (ni.hasNext())
    {
        int &num = ni.next();
        if (num % 2 != 0)
            ni.remove();
    }
    qDebug() << nums;

    QMap<QString, QString> map2;
    map2.insert("Paris", "France");
    map2.insert("New York", "USA");
    map2.insert("Mexico City", "USA");
    map2.insert("Moscow", "Russia");

    qDebug() << map2;
    QMutableMapIterator<QString, QString> map2i(map2);
    while (map2i.hasNext())
    {
        if (map2i.next().key().endsWith("City"))
            map2i.remove();
    }
    qDebug() << map2;

    // STL
    QList<QString> list3;
    list3 << "A" << "B" << "C" << "D";
    QList<QString>::const_iterator lci;
    for (lci = list3.constBegin(); lci != list3.constEnd(); ++lci)
    {
        qDebug() << *lci;
    }

    QList<QString>::reverse_iterator lri;
    for (lri = list3.rbegin(); lri != list3.rend(); ++lri)
    {
        qDebug() << *lri;
        *lri = lri->toLower();
        qDebug() << *lri;
    }
    qDebug() << list3;

    QMap<QString, QString> map3;
    map3.insert("Paris", "France");
    map3.insert("New York", "USA");
    map3.insert("Mexico City", "USA");
    map3.insert("Moscow", "Russia");

    QMap<QString, QString>::const_iterator mci;
    for (mci = map3.constBegin(); mci != map3.constEnd(); ++mci){
        qDebug() <<mci.key() << ':' << mci.value();
    }

    return 0;
}