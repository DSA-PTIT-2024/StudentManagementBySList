#include "tablestudentcontroller.h"
#include <regex>

TableStudentController::TableStudentController(QObject* parent) : QAbstractTableModel{parent}
{
    auto stu1 = _stuList.EmplaceAfter(_stuList.GetConstBeginFromHead(), "NGUYỄN HOA HẬU", "D11K7", "D20", "2002");
    auto stu2 = _stuList.EmplaceAfter(stu1, "ĐỖ LỰC SĨ", "D11K8", "D20", "2000");
    auto stu3 = _stuList.EmplaceAfter(stu2, "LÝ MINH TINH", "D11K9", "D21", "2003");
    _stuList.EmplaceAfter(stu3, "TRẦN ĐẠI GIA", "D11K10", "D21", "2003");
}

QHash<int, QByteArray> TableStudentController::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "display";
    roles[FullName] = "fullName";
    roles[StudentId] = "studentId";
    roles[ClassId] = "classId";
    roles[BirthDate] = "birthDate";
    return roles;
}

int TableStudentController::rowCount(const QModelIndex& parent) const
{
    return _stuList.GetSize();
}

int TableStudentController::columnCount(const QModelIndex& parent) const
{
    return 4;
}

QVariant TableStudentController::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto indexRow = index.row();
    auto it = _stuList.GetConstBegin();
    while (indexRow-- > 0)
    {
        if (it.NodeBase == nullptr)
            return QVariant();
        ++it;
    }

    auto stu = *it;

    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0:
            return stu.getFullName();
        case 1:
            return stu.getStudentId();
        case 2:
            return stu.getClassId();
        case 3:
            return stu.getBirthDate();
        default:
            return QVariant();
        }
    }
    else if (role == FullName)
    {
        return stu.getFullName();
    }
    else if (role == StudentId)
    {
        return stu.getStudentId();
    }
    else if (role == ClassId)
    {
        return stu.getClassId();
    }
    else if (role == BirthDate)
    {
        return stu.getBirthDate();
    }

    return QVariant();
}

QVariant TableStudentController::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return "Full Name";
            case 1:
                return "Student ID";
            case 2:
                return "Class ID";
            case 3:
                return "Birth Date";
            default:
                return QVariant();
            }
        }
    }
    return QVariant();
}

bool TableStudentController::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role != Qt::EditRole)
        return false;
    auto idx = index.row();
    auto it = _stuList.GetBegin();

    while (idx-- > 0)
    {
        if (it.NodeBase == nullptr)
            return false;
        ++it;
    }

    switch (index.column())
    {
    case 0:
        it->setFullName(value.toString());
        break;
    case 1:
        it->setStudentId(value.toString());
        break;
    case 2:
        it->setClassId(value.toString());
        break;
    case 3:
        it->setBirthDate(value.toString());
        break;
    default:
        return false;
    }
    emit dataChanged(index, index, {role});
    emit layoutChanged();
    return true;
}

// bool TableStudentController::insertRows(int row, int count, const QModelIndex& parent)
// {
//     beginInsertRows(QModelIndex(), row, row + count - 1);
//     auto it = _stuList.GetBegin();
//     while (it.PointerNext() != _stuList.GetEnd())
//     {
//         ++it;
//     }
//     while (count-- > 0)
//     {
//         _stuList.EmplaceAfter(it, "", "", "", "");
//     }
//     endInsertRows();
//     return true;
// }

