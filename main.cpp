#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <ApproxResolver.h>
#include <QDebug>
#include <ctime>

#include <ApproxFacade.h>
#define POWER 1000000
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
//    std::srand(std::time(0));

//    QList<City> lst;
//    for(int i = 0; i < POWER; i++){
//        lst.append(City(std::rand() % POWER*10, std::rand() % POWER*10));
//    }



    ApproxFacade approxFacade();

    engine.rootContext()->setContextProperty("approxFacade", &approxFacade);
//    qDebug() << list;

//    qDebug() << "finish";
//    qDebug() << lst.at(999998).x() << " " << lst.at(999998).y();

    return app.exec();
}
