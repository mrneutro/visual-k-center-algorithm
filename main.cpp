#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QDebug>
#include <ctime>
#include <QQmlContext>

#include "resolver/ApproxResolver.h"
#include "ResolverFacade.h"
#include "model/Warehouse.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    ResolverFacade *approxFacade = new ResolverFacade();
    qmlRegisterType<ResolverFacade>();
    qmlRegisterType<Warehouse>();
    engine.rootContext()->setContextProperty("approxFacade", approxFacade);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