Qt::ItemFlags TableStudentController::flags(const QModelIndex& index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

void TableStudentController::appendStudent(QString fullName, QString studentId, QString classId, QString birthDate)
{
    auto standradFullName = fullName.toUpper();
    auto standradStudentId = studentId.toUpper();
    auto standradClassId = classId.toUpper();
    auto standradBirthDate = birthDate.toUpper();
    if (IsValidStudent(standradFullName, standradStudentId, standradClassId, standradBirthDate))
    {
        auto size = _stuList.GetSize();
        beginInsertRows(QModelIndex(), size, size);
        auto it = _stuList.GetConstBeginFromHead();
        while (it.PointerNext() != _stuList.GetEnd())
        {
            ++it;
        }
        _stuList.EmplaceAfter(it, standradFullName, standradStudentId, standradClassId, standradBirthDate);
        endInsertRows();
    }
}

bool TableStudentController::updateStudent(int row, QString fullName, QString studentId, QString classId,
                                           QString birthDate)
{
    auto standradFullName = fullName.toUpper();
    auto standradStudentId = studentId.toUpper();
    auto standradClassId = classId.toUpper();
    auto standradBirthDate = birthDate.toUpper();

    if (IsValidStudent(standradFullName, standradStudentId, standradClassId, standradBirthDate))
    {
        setData(index(row, 0), standradFullName, Qt::EditRole);
        setData(index(row, 1), standradStudentId, Qt::EditRole);
        setData(index(row, 2), standradClassId, Qt::EditRole);
        setData(index(row, 3), standradBirthDate, Qt::EditRole);
        return true;
    }
    return false;
}

void TableStudentController::deleteStudent(int row)
{
    if (_stuList.IsEmpty())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    auto it = _stuList.GetBeginFromHead();
    for (int i = 0; i < row; ++i)
    {
        ++it;
    }
    if (it.NodeBase == nullptr)
        return;
    _stuList.EraseAfter(it);
    endRemoveRows();
}

void TableStudentController::sortTable(int column, Qt::SortOrder order)
{
    if (column < 0 || column > 3)
        return;
    if (_stuList.IsEmpty())
        return;
    beginResetModel();

    switch (order)
    {
    case Qt::AscendingOrder:
        _stuList.Sort([&column](const Student& a, const Student& b) {
            switch (column)
            {
            case 0:
                return a.getFullName() < b.getFullName();
            case 1:
                return a.getStudentId() < b.getStudentId();
            case 2:
                return a.getClassId() < b.getClassId();
            case 3:
                return a.getBirthDate() < b.getBirthDate();
            default:
                return false;
            }
        });
        break;
    case Qt::DescendingOrder:
        _stuList.Sort([&column](const Student& a, const Student& b) {
            switch (column)
            {
            case 0:
                return a.getFullName() > b.getFullName();
            case 1:
                return a.getStudentId() > b.getStudentId();
            case 2:
                return a.getClassId() > b.getClassId();
            case 3:
                return a.getBirthDate() > b.getBirthDate();
            default:
                return false;
            }
        });
        break;
    }

    endResetModel();
    return;
}

bool TableStudentController::IsValidStudent(QString fullName, QString studentId, QString classId, QString birthDate)
{
    if (fullName.isEmpty() || studentId.isEmpty() || classId.isEmpty() || birthDate.isEmpty())
    {
        emit hasError("All fields must be filled");
        return false;
    }

    std::regex fullNameValid(
        "^[a-zA-Z_ÀÁÂÃÈÉÊÌÍÒÓÔÕÙÚĂĐĨŨƠàáâãèéêìíòóôõùúăđĩũơƯĂẠẢẤẦẨẪẬẮẰẲẴẶ+"
        "ẸẺẼỀỀỂưăạảấầẩẫậắằẳẵặẹẻẽềềểỄỆỈỊỌỎỐỒỔỖỘỚỜỞỠỢỤỦỨỪễệỉịọỏốồổỗộớờởỡợ+ụủứừỬỮỰỲỴÝỶỸửữựỳỵỷỹ\\s]+$");

    std::regex studentIdValid("^D\\d+K\\d+$");

    std::regex classIdValid("^D\\d+$");

    std::regex birthDateValid("^\\d{4}$");

    if (!std::regex_match(fullName.toStdString(), fullNameValid))
    {
        emit hasError("Full name is invalid");
        return false;
    }

    if (!std::regex_match(classId.toStdString(), classIdValid))
    {
        emit hasError("Class ID is invalid");
        return false;
    }

    if (!std::regex_match(studentId.toStdString(), studentIdValid))
    {
        emit hasError("Student ID is invalid");
        return false;
    }

    if (!std::regex_match(birthDate.toStdString(), birthDateValid))
    {
        emit hasError("Birth date is invalid");
        return false;
    }

    return true;
}
