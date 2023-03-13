#ifndef USERDETAIL_H
#define USERDETAIL_H

#include <QAbstractListModel>
#include <QVector>



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

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    QVariant doc;
};

#endif // USERDETAIL_H
