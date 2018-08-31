#include "myfirebase.h"
#include <string.h>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include <QCryptographicHash>
#include <QtDebug>
#include <QBuffer>

MyFirebase::MyFirebase(const QString &hostName
                   , const QString &dbPath
                   , QObject *parent)
   : QObject(parent)
{
    host = forceEndChar(hostName.trimmed(), '/');
    host = host.append(dbPath.trimmed());
    init();
}

void MyFirebase::init()
{
    manager=new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*))
            ,this,SLOT(replyFinished(QNetworkReply*)));
}

void MyFirebase::listenEvents(const QString& queryString)
{
    open(buildPath(queryString));
}

void MyFirebase::open(const QUrl &url)
{
    QNetworkRequest request(url);
    request.setRawHeader("Accept", "text/event-stream");
    QNetworkReply *_reply = manager->get(request);
    connect(_reply, &QNetworkReply::readyRead, this, &MyFirebase::eventReadyRead);
    connect(_reply, &QNetworkReply::finished, this, &MyFirebase::eventFinished);
}

void MyFirebase::eventFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (reply)
    {
        QUrl redirectUrl = reply->attribute(
                    QNetworkRequest::RedirectionTargetAttribute).toUrl();
        if (!redirectUrl.isEmpty())
        {
            reply->deleteLater();
            open(redirectUrl);
            return;
        }
        reply->deleteLater();
    }
}

void MyFirebase::eventReadyRead()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if(reply)
    {
        QByteArray line=reply->readLine();
        if(!line.isEmpty())
        {
            QByteArray eventName=trimValue(line);
            line=reply->readAll();
            if(eventName=="put")
            {
                QString dataSnapshot(line);
                emit eventDataChanged(dataSnapshot);
            }
        }
    }
    reply->readAll();
}


void MyFirebase::setValue(QJsonObject jsonObj
                        , const QString &verb
                        , const QString& queryString)
{
    QJsonDocument jsonDoc(jsonObj);
    QString path = buildPath(queryString);
    QNetworkRequest request(path);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");
    QByteArray jsonBA = jsonDoc.toJson(QJsonDocument::Compact);

    QBuffer *buffer=new QBuffer();
    buffer->open((QBuffer::ReadWrite));
    buffer->write(jsonBA);
    buffer->seek(0);

    QByteArray verbBA = verb.toUtf8();
    manager->sendCustomRequest(request, verbBA ,buffer);
    buffer->close();
}

void MyFirebase::getValue(const QString& queryString)
{
    QNetworkRequest request(buildPath(queryString));
    manager->get(request);
}

void MyFirebase::replyFinished(QNetworkReply *reply)
{
    QByteArray readAll = reply->readAll();
    QJsonDocument itemDoc = QJsonDocument::fromJson(readAll);
    QJsonObject rootObject = itemDoc.object();QJsonObject json;
    emit eventResponseReady(readAll, rootObject);
}

QString MyFirebase::getPath(const QString &queryString)
{
    return buildPath(queryString);
}

QString MyFirebase::buildPath(const QString &queryString)
{
    QString destination=host;

    const int dotJsonLength = 5;
    if (destination.length() <= dotJsonLength
            || destination.right(dotJsonLength) != ".json")
        destination.append(".json");

    if (queryString.length() > 0)
            destination.append(forceStartChar(queryString,'?'));

    return destination;
}

QByteArray MyFirebase::trimValue(const QByteArray &line) const
{
    QByteArray value;
    int index = line.indexOf(':');
    if (index > 0)
        value = line.right(line.size() - index  - 1);
    return value.trimmed();
}

QString MyFirebase::forceEndChar(const QString &string, char endCh)
{
    if (string[string.length()-1] != endCh)
        return QString(string).append(endCh);
    return string;
}

QString MyFirebase::forceStartChar(const QString &string, char startCh)
{
    if (string.length() > 0 && string[0] != startCh)
        return QString(string).prepend(startCh);
    return string;
}

