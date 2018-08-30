#include "myorm.h"

#define PROJECT_ID "test-ccd18"

MyORM::MyORM(QObject *parent) : QObject(parent)
{
    m_firebase=new Firebase("https://"PROJECT_ID".firebaseio.com/", "users/jilali/");
    m_firebase->listenEvents();
    connect(m_firebase,SIGNAL(eventResponseReady(QString)),this,SLOT(onEventResponseReadyy(QString)));
    m_firebase->getValue();
}

void MyORM::init(QObject *obj)
{
    this->obj = obj ;
//    m_tableModel->setTable(obj->metaObject()->className());
//    m_tableModel->select();
//    m_databaseType = m_tableModel->database().driverName() ;
//    setCurrentRow(0);
    m_firebase->getValue();
}

void MyORM::update()
{
    m_firebase->getValue();
}

void MyORM::onEventResponseReadyy(QString data)
{
    qDebug()<<"void ActionHandler::onResponseReady(QString data)";
    qDebug()<< "data: " << data ;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QVariantMap eventMap = doc.toVariant().toMap();
    qDebug() << "dataSnapshot->getDataMap(): " << eventMap ;
    for(QVariantMap::const_iterator iter = eventMap.begin(); iter != eventMap.end(); ++iter) {
        qDebug() << iter.key() << iter.value();
        QVariant key, value ;
        key = iter.key();
        value = iter.value();
    }
}
