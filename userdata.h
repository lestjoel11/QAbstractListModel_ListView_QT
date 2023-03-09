#ifndef USERDATA_H
#define USERDATA_H

#include <QObject>

class UserData : public QObject
{
    Q_OBJECT
public:
    explicit UserData(QObject *parent = nullptr);

signals:

};

#endif // USERDATA_H
