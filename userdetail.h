#ifndef USERDETAIL_H
#define USERDETAIL_H

#include <QAbstractListModel>
#include <QVector>


struct User{
    int id;
    QString balance;
    int age;
    QString name;
    QString gender;
    QString email;
    QString phone;
};

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

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

private:

};

#endif // USERDETAIL_H
