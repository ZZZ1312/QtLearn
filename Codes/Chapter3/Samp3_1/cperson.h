#ifndef CPERSON_H
#define CPERSON_H

#include <QObject>

class CPerson : public QObject
{
    Q_OBJECT
public:
    Q_CLASSINFO("author", "Zhu")
    Q_CLASSINFO("version", "1.0.0")
    Q_CLASSINFO("company", "UPC")

    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged FINAL)
    Q_PROPERTY(QString name MEMBER m_name)
    Q_PROPERTY(int score MEMBER m_score)
private:
    int m_age = 10;
    QString m_name;
    int m_score = 79;
public:
    explicit CPerson(const QString &fName, QObject* parent = nullptr);

    int age();
    void setAge(int value);
    void incAge();
signals:
    void ageChanged(int value);

};

#endif // CPERSON_H
