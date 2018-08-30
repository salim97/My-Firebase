#ifndef RDV_H
#define RDV_H

#include <QObject>
#include "myorm.h"

// this is just an example
class RDV : public MyORM
{
public:
    // you need this macro to get thing work proply
    //use this macro, or replace it with your own constrecteur but you must put init(this); on it
    INIT_CURD(RDV) // add CURD methods( Create, Update, Read, Delete)

    AUTO_PROPERTY(QString, Date)
    AUTO_PROPERTY(QString, Title)
    AUTO_PROPERTY(int, Prix)
    AUTO_PROPERTY(QString, Other)

};

#endif // RDV_H
