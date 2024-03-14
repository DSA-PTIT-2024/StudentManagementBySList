#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>
#include <QtQml>
class Student : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString fullName READ getFullName WRITE setFullName NOTIFY fullNameChanged)
    Q_PROPERTY(QString studentId READ getStudentId WRITE setStudentId NOTIFY studentIdChanged)
    Q_PROPERTY(QString classId READ getClassId WRITE setClassId NOTIFY classIdChanged)
    Q_PROPERTY(QString birthDate READ getBirthDate WRITE setBirthDate NOTIFY birthDateChanged)
  public:
    explicit Student(QObject* parent = nullptr);
    Student(QString fullName, QString studentId, QString classId, QString birthDate, QObject* parent = nullptr);
    Student(const Student& other);
    Student(Student&& other);
    Student& operator=(const Student& other);
    Student& operator=(Student&& other);

    bool operator==(const Student& other) const;
    bool operator!=(const Student& other) const;

    QString getFullName() const;
    void setFullName(const QString& fullName);
    QString getStudentId() const;
    void setStudentId(const QString& studentId);
    QString getClassId() const;
    void setClassId(const QString& classId);
    QString getBirthDate() const;
    void setBirthDate(const QString& birthDate);

  private:
    QString _fullName;
    QString _studentId;
    QString _classId;
    QString _birthDate;

  signals:
    void fullNameChanged();
    void studentIdChanged();
    void classIdChanged();
    void birthDateChanged();
};

#endif // STUDENT_H
