#ifndef TABLESTUDENTCONTROLLER_H
#define TABLESTUDENTCONTROLLER_H
#include "src/Containers/SList/SList.hpp"
#include "student.h"
#include <QAbstractTableModel>
#include <QtQml>

class TableStudentController : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    enum StudentRoles
    {
        FullName = Qt::UserRole + 1,
        StudentId,
        ClassId,
        BirthDate
    };

  public:
    explicit TableStudentController(QObject* parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    // bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    Q_INVOKABLE void appendStudent(QString fullName, QString studentId, QString classId, QString birthDate);
    Q_INVOKABLE bool updateStudent(int row, QString fullName, QString studentId, QString classId, QString birthDate);
    Q_INVOKABLE void deleteStudent(int row);
    Q_INVOKABLE void sortTable(int column, Qt::SortOrder order);
  signals:
    void hasError(QString error);

  private:
    DSALibraries::Containers::SList<Student> _stuList;
    bool IsValidStudent(QString fullName, QString studentId, QString classId, QString birthDate);
};

#endif // TABLESTUDENTCONTROLLER_H
