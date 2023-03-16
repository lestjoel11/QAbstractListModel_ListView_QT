#ifndef USERDETAIL_H
#define USERDETAIL_H

#include <QAbstractListModel>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QList>



class UserDetail : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<QVariantMap> doc READ getDoc WRITE setDoc RESET resetDoc NOTIFY docChanged)

    Q_PROPERTY(int from READ getFrom WRITE setFrom RESET resetFrom NOTIFY fromChanged)

    Q_PROPERTY(int to READ getTo WRITE setTo RESET resetTo NOTIFY toChanged)

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

    QList<QVariantMap> getDoc() const;
    void setDoc(const QList<QVariantMap> &newDoc);
    void resetDoc();

    int getFrom() const;
    void setFrom(int newFrom);
    void resetFrom();

    int getTo() const;
    void setTo(int newTo);
    void resetTo();

private:
    QList<QVariantMap> doc;
    int from;
    int to;
    QNetworkAccessManager *manager;



signals:
    void docChanged();

    void fromChanged();

    void toChanged();

    void onLoadMoreRows(QNetworkAccessManager *manager);

public Q_SLOTS:
    void loadMoreRows();

private slots:
    void finishedReply(QNetworkReply *reply);
    void setJSONData(QNetworkAccessManager *manager);
};

#endif // USERDETAIL_H
