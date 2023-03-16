#include "userdetail.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <cmath>
#include <QJsonArray>

UserDetail::UserDetail(QObject *parent)
    : QAbstractListModel(parent)
{
    setFrom(0);setTo(20);
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &UserDetail::finishedReply);

    setJSONData(manager);

    connect(this,&UserDetail::onLoadMoreRows,this,&UserDetail::setJSONData, Qt::QueuedConnection);
}

int UserDetail::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return doc.size();

}

//Commenting out for future ref
//void UserDetail::loadJson()
//{
    //    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    //    //connect signal to slot to verify reply
    //    connect(manager,SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedReply(QNetworkReply*)));
    //    QString url = "http://localhost:3000/"+QString::number(to);
    //    QNetworkRequest request((QUrl(url)));
    //    QNetworkReply *reply = manager->get(request);
    //    QJsonDocument jsonData = QJsonDocument::fromJson(reply)


    //    QFile file("../UserDetailsListView/Data.json");
    //    QString val;

    //    QJsonObject obj;
    //    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    //    {
    //        val=file.readAll();
    //        file.close();//required to convert to utf8 or else wont output
    //        doc = QJsonDocument::fromJson(val.toUtf8()).toVariant(); //Change Dont work with QJSON dirctly ;

    //    }

//}



QVariant UserDetail::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();

    QList<QVariantMap> jsonData = getDoc();
    QVariantMap currentRow = jsonData.at(index.row());
    switch(role){
    case IdRole:
        return QVariant(currentRow.value("id").toInt());
    case BalanceRole:
        return QVariant(currentRow.value("balance").toString());
    case AgeRole:
        return QVariant(currentRow.value("age").toInt());
    case NameRole:
        return QVariant(currentRow.value("name").toString());
    case GenderRole:
        return QVariant(currentRow.value("gender").toString());
    case EmailRole:
        return QVariant(currentRow.value("email").toString());
    case PhoneRole:
        return QVariant(currentRow.value("phone").toString());
    }
    return QVariant();
}

void UserDetail::setJSONData(QNetworkAccessManager *manager)
{
    QString url = "http://localhost:3000/"+QString::number(getFrom())+"-"+QString::number(getTo());
    QNetworkRequest request((QUrl(url)));
    QNetworkReply *reply = manager->get(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
}


void UserDetail::finishedReply(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError) {
        QList<QVariantMap> list;
        QJsonArray array = QJsonDocument::fromJson(reply->readAll()).array();
        for(int i=0; i<array.size();i++){
            QJsonObject object = array.at(i).toObject();
            QVariantMap  map = object.toVariantMap();
            list.append(map);
        }
        int oldRowCount = rowCount();
        int newRowCount = oldRowCount +list.size();
        beginInsertRows(QModelIndex(), oldRowCount,newRowCount-1);
        doc.append(list);
        endInsertRows();
    }else{
        //handle error
        qDebug() << "Error: " << reply->errorString();
    }

    //delete reply object
    reply->deleteLater();
}

bool UserDetail::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        emit dataChanged(index, index, {Qt::DisplayRole});
        return true;
    }
    return false;
}

void UserDetail::loadMoreRows()
{
    nextBatch();
    emit onLoadMoreRows(manager);
}

void UserDetail::nextBatch()
{
    setFrom(getTo());
    setTo(getTo()+20);

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
}

QList<QVariantMap> UserDetail::getDoc() const
{
    return doc;
}

void UserDetail::setDoc(const QList<QVariantMap> &newDoc)
{
    if (doc == newDoc)
        return;
    doc = newDoc;
    emit docChanged();
}

void UserDetail::resetDoc()
{
    setDoc({}); // TODO: Adapt to use your actual default value
}

int UserDetail::getFrom() const
{
    return from;
}

void UserDetail::setFrom(int newFrom)
{
    if (from == newFrom)
        return;
    from = newFrom;
    emit fromChanged();
}

void UserDetail::resetFrom()
{
    setFrom({}); // TODO: Adapt to use your actual default value
}

int UserDetail::getTo() const
{
    return to;
}

void UserDetail::setTo(int newTo)
{
    if (to == newTo)
        return;
    to = newTo;
    emit toChanged();
}

void UserDetail::resetTo()
{
    setTo({}); // TODO: Adapt to use your actual default value
};
