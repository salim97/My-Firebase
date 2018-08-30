#ifndef MYORM_H
#define MYORM_H

#include <QObject>
#include "firebase.h"
#include "mypropertyhelper.h"

//print internal msg
#define debug_CLI_enable true
#define debug_GUI_enable true


class MyORM : public QObject
{
    Q_OBJECT
public:
    explicit MyORM(QObject *parent = nullptr);

    void init(QObject *obj);

    void update();
signals:

public slots:

private slots:

    void onEventResponseReadyy(QString data);
private:
    QObject *obj ;
    Firebase *m_firebase;
};

#endif // MYORM_H
