#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <ApproxResolver.h>
#include <QDebug>

int main(int argc, char *argv[])
{
//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

    City c1(12,123);
    City c2(323,3323);
    City c3(34,35);
    QList<City> lst;
    lst << c1 << c2 << c3;

    ApproxResolver apr(lst, 2);
    apr.resolve();
    qDebug() << apr.get_solution();

    return 0;
}
