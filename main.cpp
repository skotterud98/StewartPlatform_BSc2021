#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "thread.h"

int main(int argc, char *argv[])
{
    Thread* thread = new Thread;
    thread->start();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("oscillator_", thread->get_obj());


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
