#include "student.h"
#include <utility>

Student::Student(QObject* parent) : QObject{parent}, _fullName{""}, _studentId{""}, _classId{""}, _birthDate{""}
{
}

Student::Student(QString fullName, QString studentId, QString classId, QString birthDate, QObject* parent)
{
    _fullName = fullName;
    _studentId = studentId;
    _classId = classId;
    _birthDate = birthDate;
}

Student::Student(const Student& other)
    : QObject{other.parent()}, _fullName{other._fullName}, _studentId{other._studentId}, _classId{other._classId},
      _birthDate{other._birthDate}
{
}

Student::Student(Student&& other)
    : QObject{other.parent()}, _fullName{std::move(other._fullName)}, _studentId{std::move(other._studentId)},
      _classId{std::move(other._classId)}, _birthDate{std::move(other._birthDate)}
{
}

Student& Student::operator=(const Student& other)
{
    if (this != &other)
    {
        _fullName = other._fullName;
        _studentId = other._studentId;
        _classId = other._classId;
        _birthDate = other._birthDate;
    }
    return *this;
}

Student& Student::operator=(Student&& other)
{
    if (this != &other)
    {
        _fullName = std::move(other._fullName);
        _studentId = std::move(other._studentId);
        _classId = std::move(other._classId);
        _birthDate = std::move(other._birthDate);
    }
    return *this;
}

bool Student::operator==(const Student& other) const
{
    return _fullName == other._fullName && _studentId == other._studentId && _classId == other._classId &&
           _birthDate == other._birthDate;
}

bool Student::operator!=(const Student& other) const
{
    return !(*this == other);
}

QString Student::getFullName() const
{
    return _fullName;
}

void Student::setFullName(const QString& fullName)
{
    if (_fullName != fullName)
    {
        _fullName = fullName;
        emit fullNameChanged();
    }
}

QString Student::getStudentId() const
{
    return _studentId;
}

void Student::setStudentId(const QString& studentId)
{
    if (_studentId != studentId)
    {
        _studentId = studentId;
        emit studentIdChanged();
    }
}

QString Student::getClassId() const
{
    return _classId;
}

void Student::setClassId(const QString& classId)
{
    if (_classId != classId)
    {
        _classId = classId;
        emit classIdChanged();
    }
}

QString Student::getBirthDate() const
{
    return _birthDate;
}

void Student::setBirthDate(const QString& birthDate)
{
    if (_birthDate != birthDate)
    {
        _birthDate = birthDate;
        emit birthDateChanged();
    }
}
