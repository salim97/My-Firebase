#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "myfirebase.h"

//you can move this to extarnel file ( for example: config.ini ) to be able edit it later without recompile everything
#define PROJECT_ID "test-ccd18"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    MyFirebase myFirebase("https://"PROJECT_ID".firebaseio.com/", "users/jilali/") ;
    engine.rootContext()->setContextProperty("myFirebase", &myFirebase);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
