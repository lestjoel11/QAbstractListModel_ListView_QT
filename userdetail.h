#ifndef USERDETAIL_H
#define USERDETAIL_H

#include "qjsondocument.h"
#include <QAbstractListModel>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>




class UserDetail : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit UserDetail(QObject *parent = nullptr);

    enum Roles {
        IdRole = Qt::UserRole,
        BalanceRole,
        AgeRole,
        NameRole,
        GenderRole,
        EmailRole,
        PhoneRole
    };
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    void loadJson();
    void nextBatch();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    QVariant doc;
    int dataRange = 20;

public slots:
    void currentState();

private slots:
    void finishedReply(QNetworkReply *reply);
    void setJSONData(const QVariant &data);
};

#endif // USERDETAIL_H
