#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <ApproxResolver.h>
#include <QDebug>
#include <ctime>
#include <QQmlContext>

#include <ApproxFacade.h>
#include <Warehouse.h>
#define POWER 1000000
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    ApproxFacade *approxFacade = new ApproxFacade();
    qmlRegisterType<ApproxFacade>();
    qmlRegisterType<Warehouse>();
    engine.rootContext()->setContextProperty("approxFacade", approxFacade);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
