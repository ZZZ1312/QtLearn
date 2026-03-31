#include "cperson.h"


CPerson::CPerson(const QString &fName, QObject *parent)
    :m_name(fName)
{}

int CPerson::age()
{
    return m_age;
}

void CPerson::setAge(int value)
{
    m_age = value;
    emit ageChanged(m_age);
}

void CPerson::incAge()
{
    ++m_age;
    emit ageChanged(m_age);
}




