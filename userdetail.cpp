#include "userdetail.h"
#include "qforeach.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>

UserDetail::UserDetail(QObject *parent)
    : QAbstractListModel(parent)
{

}

int UserDetail::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return 10;
}

QVariant UserDetail::data(const QModelIndex &index, int role) const
{
    //Initialise with Data
    //TODO: ADD Dynamic PATH
    QFile file("../UserDetailsListView/Data.json");
    QString val;
    QJsonDocument doc;
    QJsonObject obj;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        val=file.readAll();
        file.close();//required to convert to utf8 or else wont output
        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());

        if (doc.isArray())
               {
                   QJsonObject obj = doc[index.row()].toObject();
                   qInfo() << "Name:" << obj.value("name").toString();
                   qInfo() << "Age:" << obj.value("age").toInt();
               }

    }

    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    switch(role){
        case IdRole:
            return QVariant(false);
        case BalanceRole:
            return QVariant(file.exists());
        case AgeRole:
        return QVariant(obj.value("age").toInt());
        case NameRole:
        return QVariant(obj.value("name").toString());
        case GenderRole:
        return QVariant(QStringLiteral("Test"));
        case EmailRole:
        return QVariant(QStringLiteral("Test"));
        case PhoneRole:
        return QVariant(QStringLiteral("Test"));
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
