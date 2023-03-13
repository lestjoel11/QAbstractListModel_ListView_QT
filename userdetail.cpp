#include "userdetail.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>

UserDetail::UserDetail(QObject *parent)
    : QAbstractListModel(parent)
{
    loadJson();
}

int UserDetail::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    //Change 3 When you implement loading for server The List .count
    // FIXME: Implement me!
    return 1;
}
void UserDetail::loadJson()
{
    //Initialise with Data
    //TODO: ADD Dynamic PATH
    QFile file("../UserDetailsListView/Data.json");
    QString val;

    QJsonObject obj;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        val=file.readAll();
        file.close();//required to convert to utf8 or else wont output
        doc = QJsonDocument::fromJson(val.toUtf8()).toVariant(); //Change Dont work with QJSON dirctly ;

    }

}

QVariant UserDetail::data(const QModelIndex &index, int role) const
{
    //Change 2 Use QVariant .atIndex
    //.toMap to clean 47-53
    QList obj = doc.toList();
    QMap currentRow = obj.at(index.row()).toMap();
    const int id = currentRow.value("id").toInt();
    const QString balance = currentRow.value("balance").toString();
    const int age = currentRow.value("age").toInt();
    const QString name = currentRow.value("name").toString();
    const QString gender = currentRow.value("gender").toString();
    const QString email = currentRow.value("email").toString();
    const QString phone = currentRow.value("phone").toString();

    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    switch(role){
        case IdRole:
            return QVariant(id);
        case BalanceRole:
            return QVariant(balance);
        case AgeRole:
        return QVariant(age);
        case NameRole:
        return QVariant(name);
        case GenderRole:
        return QVariant(gender);
        case EmailRole:
        return QVariant(email);
        case PhoneRole:
        return QVariant(phone);
    }
    return QVariant();
}

bool UserDetail::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags UserDetail::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}
QHash<int, QByteArray> UserDetail::roleNames() const
{
    QHash<int, QByteArray> names;
    names[IdRole] = "id";
    names[BalanceRole] = "balance";
    names[AgeRole] = "age";
    names[NameRole] = "name";
    names[GenderRole] = "gender";
    names[EmailRole] = "email";
    names[PhoneRole] = "phone";

    return names;
};
